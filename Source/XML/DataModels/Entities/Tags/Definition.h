#ifndef DEFINITION_H
#define DEFINITION_H

#include "../Tag.h"
#include "../Data.h"

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
