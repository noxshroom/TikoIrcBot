#include "XMLHandler.h"
#include <iostream>
#include <list>
/////////////////////////////////////////////////////////////////////////
XMLHandler::XMLHandler()
{
    //ctor
}
/////////////////////////////////////////////////////////////////////////
XMLHandler::~XMLHandler()
{
    //dtor
}
/////////////////////////////////////////////////////////////////////////
string XMLHandler::LoadLink(string name)
{
    XMLDocument doc;
    doc.LoadFile("links.xml");
    if( doc.Error() )
    {
        cout << "\nERROR:" << doc.ErrorID() << endl;
        return "ERROR";
    }

    XMLElement* rootNode = doc.FirstChildElement("Links");
    if (!rootNode) std::cout << "No Links element" << std::endl;

    XMLElement* linkNode = rootNode->FirstChildElement("Link");
    if(!linkNode) std::cout << "No link elements" << std::endl;

    // Loop through XML
    for( ; linkNode != NULL; linkNode = linkNode->NextSiblingElement() )
    {
        if( name == linkNode->Attribute("name") )
        {
            return linkNode->Attribute("url");
        }
    }

    return "NOTFOUND";
}
/////////////////////////////////////////////////////////////////////////
string XMLHandler::SaveLink(string name, string url)
{
    // Load existing links
    XMLDocument doc;
    doc.LoadFile("links.xml");

    if( doc.Error() ) {std::cout << "ERROR_SAVE: Could not open links.\n";}

    XMLElement* rootNode = doc.FirstChildElement("Links");
    if (!rootNode) std::cout << "No Links element" << std::endl;

    XMLElement* linkNode = rootNode->FirstChildElement("Link");
    if(!linkNode) std::cout << "No link elements" << std::endl;

    // Struct which contains data from one link
    struct Data
    {
        string name;
        string url;
    };
    // List of Data, basically contains everything from XML
    list<Data> dump;

    // Loop through XML
    for( ; linkNode != NULL; linkNode = linkNode->NextSiblingElement() )
    {
        Data d;
        d.name = linkNode->Attribute("name");
        d.url = linkNode->Attribute("url");
        dump.push_back(d);
    }

    // Set exist flag false if not found, otherwise update previous entry
    bool exist = false;
    for(auto it = dump.begin(); it != dump.end(); ++it)
    {
        if(it->name == name)
        {
            it->url = url;
            exist = true;
            break;
        }
    }

    // Link was not found, append
    if(!exist)
    {
        Data d;
        d.name = name;
        d.url = url;
        dump.push_back(d);
    }

    // Finally save new file
    FILE* file = fopen("links.xml", "w+");
    XMLPrinter printer(file);
    printer.PushHeader(true,true);

    printer.OpenElement("Links");
    for(Data d : dump)
    {
        printer.OpenElement("Link");
        printer.PushAttribute("name", d.name.c_str() );
        printer.PushAttribute("url", d.url.c_str() );
        printer.CloseElement();
    }
    printer.CloseElement();
    fclose(file);

    return "SUCCESS";
}
/////////////////////////////////////////////////////////////////////////
string XMLHandler::LoadDox(string name)
{
    XMLDocument doc;
    doc.LoadFile("dox.xml");
    if( doc.Error() )
    {
        cout << "\nERROR:" << doc.ErrorID() << endl;
        return "ERROR";
    }

    XMLElement* rootNode = doc.FirstChildElement("People");
    if (!rootNode) std::cout << "No Links element" << std::endl;

    XMLElement* linkNode = rootNode->FirstChildElement("Person");
    if(!linkNode) std::cout << "No link elements" << std::endl;

    // Loop through XML
    for( ; linkNode != NULL; linkNode = linkNode->NextSiblingElement() )
    {
        if( name == linkNode->Attribute("name") )
        {
            return linkNode->Attribute("info");
        }
    }

    return "NOTFOUND";
}
/////////////////////////////////////////////////////////////////////////
string XMLHandler::SaveDox(string name, string info)
{
    // Load existing links
    XMLDocument doc;
    doc.LoadFile("dox.xml");

    if( doc.Error() ) {std::cout << "ERROR_SAVE: Could not open dox.\n";}

    XMLElement* rootNode = doc.FirstChildElement("People");
    if (!rootNode) std::cout << "No People element" << std::endl;

    XMLElement* linkNode = rootNode->FirstChildElement("Person");
    if(!linkNode) std::cout << "No Person elements" << std::endl;

    // Struct which contains data from one link
    struct Data
    {
        string name;
        string info;
    };
    // List of Data, basically contains everything from XML
    list<Data> dump;

    // Loop through XML
    for( ; linkNode != NULL; linkNode = linkNode->NextSiblingElement() )
    {
        Data d;
        d.name = linkNode->Attribute("name");
        d.info = linkNode->Attribute("info");
        dump.push_back(d);
    }

    // Set exist flag false if not found, otherwise update previous entry
    bool exist = false;
    for(auto it = dump.begin(); it != dump.end(); ++it)
    {
        if(it->name == name)
        {
            it->info = info;
            exist = true;
            break;
        }
    }

    // Link was not found, append
    if(!exist)
    {
        Data d;
        d.name = name;
        d.info = info;
        dump.push_back(d);
    }

    // Finally save new file
    FILE* file = fopen("dox.xml", "w+");
    XMLPrinter printer(file);
    printer.PushHeader(true,true);

    printer.OpenElement("People");
    for(Data d : dump)
    {
        printer.OpenElement("Person");
        printer.PushAttribute("name", d.name.c_str() );
        printer.PushAttribute("info", d.info.c_str() );
        printer.CloseElement();
    }
    printer.CloseElement();
    fclose(file);

    return "SUCCESS";
}
