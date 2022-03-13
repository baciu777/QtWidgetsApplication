#pragma once
#include <string.h>
#include "domain.h"
#include <vector>
using std::vector;
using std::string;
using std::ostream;

class ValidatorException {
	vector<string> msgs;
	
public:
	ValidatorException( vector <string>& errors) :msgs{ errors }
	{

	}
	friend ostream& operator<<(ostream& out, const ValidatorException& ex);
	vector<string> getMessage()
	{
		//std::string str = boost::algorithm::join(msgs, " ");
		//string str(msgs.begin(), msgs.end());//avem nevoie de string in QT
		string a;
	
		return msgs;
	}
};

ostream& operator<<(ostream& out, const ValidatorException& ex);

class ActivityValidator {
public:
	/*
	verify if the given data are valid
	throw exception, otherwise
	*/
	void validate(const Activity& ac);
};
