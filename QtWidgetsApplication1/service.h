#pragma once
#include <string>
#include <iostream>
#include<unordered_map>
#include "domain.h"
#include "repository.h"
#include "validator.h"
#include "dto.h"
#include "undo.h"
#include "repolab.h"

using std::unique_ptr;
using std::string;
using std::vector;
using std::unordered_map;
class Service
{
private:
	repoAbstract& repo;
	ActivityValidator& val;
	vector<unique_ptr<ActionUndo>> undo;

public:
	Service(repoAbstract& repo, ActivityValidator& val) noexcept : repo{ repo }, val{ val }
	{

	}
	Service(const Service& ot) = delete;
	Service() = default;

	/*
	* name-string
	* description-string
	* type-string
	* duration-int
	add the activity created with given data
	throw exception if the data are invalid
	*/
	void  add(const string& name, const string& description, const string& type, int duration);
	/*
	* name-string
	* description-string
	* type-string
	* duration-int
	update the activity created with given data
	throw exception if the data are invalid
	*/
	void  update(const string& name, const  string& description, const  string& type, int duration);
	/*
	* name-string
	* description-string
	* type-string
	* duration-int
	delete the activity created with given data
	throw exception if the data are invalid
	*/
	void  delete_a(const string& name, const string& description, const string& type, int duration);
	/*
	* name-string
	* description-string
	* type-string
	* duration-int
	find the activity created with given data
	throw exception if the data are invalid
	return the activity if we found it
	*/
	Activity find(const string& name, const string& description, const string& type, int duration);
	/*
	* name-string
	* description-string
	* type-string
	* duration-int
	function find that look after a matching description
	return the activity found
	else throw repo exception
	*/
	Activity finddesc(const string& name, const string& description, const string& type, int duration);
	/*
	function that clear all the activities
	*/
	void clear_all() noexcept;
	/*
	compare 2 names
	*/
	int cmpName(const Activity& a1, const  Activity& a2);
	/*
	compare 2 descriptions
	*/
	int cmpDescription(const Activity& a1, const  Activity& a2);
	/*
	compare 2 types and if they are the same we compare the duration
	*/
	int cmpTypeDuration(const Activity& a1, const  Activity& a2);
	//typedef int(*FunctieComparare)(const Activity& ,const  Activity& );
	/*
	sort function in service
	the parametre is a pointer at the functions compare
	*/
	vector<Activity> sorta(int(Service::* FunctieComparare)(const Activity&, const Activity&));
	/*
	sort function after name
	*/
	vector<Activity> sortname();
	/*
	sort function after description
	*/
	vector<Activity> sortdesc();
	/*
   sort function after type and description
   */
	vector<Activity> sortTypeDescription();

	/*
	function that return the elements that have the description given
	*/
	const vector<Activity> filter1(const string&) const noexcept;
	/*
	function that return the elements that have the type given
	*/
	const vector<Activity> filter2(const string&) const noexcept;
	/*
	filter function -main
	*/
	//vector<Activity> filter(string);
   /*
   return all the elements that exist in the list
   */


	const vector<Activity>& getAll() const noexcept;

	unordered_map<int, Dto_duration> raport_duration();


	void UNDO();
};