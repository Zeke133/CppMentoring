#ifndef TAG_H
#define TAG_H

#include "../Entity.h"

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

        XmlTag(std::string_view content, XmlTagType type);

        XmlTagType GetType() const;

    private:

        XmlTagType tagType;

    };

}

#endif
