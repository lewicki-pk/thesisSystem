//#include "MQTTPacket.h"
//#include "transport.h"

#include <string>

class MQTTProxy
{
public:
    bool publish(std::string topic, std::string payload);
    
};
