//Collaboration with Nathan Shin, Michael Bettencourt, and Rahul Katwala
#include <iostream>
#include <string>

using namespace std;

#include "Playlist.h"

PlaylistNode::PlaylistNode(): uniqueID("none"), songName("none"), artistName("none"), songLength(0), nextNodePtr(nullptr){
}

PlaylistNode::PlaylistNode(string uniqueID, string songName, string artistName, int songLength){
    this->uniqueID = uniqueID;
    this->songName = songName;
    this->artistName = artistName;
    this->songLength = songLength;
    nextNodePtr = nullptr;
}

string PlaylistNode::GetID() const {
    return uniqueID;
}

string PlaylistNode::GetSongName() const {
    return songName;
}

string PlaylistNode::GetArtistName() const {
    return artistName;
}

int PlaylistNode::GetSongLength() const {
    return songLength;
}

PlaylistNode* PlaylistNode::GetNext() const {
    return nextNodePtr;
}

void PlaylistNode::PrintPlaylistNode() const {
    cout << "Unique ID: " << this->uniqueID << endl;
    cout << "Song Name: " << this->songName << endl;
    cout << "Artist Name: " << this->artistName << endl;
    cout << "Song Length (in seconds): " << this->songLength << endl;
}

void PlaylistNode::InsertAfter(PlaylistNode* &insert) {
    PlaylistNode* temp = this->nextNodePtr;
    this->SetNext(insert);
    insert->SetNext(temp);
      
}

void PlaylistNode::SetNext(PlaylistNode* next) {
    if(next == nullptr) {
        nextNodePtr = nullptr;
        
    }

    else {
        nextNodePtr = next;
    }
   
}
