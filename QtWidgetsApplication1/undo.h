#pragma once
#include "domain.h"
#include "repository.h"
#include "repolab.h"
class ActionUndo
{
public:
	virtual void doUndo() = 0;
	virtual ~ActionUndo() = default;


};

class Undoadd :public ActionUndo
{
	Activity addedAC;
	repoAbstract& repo;
public:
	Undoadd(repoAbstract& repo, const Activity& addedAC) : repo{ repo }, addedAC{ addedAC } {}
	void doUndo() override
	{
		repo.delete_a(addedAC);
	}


};
class Undodelete :public ActionUndo
{
	Activity deletedAC;
	repoAbstract& repo;
public:
	Undodelete(repoAbstract& repo, const Activity& deletedAC) : repo{ repo }, deletedAC{ deletedAC } {}
	void doUndo() override
	{
		repo.store(deletedAC);
	}

};
class Undoupdate :public ActionUndo
{

	Activity updatedAC;
	repoAbstract& repo;
public:
	Undoupdate(repoAbstract& repo, const Activity& updatedAC) : repo{ repo }, updatedAC{ updatedAC }  {}
	void doUndo() override
	{
		repo.update(updatedAC);
	}


};