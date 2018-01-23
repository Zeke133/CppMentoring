#ifndef DOC_CONVERTER_H
#define DOC_CONVERTER_H

// #include <string_view>
// #include <string>
// #include <vector>
// #include <queue>
// #include <stdexcept>

#include "../XML/DataModels/DataModels.h"

class DocConverter
{

public:
        
    static std::string ToString(XML::XmlElement& rootOfDocument);

private:        

};

#endif