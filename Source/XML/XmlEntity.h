#ifndef XML_ENTITY_H
#define XML_ENTITY_H

#include <string_view>
#include <string>

using namespace std;

namespace XML
{
    enum class XmlEntityType : uint8_t
    {
        CharData,       // ...
        Tag             // < ... >
    };    

    class XmlEntity
    {

    public:

        XmlEntity(string_view str)
        {
            content = str;
            entityType = str.front() == '<' ? XmlEntityType::Tag : XmlEntityType::CharData;
        };        

        string_view GetContent() const
        {
            return string_view(content);
        };

        XmlEntityType GetEntityType() const
        {
            return entityType;
        };

    private:

        string content;
        XmlEntityType entityType;

    };

};

#endif
