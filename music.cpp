#include <iostream>
#include <string>
using namespace std;

struct Song {
    string title;
    Song* prev;
    Song* next;

    // Constructor to initialize song title
    Song(string title) : title(title), prev(nullptr), next(nullptr) {}
};

class Playlist {
private:
    Song* head;
    Song* tail;
    Song* current;

public:
    // Constructor to initialize playlist
    Playlist() : head(nullptr), tail(nullptr), current(nullptr) {}

    // Add a new song to the end of the playlist
    void addSong(const string& title) {
        Song* newSong = new Song(title);
        if (!head) {  // First song in the playlist
            head = tail = current = newSong;
        } else {      // Append to the end
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }
        cout << "Added song: " << title << endl;
    }

    // Remove the current song from the playlist
    void removeCurrentSong() {
        if (!current) {
            cout << "No song to remove." << endl;
            return;
        }

        cout << "Removing song: " << current->title << endl;

        // Update links for removal
        if (current == head) {
            head = current->next;
            if (head) head->prev = nullptr;
        } else {
            current->prev->next = current->next;
        }

        if (current == tail) {
            tail = current->prev;
            if (tail) tail->next = nullptr;
        } else {
            current->next->prev = current->prev;
        }

        Song* temp = current;

        // Move current to the next song if available
        current = (current->next) ? current->next : tail;
        delete temp;
    }

    // Go to the next song in the playlist
    void nextSong() {
        if (!current || !current->next) {
            cout << "End of the playlist." << endl;
            return;
        }
        current = current->next;
        cout << "Playing: " << current->title << endl;
    }

    // Go to the previous song in the playlist
    void previousSong() {
        if (!current || !current->prev) {
            cout << "Start of the playlist." << endl;
            return;
        }
        current = current->prev;
        cout << "Playing: " << current->title << endl;
    }

    // Display the current song
    void playCurrentSong() {
        if (!current) {
            cout << "Playlist is empty." << endl;
            return;
        }
        cout << "Currently playing: " << current->title << endl;
    }

    // Display all songs in the playlist
    void showPlaylist() {
        if (!head) {
            cout << "Playlist is empty." << endl;
            return;
        }
        Song* temp = head;
        cout << "Playlist: ";
        while (temp) {
            cout << temp->title;
            if (temp->next) cout << " -> ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    Playlist myPlaylist;
    string input;
    int choice;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add song\n";
        cout << "2. Show playlist\n";
        cout << "3. Play current song\n";
        cout << "4. Next song\n";
        cout << "5. Previous song\n";
        cout << "6. Remove current song\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter song title: ";
                cin.ignore();  // Clear the newline character from the input buffer
                getline(cin, input);
                myPlaylist.addSong(input);
                break;
            case 2:
                myPlaylist.showPlaylist();
                break;
            case 3:
                myPlaylist.playCurrentSong();
                break;
            case 4:
                myPlaylist.nextSong();
                break;
            case 5:
                myPlaylist.previousSong();
                break;
            case 6:
                myPlaylist.removeCurrentSong();
                break;
            case 7:
                cout << "Exiting the playlist." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}