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


SUITE(intersection_queries_public_saint_helena) {
    TEST_FIXTURE(MapFixture, intersection_street_segments) {
        std::vector<unsigned> expected;
        std::vector<unsigned> actual;
        
        expected = {};
        actual = find_intersection_street_segments(258);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {2};
        actual = find_intersection_street_segments(0);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {50, 51, 297};
        actual = find_intersection_street_segments(63);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {60, 182};
        actual = find_intersection_street_segments(88);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {100};
        actual = find_intersection_street_segments(140);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {137, 173};
        actual = find_intersection_street_segments(178);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {143};
        actual = find_intersection_street_segments(186);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {180, 213, 214};
        actual = find_intersection_street_segments(221);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {188};
        actual = find_intersection_street_segments(223);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {199, 200};
        actual = find_intersection_street_segments(244);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {218, 219};
        actual = find_intersection_street_segments(254);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {229, 232};
        actual = find_intersection_street_segments(263);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {264, 286};
        actual = find_intersection_street_segments(296);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {270, 271};
        actual = find_intersection_street_segments(75);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {279, 280};
        actual = find_intersection_street_segments(83);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
    } //intersection_street_segments

    TEST_FIXTURE(MapFixture, intersection_street_names) {
        std::vector<std::string> expected;
        std::vector<std::string> actual;
        
        expected = {};
        actual = find_intersection_street_names(258);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>"};
        actual = find_intersection_street_names(0);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>"};
        actual = find_intersection_street_names(140);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>"};
        actual = find_intersection_street_names(186);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>"};
        actual = find_intersection_street_names(223);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "<unknown>"};
        actual = find_intersection_street_names(75);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "<unknown>"};
        actual = find_intersection_street_names(83);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "<unknown>"};
        actual = find_intersection_street_names(88);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "<unknown>"};
        actual = find_intersection_street_names(178);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "<unknown>"};
        actual = find_intersection_street_names(254);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "<unknown>"};
        actual = find_intersection_street_names(263);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "<unknown>"};
        actual = find_intersection_street_names(296);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "<unknown>", "The Run"};
        actual = find_intersection_street_names(63);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "Casons", "Casons"};
        actual = find_intersection_street_names(221);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Casons", "Casons"};
        actual = find_intersection_street_names(244);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
    } //intersection_street_names

    TEST_FIXTURE(MapFixture, directly_connected) {
        CHECK_EQUAL(0, are_directly_connected(91, 229));
        
        CHECK_EQUAL(0, are_directly_connected(188, 236));
        
        CHECK_EQUAL(0, are_directly_connected(290, 162));
        
        CHECK_EQUAL(0, are_directly_connected(295, 292));
        
        CHECK_EQUAL(0, are_directly_connected(314, 231));
        
        CHECK_EQUAL(0, are_directly_connected(323, 58));
        
        CHECK_EQUAL(1, are_directly_connected(0, 0));
        
        CHECK_EQUAL(1, are_directly_connected(63, 309));
        
        CHECK_EQUAL(1, are_directly_connected(75, 74));
        
        CHECK_EQUAL(1, are_directly_connected(83, 113));
        
        CHECK_EQUAL(1, are_directly_connected(140, 139));
        
        CHECK_EQUAL(1, are_directly_connected(175, 17));
        
        CHECK_EQUAL(1, are_directly_connected(186, 185));
        
        CHECK_EQUAL(1, are_directly_connected(221, 249));
        
        CHECK_EQUAL(1, are_directly_connected(223, 227));
        
    } //directly_connected

    TEST_FIXTURE(MapFixture, adjacent_intersections) {
        std::vector<unsigned> expected;
        std::vector<unsigned> actual;
        
        expected = {};
        actual = find_adjacent_intersections(258);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {5, 17};
        actual = find_adjacent_intersections(175);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {57, 59};
        actual = find_adjacent_intersections(58);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {74, 76};
        actual = find_adjacent_intersections(75);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {87, 219};
        actual = find_adjacent_intersections(88);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {90, 94};
        actual = find_adjacent_intersections(91);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {139};
        actual = find_adjacent_intersections(140);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {160, 253};
        actual = find_adjacent_intersections(254);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {205, 207};
        actual = find_adjacent_intersections(206);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {227};
        actual = find_adjacent_intersections(223);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {228, 237, 248};
        actual = find_adjacent_intersections(229);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {243, 245};
        actual = find_adjacent_intersections(244);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {245, 296};
        actual = find_adjacent_intersections(295);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {291, 293};
        actual = find_adjacent_intersections(292);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {322};
        actual = find_adjacent_intersections(323);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
    } //adjacent_intersections

} //intersection_queries_public_saint_helena

*/