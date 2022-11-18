#ifndef MONEYBAG_H
#define MONEYBAG_H
#include <iostream>
#include <cstdint>
#include <cinttypes>
#include <initializer_list>
#include <compare>
#include <string>

//TODO: mb there's a better way to do that?
#define Solidus Moneybag(0, 1, 0)
#define Denier Moneybag(0, 0, 1)
#define Livre Moneybag(1, 0, 0)

class Moneybag
{
public:
    typedef uint64_t coin_number_t;

    Moneybag(coin_number_t l, coin_number_t , coin_number_t );
    Moneybag(const Moneybag&);
    //delete default init?

    coin_number_t livre_number() const;
    coin_number_t solidus_number() const;
    coin_number_t denier_number() const;
    friend Moneybag operator+(const Moneybag& lhs, const Moneybag& rhs) ;
    Moneybag& operator+=(const Moneybag& rhs);
    friend Moneybag operator-(const Moneybag& lhs, const Moneybag& rhs);
    Moneybag& operator-=(const Moneybag& rhs);
    friend Moneybag operator*(coin_number_t scalar, const Moneybag& rhs);
    friend Moneybag operator*(const Moneybag& lhs, coin_number_t scalar);
    Moneybag& operator*=(coin_number_t);
    explicit operator bool() const;
    Moneybag& operator=(const Moneybag& rhs);
    std::partial_ordering operator<=>(const Moneybag&) const;//idk how to properly implement that
    bool operator<=(const Moneybag&) const;
    bool operator>=(const Moneybag&) const;
    bool operator==(const Moneybag& rhs) const;
private:
    coin_number_t m_livre;
    coin_number_t m_solidus;
    coin_number_t m_denier;
};

std::ostream& operator<<(std::ostream&, Moneybag const& );

struct Value{
public:
    //TODO: need to find a way to store (2^64-1) * 253 as a value
    typedef __int128 uint128_t; // hard to use
    explicit Value(Moneybag);
    explicit Value(Moneybag::coin_number_t);
    explicit Value();

    operator Moneybag::coin_number_t () const;
    explicit operator std::string () const;

private:
    uint64_t v;
};

#endif