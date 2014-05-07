#include "ICommand.h"
class LinkCommand : public ICommand
{
    public:
        LinkCommand();
        virtual ~LinkCommand();
        void Execute(CommandFactory* fact)
        {
            //A;
        }
    protected:
    private:
};

