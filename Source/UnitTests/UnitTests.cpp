#include <gtest/gtest.h>

#include "../Zipper/Zipper.h"

#include <fstream>
#include <string>
#include <vector>

namespace {

// The fixture for testing class Zipper.
class ZipTest : public ::testing::Test {
 protected:

  ZipTest() {}

  virtual ~ZipTest() {}

  virtual void SetUp() {
    ifstream fileStream("TestData/text.docx", ios::in | ios::binary);

    if(!fileStream.is_open())
      FAIL() << "Can't open test file!";

    docxFile.insert(docxFile.cbegin(), (istreambuf_iterator<char> (fileStream)), istreambuf_iterator<char> ());
    
    fileStream.close();
  }

  virtual void TearDown() {}

  // A predicate-formatter for asserting that file has right size.
  ::testing::AssertionResult AssertRightFileSize(const char* name_expr,
                                                const char* size_expr,
                                                const char* sizeExpected_expr,
                                                string name,
                                                uint32_t size,
                                                uint32_t sizeExpected) {
    if (size == sizeExpected)
      return ::testing::AssertionSuccess();

    return ::testing::AssertionFailure()
        << "For file name - " << name << " expected size is " << sizeExpected << " but got " << size;
  }

  // Objects declared here can be used by all tests in the test case for Zipper.
  vector<char> docxFile;

  struct filesAndSizes {
    string name;
    size_t size;
  };
  vector<struct filesAndSizes> docxContent {
    {"[Content_Types].xml",1312},
    {"_rels/.rels",590},
    {"word/_rels/document.xml.rels",817},
    {"word/document.xml",3644},
    {"word/theme/theme1.xml",6850},
    {"word/settings.xml",2561},
    {"word/fontTable.xml",1340},
    {"word/webSettings.xml",590},
    {"docProps/app.xml",712},
    {"docProps/core.xml",777},
    {"word/styles.xml",29651},
  };
};

// Tests that the Zipper::GetZipContent() method does right test archive content.
TEST_F(ZipTest, GettingArchiveContent) {
  vector<string> content;
  EXPECT_NO_THROW(
    {
      Zipper zipArchive(docxFile);
      content = zipArchive.GetZipContent();
    }
  );

  EXPECT_EQ(docxContent.size(), content.size());

  auto filePtr = content.begin();
  for(auto expectedFile : docxContent)
  {
    EXPECT_EQ(expectedFile.name, *filePtr++);
  }  
}

// Tests that the Zipper::GetFileUncompressedSize() method returns right files size.
TEST_F(ZipTest, GettingFileSize) {
  
  EXPECT_NO_THROW(
    {
      Zipper zipArchive(docxFile);
      
      for(auto file : docxContent)
      {
        EXPECT_PRED_FORMAT3(AssertRightFileSize, file.name, zipArchive.GetFileUncompressedSize(file.name), file.size);
      }
    }
  );  
}

// Tests that the Zipper::GetFile() method extract files from archive correctly.
TEST_F(ZipTest, ExtractingFiles) {
  
  string fileMaster = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>";
  EXPECT_NO_THROW(
    {
      Zipper zipArchive(docxFile);

      auto fileSz = zipArchive.GetFileUncompressedSize("_rels/.rels");

      auto file = zipArchive.GetFile("_rels/.rels");

      EXPECT_EQ(fileSz, file.size());
      
      string fileExtracted(file.data(), fileMaster.size());
      
      EXPECT_EQ(fileMaster, fileExtracted);
    }
  );  
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}