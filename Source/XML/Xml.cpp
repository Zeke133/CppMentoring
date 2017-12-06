
#include "Xml.h"


Xml::Xml(const vector<char>& xmlFile)
{    
    try
    {
        BuildTree(xmlFile);
    } 
    catch(exception)
    {
        throw exception();
    }
}

Xml::~Xml()
{
    ClearTree();
}

void Xml::BuildTree(const vector<char>& xmlFile)
{
    auto begin = xmlFile.cbegin();
    auto end = xmlFile.cend();
    end --;
    
    // truncate begin and end of document
    while (begin < end && (*begin == '\n' || *begin == '\r' || *begin == '\t')) begin ++;
    while (begin <= end && (*end == '\n' || *end == '\r' || *end == '\t')) end --;
    end ++;
    
    // take entities
    list<XmlEntity> entities;
    while (begin < end)
    {
        entities.push_back(XmlEntity::TakeXmlEntity(begin, end));
    }

    tree.content = NULL;
    tree.parent = NULL; //root
    Node * currNode = &tree;

    for(auto e : entities)
    {
        auto entityContent = e.GetContent();

        switch(e.GetEntityType())
        {
            case XmlEntityType::CharData:
            {
                currNode->children.push_back(Node {new XmlData(e), currNode});
                break;
            }
            case XmlEntityType::Tag:
            {
                switch(XmlTag::GetTagType(entityContent))
                {
                    case XmlTagType::Element:
                    {
                        switch(XmlElement::GetElementType(entityContent))
                        {
                            case XmlElementType::Start:
                            {
                                currNode->children.push_back(Node {new XmlElement(e), currNode});
                                currNode = &(currNode->children.back());
                                break;
                            }
                            case XmlElementType::End:
                            {
                                if ( XmlElement::GetElementName(entityContent) == static_cast<XmlElement *>(currNode->content)->GetElementName() )
                                {
                                    currNode = currNode->parent;
                                }
                                else throw exception();
                                break;
                            }
                            case XmlElementType::Empty:
                            {
                                currNode->children.push_back(Node {new XmlElement(e), currNode});
                                break;
                            }
                            default: throw exception();
                        }
                        break;
                    }
                    case XmlTagType::Definition:
                    {
                        currNode->children.push_back(Node {new XmlDefinition(e), currNode});
                        break;
                    }
                    default: throw exception();
                }
                break;
            }
            default: throw exception();
        }
    }    
}

void Xml::DeleteNode(Node& node)
{
    for(auto child : node.children)
        DeleteNode(child);

    node.children.clear();
    
    delete node.content;
}

void Xml::ClearTree()
{
    DeleteNode(tree);
}

void Xml::PrintNode(const Node& node, int tabs) const
{
    for(int t = 0; t < tabs; t++)
        cout << "\t";

    if (node.parent == NULL)
        cout << "<ROOT>" << endl;
    else
        cout << node.content->GetContent() << endl;

    for(auto child : node.children)
        PrintNode(child, tabs + 1);
}

void Xml::PrintTree() const
{
    PrintNode(tree, 0);
}


