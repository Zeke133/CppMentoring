
#include "Xml.h"


Xml::Xml(const vector<char>& sourceFile)
{
    xmlFile = sourceFile;
    BuildTree();
}

void Xml::BuildTree()
{
    // truncate begin and end of document
    string truncSymbols = " \n\r\t";
    {
        auto front = xmlFile.cbegin();
        while (string::npos != truncSymbols.find(*front))
        {
            xmlFile.erase(front);
            front = xmlFile.cbegin();
        }
    }
    {
        while (string::npos != truncSymbols.find(xmlFile.back()))
        {
            xmlFile.pop_back();
        }
    }

    auto begin = xmlFile.cbegin();
    auto end = xmlFile.cend();
    
    // take entities from text
    queue<XmlEntity> entities;
    while (begin < end)
    {
        // Take entity from text
        auto entity = XmlBuilder::TakeXmlEntity(begin, end);

        // If document definition - filling property
        auto content = entity.ToString();
        if (entity.GetEntityType() == XmlEntityType::Tag && XmlBuilder::GetTagType(content) == XmlTagType::Definition)
        {
            if (! definition)
                definition = unique_ptr<XmlDefinition> (new XmlDefinition(content));
            else
                throw invalid_argument("Repeat definition tag");
        }
        // Add entity to queue
        else
        {
            entities.push(entity); 
        }
    }

    // check for definition
    if (! definition) throw invalid_argument("No definition");

    // filling XML elements tree
    auto entity = entities.front();

    if (entity.GetEntityType() == XmlEntityType::Tag)
    {
        auto content = entity.ToString();
        if (XmlBuilder::GetTagType(content) == XmlTagType::Element)
        {
            // creating Root element
            auto name = XmlBuilder::GetElementName(content);
            auto type = XmlBuilder::GetElementType(content);
            xmlRoot = unique_ptr<XmlElement> (new XmlElement(content, name, type));

            entities.pop();
        }
    }
    else
    {
        throw invalid_argument("First entity isn't element");
    }

    XmlBuilder::Fill(*xmlRoot, entities);
    
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







