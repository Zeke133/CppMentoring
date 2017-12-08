
#include "XmlTag.h"

using namespace XML;

XmlTag::XmlTag(string_view str) : XmlEntity(str)
{
    tagType = GetTagType(str);
}

XmlTag::XmlTag(const XmlEntity& entity) : XmlEntity(entity)
{
    tagType = GetTagType(GetContent());
}

XmlTagType XmlTag::GetTagType() const
{
    return tagType;
}

void XmlTag::PrintContent(int tabs) const
{
    cout << GetContent() << endl;
}

XmlTagType XmlTag::GetTagType(string_view str)
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

