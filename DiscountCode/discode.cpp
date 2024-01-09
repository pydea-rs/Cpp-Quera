#include <iostream>
#include <string>

using namespace std;

bool areCharacterSetsEqual(const string pattern , const string other) {
	for(const char character: other) {
		// check each character in other string,
		// if even one character doesnt exist in pattern, then their character sets arent equal; 
		short int i = 0;
		for( ; pattern[i]; i++)
			// if pattern[i] is the same as character then break here
			if(pattern[i] == character)
				break;
				
		// if character was found in pattern, then the value of i will be less than pattern length
		if(!pattern[i]) // character not found in pattern
			return false;
	}
	
	// if all characters of other were found in pattern string, then character sets are the same.
	return true;	
}

int main() {
	short int n = 0;
	string patternString, result = "", temp;
	cin >> n;
	cin >> patternString;
	const string ANSWERS[] = {"No", "Yes"}; // this array is organized in a way that: ANSWERS[true] <=> YES, ANSWERS[false] <=> No
	// start getting strings and check if the character set of each input and the patternString is the same
	bool hasSameCharacterSet = false;
	for(short int i = 0; i < n; i++) {
		cin >> temp;
		// function areCharacterSetsEqual is called in both way
		// to check that every character of pattern exists in temp
		// and every character of temp exists in pattern, too.
		hasSameCharacterSet = areCharacterSetsEqual(patternString, temp) && areCharacterSetsEqual(temp, patternString);
		result += ANSWERS[(short int)hasSameCharacterSet] + "\n";
	}
	
	cout << result;
	return 0;
}