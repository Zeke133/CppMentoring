
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
        auto front = xmlFile.front();
        while (string::npos != truncSymbols.find(front))
        {
            xmlFile.pop_front();
            front = xmlFile.front();
        }
    }
    {
        auto back = xmlFile.back();
        while (string::npos != truncSymbols.find(back))
        {
            xmlFile.pop_back();
            back = xmlFile.back();
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
        if (entity.GetEntityType() == XmlEntityType::Tag && XmlTag::GetTagType(entity.ToString()) == XmlTagType::Definition)
        {
            if (! definition)
                definition = unique_ptr<XmlDefinition> (new XmlDefinition(entity));
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
    if (! definition) throw exception(/*no definition*/);

    // give queue to RootElement constructor which will build tree xml elements using recursion
    try
    {
        // creating Root element
        xmlRoot = unique_ptr<XmlElement> (new XmlElement(entities));
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







