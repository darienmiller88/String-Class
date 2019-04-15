#ifndef STRING_H
#define STRING_H
#include <iostream>
#include <memory>
#include <algorithm>

class String
{
	public:
		String();//default constructor that initializes a string object to a \0 character
		String(const char *word);//constructor that takes c string as argument. Acts as both a default AND copy constructor!
		String(const String &rhs);//copy constructer to create new string in terms of an another one
		String &operator=(const String &word);//assignment operator for an object
		String &operator=(const char *word);//assignment operator for an 
		String &operator+=(const String &word);
		String &operator+=(const char *word);
		friend String operator+(const String &lhs, const String &rhs);//overload + operator for two objects
		friend String operator+ (const String &rhs, char *lhs);//overload + operator for an object and a c string
		friend std::ostream &operator<<(std::ostream &os, const String &word);
		void push_back(char c);
		void pop_back();
		int length() const;
		~String();//destructor for freeing up memory
	private:
		void grow();
		int currentLen;
		int allocatedLen;
		std::unique_ptr<char[]> characters;
		static int Strlen(const char *wordLen, int dummy = 0);
};


#endif // !

