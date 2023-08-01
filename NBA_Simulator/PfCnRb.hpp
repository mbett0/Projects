#ifndef __PFCNRB_HPP__
#define __PFCNRB_HPP__

#include "RbBase.hpp"

class PfCnRb : public RbBase{
	public:
	PfCnRb() : RbBase () {};
        double rate(double x){
                return 30 * x / 14;
        }


};

#endif


