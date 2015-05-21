#ifndef SENSORDB_H
#define SENSORDB_H

#include <string>
#include <vector>
#include <map>

#include <SensorNode.hpp>

class SensorDB
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

    std::map<uint8_t, SensorNode*>::iterator begin();

    std::map<uint8_t, SensorNode*>::iterator end();

    void addSensorNode(SensorNode& newNode);

    void clearDatabase();

protected:

    SensorDB();

private:

    static SensorDB* _instance;

    std::map<uint8_t, SensorNode*> sensorNodeContainer;

};

#endif // SENSORDB_H
