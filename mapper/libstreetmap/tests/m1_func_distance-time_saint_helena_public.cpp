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


SUITE(distance_time_queries_public_saint_helena) {
    TEST_FIXTURE(MapFixture, distance_between_two_points) {
        double expected;
        double actual;
        
        expected = 42131.46180899131;
        actual = find_distance_between_two_points(LatLon(-11.68280792236328, -11.81244564056396), LatLon(-11.35332679748535, -11.62172412872314));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 56241.57087921762;
        actual = find_distance_between_two_points(LatLon(-9.709259033203125, -7.708365917205811), LatLon(-9.44832706451416, -7.269117832183838));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 115338.1317631029;
        actual = find_distance_between_two_points(LatLon(-13.0189094543457, -9.639738082885742), LatLon(-13.73339653015137, -8.867242813110352));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 155721.2280982655;
        actual = find_distance_between_two_points(LatLon(-11.77335262298584, -12.40951538085938), LatLon(-12.75326442718506, -13.43280696868896));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 166330.8801256604;
        actual = find_distance_between_two_points(LatLon(-8.751919746398926, -11.89122009277344), LatLon(-9.164484024047852, -10.43607902526855));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 230533.8129254071;
        actual = find_distance_between_two_points(LatLon(-10.50049591064453, -12.3930139541626), LatLon(-11.67993831634521, -10.65622806549072));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 296483.9968408826;
        actual = find_distance_between_two_points(LatLon(-11.36636924743652, -6.660521507263184), LatLon(-14.03187465667725, -6.682615756988525));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 300358.9512602551;
        actual = find_distance_between_two_points(LatLon(-14.38582324981689, -14.21776580810547), LatLon(-11.9944543838501, -12.92930889129639));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 487759.6217107826;
        actual = find_distance_between_two_points(LatLon(-14.3441686630249, -13.29333782196045), LatLon(-10.60994338989258, -10.93852043151855));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 522334.1841165572;
        actual = find_distance_between_two_points(LatLon(-11.60812187194824, -11.42399120330811), LatLon(-8.390690803527832, -7.950428009033203));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 525218.8668977282;
        actual = find_distance_between_two_points(LatLon(-10.55166912078857, -12.17775917053223), LatLon(-14.43496608734131, -9.425968170166016));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 619435.4716779684;
        actual = find_distance_between_two_points(LatLon(-9.430036544799805, -8.151762962341309), LatLon(-7.973432064056396, -13.58964157104492));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 683813.4452700129;
        actual = find_distance_between_two_points(LatLon(-8.734432220458984, -5.778342247009277), LatLon(-8.256604194641113, -11.97569370269775));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 906920.2922430871;
        actual = find_distance_between_two_points(LatLon(-8.111869812011719, -12.34554195404053), LatLon(-15.96532535552979, -10.10347843170166));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 925034.3244821785;
        actual = find_distance_between_two_points(LatLon(-11.05981922149658, -5.890884399414062), LatLon(-9.838635444641113, -14.2561559677124));
        CHECK(relative_error(expected, actual) < 0.001);
        
    } //distance_between_two_points

    TEST_FIXTURE(MapFixture, street_segment_length) {
        double expected;
        double actual;
        
        expected = 3.965971438841545;
        actual = find_street_segment_length(95);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 14.44067095243672;
        actual = find_street_segment_length(90);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 54.74380950785471;
        actual = find_street_segment_length(0);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 88.60965028773023;
        actual = find_street_segment_length(280);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 90.10398470052959;
        actual = find_street_segment_length(276);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 109.2694753103548;
        actual = find_street_segment_length(242);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 125.1208150859389;
        actual = find_street_segment_length(321);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 195.1577188968218;
        actual = find_street_segment_length(286);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 205.7908558412543;
        actual = find_street_segment_length(202);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 276.7976819439372;
        actual = find_street_segment_length(193);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 297.6729048036259;
        actual = find_street_segment_length(82);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 327.8526202231803;
        actual = find_street_segment_length(152);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 338.641177418342;
        actual = find_street_segment_length(240);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 354.7957890566466;
        actual = find_street_segment_length(265);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 1744.616879244426;
        actual = find_street_segment_length(69);
        CHECK(relative_error(expected, actual) < 0.001);
        
    } //street_segment_length

    TEST_FIXTURE(MapFixture, street_length) {
        double expected;
        double actual;
        
        expected = 46.50967211883511;
        actual = find_street_length(9);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 68.19403613744451;
        actual = find_street_length(3);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 234.7471720157079;
        actual = find_street_length(16);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 244.3089505400008;
        actual = find_street_length(13);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 251.0545860009665;
        actual = find_street_length(12);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 274.7560349702109;
        actual = find_street_length(2);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 702.5542600660664;
        actual = find_street_length(15);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 936.6235362456182;
        actual = find_street_length(10);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 944.8331259503633;
        actual = find_street_length(8);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 1255.356086566923;
        actual = find_street_length(11);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 1391.775400911913;
        actual = find_street_length(5);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 1945.621046947212;
        actual = find_street_length(1);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 2919.670302856548;
        actual = find_street_length(4);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 5818.223726495871;
        actual = find_street_length(7);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 8117.879506472456;
        actual = find_street_length(6);
        CHECK(relative_error(expected, actual) < 0.001);
        
    } //street_length

    TEST_FIXTURE(MapFixture, street_segment_travel_time) {
        double expected;
        double actual;
        
        expected = 0.356937429495739;
        actual = find_street_segment_travel_time(95);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 1.299660385719305;
        actual = find_street_segment_travel_time(90);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 4.926942855706924;
        actual = find_street_segment_travel_time(0);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 6.379894820716577;
        actual = find_street_segment_travel_time(280);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 6.487486898438132;
        actual = find_street_segment_travel_time(276);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 9.008698686187603;
        actual = find_street_segment_travel_time(321);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 9.834252777931932;
        actual = find_street_segment_travel_time(242);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 14.81694162057031;
        actual = find_street_segment_travel_time(202);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 17.56419470071397;
        actual = find_street_segment_travel_time(286);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 19.92943309996348;
        actual = find_street_segment_travel_time(193);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 21.43244914586106;
        actual = find_street_segment_travel_time(82);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 25.54529681207856;
        actual = find_street_segment_travel_time(265);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 29.50673582008623;
        actual = find_street_segment_travel_time(152);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 30.47770596765077;
        actual = find_street_segment_travel_time(240);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 125.6124153055987;
        actual = find_street_segment_travel_time(69);
        CHECK(relative_error(expected, actual) < 0.001);
        
    } //street_segment_travel_time

} //distance_time_queries_public_saint_helena

*/