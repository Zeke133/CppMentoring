
#include "Data.h"

using namespace XML;

XmlData::XmlData(string_view content) : XmlEntity(content, XmlEntityType::CharData)
{
    
}

