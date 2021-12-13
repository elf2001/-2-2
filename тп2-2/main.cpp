#include "helper.h"
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

string readFile(ifstream& input) {
	string s = "";
	string tmpS;
	while (getline(input, tmpS))
		s.append(tmpS).append("\n");
	return s;
}

bool isSplitterWord(const char& ch) {
	return !isalpha(ch) && !isdigit(ch);
}

std::string task(const std::string& s) {
	std::string ans;
	bool isWord = false, isWrite = false;
	int startPrevWord = -1, endPrevWord = -1, startCurWord = -1, endCurWord = -1, countWords = 0;
	for (int i = 0; i < s.size(); i++) {
		if (isSplitterWord(s[i])) {
			if (isWord)
				endCurWord = i - 1;
			isWord = false;
			if (countWords == 1 && i == s.size() - 1)
				ans
				.append(s.substr(startCurWord, endCurWord + 1 - startCurWord));
			if (countWords == 2) {
				ans
					.append(s.substr(startCurWord, endCurWord + 1 - startCurWord))
					.append(s.substr(endPrevWord + 1, startCurWord - endPrevWord - 1))
					.append(s.substr(startPrevWord, endPrevWord + 1 - startPrevWord));
				countWords = 0;
				isWrite = true;
			}
			if (countWords == 0)
				ans.append(s.substr(i, 1));
		}
		else {
			if (!isWord) {
				isWord = true;
				startPrevWord = startCurWord;
				endPrevWord = endCurWord;
				startCurWord = i;
				countWords++;
			}
		}
	}
	if (!isWrite)
		ans = s;
	return ans;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string filename;
	processInputNameOfInputFile(filename);
	ifstream input(filename);
	cout << "Результат работы:\n" << task(readFile(input));
	input.close();
}