#ifndef XML_H
#define XML_H

#include <iostream>
#include <string_view>
#include <queue>
#include <exception>
#include <memory>

#include "DataModels/DataModels.h"
#include "Builder/Builder.h"

using namespace std;

using namespace XML;

class Xml
{

public:

    Xml(const vector<char> &sourceFile);

    XmlElement GetRootElement() const;

    void PrintVisualTree() const;

private:

    vector<char> xmlFile;

    unique_ptr<XmlDefinition> definition;
    unique_ptr<XmlElement> xmlRoot;

    void PrintTree(XmlElement& root, int tabs) const;
    
};

#endif