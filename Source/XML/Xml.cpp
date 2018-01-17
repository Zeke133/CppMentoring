
#include "Xml.h"

Xml::Xml(const vector<char>& sourceFile)
{
    // copy source to private field
    xmlFile = sourceFile;
    // trying to build tree of XML file
    XmlBuilder::BuildXml(xmlFile, xmlRoot, definition);
}

XmlElement Xml::GetRootElement() const
{
    return *xmlRoot;
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

void Xml::PrintVisualTree() const
{
    cout << definition->GetContent() << endl;
    PrintTree(*xmlRoot, 0);
}










