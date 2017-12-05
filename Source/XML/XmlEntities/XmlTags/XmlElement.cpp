
#include "XmlElement.h"

using namespace XML;

XmlElement::XmlElement(string_view str) : XmlTag(str)
{
    elementType = GetElementType(str);
    elementName = GetElementName(str);
};

XmlElement::XmlElement(const XmlEntity& entity) : XmlTag(entity)
{
    elementType = GetElementType(GetContent());
    elementName = GetElementName(GetContent());
};

XmlElementType XmlElement::GetElementType() const
{
    return elementType;
};

string_view XmlElement::GetElementName() const
{
    return elementName;
};

string_view XmlElement::GetElementName(string_view str)
{
    auto start = str.find_first_not_of("</");
    auto end = str.find_first_of(" />", start);

    return str.substr(start, end-start);
}

XmlElementType XmlElement::GetElementType(string_view str)
{
    if ( str[1] == '/')  return XmlElementType::End;
    else
    if ( *(str.end() - 2) == '/' ) return XmlElementType::Empty;
    else return XmlElementType::Start;
}
