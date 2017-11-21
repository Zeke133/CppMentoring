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

    vector<char> &fileRef = file;
    try
    {
        Zipper zip(fileRef);
        zip.PutZipContent(cout);
    }
    catch(const exception& ex)
    {
        cerr << "zip error happen - " << ex.what() << endl;
    }

        
    // while(1)
    // {
    //     uint16_t i;

    //     cout << "Enter file number to look more info or other key to Exit:";
    //     if(!(cin >> i)) break;
        
    //     if(i >= ZipContent.size())
    //         cout << "Wrong number!" << endl;
    //     else
    //     {
    //         cout << *ZipContent[i] << endl;

    //         ZIP_LOCAL_FILE_HEADER * locHeader = (ZIP_LOCAL_FILE_HEADER * )(&(*(zipSourceFile.begin())) + ZipContent[i]->offset_local_header);

    //         cout << *locHeader << endl;

    //         uint32_t out_len = locHeader->uncompressed_size;
    //         uint32_t in_len = locHeader->compressed_size;
    //         uint8_t * inDataPtr = (uint8_t *)locHeader + locHeader->getRealSize();
    //         vector<uint8_t> decompressedFile;
    //         decompressedFile.reserve(locHeader->uncompressed_size);
    //         uint32_t res = 0;
               
    //         // PUFF
    //         cout << "puff = " << (res = puff(decompressedFile.data(), (long unsigned int*)&out_len, inDataPtr, (long unsigned int*)&in_len)) << endl;
            
    //         // TINF100
    //         // tinf_init();
    //         // cout << "tinf_uncompress = " << (res = tinf_uncompress(decompressedFile.data(), &out_len, inDataPtr, in_len)) << endl;

    //         if(res == 0) cout << "Decompressed file:\n" << decompressedFile.data() << endl;

    //     }
    // }
        
    return 0; 
}

