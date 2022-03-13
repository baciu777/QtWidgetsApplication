#pragma once
#include <string>
#include <iostream>
using std::string;
using std::cout;
class Activity
{
private:
	string name;
	string description;
	string type;
	int duration;
public:
	/*
	get the name of the activity
	*/
	string getname() const;
	/*
	get the description of the activity
	*/
	string getdescription() const;
	/*
	get the type of the activity
	*/
	string gettype() const;
	/*
	get the duration of the activity
	*/
	int getduration() const noexcept;
	/*
	set the name of the activity
	*/
	void setname(const string& val);
	/*
	set the description of the activity
	*/
	void setdescription(const string& val);
	/*
	set the type of the activity
	*/
	void settype(const string& val);
	/*
	set the duration of the activity
	*/
	void setduration(int val) noexcept;

	Activity() = default;

	Activity(string name, string description, string type, int duration) :name{ name }, description{ description }, type{ type }, duration{ duration }
	{
	}
	//copy constructor
	Activity(const Activity& ot) :name{ ot.name }, description{ ot.description }, type{ ot.type }, duration{ ot.duration }
	{
		//cout << "Copy";
	}

	/*
	const Activity operator=(const Activity& ot) { // ??????????
		if (this == &ot) {
			return *this;
		}
		cout << ot.getdescription();
		string aa = (ot.description);
		setdescription(aa);
		string vv = (ot.name);
		setname(vv);
		string cc = (ot.type);
		settype(cc);
		setduration(ot.duration);
		return *this;
	}
	*/


};