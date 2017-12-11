#ifndef XML_ELEMENT_H
#define XML_ELEMENT_H

#include <string_view>
#include <list>
#include <queue>
#include <iostream>
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

        // XmlElement(string_view str);
        XmlElement(const XmlElement &e);
        XmlElement(const XmlEntity &e);
        XmlElement(queue<XmlEntity> &e);
        virtual ~XmlElement();

        void operator=(const XmlElement &e);

        void SetCharData(const XmlData &data);
        XmlElement * AddChild(const XmlElement &child);
        void Fill(queue<XmlEntity> &elements);

        virtual void PrintContent(int tabs) const;
        string ToString() const;

        XmlElementType GetElementType() const;
        string_view GetElementName() const;

        static string_view GetElementName(string_view str);
        static XmlElementType GetElementType(string_view str);
        
    private:
        list<XmlElement> children;
        XmlData * charData;

        string elementName;
        XmlElementType elementType;

    };

}

#endif
