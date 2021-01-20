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


SUITE(spatial_queries_public_saint_helena) {
    TEST_FIXTURE(MapFixture, closest_poi) {
        std::set<unsigned> valid_results;
        unsigned actual;
        
        valid_results = {0};
        actual = find_closest_point_of_interest(LatLon(-14.38582324981689, -14.21776580810547));
        CHECK(valid_results.count(actual));
        
        valid_results = {0};
        actual = find_closest_point_of_interest(LatLon(-12.75326442718506, -13.43280696868896));
        CHECK(valid_results.count(actual));
        
        valid_results = {0};
        actual = find_closest_point_of_interest(LatLon(-12.72489166259766, -12.93563938140869));
        CHECK(valid_results.count(actual));
        
        valid_results = {0};
        actual = find_closest_point_of_interest(LatLon(-11.9944543838501, -12.92930889129639));
        CHECK(valid_results.count(actual));
        
        valid_results = {0};
        actual = find_closest_point_of_interest(LatLon(-11.77335262298584, -12.40951538085938));
        CHECK(valid_results.count(actual));
        
        valid_results = {0};
        actual = find_closest_point_of_interest(LatLon(-10.55166912078857, -12.17775917053223));
        CHECK(valid_results.count(actual));
        
        valid_results = {0};
        actual = find_closest_point_of_interest(LatLon(-8.256604194641113, -11.97569370269775));
        CHECK(valid_results.count(actual));
        
        valid_results = {1};
        actual = find_closest_point_of_interest(LatLon(-15.96532535552979, -10.10347843170166));
        CHECK(valid_results.count(actual));
        
        valid_results = {1};
        actual = find_closest_point_of_interest(LatLon(-14.43496608734131, -9.425968170166016));
        CHECK(valid_results.count(actual));
        
        valid_results = {1};
        actual = find_closest_point_of_interest(LatLon(-14.03187465667725, -6.682615756988525));
        CHECK(valid_results.count(actual));
        
        valid_results = {1};
        actual = find_closest_point_of_interest(LatLon(-11.36636924743652, -6.660521507263184));
        CHECK(valid_results.count(actual));
        
        valid_results = {1};
        actual = find_closest_point_of_interest(LatLon(-11.17502117156982, -6.024673461914062));
        CHECK(valid_results.count(actual));
        
        valid_results = {1};
        actual = find_closest_point_of_interest(LatLon(-11.05981922149658, -5.890884399414062));
        CHECK(valid_results.count(actual));
        
        valid_results = {1};
        actual = find_closest_point_of_interest(LatLon(-8.734432220458984, -5.778342247009277));
        CHECK(valid_results.count(actual));
        
        valid_results = {1};
        actual = find_closest_point_of_interest(LatLon(-8.305726051330566, -5.737282276153564));
        CHECK(valid_results.count(actual));
        
    } //closest_poi

    TEST_FIXTURE(MapFixture, closest_intersection) {
        std::set<unsigned> valid_results;
        unsigned actual;
        
        valid_results = {4, 7, 8, 9, 10, 61, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 167, 169, 170, 171, 172, 190, 204, 213, 214, 217, 218, 219, 222, 224, 236, 238, 262, 265, 266, 267, 276, 277, 278, 282, 284, 285, 286, 287, 288, 289, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318};
        actual = find_closest_intersection(LatLon(-11.68280792236328, -11.81244564056396));
        CHECK(valid_results.count(actual));
        
        valid_results = {4, 8, 9, 10, 61, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 167, 169, 170, 171, 172, 190, 194, 213, 214, 217, 218, 219, 222, 224, 236, 238, 262, 265, 266, 267, 271, 276, 277, 278, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318};
        actual = find_closest_intersection(LatLon(-10.50049591064453, -12.3930139541626));
        CHECK(valid_results.count(actual));
        
        valid_results = {4, 8, 9, 10, 61, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 167, 169, 170, 171, 172, 190, 194, 213, 214, 217, 218, 219, 222, 224, 262, 265, 266, 267, 271, 276, 277, 278, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318};
        actual = find_closest_intersection(LatLon(-10.55166912078857, -12.17775917053223));
        CHECK(valid_results.count(actual));
        
        valid_results = {4, 8, 9, 10, 61, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 167, 169, 170, 171, 172, 190, 214, 217, 218, 219, 222, 224, 236, 238, 262, 265, 266, 267, 276, 277, 278, 282, 284, 285, 286, 287, 288, 289, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318};
        actual = find_closest_intersection(LatLon(-11.35332679748535, -11.62172412872314));
        CHECK(valid_results.count(actual));
        
        valid_results = {4, 8, 9, 10, 61, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 167, 169, 170, 171, 172, 190, 214, 217, 218, 219, 222, 224, 236, 238, 262, 265, 266, 276, 277, 278, 282, 284, 285, 286, 287, 288, 289, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318};
        actual = find_closest_intersection(LatLon(-11.60812187194824, -11.42399120330811));
        CHECK(valid_results.count(actual));
        
        valid_results = {4, 8, 61, 85, 87, 88, 89, 90, 91, 92, 93, 94, 169, 170, 171, 172, 217, 218, 219, 222, 224, 262, 265, 276, 286, 287, 288, 310, 312, 313, 314, 315, 316, 317};
        actual = find_closest_intersection(LatLon(-13.0189094543457, -9.639738082885742));
        CHECK(valid_results.count(actual));
        
        valid_results = {4, 10, 236, 238, 243, 290, 291, 305};
        actual = find_closest_intersection(LatLon(-14.43496608734131, -9.425968170166016));
        CHECK(valid_results.count(actual));
        
        valid_results = {4, 85, 88, 90, 91, 92, 93, 94, 169, 170, 171, 172, 217, 218, 219, 222, 224, 286, 287, 288, 310, 312, 313, 314, 316, 317};
        actual = find_closest_intersection(LatLon(-13.73339653015137, -8.867242813110352));
        CHECK(valid_results.count(actual));
        
        valid_results = {61, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 167, 169, 170, 171, 172, 194, 213, 214, 217, 218, 219, 222, 224, 262, 265, 266, 267, 271, 276, 277, 278, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318};
        actual = find_closest_intersection(LatLon(-8.111869812011719, -12.34554195404053));
        CHECK(valid_results.count(actual));
        
        valid_results = {61, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 167, 169, 170, 171, 172, 194, 213, 214, 217, 218, 219, 222, 224, 262, 265, 266, 267, 271, 276, 277, 278, 282, 283, 284, 285, 286, 287, 288, 289, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318};
        actual = find_closest_intersection(LatLon(-8.256604194641113, -11.97569370269775));
        CHECK(valid_results.count(actual));
        
        valid_results = {61, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 167, 169, 170, 171, 172, 217, 218, 219, 222, 224, 262, 265, 276, 277, 278, 282, 285, 286, 287, 288, 289, 310, 311, 312, 313, 314, 315, 316, 317};
        actual = find_closest_intersection(LatLon(-11.67993831634521, -10.65622806549072));
        CHECK(valid_results.count(actual));
        
        valid_results = {61, 85, 88, 89, 90, 91, 92, 93, 94, 169, 170, 171, 172, 217, 218, 219, 222, 224, 286, 287, 288, 289, 309, 310, 311, 312, 313, 314, 315, 316, 317};
        actual = find_closest_intersection(LatLon(-8.390690803527832, -7.950428009033203));
        CHECK(valid_results.count(actual));
        
        valid_results = {61, 90, 91, 92, 93, 94, 169, 171, 172, 217, 218, 224, 286, 287, 288, 310, 311, 312, 313, 314, 315, 316, 317};
        actual = find_closest_intersection(LatLon(-8.734432220458984, -5.778342247009277));
        CHECK(valid_results.count(actual));
        
        valid_results = {61, 90, 91, 92, 93, 94, 171, 217, 218, 286, 312, 313, 314, 317};
        actual = find_closest_intersection(LatLon(-11.36636924743652, -6.660521507263184));
        CHECK(valid_results.count(actual));
        
        valid_results = {61, 90, 91, 92, 93, 94, 171, 217, 218, 312, 313, 314};
        actual = find_closest_intersection(LatLon(-14.03187465667725, -6.682615756988525));
        CHECK(valid_results.count(actual));
        
    } //closest_intersection

} //spatial_queries_public_saint_helena

*/