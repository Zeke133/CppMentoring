#ifndef XML_TAG_H
#define XML_TAG_H

#include <string_view>

using namespace std;

namespace XML
{
    enum class XmlTagType : uint8_t
    {
        Definition,     // <?xml version="1.1" encoding="UTF-8" ?>
        DocType,        // <!DOCTYPE greeting SYSTEM "hello.dtd">
        ProcInstr,      // <?xml-stylesheet href="my-style.css"?>
        Comment,        // <!-- это комментарий -->
        Element,        // <element1> </element1> <empty_element1 />
        CDATA,          // 
        Reference       // 
    };

    class XmlTag : public XmlEntity
    {

    public:

        XmlTag(string_view str) : XmlEntity(str)
        {
            // str.starts_with("?xml")
            if ( str.compare(1, 3, "!--") == 0 ) tagType = XmlTagType::Comment;
            else
            if ( str.compare(1, 5, "?xml ") == 0 ) tagType = XmlTagType::Definition;
            else
            if ( str.compare(1, 8, "!DOCTYPE") == 0 ) tagType = XmlTagType::DocType;
            else
            if ( str.compare(1, 4, "?xml") == 0 ) tagType = XmlTagType::ProcInstr;
            else tagType = XmlTagType::Element;
        };

        XmlTagType GetTagType() const
        {
            return tagType;
        };
        
    private:

        XmlTagType tagType;

    };

}

#endif
