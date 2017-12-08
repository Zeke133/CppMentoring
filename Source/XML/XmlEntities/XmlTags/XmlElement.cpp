
#include "XmlElement.h"

using namespace XML;

XmlElement::XmlElement(string_view str) : XmlTag(str), charData("")
{
    elementType = GetElementType(str);
    elementName = GetElementName(str);
}

XmlElement::XmlElement(const XmlEntity& entity) : XmlTag(entity), charData("")
{
    elementType = GetElementType(GetContent());
    elementName = GetElementName(GetContent());
}

XmlElement::XmlElement(queue<XmlEntity> &entities) : XmlTag(entities.front()), charData("")
{
    Fill(entities);
}

XmlElementType XmlElement::GetElementType() const
{
    return elementType;
}

string_view XmlElement::GetElementName() const
{
    return elementName;
}

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

void XmlElement::SetCharData(const XmlData &data)
{
    charData = data;
}

XmlElement& XmlElement::AddChild(const XmlElement &child)
{
    children.push_back(child);

    return children.back();
}

void XmlElement::Fill(queue<XmlEntity> &elements)
{
    while(true)
    {
        // recursion end - all elements filled
        if (elements.empty())
            return;

        auto e = elements.front();
        elements.pop();

        auto entityContent = e.GetContent();

        switch (e.GetEntityType())
        {
            case XmlEntityType::CharData:
            {
                SetCharData(XmlData(e));
                break;
            }
            case XmlEntityType::Tag:
            {
                switch (XmlTag::GetTagType(entityContent))
                {
                    case XmlTagType::Definition:
                    {
                        // ignore
                        break;
                    }
                    case XmlTagType::Element:
                    {
                        XmlElement element(e);

                        switch (XmlElement::GetElementType(entityContent))
                        {
                            case XmlElementType::Start:
                            {
                                auto child = AddChild(element);
                                child.Fill(elements);    // recursion call - filling all element's children
                                break;
                            }
                            case XmlElementType::End:
                            {
                                // without reference to parent element can't compare name, but XML closing TAG in right order, and need no check.

                                return; // recursion end - all element's children filled, back to parent call
                            }
                            case XmlElementType::Empty:
                            {
                                AddChild(element);
                                break;
                            }
                            default:
                                throw exception();
                        }
                        break;
                    }
                    default:
                        throw exception();
                }
                break;
            }
            default:
                throw exception();
        }
    }
}

void XmlElement::PrintContent(int tabs) const
{
    for(int t = 0; t < tabs; t++)
        cout << "\t";

    cout << GetContent() << endl;

    for(auto child : children)
        child.PrintContent(tabs + 1);
}

string XmlElement::ToString() const
{
    string text;

    if (elementName == "w:p") text += "\xd\xa";
    else if (elementName == "w:t") text += charData.ToString();
    
    for(auto child : children)
        text += child.ToString();
        
    return text;
}

