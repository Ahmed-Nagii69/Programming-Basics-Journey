// String manipulation library implemented from scratch with a several useful functions.
# include <iostream>
# include "clsString.h"
using namespace std;
int main() {

	clsString s;
	s.SetValue("ahmed Mahmoud nagy SaYm");
	cout << "String: " << s.GetValue() << endl;

	s.PrintFirstLetterOfEachWord();

	s.UpperFirstLetterOfEachWord();

	s.LowerFirstLetterOfEachWord();

	cout << s.Upper() << endl;

	cout << s.Lower() << endl;

	cout << "Vowels Count In String: " << s.CountVowels() << endl;

	cout << "Capital Letters Count In String: " << s.CountCapitalLetters()<< endl;

	cout << "Capital Small Count In String: " << s.CountCapitalLetters() << endl;

	cout << s.InvertLetterCases() << endl;

	vector <string > words = s.Split();
	cout << words[0] << "\t" << words[1] << "\t" << words[2] << "\t" <<
		words[3] << endl;





	return 0;
}