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
        load_map("/cad2/ece297s/public/maps/toronto_canada.streets.bin");
    }

    ~MapFixture() {
        //Clean-up
        close_map();
    }
};


SUITE(intersection_queries_public_toronto_canada) {
    TEST_FIXTURE(MapFixture, intersection_street_segments) {
        std::vector<unsigned> expected;
        std::vector<unsigned> actual;
        
        expected = {4, 136438};
        actual = find_intersection_street_segments(7);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {18588, 18598, 103969, 114105};
        actual = find_intersection_street_segments(19446);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {20364, 57744, 57746, 86784};
        actual = find_intersection_street_segments(21121);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {24373, 24374, 151729};
        actual = find_intersection_street_segments(25096);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {27172, 27173, 32957};
        actual = find_intersection_street_segments(27769);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {28811, 28812, 37168};
        actual = find_intersection_street_segments(29244);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {30037, 30038};
        actual = find_intersection_street_segments(30279);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {50680, 50728};
        actual = find_intersection_street_segments(46668);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {58170, 58202, 58204};
        actual = find_intersection_street_segments(53792);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {64846, 64847};
        actual = find_intersection_street_segments(58255);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {66448, 66449, 115607};
        actual = find_intersection_street_segments(59320);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {70514, 70538, 70543};
        actual = find_intersection_street_segments(61948);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {71315, 71326, 71327};
        actual = find_intersection_street_segments(62481);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {80302, 80304, 80307, 80312};
        actual = find_intersection_street_segments(68571);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {88902, 88903, 88904};
        actual = find_intersection_street_segments(73462);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {89904, 89905, 144677, 144678};
        actual = find_intersection_street_segments(74152);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {92678, 92785, 92834};
        actual = find_intersection_street_segments(76038);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {93396, 93397, 156235};
        actual = find_intersection_street_segments(76703);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {96304, 96325, 96326, 96379};
        actual = find_intersection_street_segments(78437);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {101180, 101181, 101182};
        actual = find_intersection_street_segments(81284);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {106843, 106844, 106848};
        actual = find_intersection_street_segments(84448);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {108860};
        actual = find_intersection_street_segments(85859);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {111762, 111767, 111768};
        actual = find_intersection_street_segments(87529);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {128042, 128043, 128048};
        actual = find_intersection_street_segments(96023);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {128537, 128538, 128560, 128561};
        actual = find_intersection_street_segments(96297);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {130034, 130040, 130041};
        actual = find_intersection_street_segments(97027);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {131940, 131941, 131946, 131947};
        actual = find_intersection_street_segments(97956);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {132745, 145459};
        actual = find_intersection_street_segments(98395);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {145836, 145837, 145847};
        actual = find_intersection_street_segments(104396);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {153426, 153427};
        actual = find_intersection_street_segments(107254);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
    } //intersection_street_segments

    TEST_FIXTURE(MapFixture, intersection_street_names) {
        std::vector<std::string> expected;
        std::vector<std::string> actual;
        
        expected = {"<unknown>"};
        actual = find_intersection_street_names(85859);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "<unknown>"};
        actual = find_intersection_street_names(46668);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "<unknown>"};
        actual = find_intersection_street_names(98395);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "<unknown>", "<unknown>"};
        actual = find_intersection_street_names(62481);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "<unknown>", "<unknown>"};
        actual = find_intersection_street_names(73462);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "<unknown>", "<unknown>"};
        actual = find_intersection_street_names(96023);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "<unknown>", "<unknown>"};
        actual = find_intersection_street_names(97027);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "<unknown>", "<unknown>"};
        actual = find_intersection_street_names(104396);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "<unknown>", "<unknown>", "<unknown>"};
        actual = find_intersection_street_names(74152);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "<unknown>", "<unknown>", "<unknown>"};
        actual = find_intersection_street_names(96297);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "<unknown>", "<unknown>", "<unknown>"};
        actual = find_intersection_street_names(97956);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "Bristol Road Elementary School", "Bristol Road Elementary School"};
        actual = find_intersection_street_names(25096);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "Ebenezer Road", "Ebenezer Road"};
        actual = find_intersection_street_names(76703);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"<unknown>", "Unity Drive", "Unity Drive"};
        actual = find_intersection_street_names(27769);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Avenue Road", "Avenue Road", "Lawrence Avenue West", "Lawrence Avenue West"};
        actual = find_intersection_street_names(68571);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Baggott Lane", "Ventura Lane", "Ventura Lane"};
        actual = find_intersection_street_names(87529);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Billy Bishop Way", "Billy Bishop Way", "Billy Bishop Way"};
        actual = find_intersection_street_names(59320);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Box Grove Bypass", "Box Grove Bypass", "Riverwalk Drive", "Riverwalk Drive"};
        actual = find_intersection_street_names(78437);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Cambrett Drive", "Cambrett Drive", "Drifton Crescent"};
        actual = find_intersection_street_names(61948);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Georgian Drive", "Hays Boulevard", "Hays Boulevard"};
        actual = find_intersection_street_names(84448);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Gleda Crescent", "Gleda Crescent", "Glenada Crescent"};
        actual = find_intersection_street_names(29244);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Goldberry Square", "Lawrence Avenue East", "Lawrence Avenue East", "Paulander Avenue"};
        actual = find_intersection_street_names(19446);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Grainger Crescent", "Grainger Crescent", "Wheatley Crescent"};
        actual = find_intersection_street_names(81284);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Highway 401 Collectors", "Highway 401 Collectors"};
        actual = find_intersection_street_names(7);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Highway 401 Express", "Highway 401 Express"};
        actual = find_intersection_street_names(30279);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Markham Road", "Markham Road"};
        actual = find_intersection_street_names(107254);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Neilson Road", "Neilson Road", "Sheppard Avenue East", "Sheppard Avenue East"};
        actual = find_intersection_street_names(21121);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Packard Boulevard", "Packard Boulevard", "Saratoga Drive"};
        actual = find_intersection_street_names(53792);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Thicket Trail", "Timberland Drive", "Timberland Drive"};
        actual = find_intersection_street_names(76038);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {"Tobermory Drive", "Tobermory Drive"};
        actual = find_intersection_street_names(58255);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
    } //intersection_street_names

    TEST_FIXTURE(MapFixture, directly_connected) {
        CHECK_EQUAL(0, are_directly_connected(7339, 68888));
        
        CHECK_EQUAL(0, are_directly_connected(20279, 40207));
        
        CHECK_EQUAL(0, are_directly_connected(23403, 62657));
        
        CHECK_EQUAL(0, are_directly_connected(23724, 102589));
        
        CHECK_EQUAL(0, are_directly_connected(27422, 59223));
        
        CHECK_EQUAL(0, are_directly_connected(34457, 25685));
        
        CHECK_EQUAL(0, are_directly_connected(51942, 34676));
        
        CHECK_EQUAL(0, are_directly_connected(73025, 37132));
        
        CHECK_EQUAL(0, are_directly_connected(84608, 30577));
        
        CHECK_EQUAL(0, are_directly_connected(86940, 58216));
        
        CHECK_EQUAL(0, are_directly_connected(90185, 32307));
        
        CHECK_EQUAL(0, are_directly_connected(92540, 80276));
        
        CHECK_EQUAL(0, are_directly_connected(100735, 59293));
        
        CHECK_EQUAL(1, are_directly_connected(7, 7));
        
        CHECK_EQUAL(1, are_directly_connected(19446, 82786));
        
        CHECK_EQUAL(1, are_directly_connected(27769, 27769));
        
        CHECK_EQUAL(1, are_directly_connected(29244, 36715));
        
        CHECK_EQUAL(1, are_directly_connected(53792, 53791));
        
        CHECK_EQUAL(1, are_directly_connected(59320, 59318));
        
        CHECK_EQUAL(1, are_directly_connected(68571, 68575));
        
        CHECK_EQUAL(1, are_directly_connected(76038, 76123));
        
        CHECK_EQUAL(1, are_directly_connected(76703, 108319));
        
        CHECK_EQUAL(1, are_directly_connected(78437, 78497));
        
        CHECK_EQUAL(1, are_directly_connected(81284, 81252));
        
        CHECK_EQUAL(1, are_directly_connected(84448, 84450));
        
        CHECK_EQUAL(1, are_directly_connected(85859, 85851));
        
        CHECK_EQUAL(1, are_directly_connected(87529, 87531));
        
        CHECK_EQUAL(1, are_directly_connected(88038, 88037));
        
        CHECK_EQUAL(1, are_directly_connected(97027, 97016));
        
        CHECK_EQUAL(1, are_directly_connected(98395, 104153));
        
    } //directly_connected

    TEST_FIXTURE(MapFixture, adjacent_intersections) {
        std::vector<unsigned> expected;
        std::vector<unsigned> actual;
        
        expected = {};
        actual = find_adjacent_intersections(96689);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {};
        actual = find_adjacent_intersections(99450);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {334, 12297, 70895};
        actual = find_adjacent_intersections(335);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {872, 53528};
        actual = find_adjacent_intersections(53524);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {2872, 3335, 33218};
        actual = find_adjacent_intersections(3334);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {6893, 12158, 44787};
        actual = find_adjacent_intersections(6892);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {7017, 45085};
        actual = find_adjacent_intersections(12987);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {8846, 8848, 8849};
        actual = find_adjacent_intersections(8847);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {9029, 9031, 9032};
        actual = find_adjacent_intersections(9030);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {19119, 19122};
        actual = find_adjacent_intersections(19121);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {21321, 21322, 71667};
        actual = find_adjacent_intersections(82352);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {21340, 21342, 43881};
        actual = find_adjacent_intersections(94656);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {25007, 42119};
        actual = find_adjacent_intersections(42118);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {31414, 31416, 32504, 83117};
        actual = find_adjacent_intersections(31415);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {42473, 43292, 43294};
        actual = find_adjacent_intersections(43293);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {43088, 43257};
        actual = find_adjacent_intersections(43087);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {43481, 50183, 84148};
        actual = find_adjacent_intersections(84149);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {44134, 44139};
        actual = find_adjacent_intersections(44140);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {47808, 52362};
        actual = find_adjacent_intersections(52356);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {48567, 50480, 107104};
        actual = find_adjacent_intersections(49051);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {55637, 55638, 55642};
        actual = find_adjacent_intersections(55639);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {57419, 57440, 57471};
        actual = find_adjacent_intersections(57427);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {63366, 63371};
        actual = find_adjacent_intersections(63367);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {71209, 71211, 98949};
        actual = find_adjacent_intersections(71210);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {79773, 79775, 79784};
        actual = find_adjacent_intersections(79774);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {80428, 80474, 83484};
        actual = find_adjacent_intersections(87423);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {89787, 89790};
        actual = find_adjacent_intersections(89792);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {90615, 90616, 90618};
        actual = find_adjacent_intersections(90617);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {97305, 97311};
        actual = find_adjacent_intersections(97309);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {105018, 105020};
        actual = find_adjacent_intersections(105019);
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
    } //adjacent_intersections

} //intersection_queries_public_toronto_canada

*/