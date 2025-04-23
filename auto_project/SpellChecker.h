#pragma once
#include<iostream>
#include<string>
#include<vector>

using namespace std;
class SpellChecker
{
public:
	int ComputeUnsimilarity(string Word1, string word2);
	vector<string> DisplayCloseSuggestions(string word, vector<string> AvailableWords);

};

