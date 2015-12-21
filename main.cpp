#include <cstdlib>
#include <iostream>
#include <cmath>
#include <boost/format.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

template<class Rap>
class Time
{
private:
	Rap hour, minute, second;
public:
	Time(Rap _hour, Rap _minute, Rap _second)
	{
		second = std::div(_second, 60).rem;
		minute = std::div(_minute + std::div(_second, 60).quot, 60).rem;
		hour = _hour + std::div(_minute + std::div(_second, 60).quot, 60).quot;
	}
	template<class Real>
	Real get_as_second(void) const
	{
		return static_cast<Real>(60 * 60 * hour + 60 * minute + second);
	}
	template<class Real>
	Real get_as_minute(void) const
	{
		return static_cast<Real>(60 * hour + minute + second / 60);
	}
	template<class Real>
	Real get_as_hour(void) const
	{
		return static_cast<Real>(hour + minute / 60 + second / (60 * 60));
	}
	Rap get_second(void) const { return second; }
	Rap get_minute(void) const { return minute; }
	Rap get_hour(void) const { return hour; }
	template<class Integer>
	Time operator*(Integer _m)
	{
		Time temp(_m * this->hour, _m * this->minute, _m * this->second);
		return temp;
	}
	template<class Integer>
	Time& operator*=(Integer _m)
	{
		*this = *this * _m;
		return *this;
	}
};

using ITime = Time<int>;

namespace AST 
{
	struct Time
	{
		int h, m, s;
	}; 
}

BOOST_FUSION_ADAPT_STRUCT
(
	AST::Time,
	(int, h)
	(int, m)
	(int, s)
)


void input(ITime& _t)
{
	using namespace boost::spirit;
	std::string input;
	std::cout << "ATTENTION: Please input as following form." << std::endl;
	std::cout << "XXXhYYYmZZZs" << std::endl;
	std::getline(std::cin, input);
	AST::Time origin;
	auto result = qi::phrase_parse(input.begin(), input.end(), qi::int_ >> 'h' >> qi::int_ >> 'm' >> qi::int_, qi::ascii::space, origin);
	if (result)
	{
		ITime temp(origin.h, origin.m, origin.s);
		_t = temp;
	}
	else
	{
		throw std::runtime_error("Invalid form of expression.");
	}
}

void output(const ITime& _t)
{
	std::cout << boost::format("%1%ŽžŠÔ%2%•ª%3%•b") %_t.get_hour() %_t.get_minute() %_t.get_second() << std::endl;
}

int main()
{
	try
	{
		ITime time(0, 0, 0);
		input(time);
		std::cout << "Original" << std::endl;
		output(time);
		time *= 2;
		std::cout << "Doubled" << std::endl;
		output(time);
	}
	catch(const std::runtime_error& _e)
	{
		std::cerr << _e.what() << std::endl;
	}
	std::system("pause");
	return 0;
}
