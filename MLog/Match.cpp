#include "Match.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#define MAXSTRING 22
#define MAXSCORE 20
#define MAXMD 60
#define INPUTERROR "	>Wrong input, please enter a valid value: "


using namespace std;

ostream& operator<<(ostream& output, Match const& match) { //save to file with o. operator
	output << match.HomeTeam << endl;
	output << match.AwayTeam << endl;
	output << match.HomeScore << endl;
	output << match.AwayScore << endl;
	output << match.Venue << endl;
	output << match.Matchday << endl;

	return output;
}

istream& operator>>(istream& is, Match& match) { // read from file with o. operator
	getline(is, match.HomeTeam);
	if (match.HomeTeam == "<end>") {
		return is;
	}
	getline(is, match.AwayTeam);
	is >> match.HomeScore;
	is.ignore(1024, '\n');
	is >> match.AwayScore;
	is.ignore(1024, '\n');
	getline(is, match.Venue);
	is >> match.Matchday;
	is.ignore(1024, '\n');
	return is;
}

bool Match::eof() { //CHECK FOR END OF FILE
	if (this->HomeTeam == "<end>") {
		return 1;
	}
	return 0;
}

void Match::create() { //READ IN MATCH DATA FROM USER
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer

	cout << ">Name of the home team (max. " << MAXSTRING << " characters): ";
	this->HomeTeam = stringValidator(MAXSTRING);
	cout << ">Name of the away team (max. " << MAXSTRING << " characters): ";
	this->AwayTeam = stringValidator(MAXSTRING);
	cout << ">Home score: ";
	this->HomeScore = intValidator(MAXSCORE);
	cout << ">Away score: ";
	this->AwayScore = intValidator(MAXSCORE);
	cout << ">Name of the venue (max. " << MAXSTRING << " characters): ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	this->Venue = stringValidator(MAXSTRING);
	cout << ">Matchday: ";
	this->Matchday = intValidator(MAXMD);
}

int Match::intValidator(int max) {
	int number;
	bool loop = true;

	do {
		cin >> number;
		if (cin.fail()) {
			cout << INPUTERROR;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else if (number < 0 || number > max) {
			cout << INPUTERROR;
		}
		else {
			loop = false;
		}
	} while (loop);

	return number;
}

string Match::stringValidator(size_t max) { //Validate string input to be of given length and not be empty
	string text;
	bool loop = true;

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


void Match::report(int whichMatch) { //PRINT DATA OF REPORT with index
	string score = to_string(this->HomeScore) + ':' + to_string(this->AwayScore);


	cout << "|| " << setw(7) << left << whichMatch;
	cout << "| " << setw(9) << left << this->Matchday;

	cout << "| " << setw(MAXSTRING + 1) << left << this->HomeTeam;
	cout << "| " << setw(MAXSTRING + 1) << left << this->AwayTeam;
	cout << "| " << setw(6) << left << score;
	cout << "| " << setw(MAXSTRING + 1) << left << this->Venue;
	cout << "||";
}

void Match::report() { //PRINT DATA OF REPORT
	string score = to_string(this->HomeScore) + ':' + to_string(this->AwayScore);

	cout << "|| " << setw(9) << left << this->Matchday;
	cout << "| " << setw(MAXSTRING + 1) << left << this->HomeTeam;
	cout << "| " << setw(MAXSTRING + 1) << left << this->AwayTeam;
	cout << "| " << setw(6) << left << score;
	cout << "| " << setw(MAXSTRING + 1) << left << this->Venue;
	cout << "||";
}


bool Match::compareTeam(string team) { //TEAM CHECK
	if (this->HomeTeam == team || this->AwayTeam == team) {
		return true;
	}
	return false;
}

bool Match::compareVenue(string venue) { //VENUE CHECK
	if (this->Venue == venue) {
		return true;
	}
	return false;
}



void Match::modify(int which, int value) { //MODIFY MATCHES - SCORE/MATCHDAY
	switch (which) {
	case 1:
		this->Matchday = value;
		break;
	case 4:
		this->HomeScore = value;
		break;
	case 5:
		this->AwayScore = value;
		break;
	default:
		cout << endl << "Unexpected error";
		break;
	}
}

void Match::modify(int which, string value) { //MODIFY MATCHES - TEAMS/VENUE
	switch (which) {
	case 2:
		this->HomeTeam = value;
		break;
	case 3:
		this->AwayTeam = value;
		break;
	case 6:
		this->Venue = value;
		break;
	default:
		cout << endl << "Unexpected error";
		break;
	}
}