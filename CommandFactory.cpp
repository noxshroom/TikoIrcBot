#include "CommandFactory.h"
#include "LinkCommand.h"
#include "AddLinkCommand.h"
#include "AddDoxCommand.h"
#include "DoxCommand.h"

CommandFactory::CommandFactory()
{
    //ctor
}

CommandFactory::CommandFactory(IrcBot* bot)
{
    m_bot = bot;
}

CommandFactory::~CommandFactory()
{

}

ICommand* CommandFactory::Create(std::string msg)
{
    std::istringstream s(msg);
    std::string word;
    s >> word;

    if( word == "!iltalehti")
    {

    }
    else if( word == "!link")
    {
        s >> word;
        return new LinkCommand(word);
    }
    else if( word == "!addlink")
    {
        s >> word;
        std::string url;
        s >> url;
        return new AddLinkCommand(word,url);
    }
    else if( word == "!doxme")
    {
        s >> word;
        return new AddDoxCommand(word);
    }
    else if( word == "!dox")
    {
        s >> word;
        return new DoxCommand(word);
    }
    return NULL;
}
