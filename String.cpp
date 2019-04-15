#include "String.h"
#include <iso646.h>

String::String() : currentLen(0), allocatedLen(200), characters(std::make_unique<char[]>('\0')) {}

String::String(const char *message) : currentLen(Strlen(message)), allocatedLen(200 + currentLen),
	characters(std::make_unique<char[]>(allocatedLen)) {
	for (int i = 0; i < currentLen; i++) 
		characters[i] = message[i];
	characters[currentLen] = '\0';
}

String::String(const String &rhs) : currentLen(rhs.currentLen), allocatedLen(200 + currentLen),
	characters(std::make_unique<char[]>(allocatedLen)) {
	for (int i = 0; i < currentLen; i++) 
		characters[i] = rhs.characters[i];
	characters[currentLen] = '\0';
}

String::~String(){
}

void String::grow(){
	allocatedLen *= 2;
	auto temp = std::make_unique<char[]>(allocatedLen);
	temp.swap(characters);
	characters = std::move(temp);
}

String &String::operator=(const char *rhs) {
	currentLen = Strlen(rhs);
	characters = std::make_unique<char[]>(currentLen + 1);
	
	for (int i = 0; i < currentLen; i++) 
		characters[i] = rhs[i];
	characters[currentLen] = '\0';
	return *this;
}

String &String::operator=(const String &rhs) {
	if (this != &rhs) {
		//assign the characters to a new array
		characters = std::make_unique<char[]>(rhs.currentLen + 1);
		currentLen = rhs.currentLen;
		for (int i = 0; i < currentLen; i++)
			characters[i] = rhs.characters[i];
		characters[currentLen] = '\0';
	}
	return *this;
}


String &String::operator+=(const String &word){
	if(currentLen == allocatedLen or (currentLen + word.currentLen >= allocatedLen))
		grow();
	if (this != &word) {
		std::copy_n(word.characters.get(), word.currentLen, characters.get() + currentLen);
		currentLen += word.currentLen;
	}
		
	return *this;
}

String & String::operator+=(const char * word){
	size_t wordLen = strlen(word);
	if (currentLen == allocatedLen or (currentLen + wordLen >= allocatedLen))
		grow();
	std::copy_n(word, wordLen, characters.get() + currentLen);
	currentLen += wordLen;
	return *this;
}

void String::push_back(char c){
	if(currentLen == allocatedLen)
		grow();
	characters[currentLen] = c;
	currentLen++;
}

void String::pop_back(){
	currentLen--;
}

int String::length() const{
	return currentLen;
} 

int String::Strlen(const char *word, int dummy){
	int count = 0;

	for (int i = 0; word[i] != '\0'; i++) 
		count++;
	return count;
}

//+ operator defined for the concatenation of two objects
String operator+(const String &lhs, const String &rhs) {
	String Result;

	Result.currentLen = lhs.currentLen + rhs.currentLen;
	Result.characters = std::make_unique<char[]>(Result.currentLen + 1);
	std::copy_n(lhs.characters.get(), lhs.currentLen, Result.characters.get());
	std::copy_n(rhs.characters.get(), rhs.currentLen, Result.characters.get() + lhs.currentLen);
	Result.characters[Result.currentLen] = '\0';

	return Result;
}

//+ operator defined for the concatenation of a c string and a string object
String operator+(const String &rhs, char *lhs) {
	String Result;
	size_t lhsLen = strlen(lhs);

	Result.currentLen = lhsLen + rhs.currentLen;
	Result.characters = std::make_unique<char[]>(Result.currentLen + 1);
	std::copy_n(lhs, lhsLen, Result.characters.get());
	std::copy_n(rhs.characters.get(), rhs.currentLen, Result.characters.get() + lhsLen);
	Result.characters[Result.currentLen] = '\0';

	return Result;
}

std::ostream &operator<<(std::ostream &os, const String &word) {
	return os << word.characters.get();
}
