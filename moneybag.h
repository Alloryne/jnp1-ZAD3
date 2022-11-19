#ifndef MONEYBAG_H
#define MONEYBAG_H
#include <iostream>
#include <cstdint>
#include <cinttypes>
#include <initializer_list>
#include <compare>
#include <string>

// TODO
// Użycie poprawne inline

class Moneybag
{
public:
    typedef uint64_t coin_number_t;
private:
    coin_number_t m_livre;
    coin_number_t m_solidus;
    coin_number_t m_denier;
public:
    // Konstruktory
    constexpr Moneybag( coin_number_t l, 
                        coin_number_t s , 
                        coin_number_t d); 
    constexpr Moneybag(const Moneybag&) = default;
    Moneybag() = delete; 
    // Akcesory
    constexpr coin_number_t livre_number() const;
    constexpr coin_number_t solidus_number() const;
    constexpr coin_number_t denier_number() const;
    // Operacje arytmetyczne z przypisaniem
    Moneybag& operator+=(const Moneybag& rhs);
    Moneybag& operator-=(const Moneybag& rhs);
    Moneybag& operator*=(coin_number_t);
    // Przypisywanie
    constexpr Moneybag& operator=(const Moneybag& rhs) = default;
    // Porównywanie
    std::partial_ordering operator<=>(const Moneybag&) const;
    bool operator==(const Moneybag& rhs) const = default;
    // Rzutowanie na bool
    constexpr explicit operator bool() const;
private:
    coin_number_t m_livre;
    coin_number_t m_solidus;
    coin_number_t m_denier;
};

// Operacje arytmetyczne implementowane za operacji z klasy
Moneybag operator+(const Moneybag& lhs, const Moneybag& rhs) ;
Moneybag operator-(const Moneybag& lhs, const Moneybag& rhs);
Moneybag operator*(coin_number_t scalar, const Moneybag& rhs);
Moneybag operator*(const Moneybag& lhs, coin_number_t scalar);

std::ostream& operator<<(std::ostream&, Moneybag const& );

// Stałe obiekty inicjalizowane podczas kompilacji
consteval Moneybag Livre = Moneybag(1, 0, 0);
consteval Moneybag Solidus = Moneybag(0, 1, 0);
consteval Moneybag Denier = Moneybag(0, 0, 1);

class Value{
public:
    // Konstruktory
    explicit Value(Moneybag);
    explicit Value(__uint128_t);
    explicit Value();

    // Kopiowanie
    constexpr Value &operator=(const Value &) = default;

    // Porównywanie obiektów Value, a także 
    // obiektu Value z liczbą całkowitą nieujemną
    std::strong_ordering operator<=>(Value const &) const = default;
    std::strong_ordering operator<=>(__uint128_t c) const;
    constexpr bool operator==(const __uint128_t c) const;
    // Wypisywanie wartości
    explicit operator std::string () const;

private:
    __uint128_t v;
};

#endif