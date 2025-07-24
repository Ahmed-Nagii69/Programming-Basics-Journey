#pragma once
# include <iostream>
# include <vector>
using namespace std;
class clsString
{
private:
	string _Value;
public:
	clsString() {
		_Value = "";
	};
	clsString(string Value) {
		_Value = Value;
	}
	void SetValue(string Value) {
		_Value = Value;
	}
	string GetValue() {
		return _Value;
	}

	static void PrintFirstLetterOfEachWord(string s) {
		cout << s[0] << "\t";
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == ' ')
				cout << s[i + 1] << "\t";
		}
		cout << endl;

	}
	void PrintFirstLetterOfEachWord() {
		PrintFirstLetterOfEachWord(_Value);
	}

	static void UpperFirstLetterOfEachWord(string s) {
		s[0] = toupper(s[0]);
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == ' ')
				s[i + 1] = char(toupper(s[i + 1]));
		}
		cout << s << endl;
		cout << endl;
	}
	void UpperFirstLetterOfEachWord() {
		UpperFirstLetterOfEachWord(_Value);
	}

	static void LowerFirstLetterOfEachWord(string s) {
		bool IsFirstLetter = true;
		for (int i = 0; i < s.length(); i++) {
			if (s[i] != ' ' && IsFirstLetter) {
				s[i] = tolower(s[i]);
			}
			IsFirstLetter = (s[i] == ' ') ? true : false;
		}
		cout << s << endl;
	}
	void LowerFirstLetterOfEachWord() {
		LowerFirstLetterOfEachWord(_Value);
	}

	static string Upper(string s) {
		string str = "";
		for (int i = 0; i < s.length(); i++) {
			str += toupper(s[i]);
		}
		return str;
	}
	string Upper() {
		return Upper(_Value);
	}

	static string Lower(string s) {
		string str = "";
		for (int i = 0; i < s.length(); i++) {
			str += tolower(s[i]);
		}
		return str;
	}
	string Lower() {
		return Lower(_Value);
	}

	static string InvertLetterCases(string s) {
		for (int i = 0; i < s.length(); i++) {
			if (isupper(s[i]))
				s[i] = tolower(s[i]);
			else
				s[i] = toupper(s[i]);
		}
		return s;
	}

	string InvertLetterCases() {
		return InvertLetterCases(_Value);
	}

	static string RemovePunctuations(string s)
	{

		string str= "";

		for (short i = 0; i < s.length(); i++)
		{
			if (!ispunct(s[i]))
			{
				str += s[i];
			}
		}

		return str;

	}

	string RemovePunctuations()
	{
		return RemovePunctuations(_Value);
	}

	static vector <string> Split(string s, string delim = " ") {
		int pos = 0;
		vector <string> Vwords;
		string word = "";
		while ((pos = s.find(delim)) != s.npos) {
			word = s.substr(0, pos);
			if (word != "") {
				Vwords.push_back(word);
			}
			s.erase(0, pos + delim.length());
		}
		if (s != "")
			Vwords.push_back(s);
		return Vwords;
	}

	vector <string> Split() {
		vector <string> Vwords = Split(_Value);
		return Vwords;
	}

	static bool IsVowel(char c)
	{
		char Vowels[5] = { 'a', 'e', 'i', 'o', 'u' };
		for (int i = 0; i < 5; i++) {
			if (towlower(c) == Vowels[i])
				return true;
		}
		return false;
	}

	static short  CountVowels(string s)
	{

		short Counter = 0;

		for (short i = 0; i < s.length(); i++)
		{

			if (IsVowel(s[i]))
				Counter++;

		}

		return Counter;
	}

	short  CountVowels()
	{
		return CountVowels(_Value);
	}

	static short  CountCapitalLetters(string s)
	{

		short Counter = 0;

		for (short i = 0; i < s.length(); i++)
		{

			if (isupper(s[i]))
				Counter++;

		}

		return Counter;
	}

	short  CountCapitalLetters()
	{
		return CountCapitalLetters(_Value);
	}

	static short  CountSmallLetters(string s)
	{

		short Counter = 0;

		for (short i = 0; i < s.length(); i++)
		{

			if (islower(s[i]))
				Counter++;

		}

		return Counter;
	}

	short  CountSmallLetters()
	{
		return CountSmallLetters(_Value);
	}

	static string TrimLeft(string s){

		for (short i = 0; i < s.length(); i++)
		{
			if (s[i] != ' '){
				return s.substr(i, s.length() - i); // from first letter to the end..
			}
		}
		return "";
	}

	string TrimLeft()
	{
		return TrimLeft(_Value);
	}

	static string TrimRight(string s){


		for (short i = s.length() - 1; i >= 0; i--){
			if (s[i] != ' '){
				return s.substr(0, i + 1); // from start to the first character from the end..
			}
		}
		return "";
	}

	string TrimRight()
	{
		return TrimRight(_Value);
	}

	static string Trim(string S1)
	{
		return (TrimLeft(TrimRight(S1)));

	}

	string Trim()
	{
		return Trim(_Value);
	}


};


