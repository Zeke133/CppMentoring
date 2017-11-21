#ifndef ZIPPER_H
#define ZIPPER_H

#include <iostream>
#include <string>
#include <vector>

#include "ZipperTypes.h"
#include "ZipperOstreams.h"
#include "..\Tinf100\tinf.h"
#include "..\Puff\puff.h"


class Zipper
{

public:

    Zipper(const vector<char> &sourceFile);
    ~Zipper();

    vector<string>  GetZipContent() const;
    uint32_t    GetFileUncompressedSize(uint32_t fileNumber) const;
    uint32_t    GetFile(uint32_t fileNumber, vector<char>& outputFile) const;

private:

    const vector<char>  &zipArchive;
    ZIP_END_OF_CD *     CentralDirectoryEnd;
    vector<ZIP_CD_FILE_HEADER*> ZipContent;

    void    InitZipEndOfCentralDirectory();
    void    FillZipContent();
    const ZIP_LOCAL_FILE_HEADER *   GetLocalFileHeader(uint32_t fileNumber) const;
    
};

#endif

