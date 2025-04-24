#pragma once
#include<iostream>
#include<string>
#include"Node.h"

using namespace std;
class Trie
{
	Node* root;
	bool Search(string Word, string Type);

public:
	Trie();
	void Insert(string Word);	
	void DeleteWord(string Word);
	void DisplayByBFS(string Prefix);
	void DisplayByDFS(Node*node,string Prefix);
	void DisplayByFrequecy(string Prefix);
	Node* FindNode(string Prefix);
	string CaseSensitivity(string Word);
	bool ValidateWord(string Word);
};

