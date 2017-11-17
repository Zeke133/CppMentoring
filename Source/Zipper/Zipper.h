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
    Zipper(const vector<char> &file);
    ~Zipper();

private:
    const uint32_t    zipSize;
    const uint8_t *   zipBegin;
    const uint8_t *   zipEnd;
    ZIP_END_OF_CD * CentralDirectoryEnd;
    vector<ZIP_CD_FILE_HEADER*> ZipContent;

    bool    GetZipEndOfCentralDirectory();
    bool    FillZipContent();

};

#endif

