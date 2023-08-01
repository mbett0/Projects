#ifndef __PFCNFGPCNT_HPP__
#define __PFCNFGPCNT_HPP__

#include "FgPcntBase.hpp"

class PfCnFgPcnt : public FgPcntBase{
	 public:
                PfCnFgPcnt() : FgPcntBase() {};
                double rate (double x){
                        return 20 * x / 58;
                }


};

#endif
