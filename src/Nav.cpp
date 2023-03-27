#include "MQTT.cpp"
#include <math.h>

class Nav {
    private:
    public:
        bool mining = false;
        float latitude;
        float longitude;
        float heading_deg;
        float depth_m;
        float length_m = 0;

        Nav(float latitude, float longitude, float heading_deg, float depth_m) {
            this->latitude = latitude;
            this->longitude = longitude;
            this->heading_deg = heading_deg;
            this->depth_m = depth_m;
        }

        void updateNav(double distance_m) {

            

            length_m += distance_m;
            float heading_rad = heading_deg * M_PI / 180;
            float lat_rad = latitude * M_PI / 180;
            float long_rad = longitude * M_PI / 180;
            float lat_rad_new = asin(sin(lat_rad) * cos(distance_m / 6378100) + cos(lat_rad) * sin(distance_m / 6378100) * cos(heading_rad));
            float long_rad_new = long_rad + atan2(sin(heading_rad) * sin(distance_m / 6378100) * cos(lat_rad), cos(distance_m / 6378100) - sin(lat_rad) * sin(lat_rad_new));
            latitude = lat_rad_new * 180 / M_PI;
            longitude = long_rad_new * 180 / M_PI;
        }
};