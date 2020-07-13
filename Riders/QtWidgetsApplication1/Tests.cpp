#include "Tests.h"
#include <assert.h>
void Tests::testAll()
{
	addStar_StarExists_ExceptionThrown();
	addStar_StarDoesNotExist_StarWasAdded();
}

void Tests::addStar_StarExists_ExceptionThrown()
{
	StarRepo s;
	Stars starz{ "a","b",1,2,3 };
	try {
		s.add(starz);
		assert(false);
	}
	catch (exception& e) {
		assert(e.what() != "");
	}
	StarService service{ s };
	try {
		service.add("a", "b", 1, 2, 3);
		assert(false);
	}
	catch (exception& e) {
		assert(e.what() != "");
	}
}

void Tests::addStar_StarDoesNotExist_StarWasAdded()
{
	StarRepo s;
	Stars starz{ "x","b",1,2,3 };
	s.add(starz);
	assert(s.getStars().size() != 0);
	StarService service{ s };
	service.add("y", "b", 1, 2, 3);
	assert(s.getStars().size() != 0);
}
