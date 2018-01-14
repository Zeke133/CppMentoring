
#include "Xml.h"

Xml::Xml(const vector<char>& sourceFile)
{
    // copy source to private field
    xmlFile = sourceFile;
    // trying to build tree of XML file
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
        auto content = entity.GetContent();
        if (entity.GetType() == XmlEntityType::Tag && XmlBuilder::GetTagType(content) == XmlTagType::Definition)
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

    if (entity.GetType() == XmlEntityType::Tag)
    {
        auto content = entity.GetContent();
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

    XmlBuilder::FillElement(*xmlRoot, entities);
    
}

void Xml::PrintTree() const
{
    cout << definition->GetContent() << endl;
    PrintTree(*xmlRoot, 0);
}

string Xml::ToString() const
{
    return ToString(*xmlRoot);
}

void Xml::PrintTree(XmlElement& root, int tabs) const
{
    for(int t = 0; t < tabs; t++)
            cout << "\t";

    cout << root.GetContent() << endl;

    auto data = root.GetData().GetContent();
    if (data.empty() == false)
    {
        for(int t = 0; t < tabs + 1; t++)
        cout << "\t";
        cout << data << endl;
    }

    for (auto child : root.GetChildren())
    {
        PrintTree(child, tabs + 1);   // recursion
    }
}

string Xml::ToString(XmlElement& root) const
{
    string text;
    auto name = root.GetName();

    if (name == "w:p") text += "\xd\xa";
    else if (name == "w:t")
    {
        auto data = root.GetData().GetContent();
        if (! data.empty()) text += data;
    }

    for (auto child : root.GetChildren())
    {
        text += ToString(child);    // recursion
    }

    return text;
}







