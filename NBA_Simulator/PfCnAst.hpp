#ifndef __PFCNAST_HPP__
#define __PFCNAST_HPP__

#include "AstBase.hpp"

class PfCnAst : public AstBase{
	public:
        PfCnAst() : AstBase () {};
        double rate(double x){
                return 10 * x / 5;
        }

};

#endif


