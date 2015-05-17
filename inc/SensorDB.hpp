#ifndef SENSORDB_H
#define SENSORDB_H

#include <string>
#include <vector>
#include <set>

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

    std::set<SensorNode*>::iterator begin();

    std::set<SensorNode*>::iterator end();

    void addSensorNode(SensorNode& newNode);

    void clearDatabase();

protected:

    SensorDB();

private:

    static SensorDB* _instance;

    std::set<SensorNode*> sensorNodeContainer;

};

#endif // SENSORDB_H
