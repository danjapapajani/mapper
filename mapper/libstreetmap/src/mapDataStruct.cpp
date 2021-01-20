/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "StreetsDatabaseAPI.h"
#include "Feature.h"
#include <vector>
#include <unordered_map>
#include "OSMDatabaseAPI.h"
#include <map>
#include <algorithm>
#include <string>
#include <iostream>
#include "mapDataStruct.h"
#include "m1.h"
#include "graphics.h"
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry.hpp>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;


//PSA this was the declaration that the boost library said I should use
typedef bg::model::point<double, 2, bg::cs::cartesian> point;
typedef std::pair<point, unsigned> value;

extern double latAvg;

using namespace std;

/********************************************
 **************** CONSTRUCTOR ***************
 ********************************************/
mapDataStruct::mapDataStruct(){
    
    
    
    /********************************************
     ************** positionInter ***************
     ********************************************/
    for (unsigned i = 0; i < getNumberOfIntersections(); i++){
        
        positionInter.push_back(getIntersectionPosition(i));
    }
     
     
    /********************************************
     ************** segIDToInfo   ***************
     ********************************************/
    for(unsigned j = 0; j < getNumberOfStreetSegments(); j++){
        segIDToInfo.push_back(getStreetSegmentInfo(j));
        
    }
     
    /********************************************
     ************** streetNameToID **************
     ********************************************/
    for (unsigned int i = 0; i < getNumberOfStreets(); i++) {               

        //check if the street name with given index is at the end of list
        if (streetNameToIDs.find(getStreetName(i)) == streetNameToIDs.end())
            
            //insert the street name paired with a vector
            streetNameToIDs.insert({getStreetName(i), std::vector<unsigned>()});
        
        //fill the vector with it's ID
        streetNameToIDs[getStreetName(i)].push_back(i);


    }
    
    /********************************************
     ************** interIDToSegIDs *************
     ********************************************/
    for (unsigned i = 0; i < getNumberOfIntersections(); i++){
        vector<unsigned> segmentIDs;
        //fill in vector of segment IDs for the i'th intersection
        for (unsigned j = 0; j < getIntersectionStreetSegmentCount(i); j++){
            segmentIDs.push_back(getIntersectionStreetSegment(i,j));
        }
        interIDToSegIDs.push_back(segmentIDs);
    }
    
    
    /********************************************
     ************* streetIDToSegInfo ************
     ********************************************/
    streetIDSegInfo.resize(getNumberOfStreets());
    for(unsigned i = 0; i < getNumberOfStreetSegments(); i++){
        
        streetIDSegInfo[getStreetSegmentInfo(i).streetID].push_back(i);
    }

    //filling in my hash with via using streetIDSegInfo vector
    for( unsigned i = 0; i < getNumberOfStreets(); i++){
        
        //create some temp vectors to store segment info
        vector<unsigned> tempSegVector;
        vector<unsigned> interIDs;
        
        //store vector with segment info of the street ID
        tempSegVector = streetIDSegInfo[i];
        
        //search through the hash from beginning to end
        for(auto iter = tempSegVector.begin(); iter != tempSegVector.end(); iter++){
            
            //create a struct that contains the information at that current iteration
            StreetSegmentInfo currentSeg = getStreetSegmentInfo(*iter);
            
            //store the info of the intersection IDs given that segment 
            interIDs.push_back(currentSeg.from);
            interIDs.push_back(currentSeg.to);
        }
        
        //check to see if any IDs occur twice
        sort(interIDs.begin(), interIDs.end());
        
        //erase them if they exist
        interIDs.erase(unique(interIDs.begin(), interIDs.end()), interIDs.end());
        
        //create hash where key is streetID and 
        streetIDToInterIDs.insert(make_pair(i, interIDs));
    }
    
    /********************************************
     **************** travelTime ****************
     ********************************************/
    travelTime.resize(getNumberOfStreetSegments());
    for(unsigned i = 0; i < getNumberOfStreetSegments(); i++){
        
         travelTime[i] = (((find_street_segment_length(i))/1000.0)/ 
                 (getStreetSegmentInfo(i).speedLimit) * 60) * 60;
         
    }
    
    /********************************************
     ******************* POITree ****************
     ********************************************/
    for(unsigned int i = 0; i < getNumberOfPointsOfInterest(); i++){

        point b = point(getPointOfInterestPosition(i).lat(), getPointOfInterestPosition(i).lon());
        POITree.insert(make_pair(b,i));

    }

    
    for(unsigned int i = 0; i < getNumberOfIntersections(); i++){

        point a = point(getIntersectionPosition(i).lat(), getIntersectionPosition(i).lon());
        interTree.insert(make_pair(a, i));


    }
        
    /********************************************
    ************** xyCoordSegment ***************
    ********************************************/
    for(unsigned i = 0; i < getNumberOfStreetSegments(); i++){

        StreetSegmentInfo currentSeg;
        std::vector<t_point> xyCoords;

        currentSeg = segIDToInfo[i];
        unsigned amountOfCurves = currentSeg.curvePointCount;
        if(amountOfCurves > 0){

            for(unsigned j = 0; j < amountOfCurves; j++){

                LatLon tempCoord = getStreetSegmentCurvePoint(i, j);
                t_point newCoord;

                newCoord.x = tempCoord.lon() * DEG_TO_RAD * cos(latAvg);
                newCoord.y = tempCoord.lat() * DEG_TO_RAD;

                xyCoords.push_back(newCoord);
            }
        }

        xyCoordSegment.push_back(xyCoords);

    }

    /********************************************
     ********** pointToOSMEntity/Tag ************
     ********************************************/
    for(unsigned i = 0; i < getNumberOfWays(); i++){

        const OSMWay* current = getWayByIndex(i);
        std::unordered_map<std::string, std::string> listOfTags;


        for(unsigned j = 0; j < getTagCount(current); j++){
            listOfTags.insert(getTagPair(current, j));
        }
        pointToEntityTag.insert(make_pair(current, listOfTags));

        OSMID currentID = current->id();

        pointToOSMEntity.insert(make_pair(currentID, current));
               
    }
        
        
     /********************************************
     ********** pointToOSMEntity/Tag ************
     ********************************************/
    for(unsigned i = 0; i < getNumberOfRelations(); i++){

        const OSMRelation* current = getRelationByIndex(i);
        std::unordered_map<std::string, std::string> listOfTags;

        for(unsigned j = 0; j < getTagCount(current); j++)
            listOfTags.insert(getTagPair(current, j));

        pointToEntityTag.insert(make_pair(current, listOfTags));

        OSMID currentID = current->id();
        pointToOSMEntity.insert(make_pair(currentID, current));

    }
        
    //organize major, minor, and highways
    for(unsigned i = 0; i < getNumberOfStreetSegments(); i++){

        StreetSegmentInfo currentSeg = segIDToInfo[i];
        OSMID currentID = currentSeg.wayOSMID;
        const OSMEntity* currentWay = pointToOSMEntity.find(currentID)->second;

        std::unordered_map<std::string, std::string> tags;
        tags = pointToEntityTag.find(currentWay)->second;
        auto iter = tags.find("highway");
        if(iter != tags.end()){
            if(iter->second == "motorway")
                highways.push_back(i);
            else if( iter->second == "trunk" || iter->second == "primary" || iter->second == "secondary"
                    || iter->second == "tertiary" || iter->second == "trunk_link" || 
                    iter->second == "primary_link" || iter->second == "secondary_link" ||
                    iter->second == "tertiary_link" || iter->second == "motorway_link"){
                majorRoads.push_back(i);
            } 
            else
                minorRoads.push_back(i);
        }
    }
        
    /********************************************
    ************* POINameToIDs ******************
    ********************************************/
    for(unsigned i = 0; i < getNumberOfPointsOfInterest(); i++){

        //check if the POI name with given index is at the end of list
        if(POINameToIDs.find(getPointOfInterestName(i)) == POINameToIDs.end()){

            //insert POI name paired with a vector of its IDs
            POINameToIDs.insert({getPointOfInterestName(i), std::vector<unsigned int>()});

        }
        //fill the vector with its IDs
        POINameToIDs[getPointOfInterestName(i)].push_back(i);

    }
   
}
    

       



/********************************************
 ************* findClosestPOI ***************
 ********************************************/
unsigned int mapDataStruct::findClosestPOI(LatLon position){
    
    point first = point(position.lat(), position.lon());
    
    //vector to store results of nearest neighbours
    std::vector<value> finalPOI;
    unsigned finalValue= 0;
    double distance = EARTH_RADIUS_IN_METERS;

    //K nearest neighbour search
    //put 50 closest neighbours in the "nearest neighbours vector"
    POITree.query(bgi::nearest(first,50), std::back_inserter(finalPOI));
    
    //now loop through these close points to fine the CLOSEST ONE
    for(unsigned i = 0; i < finalPOI.size(); i++){
        
        /*
         * create temporary LatLon point to compare the current one to
         * 
         * at the ith iteration, take the first part of the pair (implies LatLon
         * values)
         * 
         * get the 0th element of that part of the pair (Lat)
         * 
         * get the 1st element of that part of the pair (Lon)
         */
        
        LatLon temp = LatLon(finalPOI[i].first.get<0>(), finalPOI[i].first.get<1>());
        if(find_distance_between_two_points(temp, position) < distance){
            distance = find_distance_between_two_points(temp, position);
            finalValue = finalPOI[i].second;
        }
    
    }
    
    return finalValue;
}

/********************************************
 ************* findClosestInter *************
 ********************************************/
unsigned int mapDataStruct::findClosestInter(LatLon position){
    
    point second = point(position.lat(), position.lon());
    
    //vector to store results of nearest neighbours
    std::vector<value> finalInter;
    unsigned intersectionID = 0;
    double distance = EARTH_RADIUS_IN_METERS;
    
    
    //K nearest neighbour search
    //put 50 closest neighbouts in the "nearest neighbours vector"
    interTree.query(bgi::nearest(second,50), std::back_inserter(finalInter));
    
    for(unsigned i = 0; i < finalInter.size(); i++){
        /*
         * create temporary LatLon point to compare the current one to
         * 
         * at the ith iteration, take the first part of the pair (implies LatLon
         * values)
         * 
         * get the 0th element of that part of the pair (Lat)
         * 
         * get the 1st element of that part of the pair (Lon)
         */
        LatLon temp2 = LatLon(finalInter[i].first.get<0>(), finalInter[i].first.get<1>());
        if(find_distance_between_two_points(temp2, position) < distance){
            distance = find_distance_between_two_points(temp2, position);
            intersectionID = finalInter[i].second;
        }
    }
    

    return intersectionID;
}

/********************************************
 ************* clearMapDataStruct ***********
 ********************************************/
void mapDataStruct::clearMapDataStruct(){
    
    //clear unordered_map
    POITree.clear();
    interTree.clear();
    streetIDToInterIDs.clear();
    streetNameToIDs.clear();
    streetIDSegInfo.clear();
    interIDToSegIDs.clear();
    travelTime.clear();
   
}
