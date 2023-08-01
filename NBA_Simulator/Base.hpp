#ifndef __BASE_HPP__
#define __BASE_HPP__

#include <string>

class Base {
    public:
        /* Constructors */
        Base() { };

        /* Pure Virtual Functions */
        virtual double rating() = 0;
        virtual void Display() = 0;
	
};

#endif

