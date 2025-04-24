#pragma once
#include"Trie.h"
class Files
{
	string File;

public:
	Files(string name);
	void Save(Trie& t);
	void Load(Trie& t);
};

