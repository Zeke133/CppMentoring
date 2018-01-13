
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

void XmlElement::SetCharData(string_view content)
{
    charData = XmlData(content);
}

XmlElement& XmlElement::AddChild(const XmlElement &child)
{
    children.push_back(child);

    return children.back();
}

void XmlElement::PrintContent(int tabs) const
{
    for(int t = 0; t < tabs; t++)
        cout << "\t";
    
    cout << XmlEntity::ToString() << endl;

    auto data = charData.ToString();
    if (data.empty() == false)
    {
        for(int t = 0; t < tabs + 1; t++)
        cout << "\t";
        cout << data << endl;
    }

    for(auto child : children)
        child.PrintContent(tabs + 1);   // recursion
}

string XmlElement::ToString() const
{
    string text;
    auto data = charData.ToString();

    if (elementName == "w:p") text += "\xd\xa";
    else if (elementName == "w:t" && data.empty() == false) text += data;
    
    for(auto child : children)
        text += child.ToString();   // recursion
        
    return text;
}

