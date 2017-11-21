#include "Zipper.h"

#include <exception>

using namespace std;

Zipper::Zipper(const vector<char> &file) :
        zipSourceFile(file)
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

Zipper& Zipper::PutZipContent(ostream &output)
{
    output << "Files:" << endl;
    for(auto file : ZipContent)
    {
        cout << "\n\t" << file->GetName();
    }

    return *this;
}

void Zipper::InitZipEndOfCentralDirectory()
{
    auto iter = zipSourceFile.end();

    while(!(*iter == 0x50 && *(iter+1) == 0x4b && *(iter+2) == 0x05 && *(iter+3) == 0x06))
    {
        if(iter == zipSourceFile.begin())
        {
            throw std::exception(/*"Error in ZIP file endOfCentralDirectory record!"*/);
        }
        iter--;
    }

    CentralDirectoryEnd = (ZIP_END_OF_CD *)(&(*iter));
}

void Zipper::FillZipContent()
{
    ZIP_CD_FILE_HEADER * ptr = (ZIP_CD_FILE_HEADER *)(&(*(zipSourceFile.begin() + CentralDirectoryEnd->offset)));

    for (uint16_t i = 0; i < CentralDirectoryEnd->total_entries; i++)
    {
        if(ptr->signature != ZIP_CD_FILE_HEADER_SIGNATURE)
        {
            throw std::exception(/*"Error in ZIP file CentralDirectory record!"*/);
        }

        ZipContent.push_back(ptr);

        // ptr to next struct
        ptr = (ZIP_CD_FILE_HEADER *)((uint8_t *)ptr + ptr->getRealSize());
    }
}




