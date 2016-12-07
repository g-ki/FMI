//
//  DOMElement.h
//  XML Parser
//
//  Created by Georgi Kiryakov on 5/3/15.
//  Copyright (c) 2015 Georgi Kiryakov 81110. All rights reserved.
//

#ifndef __XML_Parser__DOMElement__
#define __XML_Parser__DOMElement__

#include <iostream>
#include <map>
#include <regex>
#include "DOMNode.h"

using namespace std;

class DOMElement : public DOMNode {
protected:
    
    string _tagName;
    
public:
    DOMElement();
    DOMElement(string name, string value = "");
    
    string tagName() const;
    
    bool hasAttribute(string name);
    string getAttribute(string name);
    void setAttribute(string name, string value);
    void removeAttribte(string name);
    
    DOMElementList childNodes() const;
    DOMElement* childNodes(size_t index) const;
    
    DOMElementList getElementsByTagName(string name, bool descendant=true) const;
    
    DOMElement& XPath(string query);
};

#endif /* defined(__XML_Parser__DOMElement__) */
