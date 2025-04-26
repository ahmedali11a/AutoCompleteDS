#pragma once
#include<map>

using namespace std;
class Node
{
public:

	map<char, Node*> letters;
	bool EndWord;
	int Frequency;

	Node();
};

