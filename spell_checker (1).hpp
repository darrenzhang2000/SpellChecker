//Darren Zhang
//This is the interface of the spell checker.

#ifndef _SPELLCHECKER_
#define _SPELLCHECKER_

#include <fstream>
#include <unordered_set>
#include <set>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>


class SpellChecker{
public:
	/**
	@param text_file the file containing the text to spell check
	@param dictionary_file the file containing all dictionary words
	@post prints out a list of all the unrecognized words followed by : 
		followed by a list of suggested corrections separated by spaces
	*/
	void SpellCheck(std::string text_file, std::string dictionary_file);
private:
	/**
	@param word a word 
	@param dictionary_file the file containing all dictionary words
	@post prints out all possible suggestions if in dictionary, which is found by inserting every letter
		of the alphabet in before, after, and in between letters of the word
	*/
	void AddMissingLetter(std::string word, std::unordered_set<std::string>& dic);

	/**
	@param word a word 
	@param dictionary_file the file containing all dictionary words
	@post prints out all possible suggestions if in dictionary, which is found by deleting every letter
		of the world
	*/
	void DeleteExtraLetter(std::string word, std::unordered_set<std::string>& dic);

	/**
	@param word a word 
	@param dictionary_file the file containing all dictionary words
	@post prints out all possible suggestions if in dictionary, which is found by replacing every letter
		of the world
	*/
	void UnreplaceReplacedLetter(std::string word, std::unordered_set<std::string>& dic);

	/**
	@param word a word 
	@param dictionary_file the file containing all dictionary words
	@post prints out all possible suggestions if in dictionary, which is found by swapping every letter
		of the world
	*/
	void UnswapSwappedLetter(std::string word, std::unordered_set<std::string>& dic);

	/**
	@param word a word (possibly with a punctuation)
	@return index of the first punct
	@post finds index of first punct and stores it in index
	*/
	int FindIndexOfPunct(std::string word);

};

#endif