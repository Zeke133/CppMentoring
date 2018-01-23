#ifndef DEFINITION_H
#define DEFINITION_H

#include "../Tag.h"

namespace XML
{
    class XmlDefinition : public XmlTag
    {

    public:

        XmlDefinition(std::string_view content);
        
    private:

    };

}

#endif
