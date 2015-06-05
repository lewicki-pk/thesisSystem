#include <SitemapGenerator.hpp>
#include <TemperatureNode.hpp>

#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include <sstream>

class SitemapGeneratorTest : public ::testing::Test
{
protected:
    void SetUp() {
        SensorDB::getInstance()->clearDatabase();
    };
    void TearDown() {};
};

TEST_F(SitemapGeneratorTest, generateSitemap_empty)
{
    std::stringstream goldenSitemap;
    goldenSitemap << "sitemap thesisSystem label=\"Main Menu\" \n{\n}\n";

    SitemapGenerator* testableGenerator = new SitemapGenerator();
    testableGenerator->generateSitemap();

    ASSERT_EQ(goldenSitemap.str(), testableGenerator->getSitemapConfigFile());
}

TEST_F(SitemapGeneratorTest, generateSitemap_one_temperatureNode)
{
    std::stringstream goldenSitemap;
    goldenSitemap << "sitemap thesisSystem label=\"Main Menu\" \n{\nFrame {\nText item=Status_1\nText item=Temperature_1\nText item=Humidity_1\n}\n}\n";

    SitemapGenerator* testableGenerator = new SitemapGenerator();

    TemperatureNode* sampleTempNode = new TemperatureNode();
    sampleTempNode->setNodeId(1);
    ASSERT_EQ(sampleTempNode->getNodeId(), 1);
    sampleTempNode->setNodeType(1);
    sampleTempNode->setLocation(1);
    sampleTempNode->setNodeStatus(1);
    sampleTempNode->setTemperatureValue(22);
    sampleTempNode->setHumidityValue(40);
    sampleTempNode->setLastReadingStatus(0);

    SensorDB::getInstance()->addSensorNode(sampleTempNode);

    testableGenerator->generateSitemap();

    ASSERT_EQ(goldenSitemap.str(), testableGenerator->getSitemapConfigFile());
    testableGenerator->saveSitemapToFile("/home/lewiatan/repository/thesisSystem/UT/tmp/thesisSystem.sitemap");
}

TEST_F(SitemapGeneratorTest, generateSitemap_two_temperatureNodes)
{
    std::stringstream goldenSitemap;
    goldenSitemap << "sitemap thesisSystem label=\"Main Menu\" \n{\nFrame {\nText item=Status_1\nText item=Temperature_1\nText item=Humidity_1\n}\nFrame {\nText item=Status_2\nText item=Temperature_2\nText item=Humidity_2\n}\n}\n";

    SitemapGenerator* testableGenerator = new SitemapGenerator();

    TemperatureNode* sampleTempNode = new TemperatureNode();
    sampleTempNode->setNodeId(1);
    ASSERT_EQ(sampleTempNode->getNodeId(), 1);
    sampleTempNode->setNodeType(1);
    sampleTempNode->setLocation(1);
    sampleTempNode->setNodeStatus(1);
    sampleTempNode->setTemperatureValue(22);
    sampleTempNode->setHumidityValue(40);
    sampleTempNode->setLastReadingStatus(0);

    SensorDB::getInstance()->addSensorNode(sampleTempNode);

    TemperatureNode* sampleTempNode2 = new TemperatureNode(2,1,3,1,25,50,0);

    ASSERT_EQ(sampleTempNode2->getNodeType(), 1);
    ASSERT_EQ(sampleTempNode2->getLocation(), 3);
    ASSERT_EQ(sampleTempNode2->getLastReadingStatus(), 0);

    SensorDB::getInstance()->addSensorNode(sampleTempNode2);

    testableGenerator->generateSitemap();

    ASSERT_EQ(goldenSitemap.str(), testableGenerator->getSitemapConfigFile());
}

TEST_F(SitemapGeneratorTest, generateSitemap_two_temperatureNodes_clone)
{
    std::stringstream goldenSitemap;
    goldenSitemap << "sitemap thesisSystem label=\"Main Menu\" \n{\nFrame {\nText item=Status_1\nText item=Temperature_1\nText item=Humidity_1\n}\nFrame {\nText item=Status_2\nText item=Temperature_2\nText item=Humidity_2\n}\n}\n";

    SitemapGenerator* testableGenerator = new SitemapGenerator();

    TemperatureNode* sampleTempNode = new TemperatureNode(1, 1, 1, 1, 22, 40, 0);
    ASSERT_EQ(sampleTempNode->getNodeId(), 1);

    SensorDB::getInstance()->addSensorNode(sampleTempNode);

    TemperatureNode* sampleTempNode2 = new TemperatureNode(*sampleTempNode);
    ASSERT_EQ(sampleTempNode2->getNodeId(), 1);
    sampleTempNode2->setNodeId(2);
    ASSERT_EQ(sampleTempNode2->getNodeId(), 2);
    sampleTempNode2->setLocation(3);
    sampleTempNode2->setTemperatureValue(25);
    sampleTempNode2->setHumidityValue(50);
    sampleTempNode2->setLastReadingStatus(0);

    ASSERT_EQ(sampleTempNode2->getNodeStatus(), 1);

    SensorDB::getInstance()->addSensorNode(sampleTempNode2);

    testableGenerator->generateSitemap();

    ASSERT_EQ(goldenSitemap.str(), testableGenerator->getSitemapConfigFile());
}
