#ifndef XML_H
#define XML_H

#include <iostream>
#include <string_view>
#include <vector>
#include <list>
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
    void PrintTree() const;
    void ClearTree();

private:
    struct Node
    {
        XmlEntity * content;
        Node * parent;
        list<Node> children;
    } tree;

    void BuildTree(const vector<char> &xmlFile);
    void DeleteTree();
    void PrintNode(const Node& node, int tabs) const;
    void DeleteNode(Node& node);
    
};

#endif