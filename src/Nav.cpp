#include "MQTT.cpp"
#include <math.h>

class Nav {
    private:
        float lat_orig_rad;
        float long_orig_rad;
    public:
        bool mining = false;
        float latitude;
        float longitude;
        float heading_deg;
        float depth_m;
        float length_m = 0;

        Nav(float latitude, float longitude, float heading_deg, float depth_m) {
            this->lat_orig_rad = latitude * M_PI / 180;
            this->long_orig_rad = longitude * M_PI / 180;
            this->latitude = latitude;
            this->longitude = longitude;
            this->heading_deg = heading_deg;
            this->depth_m = depth_m;
        }

        void updateNav(double distance_m) {
            length_m = distance_m;
            float heading_rad = heading_deg * M_PI / 180;
            float lat_rad_new = asin(sin(lat_orig_rad) * cos(distance_m / 6378100.0) + cos(lat_orig_rad) * sin(distance_m / 6378100.0) * cos(heading_rad));
            float long_rad_new = long_orig_rad + atan2(sin(heading_rad) * sin(distance_m / 6378100.0) * cos(lat_orig_rad), cos(distance_m / 6378100.0) - sin(lat_orig_rad) * sin(lat_rad_new));
            latitude = lat_rad_new * 180 / M_PI;
            longitude = long_rad_new * 180 / M_PI;
        }
};