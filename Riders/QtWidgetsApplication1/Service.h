#pragma once
#include "Repo.h"
#include "Observer.h"
using namespace std;
class AstroService : public Observable
{
private:
	AstronomerRepo& repo;
public:
	AstroService(AstronomerRepo& _r):repo{_r}{}
	
};

class StarService: public Observable {
private:
	StarRepo& repo;
public:
	void write() { this->repo.write(); }
	vector<Stars> getRepo() { return repo.getStars(); }
	StarService(StarRepo& _s):repo{_s}{}
	void add(string name, string constellation, int ra, int dec, int delimiter);
};