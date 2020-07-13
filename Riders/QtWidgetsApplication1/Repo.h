#pragma once
#include "Domain.h"
#include <vector>
using namespace std;
class AstronomerRepo {
private:
	std::vector<Astronomer> astronomers;
public:
	AstronomerRepo() { read(); }
	void read();
	std::vector<Astronomer> getRepo() { return astronomers; }
	//void write();
	//void add(Astronomer a);
	
};

class StarRepo {
private:
	vector<Stars> stars;
public:
	void read();
	void write();
	StarRepo() { read(); }
	vector<Stars> getStars() { return stars; }
	void add(Stars s);
};