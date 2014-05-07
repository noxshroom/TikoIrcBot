
#include "IrcBot.h"

using namespace std;

int main()
{
    // Init bot : username, real name
    IrcBot bot(string("MyTestBot"), string("John Smith"));
    bot.SetConnection(string("barjavel.freenode.net"), string("#BotTestFin"), 6666);
    if( !bot.Connect() )
        cout << "\nERROR: FAILED TO CONNECT" << endl;
    while ( bot.isConnected() ) {}
    return 0;
}
