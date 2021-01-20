#include <vector>
#include <string>
#include "m1.h"
#include "m2.h"
#include "m3.h"
#include "m4.h"
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
#include <limits>

extern mapDataStruct* mapDataObject;


/********************************************
 ************ TRAVELING_COURIER *************
 ********************************************/

std::vector<unsigned> traveling_courier(const std::vector<DeliveryInfo>& deliveries, 
                                        const std::vector<unsigned>& depots, 
                                        const float turn_penalty){
    
    //variable for infinity
    double inf = std::numeric_limits<double>::infinity();
    
    //calculate fastest path by changing the start depots
    double fastestTime = inf;
    double currentTime = 0;
    unsigned totalNumDepots;
    
    if(depots.size() > 19)
        totalNumDepots = depots.size()-8;
    else
        totalNumDepots = depots.size();
    
    //vector to hold final paths and temporary paths
    std::vector<unsigned> fastestPath;
    std::vector<unsigned> currentPath;
    
    //vector of booleans to check if depots is isolated
    std::vector<bool> isolated(depots.size(), false);
    
    for(unsigned i = 0; i < totalNumDepots; i++){
        
        currentPath = greedyHeuristic(deliveries, i, isolated,depots, turn_penalty);
        currentTime = compute_path_travel_time(currentPath, turn_penalty);
        
        //if this path is faster than current fastest path, update accordingly
        if(currentTime < fastestTime){
            
            fastestTime = currentTime;
            fastestPath = currentPath;
        }
        
    }
    
    return fastestPath;
    
    
}

/********************************************
 ************ GREEDYHEURISTIC ***************
 ********************************************/
 
std::vector<unsigned> greedyHeuristic (const std::vector<DeliveryInfo>& deliveries, 
                                        unsigned depotsIndex, std::vector<bool>& isolated,
                                        const std::vector<unsigned>& depots,
                                        const float turn_penalty){
    
    //vector of booleans to check if delivery has been picked up or dropped off
    std::vector<bool> pickedUp(deliveries.size(), false);
    std::vector<bool> droppedOff(deliveries.size(), false);
  
    
    //We also build fast-lookups from: intersection id to DeliveryInfo index for both
    //pickUp and dropOff intersections
    std::multimap<unsigned,size_t> pickUpIntersections; //Intersection_ID -> deliveries index
    std::multimap<unsigned,size_t> dropOffIntersections; //Intersection_ID -> deliveries index

    //Load the look-ups
    for(size_t deliveryID = 0; deliveryID < deliveries.size(); ++deliveryID) {
        unsigned pickUpInter = deliveries[deliveryID].pickUp;
        unsigned dropOffInter = deliveries[deliveryID].dropOff;
        pickUpIntersections.insert(std::make_pair(pickUpInter, deliveryID));
        dropOffIntersections.insert(std::make_pair(dropOffInter, deliveryID));
    }
   
   
    
    //final path to return
    std::vector<unsigned> finalPath;
    //temporary paths
    std::vector<unsigned> currentPath;
    //vector of paths
    std::vector<vector<unsigned>> deliveryPath;
    //vector to check inital path
    std::vector<unsigned> checkPath;
   
    
     //variable for infinity
    double inf = std::numeric_limits<double>::infinity();
    //set initial minimum distance for various pick up/drop off as infinity
    double minDistance = inf;
    double minDistanceDepots = inf;
    double minDistanceNext = inf;
    
    
    //starting intersection is any depots
    unsigned start = depots[depotsIndex];

    //number of total deliveries
    unsigned int numOfDeliveries = deliveries.size();
    //counter for while
    unsigned int numOfDeliveriesCounter = deliveries.size()*2-1;
    //ID of closest pick up 
    unsigned nearestDelivery = 0;
   
    /*
     * find initial path 
     * check to see if first depots is valid
     */
    checkPath = find_path_between_intersections(depots[depotsIndex], deliveries[0].pickUp, turn_penalty);
    
    while (checkPath.size() == 0){
        checkPath = find_path_between_intersections(depots[depotsIndex + 1], deliveries[0].pickUp, turn_penalty);
        isolated[depotsIndex] = true;
        depotsIndex++;
        start = depots[depotsIndex];
    } 
    
    //vector of visited intersections
    std::vector<unsigned> alreadyVisited;
    
    alreadyVisited.push_back(start);
    
    //find closest starting pick up
    LatLon currentPosition = mapDataObject->positionInter[alreadyVisited.back()];
    
    for(unsigned i = 0; i < numOfDeliveries; i++){
        
        //get intersection ID of pick up for current delivery
        unsigned nearestPickUp = deliveries[i].pickUp;
        
        //convert to latlon
        LatLon nearestPosition = mapDataObject->positionInter[nearestPickUp];
        
        unsigned currentDistance = find_distance_between_two_points(currentPosition, nearestPosition);
        
        if(currentDistance < minDistance){
            
            minDistance = currentDistance;
            nearestDelivery = i;
        }
  
    }
    
    unsigned tempPickUpID = deliveries[nearestDelivery].pickUp;
    
    if(std::find(alreadyVisited.begin(), alreadyVisited.end(), tempPickUpID) == alreadyVisited.end()){
                
        //Find all the deliveries picking-up from this intersection
        auto findID = pickUpIntersections.equal_range(tempPickUpID);

        //Mark each delivery as picked-up
        for(auto keyID = findID.first; keyID != findID.second; ++keyID){

            size_t deliveryID = keyID->second; 
            pickedUp[deliveryID] = true;

        }
    }
    //put visited intersection into path of intersections
    alreadyVisited.push_back(deliveries[nearestDelivery].pickUp);
   
    //find path between the intersections
    currentPath = find_path_between_intersections(start, alreadyVisited.back(),
            turn_penalty);
    
    deliveryPath.push_back(currentPath);
    
    //add path from starting depots to closest pick up to final vector
    finalPath.insert(finalPath.end(), currentPath.begin(), currentPath.end());

    /*
     * greedy heuristic 1++ implementation
     * check for closest pick up or legal drop off
     */
    while(numOfDeliveriesCounter != 0){
        
        
        //position of current intersection
        LatLon currentNewPosition = mapDataObject->positionInter[alreadyVisited.back()];
        
        //set the if the closest intersection is a pick up to false
        bool isPickedUp = false;
        
        //initialize min distance to infinity 
        minDistanceNext = inf;
       
        /*
         * loop through vector of closest intersections and find closest pick up
         * or legal drop off
         */
        for(unsigned i = 0; i < numOfDeliveries; i++){
 
            unsigned pickUpID = deliveries[i].pickUp;
            unsigned dropOffID = deliveries[i].dropOff;
            
            /*
             * if delivery hasn't been picked up or dropped off, pick it up
             * 
             * other wise, if delivery has been picked up but not dropped off,
             * drop it off
             */
            if(pickedUp[i] == false && droppedOff[i] == false){
                
                //convert to latlon
                LatLon nextPosition = mapDataObject->positionInter[pickUpID];
                
                //find distance between current position and next one
                unsigned currentDistance = find_distance_between_two_points(currentNewPosition, nextPosition);
                
                //update minimum distance accordingly
                if(currentDistance < minDistanceNext){
                    
                    minDistanceNext = currentDistance;
                    nearestDelivery = i;
                    
                    //the next delivery is a pick up
                    isPickedUp = true;
                } 
            } else if(pickedUp[i] == true && droppedOff[i] == false){ 
                
                LatLon nextDropOffPosition = mapDataObject->positionInter[dropOffID];
                
                unsigned currentDistance = find_distance_between_two_points(currentNewPosition, 
                        nextDropOffPosition);
                
                if(currentDistance < minDistanceNext){
            
                    minDistanceNext = currentDistance;
                    nearestDelivery = i;

                    //the next delivery is a drop off
                    isPickedUp = false;
                }
            }
        }
         
        /*
         * if next delivery is a pick up, update accordingly
         * 
         * other wise, next delivery is a drop off and update accordingly
         */
        if(isPickedUp){
            
            unsigned pickUpID = deliveries[nearestDelivery].pickUp;
            
            /*
             * if pick up ID has not already been visited, mark all pick ups with
             * the same ID as picked up
             *
             * other wise, add to already visited vector as usual*/
            if(std::find(alreadyVisited.begin(), alreadyVisited.end(), pickUpID) == alreadyVisited.end()){
                
                //Find all the deliveries picking-up from this intersection
                auto range_pair = pickUpIntersections.equal_range(pickUpID);

                //Mark each delivery as picked-up
                for(auto key_value_iter = range_pair.first; key_value_iter != range_pair.second; ++key_value_iter){
                    
                    size_t deliveryID = key_value_iter->second; 
                    pickedUp[deliveryID] = true;
                    numOfDeliveriesCounter--; 
                    
                }
                
                 //put visited intersection into path of intersections
                alreadyVisited.push_back(deliveries[nearestDelivery].pickUp);

                //find path between the intersections
                currentPath = find_path_between_intersections(alreadyVisited.rbegin()[1], 
                        alreadyVisited.back(), turn_penalty);

                deliveryPath.push_back(currentPath);

                //add path from starting depots to closest pick up to final vector
                finalPath.insert(finalPath.end(), currentPath.begin(), currentPath.end());
      
            }
        } else {
 
            unsigned dropOffID = deliveries[nearestDelivery].dropOff;
            
            /*
             * if drop off ID hasn't already been visited, mark all drop offs
             * whose pick up has been visited as true
             * 
             * otherwise, if drop off ID has already been visited and pick up ID
             * is true, check to see if the last visited ID is that drop off
             * 
             * otherwise, add drop off to already visited as usual 
             */
            if(std::find(alreadyVisited.begin(), alreadyVisited.end(), dropOffID) == alreadyVisited.end()){
                
                //Find all the deliveries picking-up from this intersection
                auto range_pair = dropOffIntersections.equal_range(dropOffID);

                //Mark each delivery as picked-up
                for(auto key_value_iter = range_pair.first; key_value_iter != range_pair.second; ++key_value_iter){
                    
                    size_t deliveryID = key_value_iter->second; 
                    
                    if(pickedUp[deliveryID] == true){
                    droppedOff[deliveryID] = true;
                    numOfDeliveriesCounter--; 
                    
                    }
                }
               
                //put visited intersection into path of intersections
                alreadyVisited.push_back(deliveries[nearestDelivery].dropOff);

                //update boolean vector for pickups and drop off
                droppedOff[nearestDelivery] = true; 

                //find path between the intersections
                currentPath = find_path_between_intersections(alreadyVisited.rbegin()[1], 
                        alreadyVisited.back(), turn_penalty);

                deliveryPath.push_back(currentPath);

                //add path from starting depots to closest pick up to final vector
                finalPath.insert(finalPath.end(), currentPath.begin(), currentPath.end());
                
            
        } else if(std::find(alreadyVisited.begin(), alreadyVisited.end(), dropOffID) != alreadyVisited.end()
                && pickedUp[nearestDelivery]){
                
                /*
                 * if drop off ID is the last visited intersection, decrement counter
                 * but do not calculate path
                 */ 
                if(alreadyVisited.back() == dropOffID){
                    
                //update boolean vector for pickups and drop off
                droppedOff[nearestDelivery] = true; 
                numOfDeliveriesCounter--; 
                    
                } else {
                    
                    //put visited intersection into path of intersections
                    alreadyVisited.push_back(deliveries[nearestDelivery].dropOff);

                    //update boolean vector for pickups and drop off
                    droppedOff[nearestDelivery] = true; 

                    //find path between the intersections
                    currentPath = find_path_between_intersections(alreadyVisited.rbegin()[1], 
                            alreadyVisited.back(), turn_penalty);

                    deliveryPath.push_back(currentPath);

                    //add path from starting depots to closest pick up to final vector
                    finalPath.insert(finalPath.end(), currentPath.begin(), currentPath.end());

                    numOfDeliveriesCounter--; 
                    
                }
   
            } else {
            
                //put visited intersection into path of intersections
                alreadyVisited.push_back(deliveries[nearestDelivery].dropOff);

                //update boolean vector for pickups and drop off
                droppedOff[nearestDelivery] = true; 

                //find path between the intersections
                currentPath = find_path_between_intersections(alreadyVisited.rbegin()[1], 
                        alreadyVisited.back(), turn_penalty);

                deliveryPath.push_back(currentPath);

                //add path from starting depots to closest pick up to final vector
                finalPath.insert(finalPath.end(), currentPath.begin(), currentPath.end());
                numOfDeliveriesCounter--; 
            }
 
        }
 
    }
    
    //holds closest depots ID
    unsigned closestDepots = 0;
    
    //get current position
    LatLon positionNow = mapDataObject->positionInter[alreadyVisited.back()];
    
    //find closest depot
    for(unsigned i = 0; i < depots.size(); i++){
        
        if(!isolated[i]){
        
            LatLon depotsPosition = mapDataObject->positionInter[depots[i]];

            unsigned currentDistanceDepots = find_distance_between_two_points(positionNow, depotsPosition);

            if(currentDistanceDepots < minDistanceDepots){

                minDistanceDepots = currentDistanceDepots;
                closestDepots = depots[i];
            }
        
        }   
    }
    
    //find path from current position to closest depots
    currentPath = find_path_between_intersections(alreadyVisited.back(), closestDepots, turn_penalty);
    
    deliveryPath.push_back(currentPath);
    
    //add to final vector
    finalPath.insert(finalPath.end(), currentPath.begin(), currentPath.end());
    
   return finalPath; 
}
