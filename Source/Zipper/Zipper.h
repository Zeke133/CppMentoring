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

    Zipper& PutZipContent(ostream &output);

private:

    const vector<char> &zipSourceFile;
    ZIP_END_OF_CD * CentralDirectoryEnd;
    vector<ZIP_CD_FILE_HEADER*> ZipContent;

    void    InitZipEndOfCentralDirectory();
    void    FillZipContent();
    
};

#endif

