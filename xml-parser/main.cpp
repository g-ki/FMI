//
//  main.cpp
//  XML Parser
//
//  Created by Georgi Kiryakov on 5/2/15.
//  Copyright (c) 2015 Georgi Kiryakov 81110. All rights reserved.
//

#include <iostream>
#include <curl/curl.h>
#include <typeinfo>
#include "DOMDocument.h"

using namespace std;


string tidy(string str){
    stringstream tmp;
    const char *p = str.c_str();
    int level = 0;
    
    while (*p != '\0') {
        if(*p == '<' && *(p+1) == '/' && *(p-1) == '>') {
            tmp << '\n';
            level--;
            for (int i=0; i<level; i++)
                tmp << '\t';
        } else if(*p == '<' && *(p+1) == '/')
            level--;
        else if(*p == '<') {
            
            if(level != 0)
                tmp << '\n';
            
            for (int i=0; i<level; i++)
                tmp << '\t';
            level++;
        }
        tmp << *p;
        p++;
    }
    
    return tmp.str();
}

size_t writeCurl(void *ptr, size_t size, size_t count, void *stream) {
    ((string*)stream)->append((char*)ptr, 0, size*count);
    return size*count;
}
CURL* curl;
CURLcode res;
string buffer;
void spider(const string& url) {
    
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        /* example.com is redirected, so we tell libcurl to follow redirection */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCurl);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        
        /* always cleanup */
        curl_easy_cleanup(curl);
        
        //cout<<buffer;
        
        DOMDocument doc;
        doc.loadXML(buffer);
        
        DOMElement* el = (DOMElement*)doc.document()->childNodes(0);
        
        string path;
        cout<<endl<<"XPath: "; cin>>path;
        el = &el->XPath(path);
        //cout<<el->nodeValue();
        cout<<tidy(*el);
    }
    
}

int main() {
    
    /*
    string url;
    url  = "http://www.senate.gov/general/contact_information/senators_cfm.xml";
    spider(url);
    */
    
    DOMDocument *doc;
    
    doc = new DOMDocument;
        
    doc->load("simple.xml");
    
    DOMElement* el = (DOMElement*)doc->document();
    DOMElement* newEl = new DOMElement("price", "$196");
    el->insert(newEl, el->childNodes(0));
    
    
    DOMElement &a = *(new DOMElement("tag", "#hashtag FMI"));
    
    el->insert(&a, el->childNodes(0));
    
    DOMElementList r = el->getElementsByTagName("price");
    for (int i=0; i<r.size(); i++) {
        cout<<r[i]->nodeValue()<<endl;
    }
    
    
    el = &el->XPath("food/price");
    cout<<endl;
    cout<<tidy(*el)<<endl;
    cout<<tidy(*doc);
    delete doc;
    
    return 0;
}
