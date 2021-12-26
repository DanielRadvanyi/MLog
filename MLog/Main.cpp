#include "Match.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#define INPUTERROR "	>Wrong input, please enter a valid value: "
#define MAXSCORE 20
#define MAXSTRING 22
#define MAXMD 60
#define MAXPATHLENGTH 30
#define ERR "Unexpected error"

using namespace std;

int intValidator(int min, int max) { //Validate integer input to be between given values and to be an integer
	int number;
	bool loop = true;

	do {
		cin >> number;
		if (cin.fail()) {
			cout << INPUTERROR;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else if (number < min || number > max) {
			cout << INPUTERROR;
		}
		else {
			loop = false;
		}
	} while (loop);

	return number;
}

string stringValidator(size_t max, bool debuffer) { //Validate string input to be of given length and not be empty
	string text;
	bool loop = true;

	if (debuffer) {
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	do {
		getline(cin, text);
		if (text.empty()) {
			cout << INPUTERROR;
		}
		else if (text.size() >= max) {
			cout << INPUTERROR;
		}
		else {
			loop = false;
		}
	} while (loop);
	return text;
}


int menu() { //MAIN MENU
	int reply;

	cout << endl << "MENU" << endl;
	cout << "1. Initialize" << endl;
	cout << "2. Save matches to file" << endl;
	cout << "3. Read matches from file" << endl;
	cout << "4. Add new match" << endl;
	cout << "5. Edit a match" << endl;
	cout << "6. Report of a team's matches" << endl;
	cout << "7. Report of a venue's matches" << endl;
	cout << "8. Exit" << endl;
	cout << ">Choose your action: ";

	reply = intValidator(1, 8);
	cout << endl;

	return reply;
}


void addMatch(vector<Match>& match) { //Call function from Match.cpp that reads in matches.
	Match tempMatch;
	tempMatch.create();
	match.push_back(tempMatch); //Push newly added match to end of vector of matches.
}

void report(vector<Match>& match, vector<int> whichMatches, bool includeIndex) { //PRINT REPORT OF ALL GIVEN MATCHES. Works for both by team and by venue filter.
	int counter = 0;

	if (includeIndex) {
		cout << "||//////////////////////////////////////////////////////////////////////////////////////////////////////||" << endl;
		cout << "|| " << setw(7) << left << "Index";
		cout << "| " << setw(9) << left << "Matchday";
		cout << "| " << setw(MAXSTRING + 1) << left << "Home team";
		cout << "| " << setw(MAXSTRING + 1) << left << "Away team";
		cout << "| " << setw(6) << left << "Score" << "| ";
		cout << setw(MAXSTRING + 1) << left << "Venue";
		cout << "||" << endl;
		cout << "||--------|----------|------------------------|------------------------|-------|------------------------||" << endl;
	}
	else {
		cout << "||/////////////////////////////////////////////////////////////////////////////////////////////||" << endl;
		cout << "|| " << setw(9) << left << "Matchday";
		cout << "| " << setw(MAXSTRING + 1) << left << "Home team";
		cout << "| " << setw(MAXSTRING + 1) << left << "Away team";
		cout << "| " << setw(6) << left << "Score" << "| ";
		cout << setw(MAXSTRING + 1) << left << "Venue";
		cout << "||" << endl;
		cout << "||----------|------------------------|------------------------|-------|------------------------||" << endl;
	}

	for (auto& iter : match) { //This iterates through each match (counting their indexes). Then it iterates through the indexes of the matches we need. If there's a match, print data.
		for (auto iterVec : whichMatches) {
			if (iterVec == counter) {
				if (includeIndex) {
					iter.report(iterVec);
				}
				else {
					iter.report();
				}
				cout << endl;
			}
		}
		counter++;
	}

	if (includeIndex) {
		cout << "||//////////////////////////////////////////////////////////////////////////////////////////////////////||" << endl;
	}
	else {
		cout << "||/////////////////////////////////////////////////////////////////////////////////////////////||" << endl;
	}
}

void report(Match& match) { //PRINT REPORT OF ONE MATCH
	cout << "|| " << setw(9) << left << "Matchday";
	cout << "| " << setw(MAXSTRING + 1) << left << "Home team";
	cout << "| " << setw(MAXSTRING + 1) << left << "Away team";
	cout << "| " << setw(6) << left << "Score" << "| ";
	cout << setw(MAXSTRING + 1) << left << "Venue";
	cout << "||" << endl;
	cout << "||----------|------------------------|------------------------|-------|---------------------||" << endl;

	match.report();
	cout << endl;
}


vector<int> getMatches(vector<Match>& match, string type) { //This function iterates through every match to filter out which ones are to be included in the report.
	vector<int> whichMatches;
	string criteria;
	int counter = 0;

	if (type == "team") {
		cout << ">Which team's matches would you like a report of? ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer
		getline(cin, criteria);

		for (auto& iter : match) {
			if (iter.compareTeam(criteria)) {
				whichMatches.push_back(counter);
			}
			counter++;
		}
	}
	else if (type == "venue") {
		cout << ">Which venue's matches would you like a report of? ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer
		getline(cin, criteria);

		for (auto& iter : match) {
			if (iter.compareVenue(criteria)) {
				whichMatches.push_back(counter);
			}
			counter++;
		}
	}
	else if (type == "all") {
		for (size_t x = 0; x < match.size(); x++) {
			whichMatches.push_back(x);
		}
	}

	return whichMatches;
}

void editMatch(vector<Match>& match) { //MODIFY MATCHES
	int whichValue, valueInt;
	string valueStr;
	size_t choice;

	cout << "Make a correction" << endl << endl;

	report(match, getMatches(match, "all"), true);

	cout << endl << ">Which match would you like to edit (enter index)? ";
	choice = intValidator(0, match.size() - 1);

	cout << endl << "You selected this match: " << endl;
	report(match[choice]);


	cout << endl << ">Which value would you like to edit? " << endl;
	cout << "1. Matchday" << endl;
	cout << "2. Home team" << endl;
	cout << "3. Away team" << endl;
	cout << "4. Home score" << endl;
	cout << "5. Away score" << endl;
	cout << "6. Venue" << endl << ">";
	whichValue = intValidator(1, 6);


	cout << endl << ">What would be the new value? ";
	if (whichValue == 1 || whichValue == 4 || whichValue == 5) { //integer value
		if (whichValue == 1) {
			valueInt = intValidator(1, MAXMD);
		}
		else {
			valueInt = intValidator(0, MAXSCORE);
		}
		match[choice].modify(whichValue, valueInt);
	}
	else {
		valueStr = stringValidator(MAXSTRING, true);

		match[choice].modify(whichValue, valueStr);
	}


	cout << endl << "Value changed." << endl;

}

void saveToFile(vector<Match>& match) { //SAVE TO FILE
	string path;
	string choice;

	cout << "Saving to file." << endl << endl << ">File name(with extension, max. " << MAXPATHLENGTH << " characters): ";
	path = stringValidator(MAXPATHLENGTH, true);

	while (true) { //Check if a file already exists with the same name
		ifstream checkfile;
		checkfile.open(path);
		if (checkfile) { //there is a file with matching name
			checkfile.close();
			cout << "	>File already exists. Would you like to overwrite it (Y/N)? ";

			cin >> choice;
			bool exit = false;
			while (true) {
				char letter = choice[0];
				if (toupper(letter) == (char)'Y') {  //proceed to overwrite
					exit = true;
					break;
				}
				else if (toupper(letter) == (char)'N') { //Fetch new path and repeat check
					cout << "	>Give a new path: ";
					path = stringValidator(MAXPATHLENGTH, true);
					break;
				}
				else { //user entered a random letter
					cout << "	>Wrong input. Please try again: ";
					cin >> choice;
				}
			}
			if (exit) {
				break;
			}
		}
		else { //no file exists with matching name
			checkfile.close();
			break;
		}
	}

	ofstream file(path);
	for (auto& iter : match) {
		file << iter;
	}
	file << "<end>";
	file.close();
	cout << endl << "File saved." << endl;
}

void readFromFile(vector<Match>& match) {
	string path;
	cout << "Reading from file." << endl << endl << ">File name(with extension, max. " << MAXPATHLENGTH << " characters): ";
	path = stringValidator(MAXPATHLENGTH, true);

	ifstream file;

	file.open(path);
	while (!file) {
		cout << "	>File doesn't exist. Please give a valid path: ";
		path = stringValidator(MAXPATHLENGTH, false);
		file.open(path);
	}
	Match temp;

	do {
		file >> temp;
		if (!temp.eof()) {
			match.push_back(temp);
		}
	} while (!temp.eof());

	file.close();
}



int main() {
	cout << "		MATCHLOG" << endl;

	vector<Match> match;

	bool run = true;
	do {
		switch (menu()) {
		case 1:
			match.clear();
			cout << "Log initialized." << endl;
			break;
		case 2:
			saveToFile(match);
			break;
		case 3:
			readFromFile(match);
			break;
		case 4:
			addMatch(match);
			break;
		case 5:
			editMatch(match);
			break;
		case 6: {
			vector<int> whichMatches = getMatches(match, "team");
			if (whichMatches.size() == 0) {
				cout << endl << "Team not found." << endl;
			}
			else {
				report(match, whichMatches, false);
			}}
			  break;
		case 7: {
			vector<int> whichMatches = getMatches(match, "venue");
			if (whichMatches.size() == 0) {
				cout << endl << "Venue not found." << endl;
			}
			else {
				report(match, whichMatches, false);
			}}
			  break;
		case 8:
			run = false;
			break;
		default:
			cout << endl << ERR;
			break;
		}
	} while (run);


	return 0;
}