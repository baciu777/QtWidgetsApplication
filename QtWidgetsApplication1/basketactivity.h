#pragma once
#include <vector>
#include <algorithm>
#include <random>    // std::default_random_engine
#include <chrono>    // std::chrono::system_clock

#include "domain.h"
#include "observer.h"
#include "service.h"

using std::vector;
/*
  Clasa care implementeaza ideea de cos
  Extinde observable, astfel cei interesati se notifica in caz ca s-a schimbat ceva la Cos
*/
class CosActivity :public Observable {
	vector<Activity> inCos;
	 Service& rep;
public:
	CosActivity( Service& rep) :rep{ rep } {}

	void adauga(const Activity& p) {
		inCos.push_back(p);
		//notificam cand se schimba ceva in cos
		notify();
	}
	void del(const Activity& p) {
		int counter = 0;
		for (const auto& ac : inCos)
		{
			if (ac.getname() == p.getname() && ac.gettype() == p.gettype())
			{
				inCos.erase(inCos.begin() + counter);
				notify();
				return;

			}
			counter++;

		}
		
	}
	void goleste() {
		//inCos.push_back(Activity{ "1","1","1",1 });
		inCos.clear();
		//notificam can dse schimba ceva in cos
		notify();
	}
	/*
	Umple cosul aleator
	*/
	void umple(int cate) {
		//int seed = std::chrono::system_clock::now().time_since_epoch().count();
		vector<Activity> all = rep.getAll();
		auto seed = std::chrono::system_clock::now().time_since_epoch().count();
		unsigned const int ss = unsigned int(seed);
		std::shuffle(all.begin(), all.end(), std::default_random_engine(ss));
		int i = 0;
		while ( all.size() > 0) {
			bool found = false;
			for (const Activity& ac : inCos)
			{
				auto activity = all.back();

				if (ac.getname() == activity.getname() && ac.gettype() == activity.gettype())
				{
					found = true;
					//return false;
				}
			}
			if (found == false)
			{
				i++;
				inCos.push_back(all.back());
			}
				all.pop_back();
				if (cate == i)
					break;
			
		}
		//notificam can dse schimba ceva in cos
		notify();
	
		
	}

	const vector<Activity>& lista() const {
		return inCos;
	}
};