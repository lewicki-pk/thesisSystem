#pragma once

#include <ISensorDB.hpp>

#include <string>
#include <vector>
#include <map>

#include <SensorNode.hpp>
#include <CommonInterfaces.hpp>

class SensorDB: public ISensorDB
{
public:

    static SensorDB* getInstance();

    virtual ~SensorDB();

    //void setSensorNodeContainer(std::set<SensorNode*> new_var)   {
    //    sensorNodeContainer = new_var;
    //}

    //std::set<SensorNode*> getSensorNodeContainer()   {
    //    return sensorNodeContainer;
    //}

    std::map<uint8_t, ISensorNode*>::iterator begin();

    std::map<uint8_t, ISensorNode*>::iterator end();

    size_t getSize();
    bool isNodeInDB(uint8_t id);
    uint8_t getAvailableNodeId();

    bool addSensorNode(ISensorNode* newNode);

    void clearDatabase();
    void updateReadings(Message msg);

protected:

    SensorDB();

private:

    static SensorDB* _instance;

    std::map<uint8_t, ISensorNode*> sensorNodeContainer;

};
