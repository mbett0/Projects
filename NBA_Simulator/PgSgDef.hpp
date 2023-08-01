#ifndef __PGSGDEF_HPP__
#define __PGSGDEF_HPP__

#include "DefBase.hpp"

class PgSgDef : public DefBase{
	public:
	PgSgDef() : DefBase() {};
	double rate(double x, double y){
		return 20 * ( x * 3 + y) / 6;
	}

};

#endif


