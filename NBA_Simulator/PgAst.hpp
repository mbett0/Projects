#ifndef __PGASSIST_HPP__
#define __PGASSIST_HPP__

#include "AstBase.hpp"

class PgAst : public AstBase{
	public:
	PgAst() : AstBase () {};
	double rate(double x){
		return 30 * x / 10.6;
	}
};

#endif

