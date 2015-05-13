
#ifndef TEMPERATURENODE_H
#define TEMPERATURENODE_H
#include "SensorNode.h"

#include <string>
#include <vector>
#include <CommonMessages.h>

class TemperatureNode : virtual public SensorNode
{
public:

    TemperatureNode ();

    virtual ~TemperatureNode ();
    std::multimap<std::string, uint8_t> getNodeParametersMap();

    void getNodeId() =0;
    void setNodeId() =0;

    void getNodeType() =0;
    void setNodeType() =0;

    void getLocation() =0;
    void setLocation() =0;

    void setTemperatureValue (uint8_t new_var)   {
        temperatureValue = new_var;
    }

    uint8_t getTemperatureValue ()   {
        return temperatureValue;
    }

    void setHumidityValue (uint8_t new_var)   {
        humidityValue = new_var;
    }

    uint8_t getHumidityValue ()   {
        return humidityValue;
    }

    void setLastReadingStatus (uint8_t new_var)   {
        lastReadingStatus = new_var;
    }

    uint8_t getLastReadingStatus ()   {
        return lastReadingStatus;
    }

    void setNodeStatus (Status new_var)   {
        nodeStatus = new_var;
    }

    Status getNodeStatus ()   {
        return nodeStatus;
    }

protected:

private:

    void initAttributes () ;

    uint8_t temperatureValue;
    uint8_t humidityValue;
    uint8_t lastReadingStatus;
    Status nodeStatus;
};

#endif // TEMPERATURENODE_H
