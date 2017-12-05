#ifndef XML_ELEMENT_H
#define XML_ELEMENT_H

#include <string_view>
#include "../XmlTag.h"

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

        XmlElement(string_view str);
        XmlElement(const XmlEntity& entity);

        XmlElementType GetElementType() const;
        string_view GetElementName() const;

        static string_view GetElementName(string_view str);
        static XmlElementType GetElementType(string_view str);
        
    private:

        string_view elementName;
        XmlElementType elementType;

    };

}

#endif
