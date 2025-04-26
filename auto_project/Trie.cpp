#include "Trie.h"
#include<iostream>
#include<queue>
#include<stack>
#include<string>
#include<algorithm>
#include<utility>
#include<vector>

Trie::Trie()
{
    root = new Node();
}

void Trie::IncreaseFrequency(string Word)
{
    Node* current = root;

    for (char letter : Word)
    {
        if (!current->letters[letter])
            return;

        current = current->letters[letter];
    }

    if (current->EndWord)
        current->Frequency++;
}

void Trie::Insert(string Word, bool isInsertFromFile)
{

    Word = CaseSensitivity(Word);

    if (!ValidateWord(Word))
    {
        cout << "The Word \"" << Word << "\" Invalid\n";
        return;
    }

    if (Search(Word, "word"))
        cout << "The Word \"" << Word << "\" Already Exist\n";

    Node* current = root;

    for (char letter : Word)
    {
        if (!current->letters[letter])
            current->letters[letter] = new Node();

        current = current->letters[letter];

    }
    current->EndWord = true;
    current->Frequency++;
    if (!isInsertFromFile) {
        cout << "The Word \"" << Word << "\" Inserted Successfully\n";
    }
}

void Trie::DeleteWord(string word) {
    word = CaseSensitivity(word);

    if (!ValidateWord(word)) {
        cout << "The Word \"" << word << "\" Invalid\n";
        return;
    }

    if (!Search(word, "word")) {
        cout << "The Word \"" << word << "\" Doesn't Exist\n";
        return;
    }

    Node* current = root;
    vector<pair<Node*, char>> path;
    for (char letter : word) {
        if (!current->letters[letter]) {
            cout << "Error: Word '" << word << "' not found during traversal.\n";
            return;
        }
        path.push_back({ current, letter }); 
        current = current->letters[letter];
    }

    current->EndWord = false;
    current->Frequency = 0;

    while (!path.empty()) {
        auto i = path.back();
        Node* child = i.first;
        path.pop_back();

        if (child->letters.empty() && !child->EndWord) {
            delete child; 
            i.first->letters.erase(i.second); 
        }
        else {
            break;
        }
    }

    cout << "Word '" << word << "' deleted successfully.\n";
}


bool Trie::Search(string Word , string Type)
{
    if (Type == "word")
    {
       
        Node* Current = root;

        for (char letter : Word)
        {
            if (!Current->letters[letter])
                return false;

            Current = Current->letters[letter];
        }

        return Current->EndWord;
    }
    else if (Type == "prefix")
    {      
        Node* Current = root;

        for (char letter : Word)
        {
            if (!Current->letters[letter])
                return false;

            Current = Current->letters[letter];
        }
        return true;
    }
      
}

vector<string> Trie::DisplayByBFS(string Prefix)
{
    vector<string> Words;
    Prefix = CaseSensitivity(Prefix);

    if (!ValidateWord(Prefix))
    {
        cout << "The Word \"" << Prefix << "\" Invalid\n";
        return Words;
    }

    if (!Search(Prefix, "prefix"))
    {
        cout << "The Word \"" << Prefix << "\" Doesn't Exist\n";
        return Words;
    }

    Node* Current = FindNode(Prefix);
    if (!Current)
        return Words;

    queue<pair<Node*, string>> q;
    q.push({ Current, Prefix });

    while (!q.empty())
    {
        auto front = q.front();
        q.pop();
        Node* node = front.first;
        string Word = front.second;

        if (node->EndWord)
        {
            Words.push_back(Word);
        }

        for (auto& pair : node->letters)
        {
            q.push({ pair.second, Word + pair.first });
        }
    }

    return Words;
}


vector<string> Trie::DisplayByDFS(string Prefix)
{
    vector<string> Words;
    Prefix = CaseSensitivity(Prefix);

    if (!ValidateWord(Prefix))
    {
        cout << "The Word \"" << Prefix << "\" Invalid\n";
        return Words;
    }

    if (!Search(Prefix, "prefix"))
    {
        cout << "The Word \"" << Prefix << "\" Doesn't Exist\n";
        return Words;
    }

    Node* startNode = FindNode(Prefix);
    if (!startNode)
        return Words;

    stack<pair<Node*, string>> nodeStack;
    nodeStack.push({ startNode, Prefix });

    while (!nodeStack.empty())
    {
        auto pairTop = nodeStack.top();
        Node* node = pairTop.first;
        string word = pairTop.second;
        nodeStack.pop();

        if (node->EndWord)
        {
            Words.push_back(word);
        }

        vector<pair<char, Node*>> sortedLetters(node->letters.begin(), node->letters.end());
        sort(sortedLetters.rbegin(), sortedLetters.rend());

        for (auto& pair : sortedLetters)
        {
            nodeStack.push({ pair.second, word + pair.first });
        }
    }

    return Words;
}

vector<string> Trie::DisplayByFrequecy(string Prefix)
{
    vector<string> Words;
    Prefix = CaseSensitivity(Prefix);

    if (!ValidateWord(Prefix))
    {
        cout << "The Word \"" << Prefix << "\" Invalid\n";
        return Words;
    }

    if (!Search(Prefix, "prefix"))
    {
        cout << "The Word \"" << Prefix << "\" Doesn't Exist\n";
        return Words;
    }

    Node* Current = FindNode(Prefix);
    if (!Current)
        return Words;

    queue<pair<Node*, string>> q;
    vector<pair<string, int>> WordsAndFrequency;

    q.push({ Current, Prefix });

    while (!q.empty())
    {
        auto front = q.front();
        q.pop();
        Node* node = front.first;
        string Word = front.second;

        if (node->EndWord)
            WordsAndFrequency.push_back({ Word, node->Frequency });

        for (auto& pair : node->letters)
            q.push({ pair.second, Word + pair.first });
    }

    sort(WordsAndFrequency.begin(), WordsAndFrequency.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
        });

    for (const auto& pair : WordsAndFrequency)
    {
        Words.push_back(pair.first);
    }

    return Words;
}

void Trie::saveToFiles(string Prefix,vector<pair<string,int>>&p)
{
    
    Node* Current = root;  

    queue<pair<Node*, string>> q;

    vector<pair<string, int>> WordsAndFrequency;

    q.push({ Current, Prefix });

    while (!q.empty())
    {
        auto front = q.front();

        q.pop();
        Node* node = front.first;
        string Word = front.second;

        if (node->EndWord)
            WordsAndFrequency.push_back({ Word,node->Frequency });


        for (auto pair : node->letters)
            q.push({ pair.second, Word + pair.first });

    }

    sort(WordsAndFrequency.begin(), WordsAndFrequency.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
        });

    p = WordsAndFrequency;  
}
void Trie::getsuggestions(string prefix, int operation) {
    vector<string> Words;

    if (operation == 1) {
        Words = DisplayByFrequecy(prefix);
    }
    else if (operation == 2) {
        Words = DisplayByBFS(prefix);
    }
    else if (operation == 3) {
        Words = DisplayByDFS(prefix);
    }
    else {
        cout << "Invalid operation." << endl;
        return;
    }

    if (Words.empty()) {
        cout << "No suggestions found for the prefix \"" << prefix << "\"." << endl;
        return;
    }

    cout << "Suggestions for \"" << prefix << "\":" << endl;

    int counter = 1;

    for (const auto& word : Words) {

        cout << counter++ << "-";
        if (word == prefix)
            cout << "*" << word << "*" << endl;
        else
            cout << word << endl;
    }
}



Node* Trie::FindNode(string Prefix)
{
    Prefix = CaseSensitivity(Prefix);
    if (!ValidateWord(Prefix))
        return NULL;

    if(!Search(Prefix,"prefix"))
        return NULL;

    Node* Current = root;

    for (char letter : Prefix)
    {
        if (!Current->letters[letter])
            return NULL;

        Current = Current->letters[letter];
    }

    return Current;
}

bool Trie::FindType(string prefix)
{
    Node* Current = FindNode(prefix);

    if (Current->EndWord)
        return false;
    else
        return true;
}

string Trie::CaseSensitivity(string Word)
{
    transform(Word.begin(), Word.end(), Word.begin(), ::tolower);

    return Word;
}

bool Trie::ValidateWord(string Word)
{
    for (char &letter : Word)
    {
        if (!isalpha(letter))
            return false;
    }

    return true;
}
