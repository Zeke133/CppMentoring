#ifndef XML_H
#define XML_H

#include <iostream>
#include <string_view>
#include <queue>
#include <exception>
#include <memory>

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
    Xml(const vector<char> &sourceFile);
    ~Xml() {};

    void PrintTree() const;
    string ToString() const;

private:
    const vector<char> xmlFile;

    unique_ptr<XmlDefinition> definition;
    unique_ptr<XmlElement> xmlRoot;

    void BuildTree(const vector<char> &xmlFile);
    
};

#endif