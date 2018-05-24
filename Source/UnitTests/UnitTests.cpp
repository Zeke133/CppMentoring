#include <gtest/gtest.h>

#include "../Zipper/Zipper.h"

#include <fstream>
#include <string>
#include <vector>

namespace
{

	struct FilesAndSizes {
		string name;
		size_t size;
	};

	vector<struct FilesAndSizes> docxContent {
		{"[Content_Types].xml", 1312},
		{"_rels/.rels", 590},
		{"word/_rels/document.xml.rels", 817},
		{"word/document.xml", 3644},
		{"word/theme/theme1.xml", 6850},
		{"word/settings.xml", 2561},
		{"word/fontTable.xml", 1340},
		{"word/webSettings.xml", 590},
		{"docProps/app.xml", 712},
		{"docProps/core.xml", 777},
		{"word/styles.xml", 29651},
	};

	// The fixture for testing class Zipper.
	class ZipTest : public ::testing::Test {

	public:

		ZipTest() {}

		virtual ~ZipTest() {}

		virtual void SetUp() {}

		virtual void TearDown() {}

		static void SetUpTestCase() {

			ifstream fileStream("TestData/text.docx", ios::in | ios::binary);

			if (!fileStream.is_open())
				FAIL() << "Can't open test file!";

			docxFile.insert(docxFile.cbegin(), (istreambuf_iterator<char>(fileStream)), istreambuf_iterator<char>());

			fileStream.close();
		}

		static void TearDownTestCase() {}

		// A predicate-formatter for asserting that file has right size.
		::testing::AssertionResult AssertRightFileSize(const char *name_expr,
													const char *size_expr,
													const char *sizeExpected_expr,
													string name,
													uint32_t size,
													uint32_t sizeExpected)
		{
			if (size == sizeExpected)
				return ::testing::AssertionSuccess();

			return ::testing::AssertionFailure()
				<< "For file name - " << name << " expected size is " << sizeExpected << " but got " << size;
		}

		// Objects declared here can be used by all tests in the test case for Zipper.
		static vector<char> docxFile;
	};

	class ZipTestContent :	public ZipTest,
							public ::testing::WithParamInterface<FilesAndSizes> {

	public:

	};

	vector<char> ZipTest::docxFile;

	TEST_F(ZipTest, GetZipContent_ExpectingNoThrow) {

		EXPECT_NO_THROW(
			{
				Zipper zipArchive(docxFile);
				zipArchive.GetZipContent();
			});
	}

	TEST_F(ZipTest, GetZipContent_AmountOfFiles) {

		Zipper zipArchive(docxFile);
		EXPECT_EQ(docxContent.size(), zipArchive.GetZipContent().size());
	}

	TEST_F(ZipTest, GetZipContent_NamesOfFiles) {

		Zipper zipArchive(docxFile);
		auto content = zipArchive.GetZipContent();
		auto fileIt = content.begin();
		for (auto expectedFile : docxContent)
		{
			EXPECT_EQ(expectedFile.name, *fileIt++);
		}
	}

	TEST_P(ZipTestContent, GetFileUncompressedSize_ExpectNoThrow) {

		EXPECT_NO_THROW(
			{
				Zipper zipArchive(docxFile);
				zipArchive.GetFileUncompressedSize(GetParam().name);
			});
	}

	TEST_P(ZipTestContent, GetFileUncompressedSize_CheckOfSize) {

		Zipper zipArchive(docxFile);
		auto file = GetParam();
		EXPECT_PRED_FORMAT3(AssertRightFileSize, file.name, zipArchive.GetFileUncompressedSize(file.name), file.size);
	}

	TEST_P(ZipTestContent, GetFile_ExpectNoThrow) {

		EXPECT_NO_THROW(
			{
				Zipper zipArchive(docxFile);
				zipArchive.GetFile(GetParam().name);
			});
	}

	TEST_P(ZipTestContent, GetFile_CheckOfSize) {

		Zipper zipArchive(docxFile);
		auto file = zipArchive.GetFile(GetParam().name);
		EXPECT_EQ(GetParam().size, file.size());
	}

	TEST_P(ZipTestContent, GetFile_CheckOfContent) {

		Zipper zipArchive(docxFile);
		auto file = zipArchive.GetFile(GetParam().name);
		string fileMaster = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>";
		string fileExtracted(file.data(), fileMaster.size());
		EXPECT_EQ(fileMaster, fileExtracted);
	}
	
	INSTANTIATE_TEST_CASE_P(ContentOfText_docx,
                        ZipTestContent,
                        ::testing::ValuesIn(docxContent));

} // namespace

int main(int argc, char **argv) {

	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
