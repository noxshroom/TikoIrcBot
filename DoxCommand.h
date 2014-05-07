///////////////////////////////////////////
#ifndef DOXCOMMAND_H
#define DOXCOMMAND_H
///////////////////////////////////////////
#include "ICommand.h"
#include "IrcBot.h"
///////////////////////////////////////////
class DoxCommand : public ICommand
{
    public:
        DoxCommand(std::string name) : ICommand() {m_name = name;}
        virtual ~DoxCommand() {}
        void Execute(IrcBot* bot)
        {
            std::string msg = bot->GetHandler()->LoadDox(m_name);
            std::string tmp = bot->ConstructString();
            // Handle the output
            if (msg == "ERROR")
            {
                std::cout << "\nThere was error with opening the file";
            }
            else if(msg == "NOTFOUND")
            {

                tmp += "I could not find nick.";
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

