#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include <limits>
#include<fstream>
#include"Node.h"
#include"Trie.h"
#include"Files.h"

using namespace std;

int main()
{

    Trie trie;
    Files fileHandler("Dictionary.txt");
    fileHandler.Load(trie);
    string input;
    int choice, sortOption , searchWord;
    vector<string> Words;

    while (true) {
        cout << "\nAutocomplete Menu:\n";
        cout << "1. Get suggestions\n";
        cout << "2. Add word\n";
        cout << "3. Delete word\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 5) {
            fileHandler.Save(trie);
            break;
        }

        switch (choice) {
        case 1:
            cout << "Enter prefix: ";
            getline(cin, input);
            if (input.empty()) {
                cout << "Error: Empty input." << endl;
                break;
            }
            cout << "Sort options:\n";
            cout << "1. By frequency (default)\n";
            cout << "2. By length (shortest first)\n";
            cout << "3. Lexicographical order\n";
            cout << "Enter sort option: ";
            cin >> sortOption;
            if (sortOption < 1 || sortOption > 3) {
                sortOption = 1; // Default to frequency
            }
            trie.getsuggestions(input, sortOption);
            if (sortOption == 2)
                Words = trie.DisplayByBFS(input);
            else if (sortOption == 3)
                Words = trie.DisplayByDFS(input);
            else if (sortOption == 1)
                Words = trie.DisplayByFrequecy(input);

            cout << "The Word You Are Looking For :";
            cin >> searchWord;
            trie.IncreaseFrequency(Words[searchWord - 1]);
            break;
        case 2:
            cout << "Enter word to add: ";
            getline(cin, input);
            trie.Insert(input,false);
            break;
        case 3:
            cout << "Enter word to delete: ";
			getline(cin, input);
			trie.DeleteWord(input);
			break;
        default:
            cout << "Error: Invalid choice." << endl;
        }
    }
}