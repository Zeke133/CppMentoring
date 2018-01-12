
#include "XmlDefinition.h"

using namespace XML;

void XmlDefinition::PrintContent(int tabs) const
{
    for(int t = 0; t < tabs; t++)
        cout << "\t";
    
    cout << ToString() << endl;
};