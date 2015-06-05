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
    EXPECT_TRUE(testableGenerator->generateItems());

    EXPECT_EQ(goldenItems.str(), testableGenerator->getItemsConfigFile());
}

TEST_F(ItemsGeneratorTest, createItemsGenerator_withOneTemperatureNode)
{
    std::stringstream goldenItems;
    goldenItems << "Number Status_2 \"Status [%.1f]\" <temperature> { mqtt=\"<[thesisSystem:/Status/2:state:default\" }\nNumber Temperature_2 \"Temperature [%.1f \xC2\xB0" "C]\" <temperature> { mqtt=\"<[thesisSystem:/Temperature/2:state:default\" }\nNumber Humidity_2 \"Humidity [%.1f %%]\" <temperature> { mqtt=\"<[thesisSystem:/Humidity/2:state:default\" }\n";

    TemperatureNode* sampleTempNode2 = new TemperatureNode(2,1,3,1,25,50,0);

    SensorDB::getInstance()->addSensorNode(sampleTempNode2);

    std::shared_ptr<ItemsGenerator> testableGenerator = std::make_shared<ItemsGenerator>();
    EXPECT_TRUE(testableGenerator->generateItems());

    EXPECT_EQ(goldenItems.str(), testableGenerator->getItemsConfigFile());

    testableGenerator->saveItemsToFile("/home/lewiatan/repository/thesisSystem/UT/tmp/thesisSystem.items");
}
