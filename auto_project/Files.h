#pragma once
#include"Trie.h"
#include<fstream>
#include<iostream>
#include<string>
#include<vector>


class Files
{
	string File;

public:
	Files(string name);
	void Save(Trie& t);
	void Load(Trie& t);
};

