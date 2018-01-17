#ifndef DOC_CONVERTER_H
#define DOC_CONVERTER_H

// #include <string_view>
// #include <string>
// #include <vector>
// #include <queue>
// #include <stdexcept>

#include "../XML/DataModels/DataModels.h"

using namespace std;

namespace XML
{   

    class DocConverter
    {

    public:
        
        static string ToString(XmlElement& rootOfDocument);

    private:        

    };

};

#endif