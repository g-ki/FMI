//
//  DOMNode.cpp
//  XML Parser
//
//  Created by Georgi Kiryakov on 5/5/15.
//  Copyright (c) 2015 Georgi Kiryakov 81110. All rights reserved.
//

#include "DOMNode.h"

DOMNode::DOMNode() : _nodeParent(NULL) {
    //cout<<"::DOMNode";
}

DOMNode::~DOMNode() {
    for (size_t i=0; i < _childNodes.size(); i++) {
        delete _childNodes[i];
    }
}

size_t DOMNode::findChildPosition(const DOMNode *node) const {
    for (size_t i=0; i < _childNodes.size(); i++) {
        if(node == _childNodes[i])
            return i;
    }
    
    return SIZE_T_MAX;
}

void DOMNode::remove(const DOMNode* node) {
    
    size_t index = findChildPosition(node);
    if(index != SIZE_T_MAX) {
        delete _childNodes[index];
        _childNodes.erase(_childNodes.begin() + index);
    }
}

DOMNode* DOMNode::insert(DOMNode *newnode, DOMNode *refnode) {
    
    if(newnode == NULL)
        return NULL;
    
    if(refnode == NULL)
    {
        _childNodes.push_back(newnode);
        return newnode;
    }
    
    size_t index = findChildPosition(refnode);
    if(index != SIZE_T_MAX)
        _childNodes.insert(_childNodes.begin() + index, newnode);
    
    return newnode;
}

DOMNode* DOMNode::append(DOMNode *newnode) {
    return insert(newnode);
}

bool DOMNode::hasAttributes() const {
    return !_attributes.empty();
}

bool DOMNode::hasChildNodes() const {
    return !_childNodes.empty();
}

void DOMNode::nodeParent(DOMNode *node) {
    _nodeParent = node;
}

void DOMNode::nodeValue(const string value) {
    _nodeValue = value;
}

void DOMNode::nodeName(const string name) {
    _nodeName = name;
}


DOMNode* DOMNode::childNodes(size_t index) const {
    if(index < _childNodes.size())
        return _childNodes[index];
    
    return NULL;
}

DOMNode::operator string() const {
    stringstream str;
    
    str << "<" << _nodeName;
    for(auto& x: _attributes){
        str << " ";
        str << x.first << "='" << x.second <<"'";
    }
    str << ">";
    str << _nodeValue;
    for (size_t i=0; i < _childNodes.size(); i++) {
        str << *childNodes()[i];
    }
    str << "</" << _nodeName << ">";
    
    return str.str();
}

ostream& operator<<(ostream& os, const DOMNode& node) {
    return os << (string)node;
}