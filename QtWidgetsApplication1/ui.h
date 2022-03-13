#pragma once
#include "service.h"
#include "list.h"
class UI
{
	//private:
	Service& serv;
	Service& servbucket;
public:
	UI(Service& serv, Service& servbucket) noexcept :serv{ serv }, servbucket{ servbucket }
	{

	}
	/*
	start de UI and read commands
	*/
	void startUI();
	/*
	read three strings and one int value and call the add fucntion fron service
	*/
	void add_ui();
	/*
	read one string and one int value and call the update fucntion fron service
	*/
	void update_ui();
	/*
	read one string and one int value and call the delete fucntion fron service
	*/
	void delete_ui();
	/*
	read three strings and one int value and call the find fucntion fron service
	*/
	void find_ui();

	//typedef int(*FunctieComparare)(const Activity&, const  Activity&);

	/*
	call the function sort from service
	*/

	void sort_ui();
	/*
	call the filters function from service
	*/
	void filter_ui();
	/*
	print all the elements that exist in the list
	*/


	void print_elems(const vector<Activity>& activities);
	/*
	print the meniu, where are all the possible commands
	*/
	void print_meniu_bucket();
	void add_bucket();
	void delete_bucket();
	void add_random_bucket();
	void write_file_bucket();


	void raportUI();


	void print_meniu();


	void undo();
};