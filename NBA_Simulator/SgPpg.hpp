#ifndef __SGPPG_HPP__
#define __SGPPG_HPP__

#include "PpgBase.hpp"

class SgPpg : public PpgBase{
        public:
                SgPpg() : PpgBase() {};
                double rate(double x){
                        return 35 * x / 30;
                }
};

#endif

