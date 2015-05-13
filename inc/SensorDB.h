
#ifndef SENSORDB_H
#define SENSORDB_H

#include <string>
#include <vector>
#include <set>

#include <SensorNode.h>

/**
 * class SensorDB
 * 
 */

class SensorDB
{
public:

    SensorDB();

    virtual ~SensorDB();

    void setSensorNodeContainer(std::set<SensorNode*> new_var)   {
        sensorNodeContainer = new_var;
    }

    std::set<SensorNode*> getSensorNodeContainer()   {
        return sensorNodeContainer;
    }

    SensorNode* begin() {
        return NULL;
    }

    SensorNode* end() {
        return NULL;
    }

protected:

private:

    std::set<SensorNode*> sensorNodeContainer;

    void initAttributes () ;

};

#endif // SENSORDB_H
