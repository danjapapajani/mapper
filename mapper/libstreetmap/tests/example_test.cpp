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
#include <random>
#include <iostream>
#include <unittest++/UnitTest++.h>

#include "StreetsDatabaseAPI.h"
#include "m1.h"
#include "m3.h"
#include "m4.h"

#include "unit_test_util.h"
#include "courier_verify.h"

using ece297test::relative_error;
using ece297test::courier_path_is_legal;


struct MapFixture {
    MapFixture() {
        //Load the map
        load_map("/cad2/ece297s/public/maps/saint-helena.streets.bin");
    }

    ~MapFixture() {
        //Clean-up
        close_map();
    }
};


SUITE(simple_legality_toronto_canada_public) {
    TEST_FIXTURE(MapFixture,simple_legality_toronto_canada) {
        std::vector<DeliveryInfo> deliveries;
        std::vector<unsigned> depots;
        std::vector<unsigned> result_path;
        float turn_penalty;
        
        deliveries = {DeliveryInfo(243, 167), DeliveryInfo(326, 295), DeliveryInfo(167, 96), DeliveryInfo(273,62), DeliveryInfo(314,324)};
        depots = {307, 101, 189};
        turn_penalty = 15;
       
        result_path = traveling_courier(deliveries, depots, turn_penalty);
        
        CHECK(courier_path_is_legal(deliveries, depots, result_path));
        
        
        
        
    } //simple_legality_toronto_canada

} //simple_legality_toronto_canada_public
