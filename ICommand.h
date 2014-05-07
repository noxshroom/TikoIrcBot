///////////////////////////////////////////
#ifndef ICOMMAND_H
#define ICOMMAND_H
///////////////////////////////////////////
class IrcBot;
#include <string>
///////////////////////////////////////////
class ICommand
{
    public:
        ICommand(){}
        virtual ~ICommand(){}
        virtual void Execute(IrcBot* bot) = 0;
    protected:
    private:
};

#endif // ICOMMAND_H
