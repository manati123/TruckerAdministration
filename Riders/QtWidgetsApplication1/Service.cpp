#include "Service.h"

void StarService::add(string name, string constellation, int ra, int dec, int delimiter)
{
	//hello here I go again
	//Here the object is saved and is send to the repo for being added --->>>> more in Repo.cpp
	Stars s{ name, constellation, ra, dec, delimiter };
	this->repo.add(s);
	this->notify();
	this->notify();
}
