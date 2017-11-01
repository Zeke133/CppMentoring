#include "Zipper.h"

using namespace std;

Zipper::Zipper(int8_t * file, int32_t size)
{
    cout << "Zipper get file" << endl;

    ZIP_END_OF_CD * endOfCd = GetZipEndOfCentralDirectory(file, size);
    
    if(endOfCd == nullptr)
    {
        cerr << "Error in ZIP file endOfCentralDirectory record!";
        return;
    }
    else
    {
        cout << *endOfCd;
    }

    ZIP_CD_FILE_HEADER * cdFileHeader = (ZIP_CD_FILE_HEADER *)(file + endOfCd->offset);
    cout << *cdFileHeader;

    ZIP_LOCAL_FILE_HEADER * localFileHeader = (ZIP_LOCAL_FILE_HEADER *)(file + cdFileHeader->offset_local_header);
    cout << *localFileHeader;

}

Zipper::~Zipper()
{
    cout << "Destructor" << endl;
}

// Return nullptr if error
ZIP_END_OF_CD * Zipper::GetZipEndOfCentralDirectory(int8_t * file, int32_t size)
{
    int8_t * ptr = file;

    ptr += size;
    while(ptr > file && !(*ptr == 0x50 && *(ptr+1) == 0x4b && *(ptr+2) == 0x05 && *(ptr+3) == 0x06))
    {
        ptr--;
    }
    
    return (ZIP_END_OF_CD *)(ptr > file ? ptr : nullptr);
}





