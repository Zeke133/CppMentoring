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
        XmlEntity(string_view str);
        XmlEntity(const XmlEntity& entity);
        virtual ~XmlEntity() {};

        XmlEntityType GetEntityType() const;
        string_view ToString() const;

        static XmlEntityType GetEntityType(string_view str);
        static XmlEntity TakeXmlEntity(vector<char>::const_iterator &it, vector<char>::const_iterator end);

    private:
        string content;
        XmlEntityType entityType;

    };

};

#endif
