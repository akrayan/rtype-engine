// testcpp.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <list>
#include <string>

#include <iostream>
#include <math.h>

/*
class MyClass
{

public:
	std::string t;
	std::string g;
	std::string v;

	MyClass();
	~MyClass();

private:

};

MyClass::MyClass()
{
}

MyClass::~MyClass()
{
}
int main()
{
	std::list <int> l1, l2;

	/*
	std::list <int> l1, l2;
    
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);

	l2.push_back(8);
	l2.push_back(16);
	l2.push_back(32);
	l2.push_back(64);

	auto it = l1.begin();
	while (it != l1.end())
	{
		std::cout << *it << std::endl;
		it++;
	}
	std::cout << "\n\n" << std::endl;

	it = l2.begin();
	while (it != l2.end())
	{
		std::cout << *it << std::endl;
		it++;
	}
	std::cout << "\n\n" << std::endl;

	l1.splice(l1.end(), l2);

	it = l1.begin();
	while (it != l1.end())
	{
		std::cout << *it << std::endl;
		it++;
	}
	std::cout << "\n\n" << std::endl;

	it = l2.begin();
	while (it != l2.end())
	{
		std::cout << *it << std::endl;
		it++;
	}
	std::cout << "\n\n" << std::endl;
	*/
/*
	MyClass *A = new MyClass();

	A->g = "carot";
	A->v = "biscuit";
	A->t = "tarte";

	MyClass *B = new MyClass();
	//int i;
	(*B) = (*A);
	/*
	//std::cout << static_cast<long long int>(A) << " " << A->t << " " << A->g << " " << A->v << std::endl;
	std::cout << /*B << " " << B->t << " " << B->g << " " << B->v << std::endl;


	return 0;
}*/

int main()
{
	float i = 0;

	while (i < 10)
	{
		std::cout << "i = " << i  << "   cos =  " << cos(i * 10) << std::endl;
		i += 0.1;
	}
}

