#ifndef __CNPPG_HPP__
#define __CNPPG_HPP__

#include "PpgBase.hpp"

class CnPpg : public PpgBase{
        public:
                CnPpg() : PpgBase() {};
                double rate(double x){
                        return 20 * x / 18;
                }
};

#endif

