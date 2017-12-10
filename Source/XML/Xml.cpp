
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
    if (definition != NULL) delete definition;
    if (xmlRoot != NULL) delete xmlRoot;
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
    
    // take entities from text
    queue<XmlEntity> entities;
    while (begin < end)
    {
        // Take entity from text
        auto entity = XmlEntity::TakeXmlEntity(begin, end);

        // If document definition - filling property
        if (entity.GetEntityType() == XmlEntityType::Tag && XmlTag::GetTagType(entity.ToString()) == XmlTagType::Definition)
        {
            if (definition == NULL)
                definition = new XmlDefinition(entity);
            else
                throw exception(/*repeat definition, only one definition allowed*/);
        }
        // Add entity to queue
        else
        {
            entities.push(entity); 
        }
    }

    // check for definition
    if (definition == NULL) throw exception(/*no definition*/);

    // give queue to RootElement constructor which will build tree xml elements using recursion
    try
    {
        // creating Root element
        xmlRoot = new XmlElement(entities);
    }
    catch(exception)
    {
        throw exception(/* Error creating Root*/);
    }
}

void Xml::PrintTree() const
{
    cout << definition->ToString() << endl;
    xmlRoot->PrintContent(0);
}

string Xml::ToString() const
{
    return xmlRoot->ToString();
}







