#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

int loadDictionary(istream& dictfile, vector<string>& dict);
int permute(string word, vector<string>& dict, vector<string>& results);

int main() {
	string word;
	vector<string> dictionary;
	vector<string> matchingWords;
	ifstream inputFile("words.txt");

	if (!inputFile.is_open()) {
		cout << "Error opening file." << std::endl;
		return 1;
	}

	int wordCount = loadDictionary(inputFile, dictionary);

	cout << "Please enter a string for an anagram: ";
	cin >> word;

	int match = permute(word, dictionary, matchingWords);

	if (match > 0) {
		for (const string& word : matchingWords) {
			cout << "Matching Word: " << word << endl;
		}
	}
	else cout << "No Matches Found" << endl;

	return 0;
}

int loadDictionary(istream& dictfile, vector<string>& dict) {
	int count = 0;
	string word;

	while (dictfile >> word) {
		dict.push_back(word);
		count++;
	}

	sort(dict.begin(), dict.end());

	return count;
}

int permute(string word, vector<string>& dict, vector<string>& results) {
	results.clear();

	sort(word.begin(), word.end());

	if (binary_search(dict.begin(), dict.end(), word)) {
		results.push_back(word);
	}

	while (next_permutation(word.begin(), word.end())) {
		if (binary_search(dict.begin(), dict.end(), word)
			&& find(results.begin(), results.end(), word) == results.end()) {
			results.push_back(word);
		}
	}

	return results.size();
}