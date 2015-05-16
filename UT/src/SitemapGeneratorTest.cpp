#include <SitemapGenerator.hpp>
#include <TemperatureNode.hpp>

#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include <sstream>

class SitemapGeneratorTest : public ::testing::Test
{
protected:
    void SetUp() {};
    void TearDown() {};
};

TEST_F(SitemapGeneratorTest, generateFullSitemap_empty)
{
    std::stringstream goldenSitemap;
    goldenSitemap << "sitemap thesisSystem label=\"Main Menu\" \n{\n}\n";

    SitemapGenerator* testableGenerator = new SitemapGenerator();
    testableGenerator->generateFullSitemap();

    ASSERT_EQ(goldenSitemap.str(), testableGenerator->getSitemapConfigFile());
}

TEST_F(SitemapGeneratorTest, generateFullSitemap_one_temperatureNode)
{
    std::stringstream goldenSitemap;
    goldenSitemap << "sitemap thesisSystem label=\"Main Menu\" \n{\nFrame {\nText item=1_Status\nText item=1_Temperature\nText item=1_Humidity\n}\n}\n";//TODO

    SitemapGenerator* testableGenerator = new SitemapGenerator();
    TemperatureNode* sampleTempNode = new TemperatureNode();
    sampleTempNode->setNodeId(1);
    ASSERT_EQ(*sampleTempNode->getNodeId(), 1);
    sampleTempNode->setNodeType(1);
    sampleTempNode->setLocation(1);
    sampleTempNode->setNodeStatus(1);
    sampleTempNode->setTemperatureValue(22); //TODO Here is the problem sir!!!
    sampleTempNode->setHumidityValue(40);
    sampleTempNode->setLastReadingStatus(0);

    SensorDB::getInstance()->addSensorNode(*sampleTempNode);

    testableGenerator->generateFullSitemap();

    ASSERT_EQ(goldenSitemap.str(), testableGenerator->getSitemapConfigFile());
}
