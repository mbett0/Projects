#ifndef __PGSGSFFGPCNT_HPP__
#define __PGSGSFFGPCNT_HPP__

#include "FgPcntBase.hpp"

class PgSgSfFgPcnt : public FgPcntBase{
	public:
		PgSgSfFgPcnt() : FgPcntBase() {};
		double rate (double x){
			return 20 * x / 48;
		}

};

#endif

