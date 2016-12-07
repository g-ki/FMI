//
//  DOMElement.cpp
//  XML Parser
//
//  Created by Georgi Kiryakov on 5/3/15.
//  Copyright (c) 2015 Georgi Kiryakov 81110. All rights reserved.
//

#include "DOMElement.h"

DOMElement::DOMElement(){
    
}

DOMElement::DOMElement(string name, string value)
{
    _tagName = name;
    _nodeName = name;
    _nodeValue = value;
}

string DOMElement::tagName() const {
    return _tagName;
}

string DOMElement::getAttribute(string name) {
    return _attributes.find(name)->second;
}

void DOMElement::setAttribute(string name, string value) {
    _attributes[name] = value;
}

void DOMElement::removeAttribte(string name) {
    _attributes.erase(name);
}

bool DOMElement::hasAttribute(string name) {
    if(_attributes.count(name) > 0)
        return true;
    
    return false;
}

DOMElementList DOMElement::childNodes() const {
    vector<DOMElement*> tmp(_childNodes.size());
    for (size_t i=0; i<_childNodes.size(); i++)
        tmp.push_back((DOMElement*)_childNodes[i]);
    
    return tmp;
}

DOMElement* DOMElement::childNodes(size_t index) const {
    if(index < _childNodes.size())
        return (DOMElement*)_childNodes[index];
    
    return NULL;
}

DOMElementList DOMElement::getElementsByTagName(string name, bool descendant) const {
    DOMElementList results;
    DOMElement* currnet;
    for (size_t i=0; i<_childNodes.size(); i++) {
        currnet = (DOMElement*)_childNodes[i];
        if(currnet->tagName() == name)
            results.push_back(currnet);
        
        if(descendant) {
            DOMElementList currentResults = currnet->getElementsByTagName(name);
            results.reserve(results.size() + currentResults.size());
            results.insert(results.end(), currentResults.begin(), currentResults.end());
        }
    }
    
    return results;
}

DOMElement& DOMElement::XPath(string query) {
    DOMElement* result = new DOMElement;
    result->_nodeName = "XPath";
    
    regex path("([-\\w]+)\\[?(\\d+|@[-'\"= \\w]+)?\\]?/?");
    regex attrRegex("[\"']([- \\w]+)?[\"']");
    smatch match, attrMathc;
    
    result->append(_nodeParent);
    DOMElement* current;
    while (regex_search(query, match, path)) {
        
        size_t size = result->size();
        for (size_t i=0; i<size; i++) {
            current = (DOMElement*)result->_childNodes.front();
           
            DOMElementList elements = current->getElementsByTagName(match[1]);
            
            result->_childNodes.insert(result->_childNodes.end(), elements.begin(), elements.end());
            
            result->_childNodes.erase(result->_childNodes.begin());
        }
        
        if(match[2].length() > 0) {
            
            if(match[2].str().find('@') < match.length()) {
                string attr = match[2];
                string attrValue;
                
                
                attr = attr.substr(1);
                
                DOMNodeList elements;
                
                regex_search(attr, attrMathc, attrRegex);
                
                if(!attrMathc.empty()) {
                    attrValue = attrMathc[1];
                    attr = attrMathc.prefix();
                    attr = attr.substr(0, attr.size() - 1);
                }
                
                for (size_t i=0; i<result->size(); i++) {
                    
                    if(result->childNodes(i)->hasAttribute(attr))
                    {
                        if(!attrValue.empty()) {
                            if(attrValue == result->childNodes(i)->getAttribute(attr))
                              elements.push_back(result->_childNodes[i]);
                        } else
                            elements.push_back(result->_childNodes[i]);
                    }
                    
                }
                result->_childNodes = elements;
                
            } else {
                current = result->childNodes(stoi(match[2]));
                result->_childNodes.clear();
                if(current != NULL)
                    result->append(current);
            }
            
        }
        
        query = match.suffix().str();
    }
    
    if(result->size() == 1)
        return *result->childNodes(0);
    
    return *result;
}
