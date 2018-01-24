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

namespace XML
{   

    class XmlBuilder
    {

    public:

        // builing XML. truncates source file, fills xmlRoot with all children and xmlDefinition.
        static std::tuple<std::unique_ptr<XmlElement>, std::unique_ptr<XmlDefinition>> BuildXml(const std::vector<char>& sourceFile);

    private:
    
        // parsing text for entities
        static XmlEntity TakeXmlEntity(std::vector<char>::const_iterator &it, std::vector<char>::const_iterator end);

        // entity level
        static XmlEntityType GetEntityType(std::string_view str);

        // tag level
        static XmlTagType GetTagType(std::string_view str);
        
        // element level
        static std::string GetElementName(std::string str);
        static XmlElementType GetElementType(std::string_view str);

        // filling tree of elements
        static void FillElement(XmlElement& root, std::queue<XmlEntity> &entities);  

    };

};

#endif