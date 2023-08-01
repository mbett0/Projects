#ifndef __SFRB_HPP__
#define __SFRB_HPP__

#include "RbBase.hpp"

class SfRb : public RbBase{
	public:
	SfRb() : RbBase () {};
        double rate(double x){
                return 20 * x / 8;
        }


};

#endif


