#pragma once
#include "repolab.h"
#include "repository.h"

class RepoFile :public Repository
{
private:
	std::string fName;
	void loadFromFile();
	void writeToFile();
public:
	RepoFile(std::string fName) : Repository(), fName{ fName }{
		loadFromFile(); //incarcam datele din fisier
	}

	void store(const Activity& loc) override {
		Repository::store(loc); //apelam metoda din clasa de baza
		writeToFile();
	}

	void delete_a(const Activity& loc) override {
		Repository::delete_a(loc); //apelam metoda din clasa de baza
		writeToFile();
	}

	void update(const Activity& loc) override {
		Repository::update(loc); //apelam metoda din clasa de baza
		writeToFile();
	}
};

