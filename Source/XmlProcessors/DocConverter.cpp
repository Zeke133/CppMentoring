#include "DocConverter.h"

using namespace std;
using namespace XML;

string DocConverter::ToString(XmlElement& root)
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

