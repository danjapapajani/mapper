/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "m1.h"
#include "m2.h"
#include "m3.h"
#include "m4.h"
#include "graphics.h"
#include "StreetsDatabaseAPI.h"
#include "OSMDatabaseAPI.h"
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <unordered_map>
#include <iostream>
#include <map>
#include "mapDataStruct.h"
#include "Feature.h"
#include "graphics_types.h"
#include <X11/keysym.h>



#define CIRCLE_DEGREE 360
#define DEFAULT_TURN_PENALTY 0 


//custom colours
t_color SAND = t_color(0xD2, 0xB4, 0x8C);
t_color WATER = t_color(0xA5, 0xDB, 0xEB);
t_color ISLAND = t_color(0xCD, 0xB7, 0x9E);
t_color GRASS = t_color(0x32, 0xCD, 0x32);
t_color BUILDING = t_color(0xC0, 0xC0, 0XC0);
t_color GOLFGREEN = t_color(0x48, 0xEB, 0x4D);
t_color GREENSPACE = t_color(0x2D, 0xC8, 0x00);
t_color POIYELLOW = t_color(0xFF, 0xFF, 0x33);
t_color MAJORROAD = t_color(0xFF, 0xFF, 0xFF);
t_color HIGHWAY = t_color(0xF1, 0xC8, 0x51);
t_color MINORROAD = t_color(0xE1, 0xE0, 0xE1);
t_color BACKGROUND = t_color(0xDC, 0xDC, 0xDC);
t_color ARROW = t_color(0xA5, 0xDB, 0xEB);


extern unsigned closestIntersect;

//vector to hold travel directions
std::vector<std::string> travelDirections;

//intersections to draw when right mouse button has been clicked twice
unsigned int intersectionFrom;
unsigned int intersectionTo;

//required for highlighting segments
std::vector<bool> segmentsToHighlight;

//required for clicking on the map for pathfinding
bool alreadyClicked = false;

bool changeMap = false;

double latAvg;

//required for indicating when to highlight an intersection (for Find feature)
bool highlightFound = false;

//to prevent buttons from reappearing
bool mapLoadedOnce = false;

//indicates when to draw Subway filters
bool drawSubwayLines = false;

//indicates when to draw Food filters
bool drawFood = false;
int numFoodButtonPress = 0;
//vector holding IDs of food POIs
std::vector<unsigned> foodPOIs;

extern int zoomLevel;
//indicates when to draw Health filters
bool drawHealth = false;
int numHealthButtonPress = 0;
//vector holdingIDs of health POIs
std::vector<unsigned> healthPOIs;

//indicates when to draw Education filter
bool drawEdu = false;
int numEduButtonPress = 0;
//vector holding IDs of coffee POIs
std::vector<unsigned> eduPOIs;

//indicates when to draw Entertainment filter
bool drawEnt = false;
int numEntButtonPress = 0;

//vector for holding IDs of entertainment POIs
std::vector<unsigned> entPOIs;

//boolean vector indicating whether an intersection has been highlighted or not
//used for highlighting the nearest intersection on mouse click
std::vector<bool> drawnIntersections;

//vectors for printing starting intersections for printing path
std::vector<bool> startIntersections;

//vectors for printing end intersections for printing path
std::vector<bool> endIntersections;

//vector of intersection IDs to highlight with Find button
 std::vector<unsigned> intIDToHighlight;

//vector to hold vector of t_points for beaches 
std::vector<std::vector<t_point>> drawBeaches;

//vector to hold vector of latlon for rivers
std::vector<std::vector<LatLon>> drawRivers;

//vector to hold vector of latlon for streams
std::vector<std::vector<LatLon>> drawStreams;

//vector to hold vector of t_points for islands
std::vector<std::vector<t_point>> drawIslands;

//vector to hold vector of t_points for parks
std::vector<std::vector<t_point>> drawParks;

//vector to hold vector of t_points for buildings
std::vector<std::vector<t_point>> drawBuildings;

//vector to hold vector of t_points for golf courses
std::vector<std::vector<t_point>> drawGolfCourses;

//vector to hold vector of t_points for greenspaces
std::vector<std::vector<t_point>> drawGreenspaces;

//vector to hold vector of t_points for Lakes
std::vector<std::vector<t_point>> drawLakes;

//making mapDataObject a global variable so I can access its contents
extern mapDataStruct* mapDataObject;

//if user clicks help icon
bool clickedHelp;

//required for setting the correct x&y values for the map range
struct intersectionData {
    LatLon position;
    std::string name;
};

//holds point of interest information to be used for plotting POIs & their name
struct POIData {
    LatLon position;
    std::string name;
};

//vector to hold intersection struct data
std::vector<intersectionData> interStruct;

//vector to hold POI structures
std::vector<POIData> POIStruct;


/********************************************
 **************** DRAW_MAP ******************
 ********************************************/
void draw_map() {
    
    
    //fill in vector of intersections
    interStruct.resize(getNumberOfIntersections());
    
    //reset all intersection highlights
    drawnIntersections.resize(getNumberOfIntersections());
    startIntersections.resize(getNumberOfIntersections());
    endIntersections.resize(getNumberOfIntersections());
    segmentsToHighlight.resize(getNumberOfIntersections());
    
    //for highlighting segments
    segmentsToHighlight.resize(getNumberOfStreetSegments());
    for (unsigned i = 0; i < getNumberOfStreetSegments(); i++){
        segmentsToHighlight[i] = false;
    }
    
    //set all the intersections to initially not highlighted
    for (unsigned i = 0; i < getNumberOfIntersections(); i++){
        
        drawnIntersections[i] = false; 
        startIntersections[i] = false;
        endIntersections[i] = false;
        
        //fill struct with position & name info for each intersection 
        interStruct[i].position = getIntersectionPosition(i);
        interStruct[i].name = getIntersectionName(i);
        
    }
    
  
    //fill in vector of POI struct information
    POIStruct.resize(getNumberOfPointsOfInterest());
    for (unsigned i = 0; i < getNumberOfPointsOfInterest(); i++) {
        
        POIStruct[i].position = getPointOfInterestPosition(i);
        POIStruct[i].name = getPointOfInterestName(i);
        
    }
    
    //put the information about POI types into the appropriate POI vector
    categorizePOIs();
   
    
    init_graphics("City Map", BACKGROUND);
    
    //calculate the coordinates of the corners of the map
    std::vector<double> screenCoords = calculateMaxMinXY();
    
    //coordinates of the corners of the map
    double maximumX = screenCoords[0];
    double maximumY = screenCoords[1];
    double minimumX = screenCoords[2];
    double minimumY = screenCoords[3];      
            
    set_visible_world(minimumX, minimumY, maximumX, maximumY);
    set_drawing_buffer(OFF_SCREEN);

    
    loadMapFeatures();
    
    //create the buttons only when the map is loaded the first time
    if (mapLoadedOnce == false){
    
        create_button("Window", "Find", act_on_find_button); 
    
        create_button("Find", "Clear", act_on_clear_button);
    
        create_button("Clear", "Food", act_on_food_button);
    
        create_button("Food", "Health", act_on_health_button);
    
        create_button("Health", "Education", act_on_edu_button);
    
        create_button("Education", "Entertainment", act_on_ent_button);
        
        //create_button("Entertainment", "Change Map", act_on_map_button);
       
    }
    
    draw_screen();

    event_loop(act_on_button_press, nullptr, nullptr, draw_screen);
    
            
    changeMap = true;
    
    close_graphics();

    
}


/********************************************
 ************* DRAW_SCREEN ******************
 ********************************************/
void draw_screen() {
    
    clearscreen();
    
    //draw the different types of roads
    if(zoomLevel == 0)
        zoomLevel0();
    else if(zoomLevel == 1)
        zoomLevel1();
    else if(zoomLevel == 2)
        zoomLevel2();
    else if(zoomLevel == 3)
        zoomLevel3();
    else if(zoomLevel == 4)
        zoomLevel4();
    else if(zoomLevel == 5)
        zoomLevel5();   
    else if(zoomLevel == 6)
        zoomLevel6();
    else if(zoomLevel == 7)
        zoomLevel7();
    else if(zoomLevel == 8)
        zoomLevel8();
    else if(zoomLevel == 9)
        zoomLevel9();
    else if(zoomLevel == 10)
        zoomLevel10();
    else if(zoomLevel == 11)
        zoomLevel11();
    else if(zoomLevel == 12)
        zoomLevel12();

    //write the directions on the screen every time so they stay there
    drawDirections(travelDirections);
    //drawSearchBar();
    
    set_coordinate_system(GL_WORLD);
    
    //to draw the highlighted street segments
    for (unsigned i = 0; i < getNumberOfStreetSegments(); i++){
        
        if (segmentsToHighlight[i] == true){
            
            highlightPath(i);
        }
    }

    for (unsigned j = 0; j < interStruct.size(); ++j) {
        
        //find the coordinates of each intersection and convert
        auto const x = interStruct[j].position.lon() * DEG_TO_RAD * cos(latAvg); 
        auto const y = interStruct[j].position.lat() * DEG_TO_RAD; 
  
        
        if (drawnIntersections[j] == true){
            
            setcolor(YELLOW);
            fillarc(x, y, 0.000002, 0, CIRCLE_DEGREE);
        }
            
    
        
        if (startIntersections[j] == true){
            
           setcolor(PURPLE);
           fillarc(x, y, 0.00001, 0, CIRCLE_DEGREE);
        }
        
        if (endIntersections[j] == true){
          
           setcolor(RED);
           fillarc(x, y, 0.00001, 0, CIRCLE_DEGREE);
        }
        
   
 
    }
    
   

    //draw points of interest
    drawPOIs(); 
    
    //highlight intersections that were searched for in find
    if (highlightFound == true){
        highlightFoundInts();
    }
    
    //draw food POIs if the Food button was pressed
    if (drawFood == true){
        drawFoodPOI();
    }
    
    //draw health POIs if the Health button was pressed
    if (drawHealth == true){
        drawHealthPOI();
    }
    
    //draw education POIs if the Education button was pressed
    if (drawEdu == true){
        drawEduPOI();
    }
    
    //draw entertainment POIs if the Entertainment button was pressed
    if (drawEnt == true) {
        drawEntPOI();
    }
    
    drawHelpIcon();
    
    copy_off_screen_buffer_to_screen();
    
}

/********************************************
 ************ ZOOMLEVELS *************
 ********************************************/

void zoomLevel0(){
    
    drawFeatures();
    //draw major roads
    drawMajorRoad(2);
    
    //draw highway
    drawHighways(3);
    
    
}

void zoomLevel1(){
    
    //set_coordinate_system(GL_WORLD);
    //don't change anything
    zoomLevel0();
}

void zoomLevel2(){
    
    //set_coordinate_system(GL_WORLD);
    drawFeatures();
    drawMinorRoad(1);
    drawMajorRoad(2);
    drawHighways(3);
    
}

void zoomLevel3(){
    
    //set_coordinate_system(GL_WORLD);
    drawFeatures();
    drawMinorRoad(1);
    drawMajorRoad(2);
    drawHighways(3);
    
    
}

void zoomLevel4(){
    
    //set_coordinate_system(GL_WORLD);
    drawFeatures();
    drawMinorRoad(2);
    drawMajorRoad(3);
    drawHighways(4);
    
    
}

void zoomLevel5(){
    
    //set_coordinate_system(GL_WORLD);
    drawFeatures();
    drawMinorRoad(2);
    drawMajorRoad(3);
    drawHighways(4);
    
   
}


void zoomLevel6(){
    
    //set_coordinate_system(GL_WORLD);
    drawFeatures();
    drawMinorRoad(4);
    drawMajorRoad(5);
    drawHighways(7);
    
    
    for (unsigned i = 0; i < mapDataObject->majorRoads.size(); i++){
        drawStreetName(mapDataObject->majorRoads[i], 6);
        
    }
    
    for (unsigned i = 0; i < mapDataObject->highways.size(); i++){
        drawStreetName(mapDataObject->highways[i], 6);
       
    }
    
    
}

void zoomLevel7(){
    
    //set_coordinate_system(GL_WORLD);
    drawFeatures();
    drawMinorRoad(4);
    drawMajorRoad(5);
    drawHighways(7);
     
   
    for (unsigned i = 0; i < mapDataObject->majorRoads.size(); i++){
        drawStreetName(mapDataObject->majorRoads[i], 7);
         
    }
    for (unsigned i = 0; i < mapDataObject->highways.size(); i++){
        drawStreetName(mapDataObject->highways[i], 7);
        
    }
}

void zoomLevel8(){
    
    //set_coordinate_system(GL_WORLD);
    drawFeatures();
    drawMinorRoad(5);
    drawMajorRoad(7);
    drawHighways(10);
     
    for (unsigned i = 0; i < mapDataObject->minorRoads.size(); i++){
        drawStreetName(mapDataObject->minorRoads[i], 8);
       
    }
    for (unsigned i = 0; i < mapDataObject->majorRoads.size(); i++){
        drawStreetName(mapDataObject->majorRoads[i], 8);
      
    }
    for (unsigned i = 0; i < mapDataObject->highways.size(); i++){
        drawStreetName(mapDataObject->highways[i], 8);
     
    }
}

void zoomLevel9(){
    
    //set_coordinate_system(GL_WORLD);
    drawFeatures();
    drawMinorRoad(5);
    drawMajorRoad(7);
    drawHighways(10);
    
     
    for (unsigned i = 0; i < mapDataObject->minorRoads.size(); i++){
        drawStreetName(mapDataObject->minorRoads[i], 9);
       
    }
    for (unsigned i = 0; i < mapDataObject->majorRoads.size(); i++){
        drawStreetName(mapDataObject->majorRoads[i], 9);
                
       
    }
    for (unsigned i = 0; i < mapDataObject->highways.size(); i++){
        drawStreetName(mapDataObject->highways[i], 9);
       
    }
}
void zoomLevel10(){
    
     //set_coordinate_system(GL_WORLD);
    drawFeatures();
    drawMinorRoad(7);
    drawMajorRoad(11);
    drawHighways(16);
    
    for (unsigned i = 0; i < mapDataObject->minorRoads.size(); i++){
        drawStreetName(mapDataObject->minorRoads[i], 10);
        
                
    }
    for (unsigned i = 0; i < mapDataObject->majorRoads.size(); i++){
        drawStreetName(mapDataObject->majorRoads[i], 10);
       
    }
    for (unsigned i = 0; i < mapDataObject->highways.size(); i++){
        drawStreetName(mapDataObject->highways[i], 10);
       
    }
}

void zoomLevel11(){
    
    //set_coordinate_system(GL_WORLD);
    drawFeatures();
    drawMinorRoad(10);
    drawMajorRoad(11);
    drawHighways(16);
     
    
    for (unsigned i = 0; i < mapDataObject->minorRoads.size(); i++)
        drawStreetName(mapDataObject->minorRoads[i], 11);
      
    for (unsigned i = 0; i < mapDataObject->majorRoads.size(); i++)
        drawStreetName(mapDataObject->majorRoads[i], 11);
       
    for (unsigned i = 0; i < mapDataObject->highways.size(); i++)
        drawStreetName(mapDataObject->highways[i], 11);
        
}
  
void zoomLevel12(){
    
    //set_coordinate_system(GL_WORLD);
    drawFeatures();
    drawMinorRoad(14);
    drawMajorRoad(30);
    drawHighways(53);
     
    for (unsigned i = 0; i < mapDataObject->minorRoads.size(); i++){
        drawStreetName(mapDataObject->minorRoads[i], 12);
       
                
    }
    for (unsigned i = 0; i < mapDataObject->majorRoads.size(); i++){
        drawStreetName(mapDataObject->majorRoads[i], 12);
        
    }
    for (unsigned i = 0; i < mapDataObject->highways.size(); i++){
        drawStreetName(mapDataObject->highways[i], 12);
        
}
}


/********************************************
 ************ LOADMAPFEATURES ***************
 ********************************************/


//loads features that will be resued in draw_screen
void loadMapFeatures(){
   
    /*
     * find number of points for each feature
     * convert point to latlon
     * store point in temp vector
     *
     */
    for (unsigned i = 0; i < getNumberOfFeatures(); i++) {

        //holds latlon coords of feature point
        std::vector<LatLon> featLatLon;
        //holds xy coords of feature point
        std::vector<t_point> featXY;
        FeatureType newType = getFeatureType(i);

        for (unsigned j = 0; j < getFeaturePointCount(i); j++) {

            //get latlon position of current feature point
            LatLon currentPoint = getFeaturePoint(i, j);

            //vectors for rivers and streams
            if (newType == River || newType == Stream) {
                featLatLon.push_back(currentPoint);
            } else {
            
            //store xy features into t_point vector
            double xCoord = (currentPoint.lon() * DEG_TO_RAD) * cos(latAvg);
            double yCoord = currentPoint.lat() * DEG_TO_RAD; 
            t_point newTPoint = t_point(xCoord, yCoord);
            featXY.push_back(newTPoint);
            
            }
        }

        //put feature type into its corresponding vector
        if (newType == Beach)
            drawBeaches.push_back(featXY);
        else if (newType == River)
            drawRivers.push_back(featLatLon);
        else if (newType == Stream)
            drawStreams.push_back(featLatLon);
        else if (newType == Island)
            drawIslands.push_back(featXY);
        else if (newType == Park)
            drawParks.push_back(featXY);
        else if (newType == Building)
            drawBuildings.push_back(featXY);
        else if (newType == Golfcourse)
            drawGolfCourses.push_back(featXY);
        else if (newType == Greenspace)
            drawGreenspaces.push_back(featXY);
        else if (newType == Lake)
            drawLakes.push_back(featXY);

        featXY.clear();
        featLatLon.clear();

    }


}

/********************************************
 *********** betweenLatLon ******************
 ********************************************/
void betweenLatLon(LatLon x, LatLon y) {

    double xBegin, xEnd, yBegin, yEnd;
            
    xBegin = (x.lon() * DEG_TO_RAD) * cos(latAvg); 
    yBegin = (x.lat()) * DEG_TO_RAD; 
    xEnd = (y.lon() * DEG_TO_RAD) * cos(latAvg); 
    yEnd = (y.lat()) * DEG_TO_RAD; 
            
    drawline(xBegin, yBegin, xEnd, yEnd);

    xBegin = (x.lon() * DEG_TO_RAD) * cos(latAvg);
    yBegin = (x.lat()) * DEG_TO_RAD;
    xEnd = (y.lon() * DEG_TO_RAD) * cos(latAvg);
    yEnd = (y.lat()) * DEG_TO_RAD;

    drawline(xBegin, yBegin, xEnd, yEnd);
            
    
}

/********************************************
 ********** drawStreetSegment ***************
 ********************************************/
void drawStreetSegment(unsigned ID) {
   

    StreetSegmentInfo currentSeg = mapDataObject->segIDToInfo[ID];

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
        
        if(zoomLevel > 6){
            
            if(currentSeg.oneWay) {
             

            t_bound_box arrow(from.x - 0.04, from.y - 0.04, from.x + 0.04, from.y + 0.04);
            setcolor(ARROW);

            double angle = findStreetNameAngle(from, to);
            settextrotation(angle);
            drawtext_in(arrow, "->");
            
        }
       }
    } else{
        
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
 ************** latLonToXY ******************
 ********************************************/
t_point latLonToXY(LatLon pointOne){
    
    //extract each part of LatLon
    double lon = pointOne.lon();
    double lat = pointOne.lat();
    
    //apply given formula to get Cartesian coordinates
    double xCoord = (lon * DEG_TO_RAD) * cos(latAvg);
    double yCoord = lat * DEG_TO_RAD; 
    
    return t_point(xCoord, yCoord);
}


/********************************************
 ************** drawMajorRoad ***************
 ********************************************/
void drawMajorRoad(int width) {
    
    //iterate through the pre-loaded vector of major roads to draw
    std::vector<unsigned> majorRoads = mapDataObject->majorRoads;
    for (auto iter = majorRoads.begin(); iter != majorRoads.end(); iter++) {
        //draw the road
        setlinestyle(SOLID);
        setlinewidth(width);
        setcolor(MAJORROAD);
        drawStreetSegment(*iter);
    }
}


/********************************************
 ************** drawHighways  ***************
 ********************************************/
void drawHighways(int width){
    
    //iterate through the vector of highways to draw
    std::vector<unsigned> highways = mapDataObject->highways;
    for(auto iter = highways.begin(); iter != highways.end(); iter++){
        
        //draw the highway
        setlinestyle(SOLID);
        setlinewidth(width);
        setcolor(HIGHWAY);
        drawStreetSegment(*iter);
    }
}


/********************************************
 ************* drawMinorRoad ****************
 ********************************************/
void drawMinorRoad(int width){
    
    std::vector<unsigned> minorRoads = mapDataObject->minorRoads;
    for(auto iter = minorRoads.begin(); iter != minorRoads.end(); iter++){
        
        //draw the minor road
        setlinestyle(SOLID);
        setlinewidth(width);
        setcolor(MINORROAD);
        drawStreetSegment(*iter);
    }
}


/********************************************
 ********* ACT_ON_BUTTON_PRESS **************
 ********************************************/
void act_on_button_press(float x, float y, t_event_buttonPressed event) {
    
    
    //left mouse key clicked
    if (event.button == 1){ 
        
        //find where was clicked in LatLon coordinates
        float lon = cartesianToLongitude(x);
        float lat = y / DEG_TO_RAD; 
        
        //create LatLon coordinate 
        LatLon position(lat, lon);
        
        //find the closest intersection ID & name
        unsigned int closestIntID = find_closest_intersection(position);
        
        std::string closestIntName = getIntersectionName(closestIntID);
        
        
        //if the intersection is highlighted and it's clicked on again, unhighlight it
        if (drawnIntersections[closestIntID] == true){
            
            //note that it's no longer highlighted
            drawnIntersections[closestIntID] = false;
            
            
        }
        
        //the intersection was not already highlighted
        else {
            //note that the intersection has been highlighted
            drawnIntersections[closestIntID] = true;
        
            std::cout<<"The closest intersection is: " <<closestIntName<<std::endl;
           //FOR DEBUGGING:
            std::cout<<"Closest Intersection ID is: "<<closestIntID<<std::endl;
        }
        
        
        //find the closest point of interest ID & name
        unsigned int closestPOIID = find_closest_point_of_interest(position);
        std::string closestPOIName = getPointOfInterestName(closestPOIID);
    
        //find the position of the closest POI to compare to mouse position
        LatLon closestPOILatLon = getPointOfInterestPosition(closestPOIID);
        
        //convert to cartesian 
        t_point closestPOIXY = latLonToXY(closestPOILatLon);
        
        //if a POI is clicked (within a specified range) display its name
        if ((x <= closestPOIXY.x + 0.0000005 ) && (x >= closestPOIXY.x - 0.0000005)){
            if ((y <= closestPOIXY.y + 0.0000005) && ( y >= closestPOIXY.y - 0.0000005)){
                std::cout<<"POI: "<<closestPOIName<<std::endl;
                setcolor(BLACK);
                settextrotation(0);
                drawtext(closestPOIXY.x + 0.000001, closestPOIXY.y + 0.000001, closestPOIName, 50, 50);
            }
        }
        
        
        int helpXCoord = xworld_to_scrn(x);
        int newY = yworld_to_scrn(y);

        // help box is clicked
        if (helpXCoord > 8 && helpXCoord < 50 && newY > 875 && newY < 950) {
            if(clickedHelp)
                clickedHelp = false;
            else
            clickedHelp = true;
        } 
        
        draw_screen();
    }
    
    //right button was pressed to find path between clicked intersection points
    if (event.button == 3){
        
       
        //this is the first time the user right clicks the intersection
        if (alreadyClicked == false){
            
            //find where was clicked in LatLon coordinates
            float lon = cartesianToLongitude(x);
            float lat = y / DEG_TO_RAD; 
            
            //create LatLon coordinate 
            LatLon position1(lat, lon);
        
            //find the closest intersection ID & name
            intersectionFrom = find_closest_intersection(position1);
            
            //std::cout<<"intersectionFrom: "<<intersectionFrom<<std::endl;
            
            startIntersections[intersectionFrom] = true;
            
            alreadyClicked = true;
 
        }
        
        //user has clicked a second intersection
        else if (alreadyClicked == true) {
            
            //find where was clicked in LatLon coordinates
            float lon = cartesianToLongitude(x);
            float lat = y / DEG_TO_RAD; 
        
            //create LatLon coordinate 
            LatLon position2(lat, lon);
        
            //find the closest intersection ID & name
            intersectionTo = find_closest_intersection(position2);
            
            //std::cout<<"intersectionTo: "<<intersectionTo<<std::endl;
            
            endIntersections[intersectionTo] = true;
            
            alreadyClicked = false; 
            
            
            std::vector<unsigned> clickedPath = find_path_between_intersections(intersectionFrom, intersectionTo, DEFAULT_TURN_PENALTY);
        
            for(unsigned i = 0; i< clickedPath.size(); i++){
                segmentsToHighlight[clickedPath[i]] = true;
            }
        
            travelDirections = getDirections(clickedPath);
            
        }
        
    
            
    }
    
    
    //draw food POIs if the Food button was pressed
    if (drawFood == true){
        drawFoodPOI();
    }
    
    //draw health POIs if the Food button was pressed
    if (drawHealth == true){
        drawHealthPOI();
    }
    
     //draw education POIs if the Food button was pressed
    if (drawEdu == true){
        drawEduPOI();
    }
    
    //draw entertainment POIs if the Entertainment button was pressed
    if (drawEnt == true){
        drawEntPOI();
    }
    
  
   
 
}

/********************************************
 ********* cartesianToLongitude *************
 ********************************************/
float cartesianToLongitude(float x) {
    float lon = x / (cos(latAvg) * DEG_TO_RAD);
    return (lon);
}


/********************************************
 ********** findStreetNameAngle *************
 ********************************************/

double findStreetNameAngle(t_point from, t_point to){
    
    double finalAngle;
    finalAngle = 0;
    
    if(from.x == to.x)
        return 90;
    else if(from.y == to.y)
        return 0;
    
    //convert final angle into degrees since t_point is in cartesian
    
    finalAngle = atan((to.y - from.y) / (to.x - from.x)) * 180 / PI;
    
    return finalAngle;
    
    
}


/********************************************
 ******* findStreetStreetNameAngle **********
 ********************************************/
double findStreetStreetNameAngle(unsigned segID){
    
    double finalAngle;
    finalAngle = 0;
    
    unsigned int begin = mapDataObject->segIDToInfo[segID].from;
    unsigned int end = mapDataObject->segIDToInfo[segID].to;
    
    //get inter position in latlon coordinates
    LatLon pointFrom = mapDataObject->positionInter[begin];
    LatLon pointTo = mapDataObject->positionInter[end];
    
    t_point from = latLonToXY(pointFrom);
    t_point to = latLonToXY(pointTo);
    
    if((from.x - to.x) == 0){
        return 0;
    }
    
    finalAngle = atan((from.y - to.y) / (from.x - to.x)) * 180 / PI;
    
    while(finalAngle < 0)
        finalAngle += CIRCLE_DEGREE;
    
    return finalAngle;
                 
}

/********************************************
 ************* DRAWSTREETNAME ***************
 ********************************************/

void drawStreetName(unsigned segID, unsigned zoom){
    
     unsigned int fromCoord = mapDataObject->segIDToInfo[segID].from;
        unsigned int toCoord = mapDataObject->segIDToInfo[segID].to;
        
        //get lat lon position of coordinates
        LatLon beginPoint = mapDataObject->positionInter[fromCoord];
        LatLon endPoint = mapDataObject->positionInter[toCoord];
        
        //convert to XY
        t_point begin = latLonToXY(beginPoint);
        t_point end = latLonToXY(endPoint);
    
    
        //find number of curve points per name
        unsigned curvyCount = mapDataObject->segIDToInfo[segID].curvePointCount;
        
        //find street ID for given segment
        unsigned streetID = mapDataObject->segIDToInfo[segID].streetID;
        
        std::string nameSeg = getStreetName(streetID);
        
        t_point middlePoint;
        
        if(nameSeg!= "<unknown>"){
            

            if(curvyCount < 2){

                middlePoint.x = (begin.x + end.x)/2;
                middlePoint.y = (begin.y + end.y)/2;
                
        } else {
                
                LatLon newCurve = getStreetSegmentCurvePoint(segID, curvyCount / 2);

                middlePoint = latLonToXY(newCurve);
                middlePoint.x = (begin.x + end.x)/2;
                middlePoint.y = (begin.y + end.y)/2;
        }
            
            
            double finalLength = find_street_segment_length(segID);
            
            //distance of street relative to screen
            unsigned smallest = 7000 / (zoom * zoom);
            
            if (finalLength < smallest)
                return;
            
            double angle = findStreetNameAngle(begin , end);
            
            unsigned font = 12 - zoom / 3;
            double mapBorderx = finalLength * cos(angle);
            double mapBordery = finalLength * sin(angle);
            
            //my version of handle zoom in
            settextrotation(angle);
            if (zoomLevel > 6){
                
                setfontsize(font);
                setcolor(BLACK);
                drawtext(middlePoint, nameSeg, finalLength / 100000, finalLength / 100000);
            } else {
                
                
                setfontsize(font);
                setcolor(BLACK);
                drawtext(middlePoint, nameSeg, (mapBorderx / 600000) / 2, (mapBordery / 600000) /2);
                
            }
            
        }
}


/********************************************
 **************** drawPOIs ******************
 ********************************************/
void drawPOIs(){
    
    //go through all the POIs stored in the POI struct and draw them at their 
    //stored position
    for (unsigned i = 0; i < POIStruct.size(); ++i) {

        setcolor(POIYELLOW);
        
        //get the position of the POI in Cartesian coordinates
        auto const x = POIStruct[i].position.lon() * DEG_TO_RAD * cos(latAvg);
        auto const y = POIStruct[i].position.lat() * DEG_TO_RAD; 
        
        
        fillarc(x, y, 0.0000005, 0, CIRCLE_DEGREE);
        
        
    }
    
}


/********************************************
 ********* ACT_ON_FIND_BUTTON ***************
 ********************************************/
void act_on_find_button(void (*drawscreen_ptr) (void)){
    
    //user can either search a single intersection or two intersections
    //and the map will draw the path between them
    std::string userResponse;
    std::cout<<"Would you like to find an Intersection or POI? (Intersection/POI)"<<std::endl;
    std::getline (std::cin, userResponse);
    std::string intersection = "Intersection";
    std::string poi = "POI";
    
    //either drop a pin at an intersection or find the path between inputted intersections
    if (userResponse == intersection){
    
        std::string streetName1, streetName2, streetName3, streetName4;
        std::vector<unsigned> tempVector1;
        std::vector<unsigned> tempVector2;
        std::vector<unsigned> tempVector3;
        std::vector<unsigned> tempVector4;
        unsigned intersectionStart = 0;
        unsigned intersectionEnd = 0;
        std::vector<unsigned> pathToHighlight; 



       std::string no = "No";
       std::string yes = "Yes";
       
      
        //parse first street name
        do{
            std::cout<<"Would you like directions between intersections (Yes/No)?"<<std::endl;
            std::getline (std::cin,userResponse);
            
         
            //only one intersection to drop a pin at
            if (userResponse == no){
                do {
                    std::cout<<"Enter the name of the first street: "<<std::endl;
                    std::getline (std::cin, streetName1);

                    //just used to check if empty
                    tempVector1 = find_street_ids_from_name(streetName1);


                    if (tempVector1.size() == 0){
                        //street does not exist
                        std::cout<<"Street does not exist."<<std::endl;
                    }

                    //keep asking to enter street name if invalid
                } while (tempVector1.size() == 0);


                //parse second street name
                do {
                    std::cout<<"Enter the name of the second street: "<<std::endl;
                    std::getline (std::cin, streetName2);

                    //check if empty
                    tempVector2 = find_street_ids_from_name(streetName2);

                    if (tempVector2.size() == 0){
                        //second street input does not exist
                        std::cout<<"Street does not exist."<<std::endl;
                    }

                    //keep asking to enter street name if invalid
                } while (tempVector2.size() == 0);

            }

            //find the path between intersections
            if (userResponse == yes){


                do {
                    std::cout<<"Enter the name of the first street: "<<std::endl;
                    std::getline (std::cin, streetName1);

                    //just used to check if empty
                    tempVector1 = find_street_ids_from_name(streetName1);


                    if (tempVector1.size() == 0){
                        //street does not exist
                        std::cout<<"Street does not exist."<<std::endl;
                    }

                    //keep asking to enter street name if invalid
                } while (tempVector1.size() == 0);


                //parse second street name
                do {
                    std::cout<<"Enter the name of the second street: "<<std::endl;
                    std::getline (std::cin, streetName2);

                    //check if empty
                    tempVector2 = find_street_ids_from_name(streetName2);

                    if (tempVector2.size() == 0){
                        //second street input does not exist
                        std::cout<<"Street does not exist."<<std::endl;
                    }

                    //keep asking to enter street name if invalid
                } while (tempVector2.size() == 0);




                //parse third street name
                do {
                    std::cout<<"Enter the name of the other first street: "<<std::endl;
                    std::getline (std::cin, streetName3);

                    //just used to check if empty
                    tempVector3 = find_street_ids_from_name(streetName3);

                    if (tempVector3.size() == 0){
                        //street does not exist
                        std::cout<<"Street does not exist."<<std::endl;
                    }

                    //keep asking to enter street name if invalid
                } while (tempVector3.size() == 0);

                //parse fourth street name
                do {
                    std::cout<<"Enter the name of the other second street: "<<std::endl;
                    std::getline (std::cin, streetName4);

                    //check if empty
                    tempVector4 = find_street_ids_from_name(streetName4);

                    if (tempVector4.size() == 0){
                        //second street input does not exist
                        std::cout<<"Street does not exist."<<std::endl;
                    }

                    //keep asking to enter street name if invalid
                } while (tempVector4.size() == 0);


                //draw the two intersections
                //get the intersections to highlight for the first set 
                intIDToHighlight = find_intersection_ids_from_street_names(streetName1, streetName2);

                //error checking correct user input
                if (intIDToHighlight.size() == 0 ){
                    //no intersection was found for the entered street names
                    std::cout<<"Intersection does not exist."<<std::endl;
                }

                else {
                    intersectionStart = intIDToHighlight[0];
                    //to highlight the starting intersection green
                    startIntersections[intersectionStart] = true;
                    highlightFound = true;
                }

                //get the intersections to highlight for the second set of streets
                std::vector<unsigned> moreIDsToHighlight = find_intersection_ids_from_street_names(streetName3, streetName4);

               
                //check that the intersection exists
                if (moreIDsToHighlight.size() == 0){
                    //no intersection found
                    std::cout<<"Intersection does not exist."<<std::endl;
                }
                
                else {
                    intersectionEnd = moreIDsToHighlight[0];
                    //to highlight end intersection red
                    endIntersections[intersectionEnd] = true;
                    highlightFound = true;
                }


                //highlights the start and final destination intersections (drops pin & writes name)
                intIDToHighlight.insert(std::end(intIDToHighlight), std::begin(moreIDsToHighlight), std::end(moreIDsToHighlight));


                //get the path to highlight based on the user info inputted above
                pathToHighlight = find_path_between_intersections(intersectionStart, intersectionEnd, DEFAULT_TURN_PENALTY);

                
                travelDirections = getDirections(pathToHighlight);

                //note the segments that will have to be highlighted for the path
                for(unsigned i = 0; i < pathToHighlight.size(); i++){

                    segmentsToHighlight[pathToHighlight[i]] = true;

                }

               

            }


            else if (userResponse == no){

                //find the intersections between two streets
                intIDToHighlight.clear(); 

                intIDToHighlight = find_intersection_ids_from_street_names(streetName1, streetName2);

                //CORNER CASE: intersection does not exist
                if (intIDToHighlight.size() == 0 ){
                    //no intersection was found for the entered street names
                    std::cout<<"Intersection does not exist."<<std::endl;
                }
                else {
                    highlightFound = true;
                }

               
            }
        
            //user inputted something other than yes/no for intersection search
            else {
                std::cout<<"Please chose Yes or No"<<std::endl;
            }

        } while((userResponse != "Yes") && (userResponse != "No"));
 
    }
  
    
    //user inputted that they want to find a path to a POI 
    else if (userResponse == poi){
        
        std::string firstStreet, secondStreet;
        std::vector<unsigned> tempVec1;
        std::vector<unsigned> tempVec2;
        unsigned startPoint = 0;
        std::string poiName;
        std::vector<unsigned> intToPoiPath;
        
        
        //parse the first street 
        do {
            std::cout<<"Enter the name of the first street "<<std::endl;
            std::getline(std::cin, firstStreet);
            
            //check if there are any streets by that name
            tempVec1 = find_street_ids_from_name(firstStreet);
            
            //no street with that name exists
            if (tempVec1.size() == 0){
                std::cout<<"Street does not exist."<<std::endl;
            }
            
        //keep asking until a valid street name is input
        } while (tempVec1.size() == 0);
        
        
        //parse the second street
        do {
            std::cout<<"Enter the name of the second street"<<std::endl;
            std::getline(std::cin, secondStreet);
            
            //look for all streets by that name
            tempVec2 = find_street_ids_from_name(secondStreet);
            
            //check for for streets by that name
            if (tempVec2.size() == 0){
                std::cout<<"Street does not exist."<<std::endl;
            }
            
        } while (tempVec2.size() == 0);
        
       
        intIDToHighlight = find_intersection_ids_from_street_names(firstStreet, secondStreet);
        
        if (intIDToHighlight.size() == 0){
            //intersection wasn't found
            std::cout<<"Intersection does not exist."<<std::endl;
        }
        
        //valid intersection so highlight it
        else {
            startPoint = intIDToHighlight[0];
            //to highlight intersection green
            startIntersections[startPoint] = true;
            highlightFound = true;
            
        }
        
        //prompt user to enter poi destination
        do{
            std::cout<<"Enter the name of the POI"<<std::endl;
            std::getline(std::cin, poiName);


            intToPoiPath = find_path_to_point_of_interest(startPoint, poiName, DEFAULT_TURN_PENALTY);

            //either the POIs name doesn't exist or there's no path
            if (intToPoiPath.size() == 0){
                std::cout<<"Error: Please re-enter destination name."<<std::endl;
            }
            
        } while (intToPoiPath.size() == 0);
        
        
        travelDirections = getDirections(intToPoiPath);
        
        endIntersections[closestIntersect] = true;
        
        //note the segments to highlight for the path from the intersection
        //to the POI
        for (unsigned i = 0; i < intToPoiPath.size(); i++){
       
            segmentsToHighlight[intToPoiPath[i]] = true;
            
        }
        
        
    }
        
        
    drawscreen_ptr();
    
}


/********************************************
 *********** highlightFoundInts *************
 ********************************************/
void highlightFoundInts (){
    
    
    for (unsigned i = 0; i < intIDToHighlight.size(); i++){
        
        //get where the intersection is in LatLon then convert
        LatLon intPositionLatLon = getIntersectionPosition(intIDToHighlight[i]);
        t_point intPositionXY = latLonToXY(intPositionLatLon);
        
        std::string highlightIntName = getIntersectionName(intIDToHighlight[i]);
        
        //highlight the intersection by drawing its name and an icon
        settextrotation(0);
        draw_surface(load_png_from_file("/nfs/ug/homes-1/t/tremb101/ece297/work/mapper/libstreetmap/resources/map_pin.png"), intPositionXY.x, intPositionXY.y);
        setcolor(BLACK);
        drawtext(intPositionXY.x + 0.000001, intPositionXY.y + 0.000001, highlightIntName, 25, 25);
        
    }
    
   
    
}


/********************************************
 ********** ACT_ON_FOOD_BUTTON **************
 ********************************************/
void act_on_food_button(void (*drawscreen_ptr) (void)){
    
    numFoodButtonPress++;
    
    //allows for filters to be turned off
    if ((numFoodButtonPress % 2)  == 1){
        drawFood = true;
    } 
    else if ((numFoodButtonPress % 2) == 0){
        drawFood = false; 
    }
    
   
   
    drawscreen_ptr();
    
}

/********************************************
 ******** ACT_ON_HEALTH_BUTTON **************
 ********************************************/
void act_on_health_button(void (*drawscreen_ptr) (void)){
    
    numHealthButtonPress++;
    
    //allows for filters to be turned off
    if ((numHealthButtonPress % 2)  == 1){
        drawHealth = true;
    } 
    else if ((numHealthButtonPress % 2) == 0){
        drawHealth = false; 
    }
    
    
   
    drawscreen_ptr();
    
}


/********************************************
 ********** ACT_ON_EDU_BUTTON ***************
 ********************************************/
void act_on_edu_button(void (*drawscreen_ptr) (void)){
    
    numEduButtonPress++;
    
    //allows for filters to be turned off
    if ((numEduButtonPress % 2)  == 1){
        drawEdu = true;
    } 
    else if ((numEduButtonPress % 2) == 0){
        drawEdu = false; 
    }
    
    
   
    drawscreen_ptr();
}



/********************************************
 *********** ACT_ON_ENT_BUTTON **************
 ********************************************/
void act_on_ent_button(void (*drawscreen_ptr) (void)){

    numEntButtonPress++;
    
    //allows for filters to be turned off
    if ((numEntButtonPress % 2)  == 1){
        drawEnt = true;
    } 
    else if ((numEntButtonPress % 2) == 0){
        drawEnt = false; 
    }
    
    
    drawscreen_ptr();
    
}


/********************************************
 ************** drawFoodPOI *****************
 ********************************************/
void drawFoodPOI(){
    
        
    //iterate through the vector of food POIs to draw
    for (unsigned i = 0; i < foodPOIs.size(); i ++){
        
        //find where that POI is
        LatLon drawPosLatLon = getPointOfInterestPosition(foodPOIs[i]);
        //convert latlon position to xy 
        t_point drawPosXY = latLonToXY(drawPosLatLon);
        //draw the POI icon at that position
            
        setcolor(BLUE);
        fillarc(drawPosXY.x, drawPosXY.y, 0.0000005, 0, CIRCLE_DEGREE);
        
    }
    
}



/********************************************
 ************** drawHealthPOI ***************
 ********************************************/
void drawHealthPOI(){
    
    for (unsigned i = 0; i < healthPOIs.size(); i++){
        
        //get the location for each health POI (in LatLon then convert to Cartesian)
        LatLon drawPosLatLon = getPointOfInterestPosition(healthPOIs[i]);
        t_point drawPosXY = latLonToXY(drawPosLatLon);
        
        //draw the POI
        setcolor(RED);
        fillarc(drawPosXY.x, drawPosXY.y, 0.0000005, 0, CIRCLE_DEGREE);
    } 
    
    
}



/********************************************
 *************** drawEduPOI *****************
 ********************************************/
void drawEduPOI(){
    
    for (unsigned i = 0; i < eduPOIs.size(); i++){
        
        //get the location for each education POI (in LatLon then convert to Cartesian)
        LatLon drawPosLatLon = getPointOfInterestPosition(eduPOIs[i]);
        t_point drawPosXY = latLonToXY(drawPosLatLon);
        
        //draw the POI
        setcolor(MEDIUMPURPLE);
        fillarc(drawPosXY.x, drawPosXY.y, 0.0000005, 0, CIRCLE_DEGREE);
        
    }
    
}


/********************************************
 *************** drawEntPOI *****************
 ********************************************/
void drawEntPOI(){
    
     for (unsigned i = 0; i < entPOIs.size(); i++){
        
        //get the location for each entertainment POI (in LatLon then convert to Cartesian)
        LatLon drawPosLatLon = getPointOfInterestPosition(entPOIs[i]);
        t_point drawPosXY = latLonToXY(drawPosLatLon);
        
        //draw the POI
        setcolor(ORANGE);
        fillarc(drawPosXY.x, drawPosXY.y, 0.0000005, 0, CIRCLE_DEGREE);
        
    }
    
}


/********************************************
 ************ categorizePOIs ****************
 ********************************************/
void categorizePOIs(){
    
    //Get the information about all the points of interest
    for (unsigned i = 0; i < getNumberOfPointsOfInterest(); i++){
        
        //sort Food category
        if (getPointOfInterestType(i) == "cafe" || getPointOfInterestType(i) == "fast_food"
                || getPointOfInterestType(i) == "restaurant" || getPointOfInterestType(i) == "pub") {
            
            foodPOIs.push_back(i);
            
        }
        
        //sort Health category
        else if (getPointOfInterestType(i) == "clinic" || getPointOfInterestType(i) == "dentist"
                || getPointOfInterestType(i) == "doctors" || getPointOfInterestType(i) == "hospital"
                || getPointOfInterestType(i) == "pharmacy"){
            
            
            healthPOIs.push_back(i);
        }
        
        //sort Education category
        else if (getPointOfInterestType(i) == "college" || getPointOfInterestType(i) == "library"
                || getPointOfInterestType(i) == "school" || getPointOfInterestType(i) == "university") {
            
            
            eduPOIs.push_back(i);
        }
        
        //sort Entertainment category
        else if (getPointOfInterestType(i) == "casino" || getPointOfInterestType(i) == "cinema" 
                || getPointOfInterestType(i) == "nightclub") {
            
            entPOIs.push_back(i);
        }
    }
}

/********************************************
 ********* ACT_ON_CLEAR_BUTTON **************
 ********************************************/
void act_on_clear_button(void (*drawscreen_ptr) (void)){
    
    //stop displaying all the highlighted intersections/segments
    //by setting their bools to false
    
    //clear intersection highlighted when Find pressed
    highlightFound = false;
    
    //unhighlight all of the segments of the path
    for(unsigned i = 0; i < segmentsToHighlight.size(); i++){
        segmentsToHighlight[i] = false;
    }
    
    //clear the starting intersections highlighted when the right mouse button
    //is pressed
    for(unsigned i = 0; i < startIntersections.size(); i++){
        startIntersections[i] = false;
    }
    
    //clear the end intersections highlighted when the right mouse button
    //is pressed
    for(unsigned i = 0; i < endIntersections.size(); i++){
        endIntersections[i] = false;
    }
    
    //clear the intersections highlighted when the left mouse button is pressed
    for(unsigned i =0; i < drawnIntersections.size(); i++){
        drawnIntersections[i] = false;
    }
    
    //make the directions go away
    travelDirections.resize(0);
    
    drawscreen_ptr();
}


/********************************************
 *********** calculateMaxMinXY **************
 ********************************************/
std::vector<double> calculateMaxMinXY(){
    
    std::vector<double> tempVector;
    //avoids SEG FAULT
    tempVector.resize(4);
    
    double maxLat = getIntersectionPosition(getNumberOfIntersections()-1).lat();
    double minLat = getIntersectionPosition(0).lat();
    double maxLon = getIntersectionPosition(getNumberOfIntersections()-1).lon();
    double minLon = getIntersectionPosition(0).lon();
    
    LatLon compare;
    
    
    //for some reason that 1000 is important?
    //I think its because of the maps default settings
    for (unsigned i = 0; i < getNumberOfIntersections(); i+=1000) {
        
        compare = mapDataObject->positionInter[i];
        
       
        if (compare.lon() < minLon) {
            minLon = compare.lon();
        }
        else if (compare.lon() > maxLon) {
            maxLon = compare.lon();
        }

       if(compare.lat() < minLat){
            minLat = compare.lat();
        }
        else if(compare.lat() > maxLat){
            maxLat = compare.lat();
        }
        
        
    }

    latAvg = (maxLat + minLat) / 2.0;
    latAvg = latAvg  * DEG_TO_RAD;
    
    //parameters for the visible world
    double minimumX = minLon * DEG_TO_RAD * cos(latAvg);
    double minimumY = minLat * DEG_TO_RAD;
    double maximumX = maxLon * DEG_TO_RAD * cos(latAvg);
    double maximumY = maxLat * DEG_TO_RAD;
    
    tempVector[0] = maximumX;
    tempVector[1] = maximumY;
    tempVector[2] = minimumX;
    tempVector[3] = minimumY;
    
    return (tempVector);
     
}


/********************************************
 ************** loadNewMap ******************
 ********************************************/
void loadNewMap(){
    
    std::cout<<"Closing previous map"<<std::endl;
    close_map();
    
    std::string new_map_path;
    
    std::cout<<"Enter map path: "<<std::endl;
    std::getline (std::cin, new_map_path);
    
    bool load_success = load_map(new_map_path);
    if (!load_success){
        std::cout<<"Failed to load map "<<new_map_path<<std::endl;
    }
    
    std::cout<<"Successfully loaded map " <<new_map_path<<std::endl;
    
    mapLoadedOnce = true; 
    
    draw_map();
    
}


/********************************************
 ************ ACT_ON_MAP_BUTTON *************
 *******************************************
void act_on_map_button(void (*drawscreen_ptr) (void)){
    
   
    loadNewMap();
    
}

*/
/********************************************
 ************* DRAWFEATURES *****************
 ********************************************/

void drawFeatures(){
    
    
    //draw Lakes
    for (unsigned i = 0; i < drawLakes.size(); i++) {
        setcolor(WATER);

        //make vector into array of features
        t_point* cartesianArray;
        cartesianArray = &drawLakes.at(i)[0];
        fillpoly(cartesianArray, drawLakes[i].size());
    }


    for (unsigned i = 0; i < drawBeaches.size(); i++) {
        setcolor(SAND);

        //make vector into an array of features
        t_point* cartesianArray;
        cartesianArray = &drawBeaches.at(i)[0];
        fillpoly(cartesianArray, drawBeaches[i].size());
    }


    for (unsigned i = 0; i < drawIslands.size(); i++) {
        setcolor(ISLAND);

        //make vector into array of features
        t_point* cartesianArray;
        cartesianArray = &drawIslands.at(i)[0];
        fillpoly(cartesianArray, drawIslands[i].size());
    }

    for (unsigned i = 0; i < drawParks.size(); i++) {
        setcolor(GRASS);

        //make vector into array of features
        t_point* cartesianArray;
        cartesianArray = &drawParks.at(i)[0];
        fillpoly(cartesianArray, drawParks[i].size());
    }

    if(zoomLevel > 4){
    //draw buildings
    for (unsigned i = 0; i < drawBuildings.size(); i++) {
        setcolor(BUILDING);

        //make vector into array of features
        t_point* cartesianArray;
        cartesianArray = &drawBuildings.at(i)[0];
        fillpoly(cartesianArray, drawBuildings[i].size());
    }
    }

    //draw golf courses
    for (unsigned i = 0; i < drawGolfCourses.size(); i++) {
        setcolor(GOLFGREEN);

        //make vector into array of features
        t_point* cartesianArray;
        cartesianArray = &drawGolfCourses.at(i)[0];
        fillpoly(cartesianArray, drawGolfCourses[i].size());
    }

    //draw greenspaces
    for (unsigned i = 0; i < drawGreenspaces.size(); i++) {
        setcolor(GREENSPACE);

        //make vector into array of features
        t_point* cartesianArray;
        cartesianArray = &drawGreenspaces.at(i)[0];
        fillpoly(cartesianArray, drawGreenspaces[i].size());
    }

    for (unsigned i = 0; i < drawRivers.size(); i++) {
        setlinewidth(3);
        setcolor(WATER);

        //create lines between each latlon coordinate
        for (unsigned j = 0; j < (drawRivers[i].size() - 1); j++) {
            betweenLatLon(drawRivers[i].at(j), drawRivers[i].at(j + 1));
        }
    }

    for (unsigned i = 0; i < drawStreams.size(); i++) {
        setlinewidth(1);
        setcolor(WATER);

        //create lines between each latlon coordinate
        for (unsigned j = 0; j < (drawStreams[i].size() - 1); j++) 
            betweenLatLon(drawStreams[i].at(j), drawStreams[i].at(j + 1));
    }
    }


/********************************************
 ************ ACT_ON_HELP_BUTTON *************
 ********************************************

void act_on_help_button(void(*drawscreen_ptr) (void)){
    
    //instructions describing how to use the map
    std::cout<<"Welcome to the map!"<<std::endl;
    std::cout<<"The following commands are available: "<<std::endl;
    std::cout<<"> Click 'Find' to search for an intersection or POI"<<std::endl;
    std::cout<<"> Click 'Food', 'Health', 'Education', or 'Entertainment'"
            "to filter Points of Interest"<<std::endl;
    std::cout<<"> Click Change Map to view a new city"<<std::endl;
    std::cout<<"> Left click to find the nearest intersection"<<std::endl;
    std::cout<<"> Right click two intersections to find directions"<<std::endl;
    std::cout<<"> Click 'Clear' to clear the map"<<std::endl;
    
    
    drawscreen_ptr();
}
*/


/********************************************
 ************ DRAWDIRECTIONS ****************
 ********************************************/

void drawDirections(std::vector<string> directions){
    
    set_coordinate_system(GL_SCREEN);
    
    settextrotation(0);
    
    //bottom left & top right screen locations of the first box holding 
    //travel directions
    float bottomLeftXDirec = 0;
    float bottomLeftYDirec = 90;
    float topRightXDirec = 350;
    float topRightYDirec = 20;
    
    //centre of the first box holding travel directions
    float xCentreDirec = 175;
    float yCentreDirec = 55;
    
    //botton left & top right screen locations fo the box holding the 
    //title "Travel Directions"
    float bottomLeftXTitle = 0;
    float bottomLeftYTitle = 20;
    float topRightXTitle = 350;
    float topRightYTitle = 0;
    
    //cnetre of the box holding the title "Travel Directions"
    float xCentreTitle = 175;
    float yCentreTitle = 10;
    
    t_point titleCentre(xCentreTitle, yCentreTitle);
    
    
    if(directions.size() != 0){
    setcolor(WATER);
    drawrect(bottomLeftXTitle, bottomLeftYTitle, topRightXTitle, topRightYTitle);
    fillrect(bottomLeftXTitle, bottomLeftYTitle, topRightXTitle, topRightYTitle);
    
    //draw the text overtop of the box
    setcolor(WHITE);
    drawtext(titleCentre, "Travel Directions");
    }
  
    //keep drawing boxes below one another for every travel direction that there is
    for (unsigned i = 0; i < directions.size(); i++){
        //draw a white transparent bachkground
        setcolor(255,255,255,180);
        fillrect(bottomLeftXDirec , bottomLeftYDirec , topRightXDirec , topRightYDirec);
        
        //draw white border
        setcolor(WHITE);
        drawrect(bottomLeftXDirec , bottomLeftYDirec , topRightXDirec , topRightYDirec);
        
        //draw text passed in string vector
        t_point boxCentre(xCentreDirec, yCentreDirec);
        setcolor(BLACK);
        drawtext(boxCentre, directions[i]);
        
        bottomLeftYDirec += 70;
        topRightYDirec += 70;
        
        yCentreDirec += 70;
        
        
    }
}

void drawHelpIcon(){
    
    set_coordinate_system(GL_SCREEN);
    
    //draw information icon
    draw_surface(load_png_from_file("/nfs/ug/homes-3/p/papajan6/ece297/work/mapper/libstreetmap/resources/help.png"), 8, 875);
        
    if(clickedHelp){
            
        drawHelp();
            
        }
    
    set_coordinate_system(GL_WORLD);
    copy_off_screen_buffer_to_screen();
    
}

void drawHelp(){
    
    set_coordinate_system(GL_SCREEN);
    
    //creating textbox
    setlinestyle(SOLID);
    setcolor(t_color(255,255,255,180));
    drawrect(60, 750 , 400, 800);
    setcolor(t_color(255,255,255,180));
    fillrect(61, 649, 399, 799);
    setfontsize(10);

    //initalize title to be black
    setcolor(BLACK);
    
    //words to appear on screen
    string textOutput1 = "Welcome to OurMap!";
    string textOutput2 = "The following commands are available:";
    string textOutput3 = "> Click 'Find' to search for an intersection or POI.";
    string textOutput4 = "> Click 'Food', 'Health', 'Education',";
    string textOutput5 = "or 'Entertainment'to filter Points of Interest.";
    string textOutput6 = "> Click Change Map to view a new city";
    string textOutput7 = "> Left click to find the nearest intersection ";
    string textOutput8 = "> Right click two intersections to find directions";
    string textOutput9 = "> Click 'Clear' to clear the map";
                 

    //make t box for each line of text
    t_bound_box outputTBoundBox1    = t_bound_box(60, 510, 405, 805);
    t_bound_box outputTBoundBox2    = t_bound_box(60, 545, 400, 805);
    t_bound_box outputTBoundBox3    = t_bound_box(60, 565, 400, 815);
    t_bound_box outputTBoundBox4    = t_bound_box(60, 585, 400, 825);
    t_bound_box outputTBoundBox5    = t_bound_box(60, 595, 400, 845);
    t_bound_box outputTBoundBox6    = t_bound_box(60, 605, 400, 865);
    t_bound_box outputTBoundBox7    = t_bound_box(60, 625, 400, 875);
    t_bound_box outputTBoundBox8    = t_bound_box(60, 645, 400, 885);
    t_bound_box outputTBoundBox9    = t_bound_box(60, 656, 400, 900);

    // write out each line of text, alternate colours for headings and body text
    drawtext_in(outputTBoundBox1, textOutput1);
    
    //make other text after title grey
    setcolor(t_color(0x70, 0x6F, 0x6E));
    drawtext_in(outputTBoundBox2, textOutput2);
    drawtext_in(outputTBoundBox3, textOutput3);
    drawtext_in(outputTBoundBox4, textOutput4);
    drawtext_in(outputTBoundBox5, textOutput5);
    drawtext_in(outputTBoundBox6, textOutput6);
    drawtext_in(outputTBoundBox7, textOutput7);
    drawtext_in(outputTBoundBox8, textOutput8);
    drawtext_in(outputTBoundBox9, textOutput9);
   
    return;
    
}
