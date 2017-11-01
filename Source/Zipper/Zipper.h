#ifndef ZIPPER_H
#define ZIPPER_H

#include <iostream>
#include <string>

#include "ZipperTypes.h"
#include "ZipperOstreams.h"

#include <zlib.h>


class Zipper
{
public:
    Zipper(int8_t * file, int32_t size);
    ~Zipper();

private:
    ZIP_END_OF_CD * GetZipEndOfCentralDirectory(int8_t * file, int32_t size);

};

#endif

