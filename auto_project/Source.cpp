#include<iostream>
#include"Node.h"
#include"Trie.h"
using namespace std;

int main()
{

	Trie trie;

	trie.Insert("Ahmed");
	trie.Insert("ali");
	trie.Insert("aly");
	trie.Insert("Ahmed");
	trie.Insert("soliman");
	trie.Insert("soqiman");
	trie.Insert("soliman");
	trie.Insert("Ahmed");
	trie.Insert("ahmad");
	trie.Insert("ahm");

	string prefix;

	

	

	for(int i=0;i<3;i++)
	{
		cin >> prefix;

	

		trie.DisplayByBFS(prefix);
		cout << "===================\n";
		trie.DisplayByDFS(prefix);
		cout << "===================\n";
		trie.DisplayByFrequecy(prefix);
		cout << "===================\n";

	}

	return 0;
}