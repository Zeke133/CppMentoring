#ifndef XML_DEFINITION_H
#define XML_DEFINITION_H

#include <string_view>
#include "../XmlTag.h"

using namespace std;

namespace XML
{
    class XmlDefinition : public XmlTag
    {

    public:

        XmlDefinition(string_view str) : XmlTag(str) {};
        XmlDefinition(const XmlEntity& entity) : XmlTag(entity) {};
        virtual ~XmlDefinition() {};

        virtual string ToString() const {return string();};
        virtual void PrintContent(int tabs) const;
        
    private:

    };

}

#endif
