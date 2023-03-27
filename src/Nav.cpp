#include "MQTT.cpp"
#include <math.h>

#define EARTH_RAD 6372895.0

class Nav {
    private:
        double lat_orig_rad;
        double long_orig_rad;
    public:
        bool mining = false;
        double latitude;
        double longitude;
        double heading_deg;
        double depth_m;
        double length_m = 0;

        Nav(double latitude, double longitude, double heading_deg, double depth_m) {
            this->lat_orig_rad = latitude * M_PI / 180;
            this->long_orig_rad = longitude * M_PI / 180;
            this->latitude = latitude;
            this->longitude = longitude;
            this->heading_deg = heading_deg;
            this->depth_m = depth_m;
        }

        void updateNav(double distance_m) {
            length_m = distance_m;
            double heading_rad = heading_deg * M_PI / 180;
            double lat_rad_new = asin(sin(lat_orig_rad) * cos(distance_m / EARTH_RAD) + cos(lat_orig_rad) * sin(distance_m / EARTH_RAD) * cos(heading_rad));
            double long_rad_new = long_orig_rad + atan2(sin(heading_rad) * sin(distance_m / EARTH_RAD) * cos(lat_orig_rad), cos(distance_m / EARTH_RAD) - sin(lat_orig_rad) * sin(lat_rad_new));
            latitude = lat_rad_new * 180 / M_PI;
            longitude = long_rad_new * 180 / M_PI;
        }
};