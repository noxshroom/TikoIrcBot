#ifndef ADDLINKCOMMAND_H
#define ADDLINKCOMMAND_H

#include "ICommand.h"
#include "IrcBot.h"

class AddLinkCommand : public ICommand
{
    public:
        AddLinkCommand(std::string name, std::string url) : ICommand()
        {m_name = name; m_url = url;}
        virtual ~AddLinkCommand() {}
        void Execute(IrcBot* bot)
        {
            std::string tmp = bot->ConstructString();
            std::string msg = "";

            msg= bot->GetHandler()->SaveLink(m_name,m_url);
            if(msg == "SUCCESS")
            {
                tmp +=  "Link added succesfully.";
                bot->SendRaw(tmp);
            }
        }
    protected:
    private:
        std::string m_name, m_url;
};

#endif // ADDLINKCOMMAND_H
