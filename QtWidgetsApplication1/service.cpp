#include "service.h"
#include <functional>
#include <iostream>
#include <algorithm>

void Service::add(const string& name, const string& description, const string& type, int duration)
{
	Activity ac{ name,description,type,duration };
	val.validate(ac);
	repo.store(ac);
	//undo.push_back(new Undoadd{ repo,ac });
	undo.push_back(std::make_unique<Undoadd>(repo, ac));
}
void Service::update(const string& name, const string& description, const string& type, int duration)
{
	Activity ac{ name,description,type,duration };
	Activity old_ac = find(name, description, type, duration);
	val.validate(ac);
	repo.update(ac);
	undo.push_back(std::make_unique<Undoupdate>(repo, old_ac));
}
Activity Service::find(const string& name, const string& description, const string& type, int duration)
{
	Activity ac{ name,description,type,duration };
	val.validate(ac);

	return repo.find(ac);
	//return ac;
//else return ac;//change it at the second iteration

}
Activity Service::finddesc(const string& name, const string& description, const string& type, int duration)
{
	Activity ac{ name,description,type,duration };
	val.validate(ac);
	return repo.finddesc(ac);
	//return ac;
//else return ac;//change it at the second iteration

}
void Service::delete_a(const string& name, const string& description, const string& type, int duration)
{
	Activity ac{ name,description,type,duration };
	val.validate(ac);
	Activity old_ac = find(name, description, type, duration);
	repo.delete_a(ac);
	//change it at the second iteration
	undo.push_back(std::make_unique<Undodelete>(repo, old_ac));

}
void Service::clear_all() noexcept
{
	repo.getAll_for_del().clear();
}
int Service::cmpName(const Activity& a1, const  Activity& a2)
{
	return a1.getname() < a2.getname();
}

int Service::cmpDescription(const Activity& a1, const  Activity& a2)
{
	return a1.getdescription() < a2.getdescription();
}
int Service::cmpTypeDuration(const Activity& a1, const  Activity& a2)
{
	if (a1.gettype() < a2.gettype())
		return 1;
	if (a1.gettype() == a2.gettype() && a1.getduration() < a2.getduration())return 1;
	else return 0;
}


vector<Activity> Service::sorta(int(Service::* FunctieComparare)(const Activity&, const Activity&))
{
	vector<Activity>  copyAll = repo.getAll();
	for (Activity& el1 : copyAll)
		for (Activity& el2 : copyAll)
			if ((this->*FunctieComparare)(el1, el2))
			{
				Activity aux = el1;
				el1 = el2;
				el2 = aux;
			}
	//std::sort(copyAll.begin(), copyAll.end(),cmp);
	return copyAll;
}
vector<Activity> Service::sortname()
{
	vector<Activity>  copyAll = repo.getAll();
	std::sort(copyAll.begin(), copyAll.end(), [](const Activity& a1, const  Activity& a2)
		{
			return a1.getname() < a2.getname();
		});
	return copyAll;
}
vector<Activity> Service::sortdesc()
{
	vector<Activity>  copyAll = repo.getAll();
	std::sort(copyAll.begin(), copyAll.end(), [](const Activity& a1, const  Activity& a2)
		{
			return a1.getdescription() < a2.getdescription();
		});
	return copyAll;
}
vector<Activity> Service::sortTypeDescription()
{
	vector<Activity>  copyAll = repo.getAll();
	std::sort(copyAll.begin(), copyAll.end(), [](const Activity& a1, const  Activity& a2)
		{
			return a1.gettype() < a2.gettype() || a1.gettype() == a2.gettype() && a1.getdescription() < a2.getdescription();
		});
	return copyAll;
}
/*vector<Activity> Service::sortt(cmp* cmpT)
{
	vector<Activity>  copyAll = repo.getAll();
	std::sort(copyAll.begin(), copyAll.end(), cmpT);
	//std::sort(copyAll.begin(), copyAll.end(),cmp);
	return copyAll;
}*/

const vector<Activity> Service::filter1(const string& desc) const noexcept
{

	vector<Activity>  copyAll = repo.getAll();
	vector<Activity>  aux;
	/*for (const Activity& el1 : copyAll)
	{
		if (el1.getdescription() == desc)
		{
			 aux.push_back(el1);
		}
	}*/
	auto rez = std::copy_if(copyAll.begin(), copyAll.end(), std::back_inserter(aux), [desc](const Activity& ac)
		{
			return ac.getdescription() == desc;
		});
	return aux;




}

const vector<Activity> Service::filter2(const string& type) const noexcept
{
	/*vector<Activity>  aux;
	vector<Activity>  copyAll = repo.getAll();
	for (const Activity& el1 : copyAll)
		if (el1.getdescription() == type)
			aux.push_back(el1);
	return aux;*/
	vector<Activity>  copyAll = repo.getAll();
	vector<Activity>  aux;
	auto rez = std::copy_if(copyAll.begin(), copyAll.end(), std::back_inserter(aux), [type](const Activity& ac)
		{
			return ac.gettype() == type;
		});
	return aux;
}

unordered_map<int, Dto_duration> Service::raport_duration()
{
	unordered_map<int, Dto_duration> raport;
	const auto& all = getAll();
	for (const auto& ac : all)
	{

		if (raport.find(ac.getduration()) != raport.end())
			raport[ac.getduration()].addNr();
		else
			raport[ac.getduration()] = Dto_duration(ac.getduration());
	}
	return raport;
}

const vector<Activity>& Service::getAll() const noexcept
{
	return repo.getAll();
}


void Service::UNDO()
{
	if (undo.empty())
		throw RepoException("nu more operations");
	undo.back()->doUndo();
	undo.pop_back();

}