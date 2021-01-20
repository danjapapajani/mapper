/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 *
 */
/*
#include <unittest++/UnitTest++.h>
#include "m1.h"
#include "StreetsDatabaseAPI.h"
#include <algorithm>
#include "unit_test_util.h"
using namespace std;

struct MapFixture {
    MapFixture() {
        //Load the map
        load_map("/cad2/ece297s/public/maps/toronto_canada.streets.bin");
    }

    ~MapFixture() {
        //Clean-up
        close_map();
    }
};

TEST_FIXTURE(MapFixture, street_ids_from_name){
    
        UNITTEST_TIME_CONSTRAINT(0.000250*getNumberOfStreets());
        vector<unsigned> expectedIDs;
        vector<unsigned> actualIDs;
        string expectedName;
        string actualName;
        
        for (unsigned i = 0; i < getNumberOfStreets(); i++){
            expectedName = getStreetName(i);
            actualIDs = find_street_ids_from_name(expectedName);
            
            for (unsigned j = 0; j < actualIDs.size(); j++){
                actualName = getStreetName(actualIDs[j]);
                CHECK_EQUAL(expectedName, actualName);
                
             
            }  
        }
    
}
*/

