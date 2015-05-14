#include <SensorDB.hpp>

SensorDB::SensorDB() {
    initAttributes();
}

SensorDB::~SensorDB() { }

std::set<SensorNode*>::iterator SensorDB::begin() {

    return sensorNodeContainer.begin(); 
}

std::set<SensorNode*>::iterator SensorDB::end() {
    return sensorNodeContainer.end(); 
}

void SensorDB::addSensorNode(SensorNode* newNode) {
    sensorNodeContainer.insert(newNode);
}
