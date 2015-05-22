#include <Controler.hpp>
#include <TemperatureNode.hpp>

#include <gtest/gtest.h>

class ConstrolerTest : public ::testing::Test
{
protected:

    void SetUp() { };
    void TearDown() { };
};

TEST_F(ConstrolerTest, addNewNodeBasedOnInitMessage)
{
    Header hdr {1, 1, 0, 1, 123, static_cast<Status>(0)}; 
    InitMsgData initData = {0};
    Message msg = {hdr, initData};

    SensorDB* sensorDB = SensorDB::getInstance();

    Controler testControler;
    testControler.registerNode(msg);

    ASSERT_EQ(sensorDB->getSize(),1u);
    ASSERT_EQ(sensorDB->begin()->first, 1u);
}
