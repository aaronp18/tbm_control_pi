#include <mqtt/client.h>
#include <chrono>

const char * const BoolToString(bool b)
{
  return b ? "true" : "false";
}

class MQTT {
    private:
        std::string ip; //TODO: change to real IP
        std::string team = "Warwick Boring";
        uint timestamp;
        std::string msg;
    public:

        MQTT(std::string ip = "localhost:1883") {
            this->ip = ip;
        }

        int send(bool mining, float latitude, float longitude, float heading_deg, float depth_m, float length_m) {
            mqtt::client client(ip, "publisher", mqtt::create_options(MQTTVERSION_5));
            client.connect();
            timestamp = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            msg = "{'team': '" + team + "', 'timestamp': " + std::to_string(timestamp) + ", 'mining': " + BoolToString(mining) + ", 'latitude': " + std::to_string(latitude) + ", 'longitude': " + std::to_string(longitude) + ", 'heading_deg': " + std::to_string(heading_deg) + ", 'depth_m': " + std::to_string(depth_m) + ", 'length_m': " + std::to_string(length_m) + "}";
            mqtt::message_ptr pubmsg = mqtt::make_message("nabc23/warwick_boring", "");
            pubmsg->set_payload(msg);
            client.publish(pubmsg);
            return (0); //success
        }
};