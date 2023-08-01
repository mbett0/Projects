#ifndef __SGSFAST_HPP__
#define __SGSFAST_HPP__

#include "AstBase.hpp"

class SgSfAst : public AstBase{
	public:
	SgSfAst() : AstBase () {};
        double rate(double x){
                return 20 * x / 10.6;
        }

};

#endif

