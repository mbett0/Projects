#ifndef __PFCNDEF_HPP__
#define __PFCNDEF_HPP__

#include "DefBase.hpp"

class PfCnDef : public DefBase{
	public:
        PfCnDef() : DefBase() {};
        double rate(double x, double y){
                return 20 * ( x + (y * 2)) / 5;
        }

};

#endif
