#include "Zipper.h"

using namespace std;

Zipper::Zipper(const vector<char> &file) :
        zipArchive(file)
{   
    try
    {
        InitZipEndOfCentralDirectory();
        FillZipContent();
    } 
    catch(exception)
    {
        throw exception(/*"Error in zip archive structure!"*/);
    }
}

Zipper::~Zipper()
{
    ZipContent.clear();
}

vector<string> Zipper::GetZipContent() const
{
    vector<string> filesNames;
    filesNames.reserve(ZipContent.size());

    for(auto file : ZipContent)
    {
        auto view = file->GetName();      
        filesNames.push_back(string(view.data(), view.size()));
    }

    return filesNames;
}

uint32_t Zipper::GetFileUncompressedSize(uint32_t fileNumber) const
{
    return ZipContent[fileNumber]->uncompressed_size;
}

uint32_t Zipper::GetFile(uint32_t fileNumber, vector<char>& outputFile) const
{
    long unsigned int outputFileSize = outputFile.size();

    const ZIP_LOCAL_FILE_HEADER * localFileHeader = GetLocalFileHeader(fileNumber);

    if(localFileHeader->compression != COMPRESSION::deflated)
        throw exception(/*"Error decompressing file from archive: unsupported compression method!"*/);

    // TINF100
    // tinf_init();
    // cout << "tinf_uncompress = " << (res = tinf_uncompress(decompressedFile.data(), &out_len, inDataPtr, in_len)) << endl;

    long unsigned int compressedSize = localFileHeader->compressed_size;
    uint32_t res = puff((unsigned char*)outputFile.data(), &outputFileSize, (uint8_t *)localFileHeader + localFileHeader->getRealSize(), &compressedSize);
    if(res != 0)
        throw exception(/*"Error decompressing file from archive!"*/);
    
    return outputFileSize;
}

void Zipper::InitZipEndOfCentralDirectory()
{
    auto iter = zipArchive.end();

    while(!(*iter == 0x50 && *(iter+1) == 0x4b && *(iter+2) == 0x05 && *(iter+3) == 0x06))
    {
        if(iter == zipArchive.begin())
        {
            throw exception(/*"Error in ZIP file endOfCentralDirectory record!"*/);
        }
        iter--;
    }

    CentralDirectoryEnd = (ZIP_END_OF_CD *)(&(*iter));
}

void Zipper::FillZipContent()
{
    ZIP_CD_FILE_HEADER * ptr = (ZIP_CD_FILE_HEADER *)(&(*(zipArchive.begin() + CentralDirectoryEnd->offset)));

    for (uint16_t i = 0; i < CentralDirectoryEnd->total_entries; i++)
    {
        if(ptr->signature != ZIP_CD_FILE_HEADER_SIGNATURE)
        {
            throw exception(/*"Error in ZIP file CentralDirectory record!"*/);
        }

        ZipContent.push_back(ptr);

        // ptr to next struct
        ptr = (ZIP_CD_FILE_HEADER *)((uint8_t *)ptr + ptr->getRealSize());
    }
}

const ZIP_LOCAL_FILE_HEADER * Zipper::GetLocalFileHeader(uint32_t fileNumber) const
{
    return (ZIP_LOCAL_FILE_HEADER * )(&(*(zipArchive.begin())) + ZipContent[fileNumber]->offset_local_header);
}




