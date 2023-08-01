#ifndef __DEFBASE_HPP__
#define __DEFBASE_HPP__
//#include "Player.hpp"

//class Player;
using namespace std;

class DefBase {
	public:
	DefBase() {};
	virtual double rate(double, double )=0;
};

#endif
