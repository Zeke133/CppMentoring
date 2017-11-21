#ifndef ZIPPER_OSTREAMS_H
#define ZIPPER_OSTREAMS_H

#include <iostream>
#include "ZipperTypes.h"

using namespace std;

ostream &operator<<( ostream &output, const VERSION_MADE_BY &ver);
ostream &operator<<( ostream &output, const COMPRESSION &compression);
ostream &operator<<( ostream &output, const FLAGS &flags);
ostream &operator<<( ostream &output, const INT_ATTR &attr);
ostream &operator<<( ostream &output, const MS_DOS_TIME &time);
ostream &operator<<( ostream &output, const MS_DOS_DATE &date);
ostream &operator<<( ostream &output, const VERSION &ver);
ostream &operator<<( ostream &output, const ZIP_LOCAL_FILE_HEADER &locFileHeader);
ostream &operator<<( ostream &output, const ZIP_CD_FILE_HEADER &cdFileHeader);
ostream &operator<<( ostream &output, const ZIP_END_OF_CD &endOfCd);

#endif
