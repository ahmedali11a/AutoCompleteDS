#include "Files.h"
#include "Trie.h"
using namespace std;
Files::Files(string name)
{
	File = name;
	
}
void Files::Save(Trie& t)
{
	ofstream file(File);
	if (file.is_open())
	{
		vector<pair<string, int>> words;
		t.saveToFiles("\n",words);
		for (const auto& word : words)
		{
			file << word.first << " " << word.second << endl;
		}
	}
	else
	{
		cout << "Error opening file for writing." << endl;
	}
	file.close();
}
void Files::Load(Trie& t)
{
	ifstream file(File);
	if (!file.is_open()) {
		cout << "Error opening file for reading." << endl;
		return;
	}

	string word;
	int wordCount;
	while (file>> word>>wordCount) {
		if (word.empty()) {
			continue;
		}
		t.Insert(word,true);
		t.FindNode(word)->Frequency = wordCount;
	}
	file.close();
	cout << "File loaded successfully." << endl;

}
