#include "../../../googleTest/googletest/include/gtest/gtest.h"

#include "../XML/DataModels/DataModels.h"
#include "../XML/DataModels/Entity.h"

//using namespace XML;
 
TEST(XMLtests, test1) {
    
    XML::XmlEntity entity_tag_definition("<?xml version=\"1.1\" encoding=\"UTF-8\" ?>", XML::XmlEntityType::Tag);

    EXPECT_EQ (XML::XmlEntityType::Tag, entity_tag_definition.GetType());
    EXPECT_EQ ("<?xml version=\"1.1\" encoding=\"UTF-8\" ?>", entity_tag_definition.GetContent());

}
 
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}