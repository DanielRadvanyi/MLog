#pragma once
#ifndef MATCH_H_INCLUDED 
#define MATCH_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class Match {
public:
	friend ostream& operator<<(ostream& output, Match const& match);
	friend istream& operator>>(istream& input, Match& match);
	bool eof();
	void modify(int which, int value);
	void modify(int which, string value);
	void create();
	int intValidator(int max);
	string stringValidator(size_t max);
	void report(int whichMatch);
	void report();
	bool compareTeam(string team);
	bool compareVenue(string venue);

private:
	string HomeTeam, AwayTeam, Venue;
	int HomeScore = -1, AwayScore = -1, Matchday = -1;
};

#endif