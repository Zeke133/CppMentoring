#ifndef ELEMENT_H
#define ELEMENT_H

#include <list>

#include "../Tag.h"
#include "../Data.h"

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

        XmlElement(string_view content, string_view name, XmlElementType type);

        void SetData(string_view content);
        XmlElement& AddChild(const XmlElement &child);      // returns reference to added child

        XmlElementType GetType() const;
        string GetName() const;
        list<XmlElement> GetChildren() const;
        XmlData GetData() const;

    private:

        list<XmlElement> children;
        XmlData data;

        string elementName;
        XmlElementType elementType;

    };

}

#endif
