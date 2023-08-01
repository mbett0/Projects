#ifndef __PGPPG_HPP__
#define __PGPPG_HPP__

#include "PpgBase.hpp"

class PgPpg : public PpgBase{
	public:
		PgPpg() : PpgBase() {};
		double rate(double x){
			return 25 * x / 27;
		}
};

#endif
