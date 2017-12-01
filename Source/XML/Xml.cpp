
#include "Xml.h"

struct Node
{
    XmlEntity * content;
    Node * parent;
    vector<Node *> children;
};

string_view GetTag(vector<char>::const_iterator &cit, vector<char>::const_iterator cend)
{
auto begin = cit;

    while (cit != cend && *cit != '>')
    {
        cit += 1;
    }
    cit += 1;
    uint32_t length = cit - begin;
    string_view tagContent(&(*begin), length);
    return tagContent;
}

string_view GetData(vector<char>::const_iterator &cit, vector<char>::const_iterator cend)
{
auto begin = cit;

    while (cit != cend && *cit != '<')
    {
        cit += 1;
    }
    string_view data(&(*begin), cit - begin);
    return data;
}

void BuildTree(const vector<char> &xmlFile)
{
    auto cbegin = xmlFile.cbegin();
    auto cend = xmlFile.cend();

    vector<string_view> strings;

    auto curr = cbegin;
    while(curr != cend)
    {
        // Trash
        if(*curr == '\n' || *curr == '\r' || *curr == '\t') curr += 1;
        // Tag
        else if(*curr == '<')
        {
            string_view tag = GetTag(curr, cend);
            strings.push_back(tag);            
        }
        // Data
        else
        {
            string_view body = GetData(curr, cend);
            strings.push_back(body);
        }
    }

    cout << "Xml tags are:" << endl;
    for(auto str : strings)
    {
        cout << str << endl;
    }

    Node tree;
    tree.parent = NULL; //root
    Node * currNode = &tree;
    for(auto str : strings)
    {
        XmlEntity entity(str);
        auto entityType = entity.GetEntityType();
        switch(entityType)
        {
            case XmlEntityType::CharData:
            {
                Node * child = new Node {new XmlData(str), currNode};
                currNode->children.push_back(child);
                break;
            }
            case XmlEntityType::Tag:
            {
                XmlTag tag(str);
                auto tagType = tag.GetTagType();
                switch(tagType)
                {
                    case XmlTagType::Element:
                    {
                        XmlElement element(str);
                        auto elementType = element.GetElementType();
                        switch(elementType)
                        {
                            case XmlElementType::Start:
                            {
                                Node * child = new Node {new XmlElement(str), currNode};
                                currNode->children.push_back(child);
                                currNode = child;
                                break;
                            }
                            case XmlElementType::End:
                            {
                                auto end = XmlElement(str);
                                XmlElement * start = static_cast<XmlElement *>(currNode->content);
                                if ( end.GetElementName() == (*start).GetElementName() )
                                {
                                    currNode = currNode->parent;
                                }
                                else throw exception();
                                break;
                            }
                            case XmlElementType::Empty:
                            {
                                Node * child = new Node {new XmlElement(str), currNode};
                                currNode->children.push_back(child);
                                break;
                            }
                            default: throw exception();
                        }
                        break;
                    }
                    case XmlTagType::Definition:
                    {
                        Node * child = new Node {new XmlDefinition(str), currNode};
                        currNode->children.push_back(child);
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



