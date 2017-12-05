
#include "XmlEntity.h"

using namespace XML;

XmlEntity::XmlEntity(string_view str)
{
    content = str;
    entityType = GetEntityType(str);
};

XmlEntity::XmlEntity(const XmlEntity& entity)
{
    content = entity.content;
    entityType = entity.entityType;
};

string_view XmlEntity::GetContent() const
{
    return string_view(content);
};

XmlEntityType XmlEntity::GetEntityType() const
{
    return entityType;
};

XmlEntityType XmlEntity::GetEntityType(string_view str)
{
    return str.front() == '<' ? XmlEntityType::Tag : XmlEntityType::CharData;
}

XmlEntity XmlEntity::TakeXmlEntity(vector<char>::const_iterator &it, vector<char>::const_iterator end)
{
    auto begin = it;

    while (it < end)
    {
        // Trash
        if (*it == '\n' || *it == '\r' || *it == '\t')
        {
            it++;
            continue;
        }
        // Tag
        else if (*it == '<')
        {
            while (it < end)
            {
                if (*it == '>')
                {
                    it++;
                    break;
                }
                else it++;
            }
            break;
        }
        // Data
        else
        {
            while (it < end && *it != '<') it++;
            break;
        }
    }

    return XmlEntity(string_view(&(*begin), it - begin));
}

