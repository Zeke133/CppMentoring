#ifndef XML_BUILDER_H
#define XML_BUILDER_H

#include <string_view>
#include <string>
#include <vector>

using namespace std;

namespace XML
{   

    class XmlBuilder
    {

    public:
        
        static XmlEntityType GetEntityType(string_view str);
        static XmlEntity TakeXmlEntity(vector<char>::const_iterator &it, vector<char>::const_iterator end);

        static XmlTagType GetTagType(string_view str);
        
        static string_view GetElementName(string_view str);
        static XmlElementType GetElementType(string_view str);

        
        void SetCharData(const XmlData &data);
        XmlElement * AddChild(const XmlElement &child);
        void Fill(queue<XmlEntity> &elements);

    private:
        

    };

};

#endif