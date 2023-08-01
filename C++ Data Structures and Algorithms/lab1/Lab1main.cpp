//Collaboration with Nathan Shin, Michael Bettencourt, and Rahul Katwala
#include <iostream>
#include <string>

using namespace std;

#include "Playlist.h"

void PrintMenu();
void AddSong(PlaylistNode* &head, PlaylistNode* &tail);
void RemoveSong(PlaylistNode* &head, PlaylistNode* &tail);
void ChangePosition(PlaylistNode* &head, PlaylistNode* &tail);
void OutputSongsArtist(PlaylistNode* head);
int OutputTotalTimeInSeconds(PlaylistNode* head);
void OutputFullPlaylist(PlaylistNode* head);

int main() {
    PlaylistNode* head = nullptr; //variable declarations
    PlaylistNode* tail = nullptr;
    string playlistTitle;
    char userOption;

    cout << "Enter playlist's title:" << endl; //user prompt for playlist title
    getline(cin, playlistTitle);
    cout << endl;

    //menu continues to loop until user enters 'q'
    do {
        cout << playlistTitle << " PLAYLIST MENU" << endl;
        PrintMenu();
        cin >> userOption;

        /*need cin.ignore for newline characters after almost every cin >>;
          otherwise newline would be taken in by getline as the val for
          whatever var is passed*/
        cin.ignore(1000, '\n');
        cout << endl;

        if(userOption == 'a') {
            AddSong(head, tail);
        }

        if(userOption == 'd') {
            RemoveSong(head, tail);
        }

        if(userOption == 'c') {
            ChangePosition(head, tail);
        }

        if(userOption == 's') {
            OutputSongsArtist(head);
        }

        if(userOption == 't') {
            cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
            cout << "Total time: " << OutputTotalTimeInSeconds(head) << " seconds" << endl << endl;
        }

        if(userOption == 'o') {
            cout << playlistTitle << " - OUTPUT FULL PLAYLIST" << endl;
            OutputFullPlaylist(head);
        }


  
    } while (userOption != 'q');

    return 1;

}

void PrintMenu() {
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl << endl;
    cout << "Choose an option:";
}

void AddSong(PlaylistNode* &head, PlaylistNode* &tail) {
    string uniqueID;
    string songName;
    string artistName;
    int songLengthInSeconds;

    cout << "ADD SONG" << endl;
    cout << "Enter song's unique ID:" << endl; //user prompts for parameters to add a new song
    cin >> uniqueID;
    cin.ignore(1000, '\n');
    cout << "Enter song's name:" << endl;
    getline(cin, songName);
    cout << "Enter artist's name:" << endl;
    getline(cin, artistName);
    cout << "Enter song's length (in seconds):" << endl;
    cin >> songLengthInSeconds;
    cin.ignore(1000, '\n');
    cout << endl;

    PlaylistNode* newSong = new PlaylistNode(uniqueID,songName,artistName,songLengthInSeconds); //create pointer to newSong. New song's nxtPtr will always be nullptr


    if(head == nullptr) { //if head and tail are nullptr, then set both head and tail to newSong
        head = newSong;
        tail = newSong;
    }

    else {
        tail -> SetNext(newSong);
        tail = newSong;
    }

}

void RemoveSong(PlaylistNode* &head, PlaylistNode* &tail) {
    if(head == nullptr) {
        cout << "Playlist is empty" << endl << endl;
        return;
    }

    string uniqueID;
    PlaylistNode* next = head;
    PlaylistNode* prev = nullptr;

    cout << "REMOVE SONG" << endl;
    cout << "Enter song's unique ID:" << endl;
    cin >> uniqueID;
    cin.ignore(1000, '\n');

    while(next != nullptr) {
        if(next->GetID() == uniqueID) {
            cout << "\"" << next->GetSongName() << "\" removed." << endl;
            
            if(next == head) {
                head = next->GetNext();
                delete next;
                
            }

            else if (next == tail) {
                tail = prev;
                prev->SetNext(nullptr);
                delete next;

                
            }

            else {
                PlaylistNode* temp = next->GetNext();
                prev->SetNext(temp);
                delete next;
            }
            
            break;
        }
        prev = next;
        next = next->GetNext();
    }
    cout << endl;
}

void OutputFullPlaylist(PlaylistNode* head){
    if(head == nullptr) {
        cout << "Playlist is empty" << endl << endl;
        return;
    }

    unsigned positionOnPlaylist = 1;
    PlaylistNode* temp = head;

    while (temp != nullptr) {
        cout << positionOnPlaylist << "." << endl;
        temp->PrintPlaylistNode();
        cout << endl;
        positionOnPlaylist++;
        temp = temp->GetNext();
    }
}
void OutputSongsArtist(PlaylistNode* head) {
    string artistName;
    int positionOnPlaylist = 1;
    PlaylistNode* temp = head;

    cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
    cout << "Enter artist's name:" << endl << endl;
    getline(cin, artistName);

    while (temp != nullptr) {
        if(temp->GetArtistName() == artistName) {
            cout << positionOnPlaylist << "." << endl;
            temp->PrintPlaylistNode();
            cout << endl;
        }
        temp = temp->GetNext();
        positionOnPlaylist++;
    }
}

int OutputTotalTimeInSeconds(PlaylistNode* head) {
    int totalSongLength = 0;
    PlaylistNode* temp = head;

    while(temp != nullptr) {
        totalSongLength += temp->GetSongLength();
        temp = temp->GetNext();
    }

    return totalSongLength;
}

void ChangePosition(PlaylistNode* &head, PlaylistNode* &tail) {
    int oldPos;
    int newPos;
    cout << "CHANGE POSITION OF SONG" << endl;
    cout << "Enter song's current position:" << endl;
    cin >> oldPos;
    cout << "Enter new position for song:" << endl;
    cin >> newPos;
    
    PlaylistNode* prev = 0;
    PlaylistNode* curr = head;
    
    if ( head == tail) {
        return;
    }
    
   //finds chosen node from the list
    for (int i = 1; i < oldPos; i++) {
        prev = curr;
        curr = curr->GetNext();
    }

    string SongName = curr->GetSongName();
    
    // removes chosen node from the list
    if (prev == 0) {
        head = curr->GetNext();
    }
    
    else {
        prev->SetNext(curr->GetNext());
    }

    if (curr == tail){
        tail = prev;
    }
    
    PlaylistNode* temp = curr; // assigns temp to the selected node
    prev = nullptr;
    curr = head;
    int counter = 0; //how many nodes are in the list
    
    //adds chosen node into new selected spot
    
    for(PlaylistNode* i=head; i!=0; i=i->GetNext()){
        counter++;
    }
    
    if(newPos > counter) {
        tail->SetNext(temp);
        temp -> SetNext(nullptr);
        tail=temp;
    }
    
    else if (newPos<=1) {
        temp->SetNext(head);
        head = temp;
    }
    
    else {
        
        for (int i = 1; i < newPos; i++) {
            prev = curr;
            curr = curr->GetNext();
        }

        PlaylistNode* sub = prev->GetNext();
        prev->SetNext(temp);
        temp->SetNext(sub);
    }
    
    cout << "\"" << SongName << "\" moved to position " << newPos << endl;
    cout<< endl;
    return;
           

}
