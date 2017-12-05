#ifndef XML_DEFINITION_H
#define XML_DEFINITION_H

#include <string_view>

using namespace std;

namespace XML
{
    class XmlDefinition : public XmlTag
    {

    public:

        XmlDefinition(string_view str) : XmlTag(str) {};
        XmlDefinition(const XmlEntity& entity) : XmlTag(entity) {};
        
    private:

    };

}

#endif
