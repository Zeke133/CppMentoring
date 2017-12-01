#ifndef XML_ELEMENT_H
#define XML_ELEMENT_H

#include <string_view>

using namespace std;

namespace XML
{
    enum class XmlElementType
    {
        Start,          // <element1>
        End,            // </element1>
        Empty           // <empty_element1 />
    };

    class XmlElement : public XmlTag
    {

    public:

        XmlElement(string_view str) : XmlTag(str)
        {
            if ( str[1] == '/')  elementType = XmlElementType::End;
            else
            if ( *(str.end() - 2) == '/' ) elementType = XmlElementType::Empty;
            else elementType = XmlElementType::Start;

            auto start = str.find_first_not_of("</");
            auto end = str.find_first_of(" />", start);
            elementName = str.substr(start, end-start);
        };

        XmlElementType GetElementType() const
        {
            return elementType;
        };

        string_view GetElementName() const
        {
            return elementName;
        };
        
    private:

        string_view elementName;
        XmlElementType elementType;

    };

}

#endif
