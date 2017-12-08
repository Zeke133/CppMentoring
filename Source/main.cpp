#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <exception>

#include "Zipper\Zipper.h"
#include "XML\Xml.h"

using namespace std;


int main(void)
{    
    string fileName;

    cout << "Input full file name to open: ";
    getline(cin, fileName);

    ifstream fileStream(fileName, ios::in | ios::binary);

    if(!fileStream.is_open())
    {
        cerr << "Error opening file!\n";
        return 1;
    }

    fileStream.seekg(0, fileStream.end);
    int32_t len = fileStream.tellg();
    fileStream.seekg(0, fileStream.beg);
    cout << "File size: " << len << endl;   
    
    vector<char> file((istreambuf_iterator<char> (fileStream)), istreambuf_iterator<char> ());
    
    if (!fileStream)
        cerr << "Error: only " << fileStream.gcount() << " could be read\n";

    fileStream.close();
    
    try
    {
        Zipper zip(file);
        auto filesNames = zip.GetZipContent();
        cout << "ZipContent:" << endl;
        for(auto name : filesNames)
        {
            cout << name << endl;
        }
        cout << endl;
        
        cout << "File \"word/document.xml\" uncompressed size is " << zip.GetFileUncompressedSize("word/document.xml") << " bytes" << endl;

        auto unzipedFile = zip.GetFile("word/document.xml");
        cout << endl;

        Xml xml(unzipedFile);
        cout << "XML tree:" << endl;
        xml.PrintTree();

        cout << "XML as text:" << endl;
        cout << xml.ToString() << endl;

    }
    catch(const exception& ex)
    {
        cerr << "Error happen - " << ex.what() << endl;
    }
    
    return 0; 
}

