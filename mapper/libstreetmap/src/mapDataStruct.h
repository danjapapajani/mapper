/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mapDataStruct.h
 * Author: papajan6
 *
 * Created on February 1, 2018, 10:57 AM
 */

#ifndef MAPDATASTRUCT_H
#define MAPDATASTRUCT_H
#include "StreetsDatabaseAPI.h"
#include "OSMDatabaseAPI.h"
#include "graphics.h"
#include "Feature.h"
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <string>
#include <iostream>
#include <utility>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry.hpp>
#include "LatLon.h"

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;


//PSA this was the declaration that the boost library said I should use
typedef bg::model::point<double, 2, bg::cs::cartesian> point;
typedef std::pair<point, unsigned> value;


using namespace std; 

class mapDataStruct{
private:
    
    /*
     * making all vectors, maps, and hashtables public to ensure accessibility
     * please note I know this is bad practice 
     */
    
public:
    
    //hash table with key of name and value of vector of POI IDs
    unordered_map<string, vector<unsigned int>> POINameToIDs;
   
    //hash with street ID and its info
    vector<StreetSegmentInfo> segIDToInfo;
    
    //hash table with key of street name and value of the IDs 
    unordered_map<string, vector<unsigned>> streetNameToIDs;
    
    //vector of street IDs to intersection IDS 
    unordered_map<unsigned, vector<unsigned>> streetIDToInterIDs;
 
    //vector of street segment info structs given from API
    vector<vector<unsigned>> streetIDSegInfo;

    //vector indexed by intersectionID holding vector of segmentIDs for that intersectionID (used for find_intersection_street_segments)
    vector<vector<unsigned>> interIDToSegIDs;
    
    //vector that holds travel time with index of street segment ID
    vector<double> travelTime;
    
    //vector holding position of intersections
    vector<LatLon> positionInter;
    
    //vector holding all major roads from OSMDatabase
    vector<unsigned> majorRoads;
    
    //vector to hold all highways from OSMDatabase
    vector<unsigned> highways;
    
    //vector to hold all minor roads from OSMDatabase
    vector<unsigned> minorRoads;
    
    //hash with curve point coords in xy 
    vector<vector<t_point>> xyCoordSegment;
    
    //rtree containing value of pair of LatLon info and POI index
    bgi::rtree<value, bgi::quadratic<16>> POITree;
    
    //rtree containing value of pair of LatLon info and intersection index
    bgi::rtree<value, bgi::quadratic<16>> interTree;
    
    //hash with key of OSMID and value of entity object/pointer
    unordered_map<OSMID, const OSMEntity*> pointToOSMEntity;
    
    //hash with key of OSMID entity object/ptr and value of another hash
    unordered_map<const OSMEntity*, unordered_map<string,string>> pointToEntityTag;
    
    //function to calculate area of polygon
    double getArea(std::vector<t_point> newPosition);
    unsigned int findClosestPOI(LatLon position);
    unsigned int findClosestInter(LatLon position);
    mapDataStruct();
    void clearMapDataStruct();
    
};


#endif /* MAPDATASTRUCT_H */

