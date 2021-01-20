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


SUITE(distance_time_queries_public_toronto_canada) {
    TEST_FIXTURE(MapFixture, distance_between_two_points) {
        double expected;
        double actual;
        
        expected = 2356.551894245857;
        actual = find_distance_between_two_points(LatLon(43.79279327392578, -79.40152740478516), LatLon(43.78813934326172, -79.37289428710938));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 2428.151755897328;
        actual = find_distance_between_two_points(LatLon(43.71529388427734, -79.55553436279297), LatLon(43.73324203491211, -79.53833770751953));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 2949.60709968117;
        actual = find_distance_between_two_points(LatLon(43.59196853637695, -79.37844085693359), LatLon(43.59408187866211, -79.41493988037109));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 3548.214845908753;
        actual = find_distance_between_two_points(LatLon(43.82280349731445, -79.18561553955078), LatLon(43.83701705932617, -79.14602661132812));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 7083.209203471775;
        actual = find_distance_between_two_points(LatLon(43.64250946044922, -79.35969543457031), LatLon(43.60358428955078, -79.29006958007812));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 9272.784199050997;
        actual = find_distance_between_two_points(LatLon(43.54529571533203, -79.10993194580078), LatLon(43.56031036376953, -79.22308349609375));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 9502.646562630267;
        actual = find_distance_between_two_points(LatLon(43.71036148071289, -79.60934448242188), LatLon(43.65697860717773, -79.70158386230469));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 10259.69455752464;
        actual = find_distance_between_two_points(LatLon(43.59600830078125, -79.11286163330078), LatLon(43.52816772460938, -79.19911193847656));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 10810.79465902317;
        actual = find_distance_between_two_points(LatLon(43.87495422363281, -79.56262969970703), LatLon(43.85248184204102, -79.43147277832031));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 14257.15447348564;
        actual = find_distance_between_two_points(LatLon(43.61819458007812, -79.22166442871094), LatLon(43.72824478149414, -79.31253051757812));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 14466.27648594318;
        actual = find_distance_between_two_points(LatLon(43.77970123291016, -79.60785675048828), LatLon(43.71545028686523, -79.45131683349609));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 16151.5711297336;
        actual = find_distance_between_two_points(LatLon(43.7325325012207, -79.09117126464844), LatLon(43.58732604980469, -79.09316253662109));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 17244.03077702476;
        actual = find_distance_between_two_points(LatLon(43.56804275512695, -79.77233123779297), LatLon(43.69831466674805, -79.65619659423828));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 23088.60558041353;
        actual = find_distance_between_two_points(LatLon(43.84590911865234, -79.17972564697266), LatLon(43.66649627685547, -79.32427978515625));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 26696.83790673241;
        actual = find_distance_between_two_points(LatLon(43.77907943725586, -79.08944702148438), LatLon(43.88920211791992, -79.38510131835938));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 28346.5711368084;
        actual = find_distance_between_two_points(LatLon(43.5703125, -79.68901062011719), LatLon(43.77373886108398, -79.47676086425781));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 29221.49002234369;
        actual = find_distance_between_two_points(LatLon(43.65841293334961, -79.78363037109375), LatLon(43.66227722167969, -79.42051696777344));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 30851.35060581534;
        actual = find_distance_between_two_points(LatLon(43.77691268920898, -79.58845520019531), LatLon(43.56536483764648, -79.34043121337891));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 31805.81615727611;
        actual = find_distance_between_two_points(LatLon(43.7193603515625, -79.52051544189453), LatLon(43.89463424682617, -79.20743560791016));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 34408.83086704562;
        actual = find_distance_between_two_points(LatLon(43.74295425415039, -79.03385925292969), LatLon(43.64625930786133, -79.44028472900391));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 36762.76484817623;
        actual = find_distance_between_two_points(LatLon(43.89926147460938, -79.00795745849609), LatLon(43.57030868530273, -79.05248260498047));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 38140.16821192804;
        actual = find_distance_between_two_points(LatLon(43.87306213378906, -79.04129791259766), LatLon(43.88061904907227, -79.51689147949219));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 38384.24630290481;
        actual = find_distance_between_two_points(LatLon(43.89250564575195, -79.44643402099609), LatLon(43.5764045715332, -79.25479125976562));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 40275.23822157075;
        actual = find_distance_between_two_points(LatLon(43.8380126953125, -79.22557830810547), LatLon(43.91736602783203, -79.71571350097656));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 41625.44069501305;
        actual = find_distance_between_two_points(LatLon(43.56082534790039, -79.01221466064453), LatLon(43.72190093994141, -79.47900390625));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 44869.30046041508;
        actual = find_distance_between_two_points(LatLon(43.87590789794922, -79.01165771484375), LatLon(43.90193939208984, -79.57024383544922));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 45646.59117179606;
        actual = find_distance_between_two_points(LatLon(43.64857482910156, -79.20729827880859), LatLon(43.7132568359375, -79.76767730712891));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 50284.11633087695;
        actual = find_distance_between_two_points(LatLon(43.90982437133789, -79.60358428955078), LatLon(43.48199844360352, -79.40149688720703));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 51318.54446459973;
        actual = find_distance_between_two_points(LatLon(43.65852355957031, -79.65676879882812), LatLon(43.54739761352539, -79.03836822509766));
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 60998.15420726743;
        actual = find_distance_between_two_points(LatLon(43.74922943115234, -79.02179718017578), LatLon(43.81575393676758, -79.77579498291016));
        CHECK(relative_error(expected, actual) < 0.001);
        
    } //distance_between_two_points

    TEST_FIXTURE(MapFixture, street_segment_length) {
        double expected;
        double actual;
        
        expected = 9.097748786827635;
        actual = find_street_segment_length(140688);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 9.242077259182894;
        actual = find_street_segment_length(151372);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 17.09496565388253;
        actual = find_street_segment_length(28196);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 23.48891492243527;
        actual = find_street_segment_length(124495);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 24.15866891885319;
        actual = find_street_segment_length(90597);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 25.82816268275385;
        actual = find_street_segment_length(36389);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 27.41978422292287;
        actual = find_street_segment_length(142034);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 29.72096698861328;
        actual = find_street_segment_length(113732);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 32.14021668534559;
        actual = find_street_segment_length(155517);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 44.83770116140564;
        actual = find_street_segment_length(117861);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 49.78241523119176;
        actual = find_street_segment_length(126916);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 50.86959588221137;
        actual = find_street_segment_length(77997);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 54.44416223401825;
        actual = find_street_segment_length(110253);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 55.41091787626419;
        actual = find_street_segment_length(84468);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 57.29100715801643;
        actual = find_street_segment_length(122449);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 58.2153429223323;
        actual = find_street_segment_length(142671);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 62.77545881717573;
        actual = find_street_segment_length(43905);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 66.43213964050811;
        actual = find_street_segment_length(30625);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 81.76324865924725;
        actual = find_street_segment_length(139629);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 88.29971916585265;
        actual = find_street_segment_length(86014);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 88.6499092331394;
        actual = find_street_segment_length(139231);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 125.9165822253067;
        actual = find_street_segment_length(67668);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 158.3532015020037;
        actual = find_street_segment_length(107519);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 165.0529241140918;
        actual = find_street_segment_length(42404);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 187.7234526910095;
        actual = find_street_segment_length(106519);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 222.1426656577275;
        actual = find_street_segment_length(40265);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 304.8238744061429;
        actual = find_street_segment_length(111218);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 313.4236862278825;
        actual = find_street_segment_length(99426);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 530.6419818323895;
        actual = find_street_segment_length(89824);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 660.7068089611057;
        actual = find_street_segment_length(10);
        CHECK(relative_error(expected, actual) < 0.001);
        
    } //street_segment_length

    TEST_FIXTURE(MapFixture, street_length) {
        double expected;
        double actual;
        
        expected = 68.94498340320835;
        actual = find_street_length(9098);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 83.59169625867054;
        actual = find_street_length(10487);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 88.39675553219958;
        actual = find_street_length(20909);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 91.52527038753789;
        actual = find_street_length(12181);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 143.6110441439387;
        actual = find_street_length(11357);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 186.3767927333687;
        actual = find_street_length(18773);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 192.4180805777547;
        actual = find_street_length(19096);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 199.2103325584933;
        actual = find_street_length(5903);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 229.3074513835471;
        actual = find_street_length(14456);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 272.9869484170533;
        actual = find_street_length(5701);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 325.7133661002234;
        actual = find_street_length(16463);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 331.544615044822;
        actual = find_street_length(4118);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 374.189977946363;
        actual = find_street_length(15846);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 403.568219879868;
        actual = find_street_length(17063);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 422.4275778629315;
        actual = find_street_length(3791);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 434.9550648604688;
        actual = find_street_length(14321);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 455.1225770686362;
        actual = find_street_length(12077);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 460.3702175736048;
        actual = find_street_length(14953);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 520.6063421788369;
        actual = find_street_length(16738);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 538.2839517388883;
        actual = find_street_length(11564);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 541.7509428885977;
        actual = find_street_length(4893);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 580.8783719542332;
        actual = find_street_length(18915);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 582.7553593410231;
        actual = find_street_length(18719);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 594.6168132744621;
        actual = find_street_length(19181);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 702.9298768276606;
        actual = find_street_length(20351);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 728.8731362709052;
        actual = find_street_length(5414);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 985.6279576428341;
        actual = find_street_length(13368);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 997.2200940200721;
        actual = find_street_length(14823);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 1118.827663103184;
        actual = find_street_length(15291);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 2408.61874267666;
        actual = find_street_length(2);
        CHECK(relative_error(expected, actual) < 0.001);
        
    } //street_length

    TEST_FIXTURE(MapFixture, street_segment_travel_time) {
        double expected;
        double actual;
        
        expected = 0.6550379126515898;
        actual = find_street_segment_travel_time(140688);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 0.6654295626611683;
        actual = find_street_segment_travel_time(151372);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 1.230837527079542;
        actual = find_street_segment_travel_time(28196);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 1.614157241810603;
        actual = find_street_segment_travel_time(117861);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 1.691201874415339;
        actual = find_street_segment_travel_time(124495);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 1.73942416215743;
        actual = find_street_segment_travel_time(90597);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 1.859627713158277;
        actual = find_street_segment_travel_time(36389);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 1.974224464050447;
        actual = find_street_segment_travel_time(142034);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 2.139909623180156;
        actual = find_street_segment_travel_time(113732);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 2.314095601344882;
        actual = find_street_segment_travel_time(155517);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 3.437460429480986;
        actual = find_street_segment_travel_time(122449);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 3.584333896645807;
        actual = find_street_segment_travel_time(126916);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 3.919979680849314;
        actual = find_street_segment_travel_time(110253);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 4.191504690407925;
        actual = find_street_segment_travel_time(142671);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 4.519833034836653;
        actual = find_street_segment_travel_time(43905);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 4.578263629399023;
        actual = find_street_segment_travel_time(77997);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 4.783114054116584;
        actual = find_street_segment_travel_time(30625);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 4.986982608863777;
        actual = find_street_segment_travel_time(84468);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 6.382793464786037;
        actual = find_street_segment_travel_time(139231);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 7.358692379332252;
        actual = find_street_segment_travel_time(139629);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 7.946974724926738;
        actual = find_street_segment_travel_time(86014);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 9.996419954597739;
        actual = find_street_segment_travel_time(40265);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 11.3324924002776;
        actual = find_street_segment_travel_time(67668);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 14.25178813518034;
        actual = find_street_segment_travel_time(107519);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 14.85476317026826;
        actual = find_street_segment_travel_time(42404);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 16.89511074219086;
        actual = find_street_segment_travel_time(106519);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 21.94731895724229;
        actual = find_street_segment_travel_time(111218);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 22.56650540840754;
        actual = find_street_segment_travel_time(99426);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 38.20622269193204;
        actual = find_street_segment_travel_time(89824);
        CHECK(relative_error(expected, actual) < 0.001);
        
        expected = 47.57089024519961;
        actual = find_street_segment_travel_time(10);
        CHECK(relative_error(expected, actual) < 0.001);
        
    } //street_segment_travel_time

} //distance_time_queries_public_toronto_canada

*/