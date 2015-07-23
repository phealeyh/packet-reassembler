#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Packet.h"
#include "Messages.h"

using namespace std;

/* Functional prototypes */
void printSyntax(char program[]);
void loadPackets(Messages &messages, const char *file);
void buildList(Messages &messages, Packet &packet);

void printSyntax(char program[]){
    cout << program << " is not the valid syntax. Syntax: " << program << "<packets-filename.txt" << endl;
}



void loadPackets(Messages &messages, const char *file){ //load packets into list
    ifstream fin;
    fin.open(file);
    if(!fin){
        cout << "Unable to read from " << file << endl;
        exit(0);
    }
    cout << "Read from " << file << endl;
    Packet packet;
    do{ //keep looping until end of file and END packet is found
        if(packet.loadedPacketIsGood(fin)){ //packet is good with variables loaded in
            //build the list
            buildList(messages,packet);
        }
    }while(!fin.eof() && !messages.endPacketReceived(packet));
    fin.close();
}

void buildList(Messages &messages,Packet &packet){
    Message *message;
    if(messages.messageExists(packet.getMID())) { //checking whether message exists
        message = messages.getMessage(packet); //message now points to existing message
        message->insertPacket(packet);
    }
    else if(!messages.endPacketReceived(packet)){ //no end packets received
        message = new Message(packet); //create new message along with a packet attached to it
        messages.insertMessage(*message); //insert message in linked list
        delete message; //message no longer needed
    }
}



int main(int argc, char *argv[]) {
    Messages messages; //object contains a linked list of messages
    if(argc != 2){
        printSyntax(argv[0]);
    }
    cout << "SUCCESS !" << endl;
    //load packets and build list
    loadPackets(messages, argv[1]);
    messages.printMessages(); //print messages
    return 0;
}