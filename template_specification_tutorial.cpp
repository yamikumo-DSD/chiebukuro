//tutorial_specification_tutorial.cpp

#include <iostream>

using namespace std;

struct Test
{
	template<typename T> void test1(T) const;
	template<typename T> void test2(T) const;
	void test1(double n) const;
	void test2(double n) const;
};

template<typename T>
void Test::test1(T n) const
{
	test1((double)n);
}

template<typename T>
void Test::test2(T n) const
{
	test2((double)n);
}

void Test::test2(double n) const
{
	test1(n);
	cout << n;
}

void Test::test1(double n) const
{
	test2(n);
	cout << n << endl;
}

int main()
{
	Test t;
	return 0;
}

