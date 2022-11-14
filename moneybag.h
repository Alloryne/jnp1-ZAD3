#ifndef MONEYBAG_H
#define MONEYBAG_H
#include <iostream>
#include <cstdint>
#include <cinttypes>
#include <initializer_list>

class Moneybag
{
public:
    typedef uint64_t coin_number_t;
    Moneybag(initializer_list<coin_number_t>);
    coin_number_t livre_number();
    coin_number_t solidus_number();
    coin_number_t denier_number();
    Moneybag& operator+=(const Moneybag& rhs);
    friend Moneybag operator+(Moneybag lhs, const Moneybag& rhs);
    Moneybag& operator-=(const Moneybag& rhs);
    friend Moneybag operator-(Moneybag lhs, const Moneybag& rhs);
    Moneybag& operator*=(const coin_number_t scalar);
    friend Moneybag operator*(const coin_number_t scalar, Moneybag rhs);
    friend Moneybag operator*(Moneybag lhs, const coin_number_t scalar);
private:
    coin_number_t m_livre;
    coin_number_t m_solidus;
    coin_number_t m_denier;
};


#endif