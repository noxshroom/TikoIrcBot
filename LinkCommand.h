///////////////////////////////////////////
#ifndef LINKCOMMAND_H
#define LINKCOMMAND_H
///////////////////////////////////////////
#include "ICommand.h"
#include "IrcBot.h"
///////////////////////////////////////////
class LinkCommand : public ICommand
{
    public:
        LinkCommand(std::string name) : ICommand() {m_name = name;}
        virtual ~LinkCommand() {}
        void Execute(IrcBot* bot)
        {
            std::string msg = bot->GetHandler()->LoadLink(m_name);
            std::string tmp = bot->ConstructString();
            // Handle the output
            if (msg == "ERROR")
            {
                std::cout << "\nThere was error with opening the file";
            }
            else if(msg == "NOTFOUND")
            {

                tmp += "I could not find link.";
                bot->SendRaw(tmp);
            }
            else
            {
                tmp += msg;
                bot->SendRaw(tmp);
            }
        }
    protected:
    private:
        std::string m_name;
};
#endif


