#include <iostream>
#include <fstream>
#include <string>
#include <iterator>

#include "Zipper\Zipper.h"

using namespace std;


int main(void)
{    
    string fileName;

    cout << "Input full file name to open: ";
    getline(cin, fileName);

    ifstream fileStream(fileName, ios::in | ios::binary);

    if(!fileStream.is_open())
    {
        cerr << "Error opening file!\n";
        return 1;
    }

    fileStream.seekg(0, fileStream.end);
    int32_t len = fileStream.tellg();
    fileStream.seekg(0, fileStream.beg);
    cout << "File size: " << len << endl;   
    
    vector<char> file((istreambuf_iterator<char> (fileStream)), istreambuf_iterator<char> ());

    cout << file.size() << " bytes was cached" << endl;
    
    if (fileStream)
        cout << "All data read successfully.\n";
    else
        cout << "Error: only " << fileStream.gcount() << " could be read\n";
    fileStream.close();

    vector<char> &fileRef = file;
    Zipper zip(fileRef);
        
    return 0; 
}

