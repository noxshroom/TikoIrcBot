///
// Made by: Tommi Kärki
///
///////////////////////////////////////////
#ifndef XML_HANDLER_H
#define XMLHANDLER_H
///////////////////////////////////////////
#include "tinyxml2.h"
#include <string>
using namespace std;
using namespace tinyxml2;
///////////////////////////////////////////
class XMLHandler
{
    public:
        XMLHandler();
        virtual ~XMLHandler();
        string LoadLink(string name);
        string SaveLink(string name, string url);
        string LoadDox(string name);
        string SaveDox(string name, string info);
    protected:
    private:
};

#endif // XMLHANDLER_H
