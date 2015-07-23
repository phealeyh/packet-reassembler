//
// Created by Phealey on 22/04/2015.
//
#include <list>
#include <iterator>
#include <string>
#include "Packet.h"
using namespace std;

class Message{
    friend class Messages;
    friend class Packet;
private:
    int messageID;
    list<Packet> packets;

    const list<Packet>::iterator getPosition(const int &sequenceN){
        list<Packet>::iterator itr = packets.begin();
        for(; itr != packets.end(); ++itr){
            if(itr->getSequenceNumber() > sequenceN){
                return itr;
            }
        }
        return packets.end();
    }


public:
    Message(){
    }

    Message(Packet &packet)
    {
        messageID = packet.messageID;
        packets.push_back(packet); //add packet to list
    }

    Message(const Message &other) ://messages variable is read-only
            packets(other.packets),
            messageID(other.messageID)
    {
        // copy constructor
    }
    ~Message(){
    }

    const void insertPacket(const Packet &packet) {
        packets.insert(getPosition(packet.getSequenceNumber()),packet);
    }

};
