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

        XmlDefinition(string_view content) : XmlTag(content, XmlTagType::Definition) {};
        virtual ~XmlDefinition() {};

        virtual void PrintContent(int tabs) const;
        
    private:

    };

}

#endif
