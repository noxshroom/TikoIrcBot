/*
 * IrcBot.cpp
 *
 * Original by: Tyler Allen
 *
 * Modified by: Tommi Kärki
 */
///////////////////////////////////////////
#include "IrcBot.h"
///////////////////////////////////////////
using namespace std;
///////////////////////////////////////////
//#define SERVER_ADDRESS "blacklotus.ca.us.quakenet.org"
//#define SERVER_CHANNEL "#kareliatiko"
//#define PORT "6667"
/////////////////////////////////////////////////////////////////////////
// Converts char* string or passes p_string to init
IrcBot::IrcBot(string _nick, string _usr) : nick(""),usr(""),server(""),channel(""),socketId(0),port(0)
{
    // Set login stuff
    string tmp = "NICK ";
    tmp = tmp + _nick + "\r\n";
    nick = tmp;
    tmp = ""; // Reset tmp

    tmp = "USER guest tolmoon tolsun :";
    tmp = tmp + _usr + "\r\n";
    usr = tmp;

    // Set default channel and server
    server = SERVER_ADDRESS;
    channel = SERVER_CHANNEL;
    handler = new XMLHandler();
    fact = new CommandFactory(this);
}
/////////////////////////////////////////////////////////////////////////
// Cleans up
IrcBot::~IrcBot()
{
    delete handler;
    delete fact;
    close (socketId);
}
/////////////////////////////////////////////////////////////////////////
XMLHandler* IrcBot::GetHandler()
{
    return handler;
}
/////////////////////////////////////////////////////////////////////////
CommandFactory* IrcBot::GetFactory()
{
    return fact;
}
/////////////////////////////////////////////////////////////////////////
void IrcBot::SetConnection(string _server, string _channel, int _port)
{
    server = _server;
    channel = _channel;
    port = _port;
}
/////////////////////////////////////////////////////////////////////////
bool IrcBot::Connect()
{
    struct addrinfo hints, *servinfo;

    //Ensure that servinfo is clear
    memset(&hints, 0, sizeof hints); // make sure the struct is empty

    //setup hints
    hints.ai_family = AF_UNSPEC; // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets

    //Setup the structs if error print why
    int res;
    if ((res = getaddrinfo(SERVER_ADDRESS,PORT,&hints,&servinfo)) != 0)
    {
        fprintf(stderr,"getaddrinfo: %s\n", gai_strerror(res));
        return false;
    }

    //setup the socket
    if ((socketId = socket(servinfo->ai_family,servinfo->ai_socktype,servinfo->ai_protocol)) == -1)
    {
        perror("client: socket");
        return false;
    }

    //Connect
    if (connect(socketId,servinfo->ai_addr, servinfo->ai_addrlen) == -1)
    {
        close (socketId);
        perror("Client Connect");
        return false;
    }

    //We dont need this anymore
    freeaddrinfo(servinfo);

    int count = 0;
    while (count < 10)
    {
        //declars
        count++;

        switch (count)
        {
        case 3:
            //after 3 recives send data to server (as per IRC protacol)
            sendData(nick);
            sendData(usr);
            break;
        case 4:
            //Join a channel after we connect, this time we choose beaker
            sendData(string("JOIN ") + channel + "\r\n");
        default:
            break;
        }

        // Receive and print initial connecting data
        numbytes = recv(socketId,buf,MAXDATASIZE-1,0);
        buf[numbytes]='\0';
        cout << buf;


        // If PING was sent early
        if (charSearch(buf,"PING"))
        {
            sendPong(buf);
        }

        // Something closed connection
        if (numbytes==0)
        {
            cout << "----------------------CONNECTION CLOSED---------------------------"<< endl;
            cout << timeNow() << endl;

            break;
        }
    }
    return true;
}
/////////////////////////////////////////////////////////////////////////
bool IrcBot::isConnected()
{
    // Receive & print data
    numbytes = recv(socketId,buf,MAXDATASIZE-1,0);
    buf[numbytes]='\0';
    cout << buf;

    // Handle messages sent at channel
    msgHandler(buf);

    // PING is special case, handle here
    if (charSearch(buf,"PING"))
        {   sendPong(buf);  }

    // Exit if connection closed
    if (numbytes==0)
    {
        cout << "----------------------CONNECTION CLOSED---------------------------"<< endl;
        cout << timeNow() << endl;
        return false;
    }
    return true;
}
/////////////////////////////////////////////////////////////////////////
bool IrcBot::charSearch(char *toSearch, char *searchFor)
{
    int len = strlen(toSearch);
    int forLen = strlen(searchFor); // The length of the searchfor field

    //Search through each char in toSearch
    for (int i = 0; i < len; i++)
    {
        //If the active char is equil to the first search item then search toSearch
        if (searchFor[0] == toSearch[i])
        {
            bool found = true;
            //search the char array for search field
            for (int x = 1; x < forLen; x++)
            {
                if (toSearch[i+x]!=searchFor[x])
                {
                    found = false;
                }
            }

            //if found return true;
            if (found == true)
                return true;
        }
    }

    return 0;
}
/////////////////////////////////////////////////////////////////////////
char * IrcBot::timeNow()
{
    //returns the current date and time
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    return asctime (timeinfo);
}
/////////////////////////////////////////////////////////////////////////
bool IrcBot::sendData(const string& msg)
{
    int bytes_sent = send(socketId, msg.c_str(), msg.length(), 0);
    // Copy to console what was sent. Strip \r\n from end.
    cout << "\nI sent: " << msg << endl;
    bool rtrn = false;
    if( bytes_sent > 0) rtrn = true;
    return rtrn;
}
/////////////////////////////////////////////////////////////////////////
void IrcBot::sendPong(char *buf)
{
    //Get the reply address
    //loop through bug and find the location of PING
    //Search through each char in toSearch

    char * toSearch = "PING ";

    for (uint i = 0; i < strlen(buf); i++)
    {
        //If the active char is equil to the first search item then search toSearch
        if (buf[i] == toSearch[0])
        {
            bool found = true;
            //search the char array for search field
            for (int x = 1; x < 4; x++)
            {
                if (buf[i+x]!=toSearch[x])
                {
                    found = false;
                }
            }

            //if found return true;
            if (found == true)
            {
                int count = 0;
                //Count the chars
                for (uint x = (i+strlen(toSearch)); x < strlen(buf); x++)
                {
                    count++;
                }

                //Create the new char array
                char returnHost[count + 5];
                returnHost[0]='P';
                returnHost[1]='O';
                returnHost[2]='N';
                returnHost[3]='G';
                returnHost[4]=' ';

                count = 0;
                //set the hostname data
                for (uint x = (i+strlen(toSearch)); x < strlen(buf); x++)
                {
                    returnHost[count+5]=buf[x];
                    count++;
                }

                //send the pong
                if (sendData(string(returnHost)))
                {
                    cout << timeNow() <<"  Ping Pong" << endl;
                }

                return;
            }
        }
    }

}
/////////////////////////////////////////////////////////////////////////
void IrcBot::msgHandler(char * buf)
{
    string msg(buf);
    istringstream s(msg);
    /////////// Extract info from string to factory ///////////////
    // nick is parsed here
    // :nick!~
    string first = "";
    s >> first;
    size_t position;
    position = first.find("!~");
    if ( position != string::npos) {
        fact->Sender.nick = first.substr(1,position-1);
        }
    else
        return;
    // username
    // :nick!~username@host
    size_t positionOfA;
    positionOfA = first.find("@");
    if( positionOfA != string::npos) {
        fact->Sender.username = first.substr(position+2,positionOfA-position-2);
        }
    else
        return;
    // Rest of data is seperated by space
    // stringstream to seperate words
    s >> fact->Sender.command;
    s >> fact->Sender.target;
    // Rest of string contains message
    string message;
    size_t positionOfMessage;
    // Extract it
    positionOfMessage = msg.find( fact->Sender.target) + fact->Sender.target.length();
    message = msg.substr(positionOfMessage);
    // If message was empty, set it to NOMSG
    if ( message.length() > 0) {
        fact->Sender.message = message.substr(2);
        }
    else { fact->Sender.message = "NOMSG";}

    // Create command and execute functionality
    ICommand * cmd = fact->Create(fact->Sender.message);
    if(cmd)
        cmd->Execute(this);
    delete cmd;
}
/////////////////////////////////////////////////////////////////////////
void IrcBot::SendRaw(const string& msg)
{
    string tmp = msg;
    tmp += "\r\n";
    if( sendData(tmp))
    {
        cout << "Data successfully sent." << endl;
    }else cout << "No bytes sent." << endl;
}
/////////////////////////////////////////////////////////////////////////
string IrcBot::ConstructString()
{
    string rtrn = "PRIVMSG ";
    // Strip NICK from nick to get actual nickname
    string tmpnick = nick.substr(5);
    // Add \r\n to end so compare works
    string tmp = GetFactory()->Sender.target + "\r\n";
    if( tmpnick.compare(tmp) == 0) {
        rtrn += GetFactory()->Sender.nick;
    }
    else{
        rtrn += GetFactory()->Sender.target;
    }
    rtrn += " :";
    return rtrn;
}
