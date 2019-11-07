	//Darren Zhang
//This is the implementation page of the spell checker.

#include "spell_checker.hpp"

#include <fstream>
#include <unordered_set>
#include <set>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <chrono>

	/**
	@param word a word 
	@param dictionary_file the file containing all dictionary words
	@post prints out all possible suggestions if in dictionary, which is found by inserting every letter
		of the alphabet in before, after, and in between letters of the word
	*/
void SpellChecker::AddMissingLetter(std::string word, std::unordered_set<std::string>& dic){
	std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
	std::string suggestion;
	std::unordered_set<std::string> suggestion_set;

	//Case 1: Letter is appended to the beginning
	for(int i = 0; i < alphabet.length(); i++){
		suggestion = alphabet[i]; //start with letter
		suggestion += word; //then append the word
		//if suggestion is in dictionary
		if(dic.find(suggestion) != dic.end()){
			suggestion_set.insert(suggestion);
		}
	}

	//Case 2: Letter is appended somewhere in the middle
	//For every possible places to insert the letter
	for(int i = 1; i < word.length(); i++){
		for(int j = 0; j < alphabet.length(); j++){
			suggestion = word.substr(0, i); //substr of word before insertion index
			suggestion += alphabet[j]; // insertion of letter
			suggestion += word.substr(i); //append the rest of word
			//if suggestion is in dictionary
			if(dic.find(suggestion) != dic.end()){
				suggestion_set.insert(suggestion);
			}
		}
	}	

	//Case 3: Letter is appended to the end
	for(int i = 0; i < alphabet.length(); i++){
		suggestion = word; //start with the word
		suggestion += alphabet[i]; //then append the letter
		//if suggestion is in dictionary
		if(dic.find(suggestion) != dic.end()){
			suggestion_set.insert(suggestion);
		}
	}

	for(auto e: suggestion_set){
		std::cout << e << " ";
	}
}

	/**
	@param word a word 
	@param dictionary_file the file containing all dictionary words
	@post prints out all possible suggestions if in dictionary, which is found by deleting every letter
		of the world
	*/
void SpellChecker::DeleteExtraLetter(std::string word, std::unordered_set<std::string>& dic){
	std::string suggestion;

	// case 1: deletion of every letter except the last 
	for(int i = 0; i < word.length() - 1; i++){ //for every index i to be deleted
		suggestion = word.substr(0, i) + word.substr(i + 1); //delete index i 
		if(dic.count(suggestion)){
			std::cout << suggestion << " ";
		}
	}

	// case 2: deletion of the last letter
	suggestion = word.substr(0, word.length() - 1);
	if(dic.count(suggestion)){
		std::cout << suggestion << " ";
	}
}

	/**
	@param word a word 
	@param dictionary_file the file containing all dictionary words
	@post prints out all possible suggestions if in dictionary, which is found by replacing every letter
		of the world
	*/
void SpellChecker::UnreplaceReplacedLetter(std::string word, std::unordered_set<std::string>& dic){
	std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
	std::string suggestion;

	//case 1: replacing every letter except the last 
	for(int i = 0; i < word.length() - 1; i++){ 
		for(int j = 0; j < alphabet.length(); j++){ 
			//replace word letter i with alphabet letter j
			suggestion = word.substr(0, i) + alphabet[j] + word.substr(i + 1);
			if(dic.count(suggestion)){
				std::cout << suggestion << " ";
			}
		}
	}

	//case 2: replacing the last letter
	for(int j = 0; j < alphabet.length(); j++){
		suggestion = word.substr(0, word.length() - 1) + alphabet[j];
		if(dic.count(suggestion)){
			std::cout << suggestion << " ";
		}
	}
}

	/**
	@param word a word 
	@param dictionary_file the file containing all dictionary words
	@post prints out all possible suggestions if in dictionary, which is found by swapping every letter
		of the world
	*/
void SpellChecker::UnswapSwappedLetter(std::string word, std::unordered_set<std::string>& dic){
	if(word.length() > 1){ //to avoid swapping single letters
		std::string suggestion;		

		//case 1: swapping every pair of letters except the last 2
		for(int i = 0; i < word.length() - 2; i++){
			suggestion = word.substr(0, i) + word[i + 1] + word[i] + word.substr(i + 2);
			if(dic.count(suggestion)){
				std::cout << suggestion << " ";
			}
		}

		//case 2: swapping the last pair of letters
		suggestion = word.substr(0, word.length() - 2) + word[word.length() - 1] + word[word.length() - 2];
		if(dic.count(suggestion)){
			std::cout << suggestion << " ";
		}
	}
}

	/**
	@param word a word (possibly with a punctuation)
	@return index of the first punct
	@post finds index of first punct and stores it in index
	*/
int SpellChecker::FindIndexOfPunct(std::string word){
	int index = -1;
	for(int i = 0; i < word.length() && index == -1; i++){
		if(ispunct(word[i]))
			index = i;
	}
	return index;
}

	/**


	@param text_file the file containing the text to spell check
	@param dictionary_file the file containing all dictionary words
	@post prints out a list of all the unrecognized words followed by : 
		followed by a list of suggested corrections separated by spaces
	*/
void SpellChecker::SpellCheck(std::string text_file, std::string dictionary_file){
	std::ifstream text_in(text_file);
	std::ifstream dict_in(dictionary_file);
	
	std::unordered_set<std::string> dictionary;
	std::string w;
	//Storing all the words into dictionary
	while(dict_in >> w){
		//insert word into dictionary
		dictionary.insert(w);
	}

	
	std::unordered_set<std::string> word_set;
	std::string text_word;
	//stores all text_words in word_set;
	while(text_in >> text_word){
		//makes word text_word all lowercase
		std::transform(text_word.begin(), text_word.end(), text_word.begin(),
    		[](unsigned char c){ return std::tolower(c); });
	 	
		int i = FindIndexOfPunct(text_word);
		if(i != -1){
			text_word = text_word.substr(0, i); //removes everything after punctuation: cat's becomes cat
		}

		word_set.insert(text_word);
	}

	//for every word in word_set, checks if word is in dictionary
	//if it isn't, print a list of suggested corrections
	auto start = std::chrono::steady_clock::now();
	for(auto w: word_set){
	 	//if not in dictionary
	 	if( dictionary.find(w) == dictionary.end() ){
			std::cout << w << ": ";
			AddMissingLetter(w, dictionary);
			DeleteExtraLetter(w, dictionary);
			UnreplaceReplacedLetter(w, dictionary);
			UnswapSwappedLetter(w, dictionary);
			std::cout << std::endl;
		}
	}
	auto end = std::chrono::steady_clock::now();
	std::cout << "Elapsed time in milliseconds : " 
		<< std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count()
		<< " ms" << std::endl;

}

