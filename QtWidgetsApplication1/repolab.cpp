#include "repolab.h"
#include "repository.h"
#include <iostream>


float RandomFloat(float a, float b) noexcept {
	const float random = ((float)rand()) / (float)RAND_MAX;
	const float diff = b - a;
	const float r = random * diff;
	return a + r;
}

void Repositorylab::throwRandomException() {
	const float r = RandomFloat(0, 1);
	if (r < this->numar) {
		throw RepoException("Random error");
	}
}

void Repositorylab::store(const Activity& activity)
{
	this->throwRandomException();
	for (const auto ac : activities)
		if (ac.first == activity.getname())
		{
			throw RepoException("Activity already exist");
		}
	activities[activity.getname()] = activity;

}
void Repositorylab::update(const Activity& activity)
{
	this->throwRandomException();
	bool found = false;
	for (const auto ac : activities)
		if (ac.first == activity.getname())
		{
			activities[ac.first] = activity;
			found = true;
		}
	if (!found)
		throw RepoException("This activity doesn t exist");

}
void Repositorylab::delete_a(const Activity& activity)
{
	this->throwRandomException();
	int counter = 0;
	for (const auto ac : activities)
		if (ac.first == activity.getname())
		{
			activities.erase(ac.first);
			return;

		}
	counter++;


	throw RepoException("The activity doesn t exist\n");

}
bool Repositorylab::find_bool(const Activity& activity) {
	for (const auto ac : activities)
		if (ac.first == activity.getname())
		{
			return true;
			//return false;
		}
	return false;
}
const Activity& Repositorylab::find(const Activity& activity)
{


	for (const auto& ac : activities)
		if (ac.first == activity.getname())
		{
			return ac.second;
			//return false;
		}
	throw RepoException("This activity doesn t exist");
	//return false;
}


const Activity& Repositorylab::finddesc(const Activity& activity)
{
	//getall.push_back(activity);
	for (const auto& ac : activities)
		if (ac.first == activity.getname())
		{

			return ac.second;

		}
	throw RepoException("This activity doesn t exist");
}
const vector<Activity>& Repositorylab::getAll() noexcept
{
	this->getvector.clear();
	for (auto it : this->activities) {
		getvector.push_back(it.second);
	}
	return getvector;
}

vector<Activity>& Repositorylab::getAll_for_del() noexcept
{
	this->getvector.clear();
	for (auto it : this->activities) {
		getvector.push_back(it.second);
	}
	return getvector;
	//return getvector;
}
