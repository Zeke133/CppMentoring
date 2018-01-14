#ifndef XML_H
#define XML_H

#include <iostream>
#include <string_view>
#include <queue>
#include <exception>
#include <memory>

#include "Processors/XmlBuilder.h"
#include "DataModels/DataModels.h"

using namespace std;

using namespace XML;

class Xml
{

public:

    Xml(const vector<char> &sourceFile);

    void PrintTree() const;
    string ToString() const;

private:

    vector<char> xmlFile;

    unique_ptr<XmlDefinition> definition;
    unique_ptr<XmlElement> xmlRoot;

    void BuildTree();

    void PrintTree(XmlElement& root, int tabs) const;
    string ToString(XmlElement& root) const;
    
};

#endif