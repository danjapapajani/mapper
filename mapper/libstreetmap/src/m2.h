/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   m2.h
 * Author: papajan6
 *
 * Created on February 19, 2018, 7:19 PM
 */

#ifndef M2_H
#define M2_H

#include "m1.h"
#include "m2.h"
#include "StreetsDatabaseAPI.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include "mapDataStruct.h"
#include <math.h>
#include "OSMDatabaseAPI.h"
#include "graphics.h"
#include "Feature.h"
#include <map>
#include <X11/keysym.h>

//sets up the graphics window (creates buttons and sets the visible world)
void draw_map();

//draws the streets/features/POIs of the map
void draw_screen();

//draws a straight line between given LatLon points
void betweenLatLon(LatLon x, LatLon y);

//converst Latitude & longitude to Cartesian coordinates
t_point latLonToXY(LatLon point);

//draw the roads classified by OSM as major roads
void drawMajorRoad(int width);

//draw the roads classified by OSM as highways
void drawHighways(int width);

//draw the roads classified by OSM as minor roads
void drawMinorRoad(int width);

//draw a curved line for each street segment
void drawStreetSegment(unsigned ID);

void drawStreetName(unsigned segID, unsigned zoom);

double findStreetStreetNameAngle(unsigned segID);

//loads features that will be reused in draw_screen
void loadMapFeatures();

//calculate the angle to display the street name
double findStreetNameAngle(t_point from, t_point to);

//Based on user's mouse clicks, display the map differently
//If intersection is clicked, highlight the intersection & print the intersection name
//display poi name if clicked on 
void act_on_button_press(float x, float y, t_event_buttonPressed event);

void act_on_mouse_move(float x, float y);

//convert cartesian x coordinate to longitude
float cartesianToLongitude (float x);

//draw a yellow circle indicating a point of interest
void drawPOIs();

//When Find is pressed, take in user inputted street names and find the intersection(s)
void act_on_find_button(void (*drawscreen_ptr)(void)); 

//highlight all of the intersections for the inputted streets (for Find button)
void highlightFoundInts ();

//When Food button pressed, draw or undraw the food POIs
void act_on_food_button(void (*drawscreen_ptr) (void)); 

//Draws all the food related POIs on the map 
void drawFoodPOI();
void categorizePOIs();

//Draws all the health related POIs on the map 
void drawHealthPOI();

//When Health button pressed, draw or undraw the health POIs
void act_on_health_button(void (*drawscreen_ptr) (void)); 

//When Education button pressed, draw or undraw the education POIs
void act_on_edu_button(void (*drawscreen_ptr) (void)); 

//draw the Education POIs
void drawEduPOI();

//When Entertainment button pressed, draw or undraw the entertainment POIs
void act_on_ent_button(void (*drawscreen_ptr) (void)); 

//draw the Entertainment POIs
void drawEntPOI();

//clear the whole screen when pressed
void act_on_clear_button(void (*drawscreen_ptr) (void)); 

//called when the Change Map button is pressed and prompts the user to enter
//a new map
void loadNewMap();

//when Change Map button pressed, calls loadNewMap function
void act_on_map_button(void (*drawscreen_ptr) (void)); 

//calculates the corner coordinates for the given map (to be used in set_visible_world)
std::vector<double> calculateMaxMinXY();

//draw the directions on screen 
void drawDirections(std::vector<string> directions);

//create a search bar
void drawHelpIcon();

//draw help text
void drawHelp();

void drawFeatures();
void zoomLevel0();
void zoomLevel1();
void zoomLevel2();
void zoomLevel3();
void zoomLevel4();
void zoomLevel5();
void zoomLevel6();
void zoomLevel7();
void zoomLevel8();
void zoomLevel9();
void zoomLevel10();
void zoomLevel11();
void zoomLevel12();


#endif /* M2_H */

