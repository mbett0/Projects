#ifndef __SFPFPPG_HPP__
#define __SFPFPPG_HPP__

#include "PpgBase.hpp"

class SfPfPpg : public PpgBase{
        public:
                SfPfPpg() : PpgBase() {};
                double rate(double x){
                        return 20 * x / 26;
                }
};

#endif

