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

uint32_t Zipper::GetFileUncompressedSize(const string_view fileName) const
{
    const auto localFileHeader = GetLocalFileHeader(fileName);

    if (localFileHeader == NULL)
        throw exception(/*"No requested file name in archive!"*/);

    return localFileHeader->uncompressed_size;
}

vector<char> Zipper::GetFile(const string_view fileName) const
{
    const auto localFileHeader = GetLocalFileHeader(fileName);

    if(localFileHeader == NULL)
        throw exception(/*"No requested file name in archive!"*/);

    if(localFileHeader->compression != COMPRESSION::deflated)
        throw exception(/*"Error decompressing file from archive: unsupported compression method!"*/);

    // TINF100
    // tinf_init();
    // res = tinf_uncompress(decompressedFile.data(), &out_len, inDataPtr, in_len);

    vector<char> outputFile(localFileHeader->uncompressed_size);
    auto outputPtr = (uint8_t *)(outputFile.data());
    unsigned long outputSize = outputFile.size();
    auto sourcePtr = (uint8_t *)localFileHeader + localFileHeader->getRealSize();
    unsigned long compressedSize = localFileHeader->compressed_size;

    auto res = puff(outputPtr, &outputSize, sourcePtr, &compressedSize);
    if(res != 0)
        throw exception(/*"Error decompressing file from archive!"*/);
    
    return outputFile;
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

const ZIP_CD_FILE_HEADER * Zipper::SetPtrToCDFileHeader(const void * start, uint32_t offset)
{
    return static_cast<const ZIP_CD_FILE_HEADER *>(static_cast<const void *>(static_cast<const char*>(start) + offset));
}

void Zipper::FillZipContent()
{
    auto centralDirFileHeaderPtr = SetPtrToCDFileHeader(zipArchive.data(), CentralDirectoryEnd->offset);

    for (uint16_t i = 0; i < CentralDirectoryEnd->total_entries; i++)
    {
        if(centralDirFileHeaderPtr->signature != ZIP_CD_FILE_HEADER_SIGNATURE)
        {
            throw exception(/*"Error in ZIP file CentralDirectory record!"*/);
        }

        ZipContent.push_back(centralDirFileHeaderPtr);

        // set ptr to next struct
        centralDirFileHeaderPtr = SetPtrToCDFileHeader(centralDirFileHeaderPtr, centralDirFileHeaderPtr->getRealSize());
    }
}

const ZIP_LOCAL_FILE_HEADER * Zipper::GetLocalFileHeader(const string_view fileName) const
{
    for(auto file : ZipContent)
    {
        if ( file->GetName() == fileName ) return (ZIP_LOCAL_FILE_HEADER * )(&(*(zipArchive.begin())) + file->offset_local_header);
    }
    return NULL;
}






