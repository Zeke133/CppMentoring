
#include "XmlEntity.h"

using namespace XML;

XmlEntity::XmlEntity(string_view content, XmlEntityType type)
{
    this->content = content;
    entityType = type;
}

string XmlEntity::ToString() const
{
    return string(content);
}

XmlEntityType XmlEntity::GetEntityType() const
{
    return entityType;
}



