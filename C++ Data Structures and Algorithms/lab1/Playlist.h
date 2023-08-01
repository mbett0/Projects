//Collaboration with Nathan Shin, Michael Bettencourt, and Rahul Katwala
#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>

using namespace std;

class PlaylistNode {
    private:
        string uniqueID;
        string songName;
        string artistName;
        int songLength;
        PlaylistNode* nextNodePtr;
    public:
        PlaylistNode();
        PlaylistNode(string uniqueID, string songName, string artistName, int songLength);
        string GetID() const;
        string GetSongName() const;
        string GetArtistName() const;
        int GetSongLength() const;
        PlaylistNode* GetNext() const;
        void PrintPlaylistNode() const;
        void InsertAfter(PlaylistNode* &insert);
        void SetNext(PlaylistNode* next);
};

#endif
