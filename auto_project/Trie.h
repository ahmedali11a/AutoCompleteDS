#pragma once
#include<iostream>
#include<string>
#include"Node.h"

using namespace std;
class Trie
{
	Node* root;

public:
	void Insert(string Word);
	bool Search(string Word);
	void DeleteWord(string Word);
	void DisplayByBFS(string Prefix);
	void DisplayByDFS(string Prefix);
	void DisplayByFrequecy(string Prefix);
	Node* FindNode(string Prefix);
	string CaseSensitivity(string Word);
	bool ValidatWord(string Word);
};

