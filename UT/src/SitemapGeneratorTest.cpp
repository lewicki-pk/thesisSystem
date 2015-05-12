#include <SitemapGenerator.h>

#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include <sstream>

TEST(SitemapGenerator, generateFullSitemapValidation) {
    std::stringstream goldenSitemap;
    goldenSitemap << "sitemap thesisSystem label=\"Main Menu\" \n{\n}\n";
    SitemapGenerator* testableGenerator = new SitemapGenerator();
    testableGenerator->generateFullSitemap();
    ASSERT_EQ(goldenSitemap.str(), testableGenerator->getSitemapConfigFile());

}
