#include "repository.h"
#include <iostream>
void Repository::store(const Activity& activity)
{
	for (const Activity& ac : activities)
		if (ac.getname() == activity.getname() && ac.gettype() == activity.gettype())
		{
			throw RepoException("Activity already exist");
		}
	activities.push_back(activity);
}
void Repository::update(const Activity& activity)
{
	bool found = false;
	for (Activity& ac : activities)
		if (ac.getname() == activity.getname() && ac.gettype() == activity.gettype())
		{
			string val1 = activity.getdescription();
			ac.setdescription(val1);
			int const val2 = activity.getduration();
			ac.setduration(val2);
			found = true;
		}
	if (!found)
		throw RepoException("This activity doesn t exist");

}
void Repository::delete_a(const Activity& activity)
{
	int counter = 0;
	for (const auto& ac : activities)
	{
		if (ac.getname() == activity.getname() && ac.gettype() == activity.gettype())
		{
			activities.erase(activities.begin() + counter);
			return;

		}
		counter++;

	}
	throw RepoException("The activity doesn t exist\n");

}
bool Repository::find_bool(const Activity& activity) {
	for (const Activity& ac : activities)
		if (ac.getname() == activity.getname() && ac.gettype() == activity.gettype())
		{
			return true;
			//return false;
		}
	return false;
}
const Activity& Repository::find(const Activity& activity)
{

	auto rez = std::find_if(activities.begin(), activities.end(), [&activity](const Activity& ac)
		{
			return ac.getname() == activity.getname() && ac.gettype() == activity.gettype();
		});
	if (rez != activities.end())
		return *rez;
	else throw RepoException("This activity doesn t exist");}
/*
for ( const Activity& ac : activities)
	if (ac.getname() == activity.getname() && ac.gettype() == activity.gettype())
	{
		return ac;
		//return false;
	}
throw RepoException("This activity doesn t exist");
//return false;

//std::vector<int>::iterator it= std::find_if(activities.begin(), activities.end(),[](const Activity& ac){return ac.getname()==;
*/


const Activity& Repository::finddesc(const Activity& activity)
{
	for (const Activity& ac : activities)
		if (ac.getname() == activity.getname())
		{
			return ac;
			//return false;
		}
	throw RepoException("This activity doesn t exist");
	//return false;
}
const vector<Activity>& Repository::getAll() noexcept
{
	return activities;
}

vector<Activity>& Repository::getAll_for_del() noexcept
{
	return activities;
}
