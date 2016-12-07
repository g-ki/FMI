//
//  DOMDocument.cpp
//  XML Parser
//
//  Created by Georgi Kiryakov on 5/5/15.
//  Copyright (c) 2015 Georgi Kiryakov 81110. All rights reserved.
//

#include "DOMDocument.h"

DOMDocument::DOMDocument() {
    
}

void DOMDocument::loadXML(const string& str) {
    _xml = str;
    _xml.shrink_to_fit();
    parse();
}

void DOMDocument::load(const string& filename) {
    char line;
    ifstream myfile (filename);
    if (myfile.is_open())
    {
        _xml.clear();
        while ( myfile.get(line) )
            _xml += line;
        myfile.close();
        
        _xml.shrink_to_fit();
        parse();
    }
    else cout << "Unable to open file";
}

DOMDocument::operator string() const {
    return (string)*document();
};



void DOMDocument::parse() {
    // ([\\w-]+=[-\"'\\s\\w]+[\"']|[\\w-]+=[\\w-]+)
    // (([\\w-]+)=[\"']([\\w\\s]+)[\"']|([\\w-]+)=([\\w]+))
    
    // regex expressions
    regex startOfEl("<([\\w-]+)\\s*([\\sa-z0-9_='\";-]+)?>", regex_constants::icase);
    regex attributes("(([\\w-]+)=[\"']([\\w\\s]+)[\"']|([\\w-]+)=([\\w]+))", regex_constants::icase);
    regex endOfEl("<\\/[\\w-]+>", regex_constants::icase);
    regex text(">?([^<]+)<");
    
    cmatch sResults;
    cmatch tmpResults;
    
    const char* tmp = _xml.c_str();
    const char* tmp2;
    int tmp2Size;
    stack<DOMNode*> elStartStack;
    DOMNode *parent;
    string nodeValue;
    
    elStartStack.push(&doc);
    while (regex_search(tmp, sResults, startOfEl)) {
        size_t cutLen = sResults.position() + sResults.length();
        
        DOMElement *newEl = new DOMElement(sResults[1]);
        
        // set attributes to current element
        tmp2 = sResults[2].str().c_str();
        while (regex_search(tmp2, tmpResults, attributes)) {
            newEl->setAttribute(tmpResults[2], tmpResults[3]);
            tmp2 += tmpResults.position() + tmpResults.length();
        }
        // ... attributes
        
        // close parent node if needed
        tmp2 = tmp;
        tmp2Size = 0;
        regex_search(tmp2, tmpResults, endOfEl);
        
        while (sResults.position() - tmp2Size > tmpResults.position()) {
            parent = elStartStack.top();
            elStartStack.pop();
            parent->nodeParent(elStartStack.top());
            
            tmp2 += tmpResults.position() + tmpResults.length();
            tmp2Size += tmpResults.position() + tmpResults.length();
            
            regex_search(tmp2, tmpResults , text);
            nodeValue = tmpResults[1].str();
            nodeValue = trim(nodeValue);
            if(!nodeValue.empty())
                elStartStack.top()->nodeValue(elStartStack.top()->nodeValue()+ " " + nodeValue);
            
            regex_search(tmp2, tmpResults, endOfEl);
        }
        // ... close parent
        
        // get current parrent
        parent = elStartStack.top();
        parent->append(newEl);
        elStartStack.push(newEl);
        
        tmp += cutLen;
        
        // get text
        regex_search(tmp, tmpResults , text);
        nodeValue = tmpResults[1].str();
        nodeValue = trim(nodeValue);
        if(!nodeValue.empty())
            newEl->nodeValue(nodeValue);
    }
    
    
    // finish closing tags
    while (regex_search(tmp, tmpResults, endOfEl)) {
        DOMNode *c = elStartStack.top();
        elStartStack.pop();
        
        if(elStartStack.size() > 0)
            c->nodeParent(elStartStack.top());
        
        tmp += tmpResults.position() + tmpResults[0].length();
        
        regex_search(tmp, tmpResults , text);
        nodeValue = tmpResults[1].str();
        nodeValue = trim(nodeValue);
        if(!nodeValue.empty()) {
            if(elStartStack.top()->nodeValue().empty())
                elStartStack.top()->nodeValue(nodeValue);
            else
                elStartStack.top()->nodeValue(elStartStack.top()->nodeValue() + " " + nodeValue);
        }
        
    }
}

