#pragma once
#include <vector>
#include "list.h"
#include "domain.h"
#include "repolab.h"
using std::vector;
class RepoException
{
	string msg;
public:
	RepoException(string m) : msg{ m } {

	}
	string getMessage()
	{
		return msg;
	}
};
class Repository :public repoAbstract
{
private:
	vector<Activity> activities;
public:
	Repository(const Repository& ot) = delete;
	Repository() = default;
	/*
	add one activity, throw exception if the activity already exist
	*/
	virtual void store(const Activity& activity) override;
	/*
	update one activity, throw exception if the activity doesn t exist
	*/
	virtual void update(const Activity& activity)override;
	/*
	delete one activity, throw exception if the activity doesn t exist
	*/
	virtual void delete_a(const Activity& activity)override;
	/*
	find if the "activity" exist in the list, if yes return it
	throw exception, otherwise
	*/
	const Activity& find(const Activity& activity)override;
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


	virtual bool find_bool(const Activity& activity)override;
};