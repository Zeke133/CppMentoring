#ifndef XML_BUILDER_H
#define XML_BUILDER_H

#include <string_view>
#include <string>
#include <vector>
#include <queue>
#include <stdexcept>
#include <memory>
#include <tuple>

#include "../DataModels/DataModels.h"

using namespace std;

namespace XML
{   

    class XmlBuilder
    {

    public:

        // builing XML. truncates source file, fills xmlRoot with all children and xmlDefinition.
        static tuple<unique_ptr<XmlElement>, unique_ptr<XmlDefinition>> BuildXml(const vector<char>& sourceFile);

    private:
    
        // parsing text for entities
        static XmlEntity TakeXmlEntity(vector<char>::const_iterator &it, vector<char>::const_iterator end);

        // entity level
        static XmlEntityType GetEntityType(string_view str);

        // tag level
        static XmlTagType GetTagType(string_view str);
        
        // element level
        static string GetElementName(string str);
        static XmlElementType GetElementType(string_view str);

        // filling tree of elements
        static void FillElement(XmlElement& root, queue<XmlEntity> &entities);  

    };

};

#endif