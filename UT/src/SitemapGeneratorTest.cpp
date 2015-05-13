#include <SitemapGenerator.h>

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

TEST_F(SitemapGeneratorTest, generateFullSitemapValidation) {
    std::stringstream goldenSitemap;
    goldenSitemap << "sitemap thesisSystem label=\"Main Menu\" \n{\n}\n";

    SitemapGenerator* testableGenerator = new SitemapGenerator();
    testableGenerator->generateFullSitemap();

    ASSERT_EQ(goldenSitemap.str(), testableGenerator->getSitemapConfigFile());

}
