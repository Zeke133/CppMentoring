#include <iostream>
#include <fstream>
#include <string>

#include "Zipper\Zipper.h"

using namespace std;


int main(void)
{
    string fileName;

    cout << "Input full file name to open: ";
    getline(cin, fileName);

    ifstream inFile(fileName, ios::in | ios::binary);

    if(!inFile.is_open())
    {
        cerr << "Error opening file!\n";
        return 1;
    }
    inFile.seekg(0, inFile.end);
    int32_t len = inFile.tellg();
    inFile.seekg(0, inFile.beg);
    cout << "File size: " << len << endl;

    int8_t * file = new int8_t [len];

    cout << "Reading..." << endl;
    inFile.read((char*)file, len);
    if (inFile)
        cout << "All data read successfully.\n";
    else
        cout << "Error: only " << inFile.gcount() << " could be read\n";
    inFile.close();

    Zipper zip(file, len);

    delete(file);
        
    return 0; 
}

