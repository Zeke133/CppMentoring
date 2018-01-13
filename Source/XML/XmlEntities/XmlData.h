#ifndef XML_DATA_H
#define XML_DATA_H

#include <string_view>
#include "..\XmlEntity.h"

using namespace std;

namespace XML
{
    class XmlData : public XmlEntity
    {

    public:
    
        XmlData(string_view content) : XmlEntity(content, XmlEntityType::CharData) {};

    private:

    };

}

#endif
