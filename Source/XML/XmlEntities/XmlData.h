#ifndef XML_DATA_H
#define XML_DATA_H

#include <string_view>

using namespace std;

namespace XML
{
    class XmlData : public XmlEntity
    {

    public:
    
        XmlData(string_view str) : XmlEntity(str)
        {

        };

    private:

    };

}

#endif
