#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;
class Astronomer
{
private:
	std::string name, constellation;
public:
	Astronomer() = default;
	Astronomer(std::string _name, std::string _constellation):name{_name},constellation{_constellation}{}
	~Astronomer() = default;
	std::string getName() { return name; }
	std::string getConstellation() { return constellation; }
	friend istream& operator>>(istream& input_stream, Astronomer& a);
	friend ostream& operator<<(ostream& output_stream, Astronomer& a);
	std::string toString() const;
};

class Stars {
private:
	string name, constellation;
	int ra, dec, diameter;
public:
	Stars() = default;
	Stars(string name, string constellation, int ra, int dec, int diameter):name{name},constellation{constellation},ra{ra},dec{dec}, diameter{ diameter }{}
	std::string toString() const;
	friend istream& operator>>(istream& input_stream, Stars& s);
	friend ostream& operator<<(ostream& output_stream, Stars& s);
	string getName() { return name; }
	string getConstellation() { return constellation; }
	int getDiam() { return diameter; }
	int getRa() { return ra; }
	int getDec(){return dec;}

};