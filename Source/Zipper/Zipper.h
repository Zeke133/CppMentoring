#ifndef ZIPPER_H
#define ZIPPER_H

#include <iostream>
#include <string>
#include <vector>

#include "ZipperTypes.h"
#include "ZipperOstreams.h"

#include <zlib.h>


class Zipper
{
public:
    Zipper(int8_t * file, int32_t size);
    ~Zipper();

private:
    uint8_t *   ZipBegin;
    uint32_t    ZipSize;
    ZIP_END_OF_CD * CentralDirectoryEnd;
    vector<ZIP_CD_FILE_HEADER*> ZipContent;

    bool    GetZipEndOfCentralDirectory();
    bool    FillZipContent();

};

#endif

