#pragma once
#include<iostream>
#include<string>
#include"Node.h"
#include<utility>
#include<vector>

using namespace std;
class Trie
{
	Node* root;
	bool Search(string Word, string Type);

public:
	Trie();
	void Insert(string Word, bool isInsertFromFile);
	void DeleteWord(string Word);
	void DisplayByBFS(string Prefix);
	void DisplayByDFS(string Prefix);
	void DisplayByFrequecy(string Prefix);
	Node* FindNode(string Prefix);
	void saveToFiles(string Prefix,vector<pair<string, int>>& words);
	void getsuggestions(string Prefix,int operation);
	bool FindType(string prefix);
	string CaseSensitivity(string Word);
	bool ValidateWord(string Word);
};

