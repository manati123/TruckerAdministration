#pragma once
#include "Repo.h"
#include "Service.h"
class Tests
{
public:
	void testAll();
private:
	void addStar_StarExists_ExceptionThrown();
	void addStar_StarDoesNotExist_StarWasAdded();
};

