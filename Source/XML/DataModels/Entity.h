#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <string_view>

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
        XmlEntity(string_view content, XmlEntityType type);

        XmlEntityType GetType() const;
        string GetContent() const;

    private:
        string content;
        XmlEntityType entityType;

    };

};

#endif
