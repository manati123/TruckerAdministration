#pragma once
#include <vector>
#include <algorithm>
using namespace std;
class Observer
{
public:
	virtual void update() = 0;
	virtual ~Observer() {}
};


class Observable
{
private:
	//Non-owning pointers to observer instances
	std::vector<Observer*> observers;
public:
	virtual ~Observable() {}

	void addObserver(Observer* obs)
	{
		observers.push_back(obs);
	}

	void removeObserver(Observer* obs)
	{
		auto it = std::find(observers.begin(), observers.end(), obs);
		if (it != observers.end())
			observers.erase(it);
	}

	void notify()
	{
		for (auto obs : observers)
		{
			obs->update();
		}
	}
};