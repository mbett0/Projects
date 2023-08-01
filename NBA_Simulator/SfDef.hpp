#ifndef __SFDEF_HPP__
#define __SFDEF_HPP__

#include "DefBase.hpp"

class SfDef : public DefBase{
	public:
        SfDef() : DefBase() {};
        double rate(double x, double y){
                return 20 * ( x + y) / 2.5;
	}
};

#endif

