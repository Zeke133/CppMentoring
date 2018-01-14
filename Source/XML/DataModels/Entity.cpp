
#include "Entity.h"

using namespace XML;

XmlEntity::XmlEntity(string_view content, XmlEntityType type)
{
    this->content = content;
    entityType = type;
}

string XmlEntity::GetContent() const
{
    return string(content);
}

XmlEntityType XmlEntity::GetType() const
{
    return entityType;
}



