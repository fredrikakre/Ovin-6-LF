#include "FileUtils.h"

void writeUserInputToFile()
{
	const string filename{"outputfile.txt"};
	ofstream outFile{filename};
	if (!outFile)
		error("Can't open file");

	cout << "Write some words, they will be output in the file"
			" \"outputfile.txt\", every word on separate lines."
			" quit exits\n> ";

	for (string word; cin >> word && word != "quit";)
		outFile << word << '\n';
}

void addLineNumbers(string filename)
// Copy file with filename and write a new file `filename`.linum with
// line numbers
{
	ifstream inFile{filename};
	if (!inFile)
		error("Can't open input file", filename);

	ofstream outFile{filename + ".linum"};
	if (!outFile)
		error("Can't open output file", filename + ".linum");

	int lineNumber = 1;
	for (string line; getline(inFile, line); ++lineNumber)
		outFile << lineNumber << ": " << line << '\n';
}

void characterStatistics(string filename)
{
	ifstream inFile{filename};
	if (!inFile)
		error("Can't open input file", filename);

	vector<int> stats(26); // ev. std::array
	for (unsigned char c; inFile >> c;) {
		if (isalpha(c)) {
			++stats[tolower(c) - 'a'];
		}
	}

	for (char c = 'a'; c <= 'z'; ++c) {
		cout << c << ": " << stats[c - 'a'] << '\t';
		if (c % 3 == 0) {
			cout << '\n';
		}
	}
}
