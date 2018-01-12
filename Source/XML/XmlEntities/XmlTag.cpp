
#include "XmlTag.h"

using namespace XML;

XmlTag::XmlTag(string_view content, XmlTagType type) : XmlEntity(content, XmlEntityType::Tag)
{
    tagType = type;
}

XmlTagType XmlTag::GetTagType() const
{
    return tagType;
}


