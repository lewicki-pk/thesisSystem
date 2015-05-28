#include <gtest/gtest.h>
#include <ItemsGenerator.hpp>

#include <MockSensorDB.hpp>

#include <sstream>


TEST(ItemsGeneratorTest, createItemsGenerator_withEmptySensorDB)
{
    std::stringstream goldenItems;
    goldenItems << "";

    std::shared_ptr<MockSensorDB> sensorDBPtr = std::make_shared<MockSensorDB>();

    std::shared_ptr<ItemsGenerator> testableGenerator = std::make_shared<ItemsGenerator>(sensorDBPtr);
    EXPECT_TRUE(testableGenerator->generateFullItems());

    EXPECT_EQ(goldenItems.str(), testableGenerator->getItemsConfigFile());
}
