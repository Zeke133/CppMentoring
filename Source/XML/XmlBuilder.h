#ifndef XML_BUILDER_H
#define XML_BUILDER_H

#include <string_view>
#include <string>
#include <vector>

#include "XmlEntity.h"
#include "XmlEntities/XmlTag.h"
#include "XmlEntities/XmlData.h"
#include "XmlEntities/XmlTags/XmlElement.h"
#include "XmlEntities/XmlTags/XmlDefinition.h"

using namespace std;

namespace XML
{   

    class XmlBuilder
    {

    public:
        
        static XmlEntityType GetEntityType(string_view str);
        static XmlEntity TakeXmlEntity(vector<char>::const_iterator &it, vector<char>::const_iterator end);

        static XmlTagType GetTagType(string_view str);
        
        static string GetElementName(string str);
        static XmlElementType GetElementType(string_view str);

        static void Fill(XmlElement& parent, queue<XmlEntity> &entities);

    private:        

    };

};

#endif