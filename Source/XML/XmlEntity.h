#ifndef XML_ENTITY_H
#define XML_ENTITY_H

#include <string_view>
#include <string>
#include <vector>

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
        virtual ~XmlEntity() {};

        XmlEntityType GetEntityType() const;
        string ToString() const;

    private:
        string content;
        XmlEntityType entityType;

    };

};

#endif
