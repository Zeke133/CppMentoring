#ifndef DEFINITION_H
#define DEFINITION_H

#include "../Tag.h"

using namespace std;

namespace XML
{
    class XmlDefinition : public XmlTag
    {

    public:

        XmlDefinition(string_view content);
        
    private:

    };

}

#endif
