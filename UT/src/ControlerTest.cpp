#include <Controler.hpp>
#include <TemperatureNode.hpp>

#include <gtest/gtest.h>

class ControlerTest : public ::testing::Test
{
protected:

    void SetUp() { };
    void TearDown() { };
};

TEST_F(ControlerTest, addNewNodeBasedOnInitMessage)
{
    Header hdr {0, 1, 0, 1, 123, static_cast<Status>(0)}; 
    InitMsgData initData = {0};
    Message msg = {hdr, initData};

    SensorDB* sensorDB = SensorDB::getInstance();

    Controler testControler;
    testControler.registerNode(msg);

    ASSERT_EQ(sensorDB->getSize(),1u);
    ASSERT_EQ(sensorDB->begin()->first, 1u);
}
