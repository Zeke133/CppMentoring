#include "Zipper.h"

using namespace std;

Zipper::Zipper(const vector<char> &file) :
        zipSize(file.size()),
        zipBegin((uint8_t *)file.data()),
        zipEnd(zipBegin + zipSize)
{    
    cout << "Zipper get file" << endl;
    
    if(!GetZipEndOfCentralDirectory())
    {
        cerr << "Error in ZIP file endOfCentralDirectory record!";
        return;
    }
    else
    {
        cout << *CentralDirectoryEnd;
    }

    if(!FillZipContent())
    {
        cerr << "Error in ZIP file CentralDirectory record!";
        return;
    }
    else
    {
        cout << "Files:" << endl;
        for (uint16_t i = 0; i < ZipContent.size(); i++)
        {
            cout << "\t" << i << ". """;
            put_n(cout, (uint8_t * )(&(ZipContent[i])[1]), ZipContent[i]->file_name_len);
            cout << """" << endl;
        }
    }

    while(1)
    {
        uint16_t i;

        cout << "Enter file number to look more info or other key to Exit:";
        if(!(cin >> i)) break;
        
        if(i >= ZipContent.size())
            cout << "Wrong number!" << endl;
        else
        {
            cout << *ZipContent[i] << endl;

            ZIP_LOCAL_FILE_HEADER * locHeader = (ZIP_LOCAL_FILE_HEADER * )(zipBegin + ZipContent[i]->offset_local_header);

            cout << *locHeader << endl;

            uint32_t out_len = locHeader->uncompressed_size;
            uint32_t in_len = locHeader->compressed_size;
            uint8_t * inDataPtr = (uint8_t *)locHeader + locHeader->getRealSize();
            vector<uint8_t> decompressedFile;
            decompressedFile.reserve(locHeader->uncompressed_size);
            uint32_t res = 0;
               
            // PUFF
            cout << "puff = " << (res = puff(decompressedFile.data(), (long unsigned int*)&out_len, inDataPtr, (long unsigned int*)&in_len)) << endl;
            
            // TINF100
            // tinf_init();
            // cout << "tinf_uncompress = " << (res = tinf_uncompress(decompressedFile.data(), &out_len, inDataPtr, in_len)) << endl;

            if(res == 0) cout << "Decompressed file:\n" << decompressedFile.data() << endl;

        }
    }
}

Zipper::~Zipper()
{
    ZipContent.clear();
    cout << "Destructor" << endl;
}

// Return false if error
bool Zipper::GetZipEndOfCentralDirectory()
{
    uint8_t * ptr = (uint8_t *)zipEnd;

    while(!(*ptr == 0x50 && *(ptr+1) == 0x4b && *(ptr+2) == 0x05 && *(ptr+3) == 0x06))
    {
        if(ptr == zipBegin) return false;
        ptr--;
    }

    CentralDirectoryEnd = (ZIP_END_OF_CD *)ptr;
    return true;
}

// Return false if error in headers
bool Zipper::FillZipContent()
{
    ZIP_CD_FILE_HEADER * ptr = (ZIP_CD_FILE_HEADER *)(zipBegin + CentralDirectoryEnd->offset);

    for (uint16_t i = 0; i < CentralDirectoryEnd->total_entries; i++)
    {
        if(ptr->signature != ZIP_CD_FILE_HEADER_SIGNATURE) return false;

        ZipContent.push_back(ptr);

        ptr = (ZIP_CD_FILE_HEADER *)((uint8_t *)ptr + ptr->getRealSize());
    }
    return true;
}




