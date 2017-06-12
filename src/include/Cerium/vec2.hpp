#ifndef CERIUM_VEC2_HPP
#define CERIUM_VEC2_HPP

#include <ostream>

namespace cerium
{
    struct vec2
    {
        float x, y;
        /*
            ^[start]
            ^[class][vec2]
            ^[description][Setting 0 as value of attributes of vector]
        */
        vec2(void); //^header
        /*
            ^[start]
            ^[class][vec2]
            ^[description][Setting given argument as value of attributes of vector]
            ^[argument]<value>[Value of vector]
        */
        vec2(const float & value); //^header
        /*
            ^[start]
            ^[class][vec2]
            ^[description][Setting 0 as value of attributes of vector]
            ^[argument]<valueX>[Value of x attribute of vector]
            ^[argument]<valueY>[Value of x attribute of vector]
        */
        vec2(const float & valueX, const float & valueY); //^header

        friend std::ostream & operator<<(std::ostream & o, const vec2 & v);
    };
}

#endif