
#include "XmlElement.h"

using namespace XML;

// XmlElement::XmlElement(string_view str) : XmlTag(str)
// {
//     elementType = GetElementType(str);
//     elementName = GetElementName(str);
// }

XmlElement::XmlElement(const XmlEntity& entity) : XmlTag(entity)
{
    auto text = entity.ToString();
    elementType = GetElementType(text);
    elementName = GetElementName(text);
    charData = NULL;
}

XmlElement::XmlElement(queue<XmlEntity> &entities) : XmlTag(entities.front())
{
    // init element
    auto text = entities.front().ToString();
    elementType = GetElementType(text);
    elementName = GetElementName(text);
    charData = NULL;
    entities.pop();
    // fill all children
    Fill(entities);
}

XmlElement::XmlElement(const XmlElement& entity) : XmlTag(entity)
{
    elementType = entity.elementType;
    elementName = entity.elementName;
    children = entity.children;
    if (entity.charData != NULL)
        charData = new XmlData(*(entity.charData));
    else
        charData = NULL;
}

XmlElement::~XmlElement()
{
    if (charData != NULL) delete charData;
}

void XmlElement::operator=(const XmlElement &e)
{
    if (this != &e)
    {
        elementType = e.elementType;
        elementName = e.elementName;
        children = e.children;
    
        auto tmp = new XmlData(*(e.charData));
        if (charData != NULL) delete charData;
        charData = tmp;
    }
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
    if (charData != NULL)
        delete charData;
    charData = new XmlData(data);
}

// return ptr to Added child
XmlElement * XmlElement::AddChild(const XmlElement &child)
{
    children.push_back(child);

    return &(children.back());
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

        auto textEntity = e.ToString();

        switch (e.GetEntityType())
        {
            case XmlEntityType::CharData:
            {
                SetCharData(XmlData(e));
                break;
            }
            case XmlEntityType::Tag:
            {
                switch (XmlTag::GetTagType(textEntity))
                {
                    case XmlTagType::Definition:
                    {
                        // ignore
                        break;
                    }
                    case XmlTagType::Element:
                    {
                        XmlElement element(e);

                        switch (XmlElement::GetElementType(textEntity))
                        {
                            case XmlElementType::Start:
                            {
                                auto child = AddChild(element);
                                child->Fill(elements);    // recursion call - filling all element's children
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
                    // add more elemnt types later
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

