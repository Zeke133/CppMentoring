#ifndef ELEMENT_H
#define ELEMENT_H

#include <list>

#include "../Tag.h"
#include "../Data.h"

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

        XmlElement(std::string_view content, std::string_view name, XmlElementType type);

        void SetData(std::string_view content);
        XmlElement& AddChild(const XmlElement &child);      // returns reference to added child

        XmlElementType GetType() const;
        std::string GetName() const;
        std::list<XmlElement> GetChildren() const;
        XmlData GetData() const;

    private:

        std::list<XmlElement> children;
        XmlData data;

        std::string elementName;
        XmlElementType elementType;

    };

}

#endif
