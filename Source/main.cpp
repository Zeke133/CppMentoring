#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <exception>

#include "Zipper\Zipper.h"
#include "XML\Xml.h"
#include "XmlProcessors\DocConverter.h"

using namespace std;


int main(void)
{    
    string docxFileName;
    vector<char> xmlFile;

    cout << "Input file name to open or press Enter for default sample: ";
    getline(cin, docxFileName);

    // extracting "document.xml" file from archive
    try
    {
        if (docxFileName.empty()) {
            docxFileName = "../TestData/text.docx";
        }
        ifstream fileStream(docxFileName, ios::in | ios::binary);

        if(!fileStream.is_open())
        {
            cerr << "Error opening file!\n";
            return 1;
        }

        Zipper zip(fileStream);

        auto filesNames = zip.GetZipContent();
        cout << "ZipContent:" << endl;
        for(auto name : filesNames)
        {
            cout << name << endl;
        }
        cout << endl;
        
        cout << "File \"word/document.xml\" uncompressed size is " << zip.GetFileUncompressedSize("word/document.xml") << " bytes" << endl;

        xmlFile = zip.GetFile("word/document.xml");
        cout << endl;
    }
    catch(const exception& ex)
    {
        cerr << "Error in ZIP processing. " << ex.what() << endl;
    }
    catch(...)
    {
        cerr << "Error in ZIP processing. User error." << endl;
    }

    // processing xml file for extracting raw text
    try
    {
        Xml xml(xmlFile);
        cout << "XML tree:" << endl;
        xml.PrintVisualTree();

        cout << "XML as text:" << endl;
        auto xmlRoot = xml.GetRootElement();
        cout << DocConverter::ToString(xmlRoot) << endl;

        cout << "Press Enter to exit..." << endl;
        cin.get();
    }
    catch(const exception& ex)
    {
        cerr << "Error in XML processing. " << ex.what() << endl;
    }
    catch(...)
    {
        cerr << "Error in XML processing. User error." << endl;
    }
    
    
    return 0; 
}

