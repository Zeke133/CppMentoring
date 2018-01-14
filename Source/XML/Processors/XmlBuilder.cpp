#include "XmlBuilder.h"

using namespace XML;

XmlEntityType XmlBuilder::GetEntityType(string_view str)
{
    return str.front() == '<' ? XmlEntityType::Tag : XmlEntityType::CharData;
}

XmlEntity XmlBuilder::TakeXmlEntity(vector<char>::const_iterator &it, vector<char>::const_iterator end)
{
    auto begin = it;

    while (it < end)
    {
        // Trash
        if (*it == '\n' || *it == '\r' || *it == '\t')
        {
            begin = ++it;
            continue;
        }
        // Tag
        else if (*it == '<')
        {
            while (it < end)
            {
                if (*it == '>')
                {
                    it++;
                    break;
                }
                else it++;
            }
            break;
        }
        // Data
        else
        {
            while (it < end && *it != '<') it++;
            break;
        }
    }

    string_view entity(&(*begin), it - begin);
    auto type = GetEntityType(entity);

    return XmlEntity(entity, type);
}

XmlTagType XmlBuilder::GetTagType(string_view str)
{
    // str.starts_with("?xml")
    if ( str.compare(1, 3, "!--") == 0 ) return XmlTagType::Comment;
    else
    if ( str.compare(1, 5, "?xml ") == 0 ) return XmlTagType::Definition;
    else
    if ( str.compare(1, 8, "!DOCTYPE") == 0 ) return XmlTagType::DocType;
    else
    if ( str.compare(1, 4, "?xml") == 0 ) return XmlTagType::ProcInstr;
    else return XmlTagType::Element;
}

string XmlBuilder::GetElementName(string str)
{
    auto start = str.find_first_not_of("</");
    auto end = str.find_first_of(" />", start);

    return str.substr(start, end-start);
}

XmlElementType XmlBuilder::GetElementType(string_view str)
{
    if ( str[1] == '/')  return XmlElementType::End;
    else
    if ( *(str.end() - 2) == '/' ) return XmlElementType::Empty;
    else return XmlElementType::Start;
}

void XmlBuilder::FillElement(XmlElement& parent, queue<XmlEntity>& entities)
{
    while(true)
    {
        // recursion end - all elements filled
        if (entities.empty())
            return;

        auto entity = entities.front();
        entities.pop();

        auto content = entity.GetContent();

        switch (entity.GetType())
        {
            case XmlEntityType::CharData:
            {
                parent.SetData(content);
                break;
            }
            case XmlEntityType::Tag:
            {
                switch (XmlBuilder::GetTagType(content))
                {
                    case XmlTagType::Definition:
                    {
                        // ignore
                        break;
                    }
                    case XmlTagType::Element:
                    {
                        auto name = XmlBuilder::GetElementName(content);
                        auto type = XmlBuilder::GetElementType(content);

                        XmlElement element(content, name, type);

                        switch (type)
                        {
                            case XmlElementType::Start:
                            {
                                FillElement(parent.AddChild(element), entities);    // recursion call - filling all element's children
                                break;
                            }
                            case XmlElementType::End:
                            {
                                // without reference to parent element can't compare name, but XML closing TAG in right order, and need no check.

                                return; // recursion end - all element's children filled, back to parent call
                            }
                            case XmlElementType::Empty:
                            {
                                parent.AddChild(element);
                                break;
                            }
                            default:
                                throw invalid_argument("Unknown XML element type");
                        }
                        break;
                    }
                    // add more elemnt types later
                    default:
                        throw invalid_argument("Unknown XML tag type");
                }
                break;
            }
            default:
                throw invalid_argument("Unknown XML entity type");
        }
    }
}


