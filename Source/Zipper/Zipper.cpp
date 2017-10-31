#include "Zipper.h"

using namespace std;



ostream &operator<<( ostream &output, const ZIP_END_OF_CD &endOfCd)
{
    output << "EndOfCentralDirectory:" << endl;
    output <<  hex << showbase;
    output << "\t" << "signature: " << endOfCd.signature << endl;
    output <<  dec;
    output << "\t" << "disk_num: " << endOfCd.disk_num << endl;
    output << "\t" << "disk_num_wcd: " << endOfCd.disk_num_wcd << endl;
    output << "\t" << "disk_entries: " << endOfCd.disk_entries << endl;
    output << "\t" << "total_entries: " << endOfCd.total_entries << endl;
    output << "\t" << "cd_size: " << endOfCd.cd_size <<  " bytes" << endl;
    output <<  hex << showbase;
    output << "\t" << "offset: " << endOfCd.offset << " = " << dec << endOfCd.offset << endl;
    output << "\t" << "comment_len: " << endOfCd.comment_len << endl;
    if(endOfCd.comment_len > 0)
    {
        output << "\t" << "comment: " << endOfCd.comment << endl;
    }    
    return output;
}

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
    cout << "CentralDirectoryFileHeader:" << endl;
    cout << "\t" << "offset: " << hex << cdFileHeader->offset_local_header << endl;
    cout << "\t" << "file name length: " << cdFileHeader->file_name_len << endl;
    cout << "\t" << "file name: " << cdFileHeader->file_name << endl;

    ZIP_LOCAL_FILE_HEADER * localFileHeader = (ZIP_LOCAL_FILE_HEADER *)(file + cdFileHeader->offset_local_header);
    cout << "LocalFileHeader:" << endl;
    cout << "\t" << "file name length: " << localFileHeader->file_name_len << endl;
    cout << "\t" << "file name: " << localFileHeader->file_name << endl;
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





