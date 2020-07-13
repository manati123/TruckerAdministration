#include "Repo.h"

void AstronomerRepo::read()
{
	Astronomer a{};
	ifstream file("astronomers.txt");
	while (file >> a) {
		astronomers.push_back(a);
	}
	file.close();
}

void StarRepo::read()
{

	Stars a{};
	ifstream file("stars.txt");
	if (!file.is_open())
		throw exception("file failed");
	while (file >> a) {
		this->add(a);
	}
	file.close();
}

void StarRepo::write()
{
	ofstream file("stars.txt");
	if (!file.is_open())
		throw exception("file failed");
	for (auto& item : stars)
		file << item;
	file.close();
}

void StarRepo::add(Stars s)
{
	//here after all the passing and the object-creating the object is being tested to see if it belongs in the repo(otherwise it will not be added)
	//if the object is OK then it will be added into the vector from the repo
	if (s.getDiam() <= 0)
		throw exception("Diameter too small");
	if (s.getName() == "")
		throw exception("Name empty!");
	for (auto& item : stars)
		if (item.getName() == s.getName())
			throw exception("Star already exists");
	stars.push_back(s);
}
