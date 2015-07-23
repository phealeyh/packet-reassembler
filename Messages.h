//
// Created by Phealey on 22/04/2015.
//
#include <iostream>
#include <list>
#include <iterator>
#include <iomanip>
#include "Message.h"

using namespace std;

class Messages{
    /* Private class variables */
private:
    list<Message> messages;

    const list<Message>::iterator getPosition(const int &mID){ //finds the position for the new element
        list<Message>::iterator itr = messages.begin();
        for(; itr != messages.end(); ++itr){
            if(itr->messageID > mID){
                return itr;
            }
        }
        return messages.end();
    }


public:
    Messages(){
    }
    Messages(const Messages &other) ://messages variable is read-only
            messages(other.messages)
    {
        // copy constructor
    }

    /* Functions */

    const void printMessages(){ //prints out esch message
        list<Message>::iterator mITR = messages.begin();
        list<Packet>::iterator pITR;
        for(; mITR != messages.end(); ++mITR){
            cout << "Message " << setfill('0') << setw(3) << mITR->messageID << endl;
            for(pITR = mITR->packets.begin();pITR != mITR->packets.end(); ++pITR){
                cout <<  pITR->getPacket() << endl;
            } //compress line
            cout << endl;
        }
    }


    const void insertMessage(const Message &message){ //insert new messages
        if(messages.empty()){//just simply add the message
            messages.push_back(message);
        }
        else{ //list isn't empty
            messages.insert(getPosition(message.messageID),message);
        }
    }



    bool messageExists(const int &mID){ //checks if message exists
        list<Message>::iterator itr = messages.begin();
        for(; itr != messages.end(); itr++){
            if(itr->messageID == mID){ //message exists
                return true;
            }
        }
        return false;
    }

    Message* getMessage(Packet &packet){ //returns existing message
        list<Message>::iterator itr = messages.begin();
        for(; itr != messages.end(); itr++){
            if(itr->messageID == packet.messageID){ //message exists
                return &(*itr);
            }
        }
    }
    const bool endPacketReceived(Packet &packet)const{
        return packet.message.compare("END") == 0;
    }

};