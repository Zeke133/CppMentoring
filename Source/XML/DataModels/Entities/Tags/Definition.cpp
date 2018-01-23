
#include "Definition.h"

using namespace std;
using namespace XML;

XmlDefinition::XmlDefinition(string_view content) : XmlTag(content, XmlTagType::Definition)
{

}

