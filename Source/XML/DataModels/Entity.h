#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <string_view>

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
        XmlEntity(std::string_view content, XmlEntityType type);

        XmlEntityType GetType() const;
        std::string GetContent() const;

    private:
        std::string content;
        XmlEntityType entityType;

    };

};

#endif
