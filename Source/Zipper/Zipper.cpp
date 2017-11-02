#include "Zipper.h"

using namespace std;

Zipper::Zipper(int8_t * file, int32_t size)
{
    ZipBegin = (uint8_t *)file;
    ZipSize = size;

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
            cout << *ZipContent[i] << endl;
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
    uint8_t * ptr = ZipBegin;

    ptr += ZipSize;
    while(!(*ptr == 0x50 && *(ptr+1) == 0x4b && *(ptr+2) == 0x05 && *(ptr+3) == 0x06))
    {
        if(ptr == ZipBegin) return false;
        ptr--;
    }

    CentralDirectoryEnd = (ZIP_END_OF_CD *)ptr;
    return true;
}

// Return false if error in headers
bool Zipper::FillZipContent()
{
    ZIP_CD_FILE_HEADER * ptr = (ZIP_CD_FILE_HEADER *)(ZipBegin + CentralDirectoryEnd->offset);

    for (uint16_t i = 0; i < CentralDirectoryEnd->total_entries; i++)
    {
        if(ptr->signature != ZIP_CD_FILE_HEADER_SIGNATURE) return false;
        ZipContent.push_back(ptr);
        uint8_t * temp = (uint8_t*)ptr;
        temp += sizeof(ZIP_CD_FILE_HEADER) + ptr->file_name_len + ptr->extra_field_len + ptr->file_comm_len;
        ptr = (ZIP_CD_FILE_HEADER *)temp;
    }
    return true;
}




