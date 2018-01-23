#ifndef XML_H
#define XML_H

#include <iostream>
#include <string_view>
#include <queue>
#include <exception>
#include <memory>
#include <tuple>

#include "DataModels/DataModels.h"
#include "Builder/Builder.h"

class Xml
{

public:

    Xml(const vector<char> &sourceFile);

    XML::XmlElement GetRootElement() const;

    void PrintVisualTree() const;

private:

    unique_ptr<XML::XmlDefinition> definition;
    unique_ptr<XML::XmlElement> xmlRoot;

    void PrintTree(XML::XmlElement& root, int tabs) const;
        
};


#endif