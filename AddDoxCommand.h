#ifndef ADDDOXCOMMAND_H
#define ADDDOXCOMMAND_H

#include "ICommand.h"
#include "IrcBot.h"

class AddDoxCommand : public ICommand
{
    public:
        AddDoxCommand(std::string info) : ICommand()
        {m_info = info;}
        virtual ~AddDoxCommand() {}
        void Execute(IrcBot* bot)
        {
            std::string tmp = bot->ConstructString();
            std::string msg = "";
            msg= bot->GetHandler()->SaveDox(bot->GetFactory()->Sender.nick ,m_info);
            if(msg == "SUCCESS")
            {
                tmp +=  "Info succesfully added.";
                bot->SendRaw(tmp);
            }
        }
    protected:
    private:
        std::string m_info;
};

#endif
