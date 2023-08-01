#ifndef __PGSGRB_HPP__
#define __PGSGRB_HPP__

#include "RbBase.hpp"

class PgSgRb : public RbBase{
	public:
	PgSgRb() : RbBase () {};
	double rate(double x){
		return 5 * x / 8;
	}
};

#endif


