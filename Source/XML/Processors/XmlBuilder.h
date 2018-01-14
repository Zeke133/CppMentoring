#ifndef XML_BUILDER_H
#define XML_BUILDER_H

#include <string_view>
#include <string>
#include <vector>
#include <queue>
#include <stdexcept>

#include "../DataModels/DataModels.h"

using namespace std;

namespace XML
{   

    class XmlBuilder
    {

    public:

        // entity  -   Tags        -   elements    -   start       <element1>
        //                                             end         </element1>
        //                                             empty       <empty_element1 />
        //                        
        //                         -   definition                  <?xml version="1.1" encoding="UTF-8" ?>
        //
        //                         -   Comment                     <!-- это комментарий -->
        //
        //                         -   DocType                     <!DOCTYPE greeting SYSTEM "hello.dtd">
        //
        //                         -   ProcInstr                   <?xml-stylesheet href="my-style.css"?>
        //                         -   CDATA
        //                         -   Reference
        //
        //         -   CharData                                    text

        // document -   definition
        //          -   element         -   name
        //                              -   type???
        //                              -   char content
        //                              -   properties
        
        // entity level
        static XmlEntityType GetEntityType(string_view str);
        static XmlEntity TakeXmlEntity(vector<char>::const_iterator &it, vector<char>::const_iterator end);

        // tag level
        static XmlTagType GetTagType(string_view str);
        
        // element level
        static string GetElementName(string str);
        static XmlElementType GetElementType(string_view str);

        // filling tree of elements
        static void FillElement(XmlElement& root, queue<XmlEntity> &entities);

    private:        

    };

};

#endif