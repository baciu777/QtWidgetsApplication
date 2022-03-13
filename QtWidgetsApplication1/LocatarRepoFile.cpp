#include "LocatarRepoFile.h"
#include "domain.h"
#include "repository.h"
#include <fstream>
#include <assert.h>

void RepoFile::loadFromFile() {
	std::ifstream f(fName.c_str());
	if (!f.is_open()) { // verify if the stream is opened
		throw RepoException("Unable to open file:" + fName);
	}



	while (!f.eof()) {

	
		std::string name, desc, type;
		int dur;
		f >> name;
		f >> desc;
		f >> type;
		f >> dur;
		if (f.eof())
			break;
		Activity ac{ name,desc,type,dur };
		store(ac);
		//writeToFile();
	}
	f.close();
}

void RepoFile::writeToFile() {
	std::ofstream g(fName.c_str());
	//g.open(fName);

	if (!g.is_open()) { // verify if the stream is opened
		throw RepoException("Unable to open file:" + fName);
	}
	
	for (const Activity& Activity : Repository::getAll()) {
		g << Activity.getname() << " " << Activity.getdescription() << " " << Activity.gettype() << " " << Activity.getduration() << '\n';
	}
	g.close();
}

