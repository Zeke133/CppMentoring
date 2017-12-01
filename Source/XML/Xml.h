#ifndef XML_H
#define XML_H

#include <iostream>
#include <string_view>
#include <vector>
#include <exception>

#include "XmlEntity.h"
#include "XmlEntities/XmlTag.h"
#include "XmlEntities/XmlData.h"
#include "XmlEntities/XmlTags/XmlElement.h"
#include "XmlEntities/XmlTags/XmlDefinition.h"

using namespace std;

using namespace XML;

class Xml
{

public:

    Xml(const vector<char> &xmlFile);
    ~Xml();

private:       
    
};

#endif