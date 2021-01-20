/*#include <algorithm>
#include <set>
#include <unittest++/UnitTest++.h>
#include "m1.h"
#include "unit_test_util.h"
#include "StreetsDatabaseAPI.h"
#include <iostream>

#include <vector>

using ece297test::relative_error;


    
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


SUITE(street_queries_public_toronto_canada) {
    TEST_FIXTURE(MapFixture, street_street_segments) {
        std::vector<unsigned> expected;
        std::vector<unsigned> actual;
        
        expected = {2, 9542, 9543, 16187, 16188};
        actual = find_street_street_segments(2);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {14984, 14987, 130539};
        actual = find_street_street_segments(3791);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {16344, 16345, 68447};
        actual = find_street_street_segments(4118);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {19163, 19164, 19165, 84068, 84865};
        actual = find_street_street_segments(4893);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {21257};
        actual = find_street_street_segments(5414);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {22140};
        actual = find_street_street_segments(5701);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {23148};
        actual = find_street_street_segments(5903);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {48380};
        actual = find_street_street_segments(9098);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {52160};
        actual = find_street_street_segments(10487);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {55944};
        actual = find_street_street_segments(11357);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {56794};
        actual = find_street_street_segments(11564);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {58761};
        actual = find_street_street_segments(12077);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {59363};
        actual = find_street_street_segments(12181);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {65197, 65201, 65259, 65260, 65261, 65266, 65302, 65307, 78070};
        actual = find_street_street_segments(13368);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {69652, 69655, 69667, 69668};
        actual = find_street_street_segments(14321);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {70222, 70223, 70224, 70226};
        actual = find_street_street_segments(14456);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {71790, 71798, 71799, 71801, 71805};
        actual = find_street_street_segments(14823);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {72743};
        actual = find_street_street_segments(14953);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {74465, 74496, 74549, 74658, 74835, 74854, 74928, 74956, 74964, 74966, 75012, 75013, 75188};
        actual = find_street_street_segments(15291);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {76910};
        actual = find_street_street_segments(15846);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {79764};
        actual = find_street_street_segments(16463);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {80816, 80847, 80859, 80874, 80875, 80876};
        actual = find_street_street_segments(16738);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {81945, 81946, 81947, 81948};
        actual = find_street_street_segments(17063);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {95171};
        actual = find_street_street_segments(18719);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {95613, 95712};
        actual = find_street_street_segments(18773);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {96768, 96784, 96785, 96786, 96802, 96803, 96808};
        actual = find_street_street_segments(18915);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {100936};
        actual = find_street_street_segments(19096);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {101527, 101528, 101529};
        actual = find_street_street_segments(19181);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {118605, 128569, 128570};
        actual = find_street_street_segments(20351);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {140321, 140322};
        actual = find_street_street_segments(20909);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
    } //street_street_segments

    TEST_FIXTURE(MapFixture, all_street_intersections) {
        std::vector<unsigned> expected;
        std::vector<unsigned> actual;
        
        expected = {3, 4, 10371, 10372, 16929, 16930};
        actual = find_all_street_intersections(2);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {893, 1717, 25346, 31186, 64484, 64640, 64737, 64738, 64839, 65008, 65025, 65026, 65069, 65081};
        actual = find_all_street_intersections(15291);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {6530, 21891};
        actual = find_all_street_intersections(11357);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {15418, 15424, 15427, 61743, 61744};
        actual = find_all_street_intersections(14456);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {15806, 15807, 15812, 15813};
        actual = find_all_street_intersections(3791);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {16200, 16201, 16202, 19964, 19965, 19966};
        actual = find_all_street_intersections(4893);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {17103, 17104, 17105, 60617};
        actual = find_all_street_intersections(4118);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {17996, 101669};
        actual = find_all_street_intersections(20909);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {22003, 22004};
        actual = find_all_street_intersections(5414);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {22808, 61409, 61410, 61411, 61418};
        actual = find_all_street_intersections(14321);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {22919, 22921};
        actual = find_all_street_intersections(5701);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {23884, 23889};
        actual = find_all_street_intersections(5903);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {29398, 50561, 58475, 58476, 58479, 58506, 58511, 58512, 58513};
        actual = find_all_street_intersections(13368);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {39426, 39428, 68882, 68884, 68896, 68897, 68920};
        actual = find_all_street_intersections(16738);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {40762, 40766, 69636, 69640, 69642};
        actual = find_all_street_intersections(17063);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {45837};
        actual = find_all_street_intersections(9098);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {47523, 49356};
        actual = find_all_street_intersections(10487);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {48410, 63383};
        actual = find_all_street_intersections(14953);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {48443, 72290};
        actual = find_all_street_intersections(19096);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {49530, 78720, 78737, 78741, 78750, 78756, 78757, 78760};
        actual = find_all_street_intersections(18915);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {52835, 52836};
        actual = find_all_street_intersections(11564);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {54263, 54264};
        actual = find_all_street_intersections(12077);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {54619, 54620};
        actual = find_all_street_intersections(12181);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {62779, 62783, 62789, 62791, 62792, 62793};
        actual = find_all_street_intersections(14823);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {66263, 66264};
        actual = find_all_street_intersections(15846);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {68161, 68179};
        actual = find_all_street_intersections(16463);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {77747, 77761};
        actual = find_all_street_intersections(18719);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {77957, 78074, 78075};
        actual = find_all_street_intersections(18773);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {81498, 81499, 81500, 81501};
        actual = find_all_street_intersections(19181);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {90773, 90775, 90776, 90791};
        actual = find_all_street_intersections(20351);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
    } //all_street_intersections

    TEST_FIXTURE(MapFixture, intersection_ids_from_street_names) {
        std::vector<unsigned> expected;
        std::vector<unsigned> actual;
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Airdrie Drive", "Siberry Road");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Belinda Square", "Vescovo Road");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Blossomfield Road", "Breckenridge Road");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Brow Drive", "Wells Place");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Cassels Avenue", "Gardiner Crescent");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Cunard Street", "Gleda Crescent");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Duncairn Drive", "Spears Street");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Fourteenth Avenue", "Aymarn Court");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Herzberg Gardens", "Haas Road");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Kittredge Court", "Hunters Glen");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Livingston Road", "Meeting House Road");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Roxborough Drive", "Pluto Drive");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Shires Lane", "To Rexdale Boulevard west");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Welsh Street", "Waterloo Avenue");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Wyandot Avenue", "Chelwood Road");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {4};
        actual = find_intersection_ids_from_street_names("Highway 401 Eastbound Express", "Switchover to Highway 401 Eastbound Express lanes");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {15813};
        actual = find_intersection_ids_from_street_names("Woodside Avenue", "Fairview Avenue");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {16200, 16201, 16202};
        actual = find_intersection_ids_from_street_names("Forest Glen Crescent", "<unknown>");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {21891};
        actual = find_intersection_ids_from_street_names("Highways 27, 401, 427", "Eglinton Avenue West");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {22808, 61418};
        actual = find_intersection_ids_from_street_names("Vaughan Boulevard", "Centre Street");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {23889};
        actual = find_intersection_ids_from_street_names("Rondeen Road", "Ten Oaks Boulevard");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {25911};
        actual = find_intersection_ids_from_street_names("Bridgewood Drive", "Bloor Street");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {40088};
        actual = find_intersection_ids_from_street_names("Northgate Boulevard", "Northampton Street");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {47030};
        actual = find_intersection_ids_from_street_names("Mojave Crescent", "Rocksprings Avenue");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {52835, 52836};
        actual = find_intersection_ids_from_street_names("Fawndale Crescent", "Huntsmill Boulevard");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {54620};
        actual = find_intersection_ids_from_street_names("Townley Avenue", "Bellvare Crescent");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {63383};
        actual = find_intersection_ids_from_street_names("Ardmore Crescent", "Hillholm Boulevard");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {66263};
        actual = find_intersection_ids_from_street_names("Blue Beech Crescent", "Council Ring Road");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {68235};
        actual = find_intersection_ids_from_street_names("Barberry Lane", "Old Mill Lane");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {83973};
        actual = find_intersection_ids_from_street_names("Little Hannah Lane", "Sir Francesco Street");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
    } //intersection_ids_from_street_names

} //street_queries_public_toronto_canada

*/