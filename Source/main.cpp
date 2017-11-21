#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <exception>

#include "Zipper\Zipper.h"

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

    cout << file.size() << " bytes was cached" << endl;
    
    if (fileStream)
        cout << "All data read successfully.\n";
    else
        cerr << "Error: only " << fileStream.gcount() << " could be read\n";
    fileStream.close();
    
    try
    {
        Zipper zip(file);
        auto filesNames = zip.GetZipContent();
        cout << "ZipContent:";
        for(uint32_t i = 0; i < filesNames.size(); i++)
        {
            cout << "\n\t" << i << ". " << filesNames[i];
        }
        cout << endl;

        uint16_t i;
        cout << "Enter file number to look more info or other key to Exit:";
        cin >> i;
        if(i >= filesNames.size())
            cout << "Wrong number!" << endl;

        uint32_t uncompressedFileSize = zip.GetFileUncompressedSize(i);
        cout << "File uncompressed size is " << uncompressedFileSize << " bytes" << endl;
        vector<char> uncompressedFile(uncompressedFileSize);

        uint32_t ret = zip.GetFile(i, uncompressedFile);
        cout << ret << " bytes uncompressed" << endl;
        cout << "Uncompressed file:\n" << uncompressedFile.data() << endl;
    }
    catch(const exception& ex)
    {
        cerr << "Zipper() error happen - " << ex.what() << endl;
    }
    
    return 0; 
}

