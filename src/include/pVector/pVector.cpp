#include "pVector.h"


pVector::pVector() {}

pVector::pVector(float x_, float y_)
{
    this->x = x_;
    this->y = y_;
}

pVector pVector::operator+(const pVector first)
{
    return pVector(this->x + first.x, this->y + first.y);
}

pVector pVector::operator-(const pVector first)
{
    return pVector(this->x - first.x, this->y - first.y);
}

pVector pVector::operator*(const pVector first)
{
    return pVector(this->x * first.x, this->y * first.y);
}

bool pVector::operator!=(const pVector& other)
{
    return *this != other;
}

pVector pVector::operator/(const float divisor)
{
    return pVector(this->x / divisor, this->y / divisor);
}

float pVector::magnitude()
{
    return (std::pow(((this->x * this->x) + (this->y * this->y)),0.5));
}

void pVector::normalise()
{
    float mag = magnitude();
    if (mag != 0) 
    {
        this->x = this->x / mag;
        this->y = this->y / mag;
    }
}

void pVector::setMagnitude(float mag)
{
    this->normalise(); // First normalize the vector
    this->x = this->x * mag; // Then scale it to the new magnitude
    this->y = this->y * mag;
}

void pVector::limit(float max)
{
    if (this->magnitude() > max) 
    {
        this->setMagnitude(max);
    }
}

float pVector::dot(const pVector first)
{
    return (this->x * first.x + this->y * first.y);
}