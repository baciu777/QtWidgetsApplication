#pragma once
#include <unordered_map>
#include "domain.h"
using namespace std;
class repoAbstract
{


public:
	//repoAbstract(const repoAbstract& ot) = delete;
	//repoAbstract() = default;
	virtual ~repoAbstract() = default;
	/*
	add one activity, throw exception if the activity already exist
	*/
	//virtual ~repoAbstract()=default;
	virtual void store(const Activity& activity) = 0;
	/*
	update one activity, throw exception if the activity doesn t exist
	*/
	virtual void update(const Activity& activity) = 0;
	/*
	delete one activity, throw exception if the activity doesn t exist
	*/
	virtual void delete_a(const Activity& activity) = 0;
	/*
	find if the "activity" exist in the list, if yes return it
	throw exception, otherwise
	*/
	virtual const Activity& find(const Activity& activity) = 0;
	/*
	find a matching description
	throw exception, otherwise
	*/
	virtual const Activity& finddesc(const Activity& activity) = 0;
	/*
	return all the elements that exist in the list
	*/
	virtual const vector<Activity>& getAll()  noexcept = 0;
	virtual vector<Activity>& getAll_for_del() noexcept = 0;


	virtual bool find_bool(const Activity& activity) = 0;
};


class Repositorylab :public repoAbstract
{
private:
	unordered_map<string, Activity> activities;
	vector<Activity> getvector;
	float numar;

	void throwRandomException();
public:
	Repositorylab(const Repositorylab& ot) = delete;
	Repositorylab(float numar) : numar{ numar }
	{

	}
	//Repositorylab() = default;
	//RepositoryLab(const RepositoryLab& ot) = delete;

	/*
	add one activity, throw exception if the activity already exist
	*/
	void store(const Activity& activity) override;
	/*
	update one activity, throw exception if the activity doesn t exist
	*/
	void update(const Activity& activity) override;
	/*
	delete one activity, throw exception if the activity doesn t exist
	*/
	void delete_a(const Activity& activity) override;
	/*
	find if the "activity" exist in the list, if yes return it
	throw exception, otherwise
	*/
	const Activity& find(const Activity& activity) override;
	/*
	find a matching description
	throw exception, otherwise
	*/
	const Activity& finddesc(const Activity& activity)override;
	/*
	return all the elements that exist in the list
	*/
	const vector<Activity>& getAll() noexcept override;
	vector<Activity>& getAll_for_del() noexcept override;


	bool find_bool(const Activity& activity) override;
};