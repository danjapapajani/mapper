#include <vector>
#include <string>
#include "m1.h"
#include "m2.h"
#include "m3.h"
#include <limits>
#include <list>
#include <queue>
#include "StreetsDatabaseAPI.h"
#include "mapDataStruct.h"
#include "LatLon.h"
#include <algorithm>
#include <unordered_set>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry.hpp>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

typedef bg::model::point<double, 2, bg::cs::cartesian> point;
typedef std::pair<point, unsigned> value;

//closest intersection to the POI found in find_path_to_point_of_interest
unsigned closestIntersect;

extern mapDataStruct* mapDataObject;
extern std::vector<vector<unsigned>> interIDToAdjacent;

/********************************************
 ******** COMPUTE_PATH_TRAVEL_TIME **********
 ********************************************/

double compute_path_travel_time(const std::vector<unsigned>& path, const double turn_penalty){
    
    double travelTime = 0; 
    StreetSegmentInfo currentSegInfo;
    StreetSegmentInfo prevSegInfo;
    
    //if there's no path, it requires no time
    if (path.size() == 0){
        return 0; 
    } 
    
    for (unsigned int i = 0; i < path.size(); i++){
        
        //add up travel time for each segment
        travelTime = travelTime + mapDataObject->travelTime[path[i]];
        
        //stops from adding a turn penalty at the beginning 
        if (i != 0){
            //check for changing street ids for adding a turn penalty 
            currentSegInfo = getStreetSegmentInfo(path[i]); 
            prevSegInfo = getStreetSegmentInfo(path[i-1]);
            
            //street changes i.e. there was a turn and a turn penalty must be added
            if (currentSegInfo.streetID != prevSegInfo.streetID){
                travelTime = travelTime + turn_penalty;
            }
        }
        
    }
    
    return (travelTime);
    
}



/********************************************
 ****** FIND_PATH_BETWEEN_INTERSECTIONS *****
 ********************************************/
std::vector<unsigned> find_path_between_intersections(const unsigned intersect_id_start,
const unsigned intersect_id_end,
const double turn_penalty) {
    
    //create priority queue that stores minimum at top (must create own std::greater function)
    std::priority_queue <node, vector<node>, greaterThanNode> interQ; 
    
    //create start node
    node startNode(intersect_id_start,0);
    
    interQ.push(startNode);
    
    //variable for infinity
    double inf = std::numeric_limits<double>::infinity();
    
    //when a new node is evaluated, it's intersection ID is added to this so 
    //the path can be backtracked
    std::vector<unsigned int> cameFrom;
    cameFrom.resize(getNumberOfIntersections());

    //default value of infinity
    std::vector<double> cost(getNumberOfIntersections(), inf);
    
    //vector that contains total cost to get from source node to goal node by
    //passing that node
    
    //cost of going from start to start is 0
    cost[intersect_id_start] = 0;
    
    //vector of segment IDs with an index of intersection
    std::vector<unsigned> segmentPath;
    segmentPath.resize(getNumberOfIntersections());
    
    
    while(!interQ.empty()){
        
        node currentNode = interQ.top();
        
        unsigned int currentInterID = currentNode.targetIntersection;
       
        //if the current node is infinite we don't have to search
        if(currentNode.travelTime == inf)
                continue;
        
        if(currentInterID == intersect_id_end){

            return reconstructPath(intersect_id_start, currentInterID, cameFrom, segmentPath);
        }
        
        interQ.pop();
        
        std::vector<unsigned> interNeighbours = interIDToAdjacent[currentInterID];
        for(unsigned i = 0; i < interNeighbours.size(); i++){
            
            unsigned currentNeighbour = interNeighbours[i];
            
            //find street segments that are shared between the current intersection
            //ID and the neighbour intersection ID
            std::vector<unsigned> sharedSegments = findSharedStreetSegments(currentInterID, currentNeighbour);
            
            //now we find the street segment that is the fastest/ has the least weight
            //default fastest segment
            unsigned fastestSegmentID = 0;
            double minSpeed = inf;
            
            
           
                    for(unsigned j = 0; j < sharedSegments.size(); j++){

                        unsigned currentSeg = sharedSegments[j];
                        double currentTime = mapDataObject->travelTime[currentSeg];
                        
                        //check turn penalaty for segment and add it to its current time
                        if(currentInterID != intersect_id_start){
                             
                            unsigned prevSegment = segmentPath[currentInterID];
                
                            unsigned prevStreetID = mapDataObject->segIDToInfo[prevSegment].streetID;
                            unsigned currentStreetID = mapDataObject->segIDToInfo[currentSeg].streetID;

                            if(currentStreetID != prevStreetID){

                                currentTime = currentTime + turn_penalty;
                                
                            }
                        }
                        

                        StreetSegmentInfo currentSegInfo = mapDataObject->segIDToInfo[currentSeg];
                        
                        //update fastests speed and segment accordngly 
                        if(currentTime < minSpeed){

                            if(currentSegInfo.from == currentInterID || !currentSegInfo.oneWay){

                                minSpeed = currentTime;
                                fastestSegmentID = currentSeg;
                                
                            }
                        }
                    }
                    
                
            
            //the tentative cost between current node and the neighbouring node
            double currentCost= cost[currentInterID] + mapDataObject->travelTime[fastestSegmentID];
            
            //now we check for turn penalty 
            if (currentInterID != intersect_id_start){
                
                //find shared street segments between current ID and previous intersection
                unsigned prevSegment = segmentPath[currentInterID];
                
             
                /*
                 * find the fastests segID corresponding street ID
                 * if the previous fastest segID's streetID does not match to 
                 * the current fastest segID's streetID then add a turn penalty
                 * to the current tentative cost
                 */
                unsigned prevStreetID = mapDataObject->segIDToInfo[prevSegment].streetID;
                unsigned currentStreetID = mapDataObject->segIDToInfo[fastestSegmentID].streetID;
                
                if(currentStreetID != prevStreetID){
                    
                    currentCost = currentCost + turn_penalty;
                }
                
            }
           
            if(currentCost >= cost[currentNeighbour])
                continue;
            else {
                
                cost[currentNeighbour] = currentCost;
                
                 //add node and its altCost to our queue
                interQ.push(node(currentNeighbour, cost[currentNeighbour]));
                cameFrom[currentNeighbour] = currentInterID;
                segmentPath[currentNeighbour] = fastestSegmentID;
                
            }
        }
    }
    
    //return an empty vector
    return {}; 
}



/********************************************
 ************ RECONSTRUCTPATH ***************
 ********************************************/
std::vector<unsigned> reconstructPath(unsigned interStart, unsigned curInterID, 
        std::vector<unsigned> cameFromVector, std::vector<unsigned> segIDs){
    
    //vector of final path via street segments
    std::vector<unsigned> finalPath;
    
    //bool to see if we've reached end of cameFromVector
    bool endOfPath = 0;
    
    
    /*
     * create vector that contains final reconstructed path 
     * add the current ID that we are checking (i.e. goal node)
     * to the back of this vector (push_back increases performance)
     */
    unsigned goalNode = curInterID;
    
    std::vector<unsigned> totalPath;
    totalPath.push_back(curInterID);
    
    //follow previous intersections until the current intersection is the same
    //value as the start intersection
    while(cameFromVector[curInterID] != interStart){
        
        curInterID = cameFromVector[curInterID];
        totalPath.push_back(curInterID);
    }
    
    totalPath.push_back(interStart);
    
    /*
     * now we must reconstruct path via segmentIDs
     * must use the totalPath vector and the goalNode
     */
   
    //reverse intersection IDs
    if(totalPath.size()-1 > 0)
        reverse(totalPath.begin(), totalPath.end());
    
    for(unsigned i = 1; i < totalPath.size(); i++){
        
        
        if(endOfPath == 1){
            return finalPath;
        }
        
        
        unsigned intersectionID = totalPath[i];
        unsigned insertSegmentID = segIDs[intersectionID];
       
        finalPath.push_back(insertSegmentID);
    
        
        if(totalPath[i] == goalNode)
            endOfPath = 1;
        }
 
    return finalPath;
}



/********************************************
 ***** FIND_PATH_TO_POINT_OF_INTERSEST ******
 ********************************************/
std::vector<unsigned> find_path_to_point_of_interest(const unsigned intersect_id_start,
const std::string point_of_interest_name,
const double turn_penalty){

    //rtree containing value of closest intersections
    bgi::rtree<value, bgi::quadratic<16>> closestInterTree;

    LatLon startPosition = getIntersectionPosition(intersect_id_start);
    
    //variable for infinity
    double inf = std::numeric_limits<double>::infinity();

    //vector with POI IDs for given name
    std::vector<unsigned int> POIIDs = mapDataObject->POINameToIDs[point_of_interest_name];
    
    //vector with closest intersections
    std::vector<unsigned int> closestInterPOI;
    
    double curTime;
    
    double minSpeedPOI = inf;
    //unsigned closestIntersect;
    
    if(POIIDs.size() == 0){
        return POIIDs;
    }
        
        //find closest intersection for each POI of given name
        for(unsigned i = 0; i < POIIDs.size(); i++){
            
            LatLon positionPOI = getPointOfInterestPosition(POIIDs[i]);
            unsigned closestInter = mapDataObject->findClosestInter(positionPOI);
            closestInterPOI.push_back(closestInter);
    
        }
    
     //fill my closest intersection tree
    for(unsigned int i = 0; i < closestInterPOI.size(); i++){
                
        unsigned intersectPos = closestInterPOI[i];
        point b = point(getIntersectionPosition(intersectPos).lat(), getIntersectionPosition(intersectPos).lon());
        closestInterTree.insert(make_pair(b,intersectPos));
                
    }
    
        point first = point(startPosition.lat(), startPosition.lon());

        //vector to store results of nearest neighbours
        std::vector<value> finalPOI;

        //K nearest neighbour search
        //put 6 closest neighbours in the "nearest neighbours vector"
        closestInterTree.query(bgi::nearest(first,6), std::back_inserter(finalPOI));
           
    
    for(unsigned i = 0; i < finalPOI.size(); i++){
        
        unsigned indexInter = finalPOI[i].second;
        std::vector<unsigned> shortestPath;
        
        //find optimal path with given intersection
        shortestPath = find_path_between_intersections(intersect_id_start, indexInter,
                turn_penalty);
        
        //compare path travel times and update fastest path accordingly
        if(shortestPath.size() == 0){
            
            curTime = inf;
        }
        else {

        curTime = compute_path_travel_time(shortestPath, turn_penalty);
        
        if(curTime < minSpeedPOI){
            
            minSpeedPOI = curTime;
            closestIntersect = indexInter;
        }
        
    }
    }
        
    std::vector<unsigned> finalPath = find_path_between_intersections(intersect_id_start, 
            closestIntersect, turn_penalty);
    
    return finalPath;
}


/********************************************
 ******* FINDSHAREDSTREETSEGMENTS ***********
 ********************************************/
std::vector<unsigned> findSharedStreetSegments(unsigned interOne, unsigned interTwo){
    
    std::vector<unsigned> currentStreetSegs;
    std::vector<unsigned> neighbourStreetSegs;
    
    //final segments that are going the right way
    std::vector<unsigned> finalShared;
    
    currentStreetSegs = mapDataObject->interIDToSegIDs[interOne];
    neighbourStreetSegs = mapDataObject->interIDToSegIDs[interTwo];
            
    //sort these vectors
    std::sort(currentStreetSegs.begin(), currentStreetSegs.end());
    std::sort(neighbourStreetSegs.begin(), neighbourStreetSegs.end());
            
    //new vector to store shared vectors
    std::vector<unsigned> sharedSegments;
            
    //find common elements in vector and store into shared vector
    std::set_intersection(currentStreetSegs.begin(), currentStreetSegs.end(),
            neighbourStreetSegs.begin(), neighbourStreetSegs.end(), 
            std::back_inserter(sharedSegments));
    
    //iterarte through shared segments and only return segments that are
    //going in the right direction
   
    return sharedSegments;
            
}


/********************************************
 ************** HIGHLIGHTPATH ***************
 ********************************************/

void highlightPath(unsigned ID) {
    
    StreetSegmentInfo currentSeg = mapDataObject->segIDToInfo[ID];

    if(ID == 133847){

         setcolor(BLUE);
        setlinewidth(4);
    } else {

         setcolor(RED);
        setlinewidth(4);
    }

    //get beginning and end of intersectionIDs for given segment
    unsigned int begin = currentSeg.from;
    unsigned int end = currentSeg.to;

    //get number of curved points for the segment
    unsigned curvyCount = mapDataObject->segIDToInfo[ID].curvePointCount;

    //get inter position in latlon coordinates
    LatLon pointFrom = mapDataObject->positionInter[begin];
    LatLon pointTo = mapDataObject->positionInter[end];

    t_point from = latLonToXY(pointFrom);
    t_point to = latLonToXY(pointTo);


    //vector of LatLon for curved points
    std::vector<LatLon> curvedPoints;
    curvedPoints.push_back(pointFrom);

    LatLon tempCurvePoints;

    if(curvyCount == 0){

        t_point fromOne = latLonToXY(pointFrom);
        t_point toOne = latLonToXY(pointTo);
        //draw straight line
        drawline(fromOne, toOne);

    }

    else {
        for(unsigned i = 0; i < curvyCount; i++){

            tempCurvePoints = getStreetSegmentCurvePoint(ID, i);
            curvedPoints.push_back(tempCurvePoints);  

        }

        curvedPoints.push_back(pointTo);

        for(unsigned i = 0; i < curvedPoints.size() - 1; i++){

            from = latLonToXY(curvedPoints[i]);
            to = latLonToXY(curvedPoints[i + 1]);

            drawline(from, to);
        }


    }
    curvedPoints.clear();

        
    
}



/********************************************
 ************** GETDIRECTIONS ***************
 ********************************************/

std::vector<std::string> getDirections (std::vector<unsigned> path){
    
    std::vector<std::string> directions;
    t_point currentSpot, nextSpot, futureSpot;
    
    //if the path is empty implies no destination
    if(path.size() == 0){
        directions.push_back("No destination");
        directions.erase(std::unique(directions.begin(), directions.end()), directions.end());
    
        return directions;
    }
    
    //if path is on element implies travelling on one street
    else if(path.size() == 1){
        
        std::string startName = getStreetName(mapDataObject->segIDToInfo[path[0]].streetID);
        directions.push_back("Head straight on " + startName + " until destination");
        
        directions.erase(std::unique(directions.begin(), directions.end()), directions.end());
    
        return directions;
    }else {
        
        

        for(unsigned i = 1; i < path.size(); i++){
            
            //find name of street on current segment
            unsigned currentSeg = path[i];
            StreetSegmentInfo curSegInfo = mapDataObject->segIDToInfo[currentSeg];
            unsigned curStreetID = curSegInfo.streetID; 
            std::string curName = getStreetName(curStreetID);
            
            //find name of street on next segment
            StreetSegmentInfo nextSegInfo = mapDataObject->segIDToInfo[currentSeg + 1];
            unsigned nextStreetID = nextSegInfo.streetID; 
            std::string nextName = getStreetName(nextStreetID);
            
            //convert intersection positions to cartesian in order to apply
            //cross product
            currentSpot = latLonToXY(getIntersectionPosition(curSegInfo.from));
            nextSpot = latLonToXY(getIntersectionPosition(curSegInfo.to));
            futureSpot = latLonToXY(getIntersectionPosition(nextSegInfo.from));
            
            //return cross product to determine direction
            double side = crossProduct(currentSpot, nextSpot, futureSpot);
            
            //check if street changes
            if(curName != nextName){
                
                //if cross product is negative turn left
                if(side < 0)
                    directions.push_back("Turn left onto " + curName);
                
                //if cross product is positive turn right
                else if(side > 0)
                    directions.push_back("Turn right onto " + curName);
                
            }
        }
        
        directions.push_back("You have reached your destination");
        
    }
    
    //remove any duplicate directions
    directions.erase(std::unique(directions.begin(), directions.end()), directions.end());
    
    return directions;
}



/********************************************
 ************** CROSSPRODUCT ****************
 ********************************************/
double crossProduct (t_point from, t_point to, t_point next){
    
    double one = to.x-from.x;
    double two = to.y-from.y;
    double three = next.x-to.x;
    double four = next.y-from.y;
    
    double c = (one*four) - (two*three);
    
    return c;
    
    
}
