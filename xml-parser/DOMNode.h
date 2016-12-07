//
//  DOMNode.h
//  XML Parser
//
//  Created by Georgi Kiryakov on 5/5/15.
//  Copyright (c) 2015 Georgi Kiryakov 81110. All rights reserved.
//

#ifndef __XML_Parser__DOMNode__
#define __XML_Parser__DOMNode__

#include <iostream>
#include <sstream>
#include <regex>
#include <vector>
#include <map>
#include <string>

using namespace std;

class DOMElement;
class DOMNode;

typedef vector<DOMNode*> DOMNodeList;
typedef vector<DOMElement*> DOMElementList;

class DOMNode {
    
protected:
    string _nodeName;
    string _nodeValue;
    DOMNode* _nodeParent;
    DOMNodeList _childNodes;
    map<string, string> _attributes;
    string _textContent;

public:
    
    DOMNode();
    ~DOMNode();
    
    size_t findChildPosition(const DOMNode*) const;
    
    bool hasAttributes() const;
    bool hasChildNodes() const;
    
    size_t size() const { return _childNodes.size(); }
    
    void remove(const DOMNode*);
    DOMNode* insert(DOMNode*, DOMNode* refnode=NULL);
    DOMNode* append(DOMNode*);
    
    /* Properties */
    
    void nodeName(const string);
    void nodeValue(const string);
    void nodeParent(DOMNode*);
    
    string nodeName() const { return _nodeName; }
    string nodeValue() const { return _nodeValue; }
    
    const DOMNode* nodeParent() const { return _nodeParent; }
    
    DOMNodeList childNodes() const { return _childNodes; }
    DOMNode* childNodes(size_t index) const;
    
    friend ostream& operator<<(ostream&, const DOMNode&);
    virtual operator std::string() const;
};

#endif /* defined(__XML_Parser__DOMNode__) */
