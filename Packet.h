//
// Created by Phealey on 22/04/2015.
//

#ifndef REAL_ASSIGNMENT_PACKET_H //take out when not needed !!!!!!!!!
#define REAL_ASSIGNMENT_PACKET_H //take out when not needed !!!!!!!!!

#include <string>
#include <stdlib.h>

using namespace std;


class Packet{
    friend class Messages;
    friend class Message;
private:
    int messageID; //could be an 'end' packet
    string sequenceNumber;
    string message;
    string packet;

    /* Private helper methods used for storing the private members */
    const void storeMessageID(){
        messageID = atoi(packet.substr(0, 3).c_str());
    }


    const void storeSequenceNumber(){
        int location = packet.find(":");
        sequenceNumber = packet.substr(location + 1,location);
    }

    const void storeMessage(){
        int location = packet.find(sequenceNumber);
        string temp;
        temp = packet.substr(location);
        int newLocation = temp.find(":");
        message = temp.substr(newLocation + 1, temp.size());
    }



public:
    Packet(){
    }
    Packet(const Packet &other):
            message(other.message),
            packet(other.packet),
            messageID(other.messageID),
            sequenceNumber(other.sequenceNumber)
    {
        // copy constructor
    }

    bool loadedPacketIsGood(ifstream &fin){
        char string[100];
        fin.getline(string, 100);
        packet = string; //load packet
        storeMessageID();
        storeSequenceNumber();
        storeMessage();
        return fin.good();
    }

    const string getPacket() const{
        return packet;
    }

    const int getSequenceNumber() const{
        return atoi(sequenceNumber.c_str());
    }

    const int getMID() {
        return messageID;
    }
    const string getMessage() const{
        return message;
    }

};
#endif //REAL_ASSIGNMENT_PACKET_H -- take out when not needed !!!!!!!!