
#include "Xml.h"

struct Node
{
    XmlEntity * content;
    Node * parent;
    list<Node> children;
};

void BuildTree(const vector<char> &xmlFile)
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

    cout << "Xml contants are:" << endl;
    for(auto entity : entities)
    {
        cout << entity.GetContent() << endl;
    }

    Node tree;
    tree.parent = NULL; //root
    Node * currNode = &tree;
    for(auto entity : entities)
    {
        auto entityContent = entity.GetContent();

        switch(entity.GetEntityType())
        {
            case XmlEntityType::CharData:
            {
                currNode->children.push_back(Node {new XmlData(entity), currNode});
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
                                currNode->children.push_back(Node {new XmlElement(entity), currNode});
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
                                currNode->children.push_back(Node {new XmlElement(entity), currNode});
                                break;
                            }
                            default: throw exception();
                        }
                        break;
                    }
                    case XmlTagType::Definition:
                    {
                        currNode->children.push_back(Node {new XmlDefinition(entity), currNode});
                        break;
                    }
                    default: throw exception();
                }
                break;
            }
            default: throw exception();
        }        
    }

    cout << "tree build" << endl;
}

Xml::Xml(const vector<char> &xmlFile)
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
    cout << "XML close" << endl;
}



