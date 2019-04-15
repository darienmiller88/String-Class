#include <iostream>
#include "String.h"

using namespace std;

void printString(String &word) {
	cout << word << endl;
}

int main()
{
	String word = "Darien", name = word, newWord = "Denise";

	
	word += newWord;
	word += "YUKI X YUNO";
	cout << word << endl;
	
	
	
	system("pause");
}