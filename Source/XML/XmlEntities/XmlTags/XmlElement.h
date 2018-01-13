#ifndef XML_ELEMENT_H
#define XML_ELEMENT_H

#include <string_view>
#include <list>
#include <queue>
#include <iostream>
#include <memory>
#include "../XmlTag.h"
#include "../XmlData.h"

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

        XmlElement(string_view content, string_view name, XmlElementType type) :
            XmlTag(content, XmlTagType::Element),
            charData(string_view())
        {
            elementName = name;
            elementType = type;
        };

        void SetCharData(string_view content);
        XmlElement& AddChild(const XmlElement &child);

        virtual void PrintContent(int tabs) const;
        string ToString() const;

        XmlElementType GetElementType() const;
        string_view GetElementName() const;

    private:

        list<XmlElement> children;
        XmlData charData;

        string elementName;
        XmlElementType elementType;

    };

}

#endif
