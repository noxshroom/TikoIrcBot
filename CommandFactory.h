///////////////////////////////////////////
#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H
///////////////////////////////////////////
#include <string>
#include <sstream>
#include "ICommand.h"
class IrcBot;
///////////////////////////////////////////
class CommandFactory
{
    public:
        CommandFactory();
        CommandFactory(IrcBot* bot);
        virtual ~CommandFactory();
        ICommand* Create( std::string msg);
        struct p_Sender{
            std::string nick;
            std::string username;
            std::string command;
            std::string target;
            std::string message;
        } Sender;
    protected:
    private:
        IrcBot* m_bot;
};

#endif // COMMANDFACTORY_H
