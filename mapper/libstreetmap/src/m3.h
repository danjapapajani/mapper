/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   m3.h
 * Author: tremb101
 *
 * Created on March 11, 2018, 1:10 PM
 */

#pragma once
#include <vector>
#include <string>
#include "m1.h"
#include "m2.h"
#include <queue>
#include <limits>
#include <map>
#include <vector>
#include <list>
#include <limits>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry.hpp>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

//PSA this was the declaration that the boost library said I should use
typedef bg::model::point<double, 2, bg::cs::cartesian> point;
typedef std::pair<point, unsigned> value;

//pair of unsigned intersection ID and it's edge weight (travelTime))
typedef pair<unsigned int, double> nodeFoundation;

struct node {
    
    unsigned int targetIntersection;
    double travelTime;
    
    //idk why this is important yet but its online???
    node(unsigned int _targetIntersection, double _travelTime){
        
        targetIntersection = _targetIntersection;
        travelTime = _travelTime;
    }
    
};

//greater implementation for nodes 
struct greaterThanNode{
    
    bool operator()(const node &first, const node &second) const{
        
        return first.travelTime > second.travelTime;
    }
    
};


 // Returns the time required to travel along the path specified, in seconds.
 // The path is given as a vector of street segment ids, and this function
 // can assume the vector either forms a legal path or has size == 0.
 // The travel time is the sum of the length/speed-limit of each street
 // segment, plus the given turn_penalty (in seconds) per turn implied by the path.
 // A turn occurs when two consecutive street segments have different street IDs.
 double compute_path_travel_time(const std::vector<unsigned>& path,
 const double turn_penalty);


// Returns a path (route) between the start intersection and the end
// intersection, if one exists. This routine should return the shortest path
// between the given intersections when the time penalty to turn (change
// street IDs) is given by turn_penalty (in seconds).
// If no path exists, this routine returns an empty (size == 0) vector.
// If more than one path exists, the path with the shortest travel time is
// returned. The path is returned as a vector of street segment ids; traversing
// these street segments, in the returned order, would take one from the start
// to the end intersection.
std::vector<unsigned> find_path_between_intersections(const unsigned intersect_id_start,
const unsigned intersect_id_end,
const double turn_penalty);

// Returns the shortest travel time path (vector of street segments) from
// the start intersection to a point of interest with the specified name.
// The path will begin at the specified intersection, and end on the
// intersection that is closest (in Euclidean distance) to the point of
// interest.
// If no such path exists, returns an empty (size == 0) vector.
std::vector<unsigned> find_path_to_point_of_interest(const unsigned intersect_id_start,
const std::string point_of_interest_name,
const double turn_penalty);

//function to find shared street segments between two intersection points
std::vector<unsigned> findSharedStreetSegments(unsigned interOne, unsigned interTwo);

//function to reconstruct path
std::vector<unsigned> reconstructPath(unsigned interStart, unsigned curInterID, 
        std::vector<unsigned> cameFromVector, std::vector<unsigned> segIDs);


//function to highlight each segment for the path on the map
void highlightPath(unsigned ID);

//get directions of path 
std::vector<std::string> getDirections (std::vector<unsigned> path);

double crossProduct (t_point from, t_point to, t_point next); 