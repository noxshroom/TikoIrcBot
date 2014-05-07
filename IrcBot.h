/*
 * IrcBot.h
 *
 * Original by: Tyler Allen
 *
 * Modified by: Tommi Kärki
 */
///////////////////////////////////////////
#ifndef IRCBOT_H_
#define IRCBOT_H_
///////////////////////////////////////////
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include "ICommand.h"
#include "CommandFactory.h"
#include "XMLHandler.h"
///////////////////////////////////////////
using std::string;
// How many chars stored in buffer at once
#define MAXDATASIZE 200
// Default server,channel,port
#define SERVER_ADDRESS "barjavel.freenode.net"
#define SERVER_CHANNEL "#BotTestFin"
#define PORT "6666"
///////////////////////////////////////////
class IrcBot
{
public:
    // Constructors & Destructor
    IrcBot(string _nick, string _usr);
    virtual ~IrcBot();
    // Accessors & Mutators
    XMLHandler* GetHandler();
    CommandFactory* GetFactory();
    void SetConnection(string _server, string _channel, int _port);
    // Connection methods
    bool Connect();
    bool isConnected();
    // Public implementation
    void SendRaw(const string& msg);
    string ConstructString();

private:
    // Private variables
    string nick,usr,server,channel;
    int socketId, port;
    // Pointers
    CommandFactory* fact;
    XMLHandler* handler;
    // Tools methods
    bool charSearch(char *toSearch, char *searchFor);
    char * timeNow();
    // Message methods
    bool sendData(const string& msg);
    void sendPong(char *buf);
    void msgHandler(char *buf);
    // Internal for connection
    int numbytes;
    char buf[MAXDATASIZE];

};

#endif /* IRCBOT_H_ */
