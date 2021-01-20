/*#include <algorithm>
#include <set>
#include <random>
#include <unittest++/UnitTest++.h>
#include "unit_test_util.h"
#include "m1.h"
#include "StreetsDatabaseAPI.h"

using ece297test::relative_error;

struct MapFixture {
    MapFixture() {
        //Load the map
        load_map("/cad2/ece297s/public/maps/toronto_canada.streets.bin");

        //Initialize random number generators
        rng = std::minstd_rand(3);
        rand_intersection = std::uniform_int_distribution<unsigned>(0, getNumberOfIntersections()-1);
        rand_street = std::uniform_int_distribution<unsigned>(1, getNumberOfStreets()-1);
        rand_segment = std::uniform_int_distribution<unsigned>(0, getNumberOfStreetSegments()-1);
        rand_poi = std::uniform_int_distribution<unsigned>(0, getNumberOfPointsOfInterest()-1);
        rand_lat = std::uniform_real_distribution<double>(43.48, 43.91998);
        rand_lon = std::uniform_real_distribution<double>(-79.78998, -79.00001);
    }

    ~MapFixture() {
        //Clean-up
        close_map();
    }

    std::minstd_rand rng;
    std::uniform_int_distribution<unsigned> rand_intersection;
    std::uniform_int_distribution<unsigned> rand_street;
    std::uniform_int_distribution<unsigned> rand_segment;
    std::uniform_int_distribution<unsigned> rand_poi;
    std::uniform_real_distribution<double> rand_lat;
    std::uniform_real_distribution<double> rand_lon;
};

SUITE(spatial_queries_perf_public_toronto_canada) {
    TEST_FIXTURE(MapFixture, closest_poi_perf) {
        //Verify Functionality
        std::set<unsigned> valid_results;
        unsigned actual;
        
        valid_results = {368};
        actual = find_closest_point_of_interest(LatLon(43.64250946044922, -79.35969543457031));
        CHECK(valid_results.count(actual));
        
        valid_results = {723};
        actual = find_closest_point_of_interest(LatLon(43.71545028686523, -79.45131683349609));
        CHECK(valid_results.count(actual));
        
        valid_results = {1091};
        actual = find_closest_point_of_interest(LatLon(43.85248184204102, -79.43147277832031));
        CHECK(valid_results.count(actual));
        
        valid_results = {1098};
        actual = find_closest_point_of_interest(LatLon(43.77970123291016, -79.60785675048828));
        CHECK(valid_results.count(actual));
        
        valid_results = {1126};
        actual = find_closest_point_of_interest(LatLon(43.8380126953125, -79.22557830810547));
        CHECK(valid_results.count(actual));
        
        valid_results = {1224};
        actual = find_closest_point_of_interest(LatLon(43.77691268920898, -79.58845520019531));
        CHECK(valid_results.count(actual));
        
        valid_results = {1455};
        actual = find_closest_point_of_interest(LatLon(43.65697860717773, -79.70158386230469));
        CHECK(valid_results.count(actual));
        
        valid_results = {2434};
        actual = find_closest_point_of_interest(LatLon(43.56536483764648, -79.34043121337891));
        CHECK(valid_results.count(actual));
        
        valid_results = {2489};
        actual = find_closest_point_of_interest(LatLon(43.71529388427734, -79.55553436279297));
        CHECK(valid_results.count(actual));
        
        valid_results = {4203, 5753};
        actual = find_closest_point_of_interest(LatLon(43.74922943115234, -79.02179718017578));
        CHECK(valid_results.count(actual));
        
        valid_results = {4982};
        actual = find_closest_point_of_interest(LatLon(43.77373886108398, -79.47676086425781));
        CHECK(valid_results.count(actual));
        
        valid_results = {5037};
        actual = find_closest_point_of_interest(LatLon(43.7193603515625, -79.52051544189453));
        CHECK(valid_results.count(actual));
        
        valid_results = {5208};
        actual = find_closest_point_of_interest(LatLon(43.87590789794922, -79.01165771484375));
        CHECK(valid_results.count(actual));
        
        valid_results = {5228};
        actual = find_closest_point_of_interest(LatLon(43.5703125, -79.68901062011719));
        CHECK(valid_results.count(actual));
        
        valid_results = {5506};
        actual = find_closest_point_of_interest(LatLon(43.87495422363281, -79.56262969970703));
        CHECK(valid_results.count(actual));
        
        valid_results = {5516};
        actual = find_closest_point_of_interest(LatLon(43.90193939208984, -79.57024383544922));
        CHECK(valid_results.count(actual));
        
        valid_results = {6005};
        actual = find_closest_point_of_interest(LatLon(43.56804275512695, -79.77233123779297));
        CHECK(valid_results.count(actual));
        
        valid_results = {6118};
        actual = find_closest_point_of_interest(LatLon(43.69831466674805, -79.65619659423828));
        CHECK(valid_results.count(actual));
        
        valid_results = {6409};
        actual = find_closest_point_of_interest(LatLon(43.7325325012207, -79.09117126464844));
        CHECK(valid_results.count(actual));
        
        valid_results = {6498};
        actual = find_closest_point_of_interest(LatLon(43.81575393676758, -79.77579498291016));
        CHECK(valid_results.count(actual));
        
        valid_results = {6687};
        actual = find_closest_point_of_interest(LatLon(43.48199844360352, -79.40149688720703));
        CHECK(valid_results.count(actual));
        
        valid_results = {6687};
        actual = find_closest_point_of_interest(LatLon(43.59196853637695, -79.37844085693359));
        CHECK(valid_results.count(actual));
        
        valid_results = {6848};
        actual = find_closest_point_of_interest(LatLon(43.82280349731445, -79.18561553955078));
        CHECK(valid_results.count(actual));
        
        valid_results = {6941};
        actual = find_closest_point_of_interest(LatLon(43.71036148071289, -79.60934448242188));
        CHECK(valid_results.count(actual));
        
        valid_results = {7207};
        actual = find_closest_point_of_interest(LatLon(43.73324203491211, -79.53833770751953));
        CHECK(valid_results.count(actual));
        
        valid_results = {7337};
        actual = find_closest_point_of_interest(LatLon(43.83701705932617, -79.14602661132812));
        CHECK(valid_results.count(actual));
        
        valid_results = {8278};
        actual = find_closest_point_of_interest(LatLon(43.58732604980469, -79.09316253662109));
        CHECK(valid_results.count(actual));
        
        valid_results = {8392};
        actual = find_closest_point_of_interest(LatLon(43.60358428955078, -79.29006958007812));
        CHECK(valid_results.count(actual));
        
        valid_results = {8427};
        actual = find_closest_point_of_interest(LatLon(43.91736602783203, -79.71571350097656));
        CHECK(valid_results.count(actual));
        
        valid_results = {8455};
        actual = find_closest_point_of_interest(LatLon(43.89463424682617, -79.20743560791016));
        CHECK(valid_results.count(actual));
        
        //Generate random inputs
        std::vector<LatLon> latlons;
        for(size_t i = 0; i < 15000; i++) {
            latlons.push_back(LatLon(rand_lat(rng), rand_lon(rng)));
        }
        {
            //Timed Test
            ECE297_TIME_CONSTRAINT(970);
            unsigned result;
            for(size_t i = 0; i < 15000; i++) {
                result += find_closest_point_of_interest(latlons[i]);
            }
        }
    } //closest_poi_perf

    TEST_FIXTURE(MapFixture, closest_intersection_perf) {
        //Verify Functionality
        std::set<unsigned> valid_results;
        unsigned actual;
        
        valid_results = {2136};
        actual = find_closest_intersection(LatLon(43.7193603515625, -79.52051544189453));
        CHECK(valid_results.count(actual));
        
        valid_results = {4253};
        actual = find_closest_intersection(LatLon(43.77373886108398, -79.47676086425781));
        CHECK(valid_results.count(actual));
        
        valid_results = {6084, 6093, 6100, 6101, 97673};
        actual = find_closest_intersection(LatLon(43.48199844360352, -79.40149688720703));
        CHECK(valid_results.count(actual));
        
        valid_results = {7137};
        actual = find_closest_intersection(LatLon(43.7325325012207, -79.09117126464844));
        CHECK(valid_results.count(actual));
        
        valid_results = {10260};
        actual = find_closest_intersection(LatLon(43.82280349731445, -79.18561553955078));
        CHECK(valid_results.count(actual));
        
        valid_results = {10432};
        actual = find_closest_intersection(LatLon(43.83701705932617, -79.14602661132812));
        CHECK(valid_results.count(actual));
        
        valid_results = {10545};
        actual = find_closest_intersection(LatLon(43.60358428955078, -79.29006958007812));
        CHECK(valid_results.count(actual));
        
        valid_results = {10549};
        actual = find_closest_intersection(LatLon(43.56536483764648, -79.34043121337891));
        CHECK(valid_results.count(actual));
        
        valid_results = {21784};
        actual = find_closest_intersection(LatLon(43.71036148071289, -79.60934448242188));
        CHECK(valid_results.count(actual));
        
        valid_results = {28348};
        actual = find_closest_intersection(LatLon(43.71545028686523, -79.45131683349609));
        CHECK(valid_results.count(actual));
        
        valid_results = {34716};
        actual = find_closest_intersection(LatLon(43.69831466674805, -79.65619659423828));
        CHECK(valid_results.count(actual));
        
        valid_results = {41421};
        actual = find_closest_intersection(LatLon(43.90193939208984, -79.57024383544922));
        CHECK(valid_results.count(actual));
        
        valid_results = {42815};
        actual = find_closest_intersection(LatLon(43.90982437133789, -79.60358428955078));
        CHECK(valid_results.count(actual));
        
        valid_results = {42935};
        actual = find_closest_intersection(LatLon(43.77970123291016, -79.60785675048828));
        CHECK(valid_results.count(actual));
        
        valid_results = {43170};
        actual = find_closest_intersection(LatLon(43.91736602783203, -79.71571350097656));
        CHECK(valid_results.count(actual));
        
        valid_results = {43259};
        actual = find_closest_intersection(LatLon(43.81575393676758, -79.77579498291016));
        CHECK(valid_results.count(actual));
        
        valid_results = {43659};
        actual = find_closest_intersection(LatLon(43.77691268920898, -79.58845520019531));
        CHECK(valid_results.count(actual));
        
        valid_results = {45565, 96913};
        actual = find_closest_intersection(LatLon(43.74922943115234, -79.02179718017578));
        CHECK(valid_results.count(actual));
        
        valid_results = {57597};
        actual = find_closest_intersection(LatLon(43.73324203491211, -79.53833770751953));
        CHECK(valid_results.count(actual));
        
        valid_results = {65218};
        actual = find_closest_intersection(LatLon(43.56804275512695, -79.77233123779297));
        CHECK(valid_results.count(actual));
        
        valid_results = {66201};
        actual = find_closest_intersection(LatLon(43.5703125, -79.68901062011719));
        CHECK(valid_results.count(actual));
        
        valid_results = {71302};
        actual = find_closest_intersection(LatLon(43.58732604980469, -79.09316253662109));
        CHECK(valid_results.count(actual));
        
        valid_results = {71564};
        actual = find_closest_intersection(LatLon(43.71529388427734, -79.55553436279297));
        CHECK(valid_results.count(actual));
        
        valid_results = {75116};
        actual = find_closest_intersection(LatLon(43.8380126953125, -79.22557830810547));
        CHECK(valid_results.count(actual));
        
        valid_results = {83449};
        actual = find_closest_intersection(LatLon(43.87590789794922, -79.01165771484375));
        CHECK(valid_results.count(actual));
        
        valid_results = {83714};
        actual = find_closest_intersection(LatLon(43.89463424682617, -79.20743560791016));
        CHECK(valid_results.count(actual));
        
        valid_results = {87011};
        actual = find_closest_intersection(LatLon(43.85248184204102, -79.43147277832031));
        CHECK(valid_results.count(actual));
        
        valid_results = {91612};
        actual = find_closest_intersection(LatLon(43.87495422363281, -79.56262969970703));
        CHECK(valid_results.count(actual));
        
        valid_results = {103748};
        actual = find_closest_intersection(LatLon(43.65697860717773, -79.70158386230469));
        CHECK(valid_results.count(actual));
        
        valid_results = {107411};
        actual = find_closest_intersection(LatLon(43.64250946044922, -79.35969543457031));
        CHECK(valid_results.count(actual));
        
        //Generate random inputs
        std::vector<LatLon> latlons;
        for(size_t i = 0; i < 3000; i++) {
            latlons.push_back(LatLon(rand_lat(rng), rand_lon(rng)));
        }
        {
            //Timed Test
            ECE297_TIME_CONSTRAINT(985);
            unsigned result;
            for(size_t i = 0; i < 3000; i++) {
                result += find_closest_intersection(latlons[i]);
            }
        }
    } //closest_intersection_perf

} //spatial_queries_perf_public_toronto_canada

*/