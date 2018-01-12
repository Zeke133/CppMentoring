
#include "XmlElement.h"

using namespace XML;

XmlElementType XmlElement::GetElementType() const
{
    return elementType;
}

string_view XmlElement::GetElementName() const
{
    return elementName;
}

void XmlElement::PrintContent(int tabs) const
{
    for(int t = 0; t < tabs; t++)
        cout << "\t";
    
    cout << XmlEntity::ToString() << endl;

    if (charData != NULL)
    {
        for(int t = 0; t < tabs + 1; t++)
        cout << "\t";
        cout << charData->ToString() << endl;
    }

    for(auto child : children)
        child.PrintContent(tabs + 1);   // recursion
}

string XmlElement::ToString() const
{
    string text;

    if (elementName == "w:p") text += "\xd\xa";
    else if (elementName == "w:t" && charData != NULL) text += charData->ToString();
    
    for(auto child : children)
        text += child.ToString();   // recursion
        
    return text;
}

