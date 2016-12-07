//
//  DOMDocument.h
//  XML Parser
//
//  Created by Georgi Kiryakov on 5/5/15.
//  Copyright (c) 2015 Georgi Kiryakov 81110. All rights reserved.
//

#ifndef __XML_Parser__DOMDocument__
#define __XML_Parser__DOMDocument__

#include "DOMNode.h"
#include "DOMElement.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <stack>

using namespace std;

class DOMDocument {
protected:
    string _xml;
    DOMNode doc;
    
    void parse();
    
    static string& trim(string& str){
        str.erase(str.begin(), find_if(str.begin(), str.end(),
                                       [](char& ch)->bool { return !isspace(ch); }));
        str.erase(find_if(str.rbegin(), str.rend(),
                          [](char& ch)->bool { return !isspace(ch); }).base(), str.end());
        return str;
    }
    
public:
    
    DOMDocument();
    
    void load(const string&);
    void loadXML(const string&);
    
    DOMNode* document() const { return doc.childNodes(0);}
    
    operator string() const;
};



#endif /* defined(__XML_Parser__DOMDocument__) */
