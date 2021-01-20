/*#include <algorithm>
#include <set>
#include <unittest++/UnitTest++.h>
#include "m1.h"
#include "unit_test_util.h"
#include "StreetsDatabaseAPI.h"

using ece297test::relative_error;

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


SUITE(street_queries_public_saint_helena) {
    TEST_FIXTURE(MapFixture, street_street_segments) {
        std::vector<unsigned> expected;
        std::vector<unsigned> actual;
        
        expected = {49};
        actual = find_street_street_segments(1);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {61};
        actual = find_street_street_segments(2);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {62, 63};
        actual = find_street_street_segments(3);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {138, 174, 175};
        actual = find_street_street_segments(4);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {190, 306, 319};
        actual = find_street_street_segments(5);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214};
        actual = find_street_street_segments(6);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {215, 295};
        actual = find_street_street_segments(7);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {255, 256, 257, 258};
        actual = find_street_street_segments(8);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {296};
        actual = find_street_street_segments(9);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {297, 298};
        actual = find_street_street_segments(10);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {299};
        actual = find_street_street_segments(11);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {300, 301};
        actual = find_street_street_segments(12);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {307, 308};
        actual = find_street_street_segments(13);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {316};
        actual = find_street_street_segments(15);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {317, 318};
        actual = find_street_street_segments(16);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
    } //street_street_segments

    TEST_FIXTURE(MapFixture, all_street_intersections) {
        std::vector<unsigned> expected;
        std::vector<unsigned> actual;
        
        expected = {60, 61};
        actual = find_all_street_intersections(1);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {60, 311};
        actual = find_all_street_intersections(11);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {62, 66};
        actual = find_all_street_intersections(9);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {62, 286, 287, 288, 289};
        actual = find_all_street_intersections(8);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {63, 309, 310};
        actual = find_all_street_intersections(10);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {64, 230, 231, 299};
        actual = find_all_street_intersections(5);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {90, 91};
        actual = find_all_street_intersections(2);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {92, 93, 94};
        actual = find_all_street_intersections(3);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {105, 208, 250};
        actual = find_all_street_intersections(7);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {155, 182, 221, 229, 234, 235, 237, 239, 241, 242, 243, 244, 245, 246, 247, 248, 249};
        actual = find_all_street_intersections(6);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {180, 181, 211, 212};
        actual = find_all_street_intersections(4);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {289, 309, 311};
        actual = find_all_street_intersections(16);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {311, 315, 317};
        actual = find_all_street_intersections(13);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {312, 313, 314};
        actual = find_all_street_intersections(12);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {316, 318};
        actual = find_all_street_intersections(15);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
    } //all_street_intersections

    TEST_FIXTURE(MapFixture, intersection_ids_from_street_names) {
        std::vector<unsigned> expected;
        std::vector<unsigned> actual;
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Castle Terrace", "Side Path");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Church Lane", "Casons");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Market Street", "The Run");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Napoleon Street", "Constitution Hill");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Napoleon Street", "Sandy Bay Road");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Seafront", "Shy Road");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_intersection_ids_from_street_names("Shy Road", "China Lane");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {60};
        actual = find_intersection_ids_from_street_names("Field Road", "Side Path");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {62};
        actual = find_intersection_ids_from_street_names("China Lane", "Market Street");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {289};
        actual = find_intersection_ids_from_street_names("Seales Corner", "Market Street");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {311};
        actual = find_intersection_ids_from_street_names("Seales Corner", "Napoleon Street");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {311};
        actual = find_intersection_ids_from_street_names("Side Path", "Napoleon Street");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {311};
        actual = find_intersection_ids_from_street_names("Side Path", "Seales Corner");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {315};
        actual = find_intersection_ids_from_street_names("Napoleon Street", "<unknown>");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {316, 318};
        actual = find_intersection_ids_from_street_names("Shy Road", "<unknown>");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
    } //intersection_ids_from_street_names

} //street_queries_public_saint_helena

*/