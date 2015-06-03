#include <gtest/gtest.h>
#include <ItemsGenerator.hpp>
#include <TemperatureNode.hpp>

#include <MockSensorDB.hpp>

#include <sstream>

class ItemsGeneratorTest : public ::testing::Test
{
protected:
    void SetUp() {
        SensorDB::getInstance()->clearDatabase();
    };
    void TearDown() {};
};

TEST_F(ItemsGeneratorTest, createItemsGenerator_withEmptySensorDB)
{
    std::stringstream goldenItems;
    goldenItems << "";

    std::shared_ptr<ItemsGenerator> testableGenerator = std::make_shared<ItemsGenerator>();
    EXPECT_TRUE(testableGenerator->generateFullItems());

    EXPECT_EQ(goldenItems.str(), testableGenerator->getItemsConfigFile());
}

TEST_F(ItemsGeneratorTest, createItemsGenerator_withOneTemperatureNode_noBinding_noGroup)
{
    std::stringstream goldenItems;
    goldenItems << "Number 2_Temperature \"Temperature [%.1f °C]\" <temperature> {}\n";

    TemperatureNode* sampleTempNode2 = new TemperatureNode(2,1,3,1,25,50,0);

    SensorDB::getInstance()->addSensorNode(sampleTempNode2);

    std::shared_ptr<ItemsGenerator> testableGenerator = std::make_shared<ItemsGenerator>();
    EXPECT_TRUE(testableGenerator->generateFullItems());

    EXPECT_EQ(goldenItems.str(), testableGenerator->getItemsConfigFile());
}
