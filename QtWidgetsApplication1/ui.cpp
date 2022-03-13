#include "ui.h"
#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include <chrono>
using namespace std;
using std::cin;
using std::cout;
void UI::startUI()
{
	bool ok = true;
	while (ok)
	{
		print_meniu();
		int cmd = 0;
		cin >> cmd;
		while (1)
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cmd = 1000;
			}
			if (!cin.fail())
				break;
		}
		switch (cmd)
		{
		case -1:
			cout << "Goodbye\n";
			ok = false;
			break;
		case 1:
			add_ui();
			break;
		case 2:
			update_ui();
			break;
		case 3:
			delete_ui();
			break;
		case 4:
			find_ui();
			break;
		case 5:
			sort_ui();
			break;
		case 6:
			filter_ui();
			break;
		case 0:
			print_elems(serv.getAll());
			break;
		case 7:
			print_meniu_bucket();
			break;
		case 8:
			raportUI();
			break;
		case 9:
			undo();
			break;
		default:
			break;
		}
	}
}
void UI::add_ui()
{
	string  description, type;
	int duration;
	string name;
	cout << "name: ";
	getline(cin, name);//de ce am nevoide de asta baa
	getline(cin, name);
	cout << "description: ";
	getline(cin, description);
	cout << "type: ";
	getline(cin, type);
	cout << "duration: ";

	cout << "Enter an integer number\n";
	cin >> duration;
	while (1)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			duration = -1;
		}
		if (!cin.fail())
			break;
	}

	try {
		serv.add(name, description, type, duration);
	}
	catch (const ValidatorException& ex)
	{
		cout << ex << endl;
	}
	catch (RepoException& ex)
	{
		cout << ex.getMessage() << endl;
	}

}
void UI::update_ui()
{

	string  description, type;
	int duration;
	string name;
	cout << "name: ";
	getline(cin, name);//de ce am nevoide de asta baa
	getline(cin, name);
	cout << "description: ";
	getline(cin, description);
	cout << "type: ";
	getline(cin, type);
	cout << "duration: ";

	cout << "Enter an integer number\n";
	cin >> duration;
	while (1)
	{

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			duration = -1;
		}
		if (!cin.fail())
			break;
	}

	try {
		serv.update(name, description, type, duration);
	}
	catch (const ValidatorException& ex)
	{
		cout << ex << endl;
	}
	catch (RepoException& ex)
	{
		cout << ex.getMessage() << endl;
	}

}
void UI::delete_ui()
{
	string name, description = "a", type;
	cout << "name: ";
	getline(cin, name);
	getline(cin, name);
	cout << "type: ";
	getline(cin, type);
	int constexpr duration = 10;
	try {
		serv.delete_a(name, description, type, duration);
	}
	catch (const ValidatorException& ex)
	{
		cout << ex << endl;
	}
	catch (RepoException& ex)
	{
		cout << ex.getMessage() << endl;
	}
}
void UI::find_ui()
{
	string name, description = "a", type;
	int constexpr duration = 10;
	cout << "name: ";
	getline(cin, name);
	getline(cin, name);
	cout << "type: ";
	getline(cin, type);
	try {
		Activity ac = serv.find(name, description, type, duration);
		cout << "Element gasit: " << ac.getname() << " " << ac.getdescription() << " " << ac.gettype() << " " << ac.getduration() << endl;
	}
	catch (const ValidatorException& ex)
	{
		cout << ex << endl;
	}
	catch (RepoException& ex)
	{
		cout << ex.getMessage() << endl;
	}
}
void UI::sort_ui()
{
	cout << "1 sort by name\n2 sort by description\n3 sort by type+duration\n";

	int cmd = 0;
	cin >> cmd;
	vector<Activity> activities;
	switch (cmd)
	{
	case 1:
		activities = serv.sortname();
		break;
	case 2:
		activities = serv.sortdesc();
		break;
	case 3:
		activities = serv.sortTypeDescription();
		break;
	default:
		break;
	}if (cmd == 1 || cmd == 2 || cmd == 3)
		print_elems(activities);
}
void UI::filter_ui()
{
	cout << "1 filter by description\n2 filter by type\n";

	int cmd = 0;
	cin >> cmd;
	vector<Activity> activities;

	switch (cmd)
	{

	case 1:
	{string aa;
	cin >> aa;
	activities = serv.filter1(aa); }
	break;
	case 2:
	{string bb;
	cin >> bb;
	activities = serv.filter2(bb); }
	break;
	default:
		break;

	}
	if (cmd == 1 || cmd == 2 || cmd == 3)
		print_elems(activities);
}
void UI::print_elems(const vector<Activity>& activities)
{

	if (activities.size() > 0)
		for (const Activity& ac : activities)
		{
			cout << "Element: " << ac.getname() << " " << ac.getdescription() << " " << ac.gettype() << " " << ac.getduration() << endl;
		}
	else
		cout << "0 activities:(" << endl;
}
void UI::print_meniu()
{
	cout << "0 Print all the activities\n1 Add one activity\n2 Update an activity\n3 Delete one activity\n4 Find an activity\n5 Sort\n6 Filter\n7 Bucket\n8 Raport duration\n9 Undo\n-1 Exit\n";
}
void UI::print_meniu_bucket()
{
	cout << "1 add an activity after a description\n2 generate list of activity\n3 free the list\n4 save the list\n";

	int cmd = 0;
	cin >> cmd;

	switch (cmd)
	{
	case 1:
		add_bucket();
		break;
	case 2:
		add_random_bucket();
		break;
	case 3:
		delete_bucket();
		break;
	case 4:
		write_file_bucket();
		break;
	default:
		break;
	}
	cout << " the number of activities in the bucket is: " << servbucket.getAll().size() << endl;
}
void UI::delete_bucket()
{
	servbucket.clear_all();
}
void UI::add_bucket()
{
	string  description, type;
	int duration = 0;
	string name;

	getline(cin, name);//de ce am nevoide de asta baa
	description = "2";
	cout << "name: ";
	getline(cin, name);
	cout << "type: ";
	getline(cin, type);
	while (1)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			duration = -1;
		}
		if (!cin.fail())
			break;
	}

	try {

		//Activity newe = serv.find(name, description, type, duration);
		Activity newe = serv.find(name, description, type, duration);
		servbucket.add(newe.getname(), newe.getdescription(), newe.gettype(), newe.getduration());
	}
	catch (const ValidatorException& ex)
	{
		cout << ex << endl;
	}
	catch (RepoException& ex)
	{
		cout << ex.getMessage() << endl;
	}
}

void UI::add_random_bucket()
{
	unsigned int nr;
	cin >> nr;
	vector < Activity > v = serv.getAll();
	std::mt19937 const mt{ std::random_device{}() };
	std::uniform_int_distribution<> const dist(0, v.size() - 1);
	//int rndNr = dist(mt);// numar aleator intre [0,size-1]

	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	unsigned const int ss = unsigned int(seed);
	std::shuffle(v.begin(), v.end(), std::default_random_engine(ss));
	if (servbucket.getAll().size() + nr <= v.size())
	{
		int start = v.size() - 1;
		while (nr)
		{
			Activity found = v.at(start);
			try {
				servbucket.add(found.getname(), found.getdescription(), found.gettype(), found.getduration());
				nr--;

			}
			catch (RepoException& ex)
			{
				cout << ex.getMessage() << endl;
			}
			start--;

		}
	}
	else cout << "the number given is to big" << endl;
}
//ofstream fileout;
void UI::write_file_bucket()
{
	string fName;
	getline(cin, fName);
	getline(cin, fName);
	std::ofstream out;
	out.open(fName);
	if (!out.is_open())
		cout << "The file is not open\n";
	out << "Name" << ";" << "Description" << ";" << "Type" << ";" << "Duration" << endl;
	for (auto& ac : servbucket.getAll())
	{
		out << ac.getname() << ";";
		out << ac.getdescription() << ";";
		out << ac.gettype() << ";";
		out << ac.getduration() << ";";
		out << std::endl;
	}

	out.close();
}
void UI::raportUI()
{
	auto w = serv.raport_duration();
	std::unordered_map<int, Dto_duration>::iterator it = w.begin();
	while (it != w.end())
	{
		const int y = it->first;
		Dto_duration ob = it->second;
		cout << "Duration: " << y << " " << "activities: " << ob.getNumber() << endl;
		it++;

	}
}


void UI::undo()
{
	try {
		serv.UNDO();
		print_elems(serv.getAll());
	}
	catch (RepoException& ex)
	{
		cout << ex.getMessage() << endl;
	}


}