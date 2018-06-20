#ifndef ZIPPER_H
#define ZIPPER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>

#include "ZipperTypes.h"
#include "ZipperOstreams.h"
//#include "Tinf100\tinf.h"
#include "Puff\puff.h"

class Zipper
{

public:

    Zipper(ifstream &sourceFile);             // takes reference to .zip source file stream
    ~Zipper();

    vector<string>  GetZipContent() const;          // get names of all files in archive
    uint32_t    GetFileUncompressedSize(const string_view fileName) const;
    vector<char>    GetFile(const string_view fileName) const;  // get file from archive

private:

    const vector<char>  zipArchive;                 // source archive file
    ZIP_END_OF_CD *     CentralDirectoryEnd;        // ptr to archive END OF CENTRAL DIRECTORY structure
    vector<const ZIP_CD_FILE_HEADER*> ZipContent;   // all archive CENTRAL DIRECTORY FILE HEADERS structure ptr's

    void    InitZipEndOfCentralDirectory();         // Find archive END OF CENTRAL DIRECTORY
    void    FillZipContent();                       // Find all archive CENTRAL DIRECTORY FILE HEADERS
    const ZIP_CD_FILE_HEADER * GetPtrToCDFileHeader(const void * start, uint32_t offset);   // Give pointer to Central Directory File Header

    const ZIP_LOCAL_FILE_HEADER *   GetLocalFileHeader(const string_view fileName) const;   // Get ptr to LOCAL FILE HEADER structure by file name from ZipContent
    
};

#endif

