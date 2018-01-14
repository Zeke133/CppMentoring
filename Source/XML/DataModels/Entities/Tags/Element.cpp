
#include "Element.h"

using namespace XML;

XmlElement::XmlElement(string_view content, string_view name, XmlElementType type) :
            XmlTag(content, XmlTagType::Element),
            data(string_view())
{
    elementName = name;
    elementType = type;
}

XmlElementType XmlElement::GetType() const
{
    return elementType;
}

string XmlElement::GetName() const
{
    return elementName;
}

list<XmlElement> XmlElement::GetChildren() const
{
    return children;
}

XmlData XmlElement::GetData() const
{
    return data;
}

void XmlElement::SetData(string_view content)
{
    data = XmlData(content);
}

XmlElement& XmlElement::AddChild(const XmlElement &child)
{
    children.push_back(child);

    return children.back();
}



