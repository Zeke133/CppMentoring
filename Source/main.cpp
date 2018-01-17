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
    vector<char> docxFile;
    vector<char> xmlFile;

    cout << "Input full file name to open: ";
    getline(cin, docxFileName);

    // reading .docx file
    try
    {
        ifstream fileStream(docxFileName, ios::in | ios::binary);

        if(!fileStream.is_open())
        {
            cerr << "Error opening file!\n";
            return 1;
        }

        fileStream.seekg(0, fileStream.end);
        int32_t len = fileStream.tellg();
        fileStream.seekg(0, fileStream.beg);
        cout << "File size: " << len << endl; 

        docxFile.insert(docxFile.cbegin(), (istreambuf_iterator<char> (fileStream)), istreambuf_iterator<char> ());
    
        if (!fileStream)
            cerr << "Error: only " << fileStream.gcount() << " could be read\n";

        fileStream.close(); 
    }
    catch(const exception& ex)
    {
        cerr << "Error in reading file. " << ex.what() << endl;
    }
    catch(...)
    {
        cerr << "Error in reading file. User error." << endl;
    }
    
    // extracting "document.xml" file from archive
    try
    {
        Zipper zip(docxFile);

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

