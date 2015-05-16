#include <SensorDB.hpp>

SensorDB::SensorDB()
{
    initAttributes();
}

SensorDB::~SensorDB()
{
    if (NULL != _instance)
        delete _instance;
}

SensorDB* SensorDB::_instance = NULL;

SensorDB* SensorDB::getInstance()
{
    if (NULL == _instance) {
        _instance = new SensorDB;
    }
    return _instance;
}

std::set<SensorNode*>::iterator SensorDB::begin()
{
    return sensorNodeContainer.begin(); 
}

std::set<SensorNode*>::iterator SensorDB::end()
{
    return sensorNodeContainer.end(); 
}

void SensorDB::addSensorNode(SensorNode& newNode)
{
    sensorNodeContainer.insert(&newNode);
}

void SensorDB::initAttributes()
{
}
