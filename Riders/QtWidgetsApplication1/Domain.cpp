#include "Domain.h"
#include <string>
#include <vector>


vector<string> tokenize(string input)
{
	vector<string> tokens;
	stringstream spliter(input);
	string token;
	while (getline(spliter, token, ','))
	{
		tokens.push_back(token);
	}
	return tokens;
}

istream& operator>>(istream& input_stream, Astronomer& a)
{
	string get_input;
	getline(input_stream, get_input);
	vector<string> tokens = tokenize(get_input);
	if (tokens.size() != 0)
	{
		a.name = tokens[0];
		a.constellation = tokens[1];
	}
	return input_stream;
}

ostream& operator<<(ostream& output_stream, Astronomer& a)
{
	output_stream << a.toString();
	return output_stream;
}

istream& operator>>(istream& input_stream, Stars& s)
{
	string get_input;
	getline(input_stream, get_input);
	vector<string> tokens = tokenize(get_input);
	if (tokens.size() != 0)
	{
		s.name = tokens[0];
		s.constellation = tokens[1];
		s.ra = stoi(tokens[2]);
		s.dec = stoi(tokens[3]);
		s.diameter = stoi(tokens[4]);
	}
	return input_stream;
}

ostream& operator<<(ostream& output_stream, Stars& s)
{
	output_stream << s.toString();
	return output_stream;
}

std::string Astronomer::toString() const
{
	stringstream buffer;
	buffer << this->name << "," << this->constellation << endl;
	return buffer.str();
}

std::string Stars::toString() const
{
	stringstream buffer;
	buffer << this->name << "," << this->constellation << "," << this->ra << "," << this->dec << "," << this->diameter << endl;
	return buffer.str();
}
