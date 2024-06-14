#ifndef __pVector__
#define __pVector__

#include <cmath>

class pVector
{
    public:
        float x;
        float y;
        pVector(float x_, float y_);
        pVector operator+(const pVector first);
        pVector operator-(const pVector first);
        bool operator!=(const pVector& first);
        float operator*(const pVector first);
        pVector operator/(const float divisor);
        float magnitude();
        void normalise();
        void setMagnitude(float mag);
        void limit(float max);


    private:

};


#endif // __pVector__