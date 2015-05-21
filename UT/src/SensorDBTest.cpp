#include <SensorDB.hpp>
#include <TemperatureNode.hpp>

#include <gtest/gtest.h>

class SensorDBTest : public ::testing::Test
{
protected:

    SensorDB* sensorDB = SensorDB::getInstance();

    void SetUp() {
        sensorDB->clearDatabase();
    };
    void TearDown() { };
};

TEST_F(SensorDBTest, addingNewAndDuplicatedNodeToDB)
{

    TemperatureNode* sampleTempNode = new TemperatureNode(1, 1, 1, 1, 22, 40, 0);
    ASSERT_EQ(*sampleTempNode->getNodeId(), 1);
    
    ASSERT_TRUE(sensorDB->addSensorNode(*sampleTempNode));
    ASSERT_FALSE(sensorDB->addSensorNode(*sampleTempNode));
}
