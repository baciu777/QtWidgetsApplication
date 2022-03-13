#include "tests.h"
#include <assert.h>
#include <sstream>
void testDomain()
{
	Activity a1{ "a","a","a",10 };
	assert(a1.getname() == "a");
	assert(a1.gettype() == "a");
	assert(a1.getdescription() == "a");
	assert(a1.getduration() == 10);
	string val = "b";
	a1.setdescription(val);
	a1.setname(val);
	a1.setduration(100);

	a1.settype(val);
	assert(a1.getname() == "b");
	assert(a1.gettype() == "b");
	assert(a1.getdescription() == "b");
	assert(a1.getduration() == 100);
}
void testvalidator()
{
	ActivityValidator v;
	Activity ac{ "","","",-1 };
	try
	{
		v.validate(ac);
		assert(false);
	}
	catch ( ValidatorException& ex)
	{
		std::stringstream sout;
		sout << ex;
		auto const mesaj = sout.str();
		ex.getMessage();//
		assert(mesaj.find("invalid") >= 0);
	}
}
void testRepo()
{
	Repository repo;

	Activity ac{ "a","a","a",10 };
	repo.store(ac);

	const auto& activities = repo.getAll();

	assert(activities.size() == 1);

	try
	{
		repo.store(ac);
		assert(false);

	}
	catch (RepoException&)
	{
		//assert(strcmp(e.getMessage(), "Activity already exist") == 0);
		assert(true);
	}
	Activity ac2{ "a","b","a",100 };

	repo.update(ac2);

	const auto& activities1 = repo.getAll();
	Activity aa1{ "a","b","a",100 };
	assert(activities1.at(0).getduration() == 100);
	assert(activities1.at(0).getdescription() == "b");
	Activity ac3{ "aa","b","a",100 };

	try
	{
		repo.update(ac3);
		assert(false);

	}
	catch (RepoException&)
	{
		assert(true);
	}
	assert(activities.size() == 1);
	Activity aa5{ "a","b","aaa",100 };
	repo.store(aa5);
	repo.delete_a(aa5);
	assert(activities.size() == 1);
	assert(repo.find(aa1).getname() == "a");
	assert(repo.find_bool(aa1) == true);
	Activity aa5a{ "aaaa","b","aaa",100 };
	assert(repo.find_bool(aa5a) == false);
	try
	{
		repo.find(aa5);
		assert(false);

	}
	catch (RepoException& e)
	{

		assert("This activity doesn t exist" == e.getMessage());
	}
	try
	{
		repo.finddesc(aa5a);
		assert(false);

	}
	catch (RepoException& e)
	{

		assert("This activity doesn t exist" == e.getMessage());
	}
	try
	{
		repo.delete_a(aa5);
		assert(false);

	}
	catch (RepoException&)
	{

		assert(true);
	}

}

void testservice()
{
	Repository repo;
	ActivityValidator val;

	Service serv{ repo ,val };
	try {
		serv.UNDO();
		assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}
	serv.add("a", "a", "a", 10);
	const auto& activities = serv.getAll();
	assert(activities.size() == 1);
	serv.update("a", "b", "a", 100);
	const auto& activities1 = serv.getAll();
	assert(activities1.at(0).getdescription() == "b");
	Activity aa5{ "a","b","a",100 };
	assert(serv.find("a", "b", "a", 100).getname() == aa5.getname());
	serv.add("z", "z", "z", 10);
	serv.delete_a("a", "b", "a", 100);
	serv.delete_a("z", "z", "z", 100);
	const auto& activities2 = serv.getAll();
	assert(activities2.size() == 0);

	serv.add("c", "c", "c", 10);
	serv.add("b", "b", "b", 10);
	serv.add("a", "a", "a", 10);

	serv.raport_duration();
	serv.finddesc("a", "b", "ccc", 100);


	vector<Activity> activities3 = serv.sorta(&Service::cmpName);
	assert(activities3.at(0).getname() == "a");
	assert(activities3.at(1).getname() == "b");
	assert(activities3.at(2).getname() == "c");

	vector<Activity> activities10 = serv.sorta(&Service::cmpDescription);


	assert(activities10.at(0).getname() == "a");
	assert(activities10.at(1).getname() == "b");
	assert(activities10.at(2).getname() == "c");
	vector<Activity> activities5 = serv.sorta(&Service::cmpTypeDuration);

	assert(activities5.at(0).getname() == "a");
	assert(activities5.at(1).getname() == "b");
	assert(activities5.at(2).getname() == "c");

	vector<Activity> activitiesy = serv.sortname();
	assert(activitiesy.at(0).getname() == "a");
	assert(activitiesy.at(1).getname() == "b");
	assert(activitiesy.at(2).getname() == "c");

	vector<Activity> activitiesyy = serv.sortdesc();


	assert(activitiesyy.at(0).getname() == "a");
	assert(activitiesyy.at(1).getname() == "b");
	assert(activitiesyy.at(2).getname() == "c");
	vector<Activity> activitiesyyy = serv.sortTypeDescription();

	assert(activitiesyyy.at(0).getname() == "a");
	assert(activitiesyyy.at(1).getname() == "b");
	assert(activitiesyyy.at(2).getname() == "c");

	vector<Activity> activitiess;
	activitiess = serv.filter1("b");

	assert(activitiess.size() == 1);

	vector<Activity> activities55 = serv.filter2("a");
	assert(activities55.size() == 1);
	Repository repob;
	ActivityValidator valb;
	Service servbucket{ repob, valb };
	servbucket.add("a", "a", "a", 1);
	servbucket.clear_all();


	assert(serv.getAll().size() == 3);
	serv.UNDO();
	assert(serv.getAll().size() == 2);
	serv.update("c", "c", "c", 911);
	assert(serv.find("c", "c", "c", 911).getduration() == 911);
	serv.UNDO();
	assert(serv.find("c", "c", "c", 911).getduration() == 10);
	serv.delete_a("c", "c", "c", 1);
	assert(serv.getAll().size() == 1);
	serv.UNDO();
	assert(serv.getAll().size() == 2);





}
void testbucket()
{
	Repository repo;
	ActivityValidator val;

	Service serv{ repo ,val };
	CosActivity cos{ serv };
	cos.goleste();
	cos.adauga(Activity{ "1","2","3",4 });
	cos.adauga(Activity{ "2","2","3",4 });
	cos.del(Activity{ "2","2","3",4 });
	cos.del(Activity{ "1","2","3",4 });
	serv.add("1", "z", "z", 10);
	serv.add("2", "z", "z", 10);
	serv.add("3", "z", "z", 10);
	serv.add("4", "z", "z", 10);
	cos.umple(2);
	
	assert(cos.lista().size() == 2); 
	cos.umple(5);
}

void all_tests()
{
	testDomain();
	testvalidator();
	testRepo();
	testservice();
	testbucket();
}