/* 
 * Copyright 2018 University of Toronto
 *
 * Permission is hereby granted, to use this software and associated 
 * documentation files (the "Software") in course work at the University 
 * of Toronto, or for personal use. Other uses are prohibited, in 
 * particular the distribution of the Software either publicly or to third 
 * parties.
 *
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#include "m1.h"
#include "m2.h"
#include "StreetsDatabaseAPI.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include "mapDataStruct.h"
#include <math.h>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry.hpp>
#include <time.h>
#include <queue>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;


//PSA this was the declaration that the boost library said I should use
typedef bg::model::point<double, 2, bg::cs::cartesian> point;
typedef std::pair<point, unsigned> value;

mapDataStruct* mapDataObject;
extern vector<string> newMap;
extern int newMapName;

//vector of adjacent intersections for a given intersection
std::vector<vector<unsigned>> interIDToAdjacent;



/********************************************
 **************** LOAD_MAP ******************
 ********************************************/
bool load_map(std::string map_path) {  
    //important suffixes appended to map path name
    std::string street = ".streets.bin";
    std::string osm = ".osm.bin";
    
    //parse the map path for .streets.bin to delete and then append
    //what's needed for loading database information
    std::string::size_type indexOfDot = map_path.find(street);
    
    //erase .streets.bin from string
    if(indexOfDot != std::string::npos){
        map_path.erase(indexOfDot, street.length());
    }
  
    
    loadOSMDatabaseBIN(map_path + osm);
        
        
   //Indicates whether the map has loaded successfully
   bool load_successful = loadStreetsDatabaseBIN(map_path + street);   
   
    if (load_successful){  
  
        //create new instance of an object
         mapDataObject = new mapDataStruct;
       
    
         //fill interIDToAdjacent
        for(unsigned i = 0; i < getNumberOfIntersections(); i++){
            std::vector<unsigned> adjacentInter = find_adjacent_intersections(i);
            
            interIDToAdjacent.push_back(adjacentInter);
        }
         
         
    }
    return load_successful;
}

/********************************************
 **************** CLOSE_MAP *****************
 ********************************************/
void close_map() {
    
    //Clean-up your map related data structures here
   
    mapDataObject->clearMapDataStruct();
    delete mapDataObject;
    mapDataObject = NULL;
    interIDToAdjacent.clear();
    closeStreetDatabase();
    closeOSMDatabase();
    
}

/********************************************
 ******* FIND_STREET_IDS_FROM_NAME **********
 ********************************************/
std::vector<unsigned> find_street_ids_from_name(std::string street_name) { 
    
    return (mapDataObject->streetNameToIDs[street_name]);
   
}

/********************************************
 **** FIND_INTERSECTION_STREET_SEGMENTS *****
 ********************************************/
std::vector<unsigned> find_intersection_street_segments(unsigned intersection_id){
   
    return (mapDataObject->interIDToSegIDs[intersection_id]);
    
}

/********************************************
 ***** FIND_INTERSECTION_STREET_NAMES *******
 ********************************************/
std::vector<std::string> find_intersection_street_names(unsigned intersection_id){

    //get the IDs for the segments connected to that street
    std::vector<unsigned> segments = mapDataObject->interIDToSegIDs[intersection_id];
    std::vector<std::string> streetNames;
   
    //look at each segment ID and get the name of the street to which it corresponds, and add it to the vector
    for (unsigned i = 0; i < segments.size(); i++){
        //for each segment connected to the intersection, get the streetID and the street name from that
        //insert into the list of street names
        streetNames.push_back(getStreetName(getStreetSegmentInfo(segments[i]).streetID));
    }
    
    return(streetNames);
    
}

/********************************************
 ********* ARE_DIRECTLY_CONNECTED ***********
 ********************************************/
bool are_directly_connected(unsigned intersection_id1, unsigned intersection_id2){
    
    unsigned numSegs1 = getIntersectionStreetSegmentCount(intersection_id1);
    unsigned numSegs2 = getIntersectionStreetSegmentCount(intersection_id2);
    
    if (intersection_id1 == intersection_id2){
        //an intersection is connected to itself
        return (true);
    }
    
    //look at all the segmentIDs for each intersection and check if there are any in common 
    else {
        for (unsigned i = 0; i < numSegs1; i++){
            for (unsigned j = 0; j < numSegs2; j++){
                if (getIntersectionStreetSegment(intersection_id1,i) == getIntersectionStreetSegment(intersection_id2,j)){
                    return (true);
                }
            }
        }
    }
    
    return (false);
   
}
/********************************************
 ****** FIND_ADJACENT_INTERSECTIONS *********
 ********************************************/

std::vector<unsigned> find_adjacent_intersections(unsigned intersection_id){
    
    //get the segments that connect to that intersection
    std::vector<unsigned> streetSegs = mapDataObject->interIDToSegIDs[intersection_id];
    
    std::vector<unsigned> adjacentInts;
    
    //look at the intersections that connect to that segment 
    for (unsigned i = 0; i < streetSegs.size(); i++){
        //get relevant information about the street segment being looked at
        unsigned fromIntersection = getStreetSegmentInfo(streetSegs[i]).from;
        unsigned toIntersection = getStreetSegmentInfo(streetSegs[i]).to;
        bool isOneWay = getStreetSegmentInfo(streetSegs[i]).oneWay;
        
        //add to list only if one way in the correct way 
        if ((isOneWay == true) && (fromIntersection == intersection_id)){
            adjacentInts.push_back(toIntersection);
        }
        
        //not a one way street
        else if (isOneWay == false) {
            //add the intersection that was NOT passed in
            if (intersection_id != fromIntersection){
                adjacentInts.push_back(fromIntersection);
            
            }
            else if (intersection_id != toIntersection){
               adjacentInts.push_back(toIntersection);
 
               
            }
        }
    }
    
    //remove duplicate intersections
    std::sort(adjacentInts.begin(),adjacentInts.end());
    auto new_adjacentInts=unique(adjacentInts.begin(), adjacentInts.end());
    adjacentInts.erase(new_adjacentInts, adjacentInts.end());
   
   
   return (adjacentInts);
    
}

/********************************************
 ******* FIND_STREET_STREET_SEGMENTS ********
 ********************************************/ 
std::vector<unsigned> find_street_street_segments(unsigned street_id){
    
    return (mapDataObject->streetIDSegInfo[street_id]);
    
}

/********************************************
 ****** FIND_ALL_STREET_INTERSECTIONS *******
 ********************************************/

std::vector<unsigned> find_all_street_intersections(unsigned street_id){
    
    return (mapDataObject->streetIDToInterIDs[street_id]);
    
}

/********************************************
 * FIND_INTERSECTION_IDS_FROM_STREET_NAMES **
 ********************************************/
std::vector<unsigned> find_intersection_ids_from_street_names(std::string street_name1, std::string street_name2){
  
    //vectors hold street IDs from the two given streets
    std::vector<unsigned> streetName1 = find_street_ids_from_name(street_name1);
    std::vector<unsigned> streetName2 = find_street_ids_from_name(street_name2);
    
    //vector holds intersection IDs between two given streets
    std::vector<unsigned> finalInterIDs;
    
    //vectors hold intersection IDs from the two given streets
    std::vector<unsigned> streetName1IDInterIDs;
    std::vector<unsigned> streetName2IDInterIDs;
   
    /*
     * fill temporary vectors with street IDs given a name, loop through each one
     * to fill vector of intersection IDs given the street
     * 
     * loop through the sizes of intersection vectors and store the value of
     * the intersection ID at i when it equals the same value of the other 
     * intersection ID
     *
     */
    for(auto i = streetName1.begin(); i != streetName1.end(); i++){
        
        std::vector<unsigned> tempInterStreet1 = find_all_street_intersections(*i);
        streetName1IDInterIDs.insert(streetName1IDInterIDs.end(), tempInterStreet1.begin(), tempInterStreet1.end());
        tempInterStreet1.clear();
            
    }
        
     for(auto i = streetName2.begin(); i != streetName2.end(); i++){
        
        std::vector<unsigned> tempInterStreet2 = find_all_street_intersections(*i);
        streetName2IDInterIDs.insert(streetName2IDInterIDs.end(), tempInterStreet2.begin(), tempInterStreet2.end());
        tempInterStreet2.clear();
            
     }
    
    for(unsigned i = 0; i < streetName1IDInterIDs.size(); i++){
        for(unsigned j = 0; j <streetName2IDInterIDs.size(); j++){
            if(streetName1IDInterIDs.at(i) == streetName2IDInterIDs.at(j))
                finalInterIDs.push_back(streetName1IDInterIDs.at(i));
        }
    }
    
    return finalInterIDs;

}
    

    

/********************************************
 ***** FIND_DISTANCE_BETWEEN_TWO_POINTS *****
 ********************************************/
double find_distance_between_two_points(LatLon point1, LatLon point2){
    
    
    //get latitude & longitude (from LatLon object) for each point & convert
    double lat1 =  point1.lat() * DEG_TO_RAD;
    double lon1 = point1.lon() * DEG_TO_RAD;
   
    double lat2 = point2.lat() * DEG_TO_RAD;
    double lon2 = point2.lon() * DEG_TO_RAD;
    
    double middleLat = (lat1 + lat2)/2;
    
    //calculate x and y position for first point
    double xPosition1 = lon1*cos(middleLat);
    double yPosition1 = lat1;
    
    //calculate x and y position for second point
    double xPosition2 = lon2*cos(middleLat);
    double yPosition2 = lat2;
    
    //calculate distance based on given formula
    double distance = EARTH_RADIUS_IN_METERS * sqrt((yPosition2 - yPosition1)*(yPosition2 - yPosition1) +
    (xPosition2 - xPosition1)*(xPosition2 - xPosition1));
    
    return (distance);
     
    
}

/********************************************
 ******* FIND_STREET_SEGMENT_LENGTH *********
 ********************************************/
double find_street_segment_length(unsigned street_segment_id){
    
    /*
     * calculate beginning of street segment to the curve point then add it 
     * to the length of the curve point to the end of the segment
     */
    
    StreetSegmentInfo newStreet = getStreetSegmentInfo(street_segment_id);
    double returnLength = 0;
    unsigned indexFrom = newStreet.from;
    unsigned indexTo = newStreet.to;
    unsigned curvyPart = newStreet.curvePointCount;
    
    //I found this function in the API and I cried bc I was so happy
    LatLon inter1 = getIntersectionPosition(indexFrom);
    LatLon inter2 = getIntersectionPosition(indexTo);
    
    //if its a straight line then return regular distance 
    if (curvyPart == 0)
        returnLength = find_distance_between_two_points(inter1, inter2);
    else {
        
        LatLon tempPoint1 = inter1;
        
        //count through the curve segments and add them up
        for(unsigned i = 0; i < curvyPart; i++){
            
            LatLon tempPoint2 = getStreetSegmentCurvePoint(street_segment_id, i);
            double lengthOfCurve = find_distance_between_two_points(tempPoint1, tempPoint2);
            returnLength+= lengthOfCurve; 
            tempPoint1 = tempPoint2;
        }
        
        //its lit add the lengths between the last point and the intersection!
        returnLength+= find_distance_between_two_points(tempPoint1, inter2);
    }
    
    return (returnLength);
    
}

/********************************************
 ********** FIND_STREET_LENGTH **************
 ********************************************/
double find_street_length(unsigned street_id){
    
    std::vector<unsigned> segmentInfo = find_street_street_segments(street_id);
    double lengthOfStreet = 0;
    
    //just add the segment lengths! nice
    /*
     * there are literally five different ways to iterate through a vector and 
     * its a little off putting to me
     */
    for(auto iter = segmentInfo.begin(); iter != segmentInfo.end(); iter++){
        
        lengthOfStreet+= find_street_segment_length(*iter);
        
    }
    
    return (lengthOfStreet);
  
}

/********************************************
 ***** FIND_STREET_SEGMENT_TRAVEL_TIME ******
 ********************************************/

double find_street_segment_travel_time(unsigned street_segment_id){
    
   return (mapDataObject->travelTime[street_segment_id]);
    
}

/********************************************
 ***** FIND_CLOSEST_POINT_OF_INTEREST *******
 ********************************************/
unsigned find_closest_point_of_interest(LatLon my_position){
  
    return mapDataObject->findClosestPOI(my_position);
    
}

/********************************************
 ******* FIND_CLOSEST_INTERSECTION **********
 ********************************************/
//Returns the the nearest intersection to the given position
unsigned find_closest_intersection(LatLon my_position){
  
    return mapDataObject->findClosestInter(my_position);
    
}

