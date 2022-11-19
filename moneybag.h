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
                        coin_number_t s,
                        coin_number_t d)
            : m_livre(l), m_solidus(s), m_denier(d) {};
    constexpr Moneybag(const Moneybag&) = default;
    Moneybag() = delete;

    // Akcesory
    constexpr coin_number_t livre_number() const{
        return m_livre;
    }
    constexpr coin_number_t solidus_number() const{
        return m_solidus;
    }
    constexpr coin_number_t denier_number() const{
        return m_denier;
    }
    // Operacje arytmetyczne z przypisaniem
    Moneybag& operator+=(const Moneybag& rhs){
        if (m_livre + rhs.m_livre < m_livre ||
            m_solidus + rhs.m_solidus < m_solidus ||
            m_denier + rhs.m_denier < m_denier) {
            throw std::out_of_range("Wynik z poza zakresu");
        }
        m_livre += rhs.m_livre;
        m_solidus += rhs.m_solidus;
        m_denier += rhs.m_denier;
        return *this;
    }
    Moneybag& operator-=(const Moneybag& rhs){
        if (m_livre - rhs.m_livre > m_livre ||
            m_solidus - rhs.m_solidus > m_solidus ||
            m_denier - rhs.m_denier > m_denier) {
            throw std::out_of_range("Wynik z poza zakresu");
        }
        m_livre -= rhs.m_livre;
        m_solidus -= rhs.m_solidus;
        m_denier -= rhs.m_denier;
        return *this;
    }
    Moneybag& operator*=(coin_number_t t){
        if ((m_livre * t) / t != m_livre ||
            (m_solidus * t) / t != m_solidus ||
            (m_denier * t) / t != m_denier) {
            throw std::out_of_range("Wynik z poza zakresu");
        }
        m_livre *= t;
        m_solidus *= t;
        m_denier *= t;
        return *this;
    }
    // Przypisywanie
    constexpr Moneybag& operator=(const Moneybag& rhs) = default;
    // Porównywanie
    std::partial_ordering operator<=>(const Moneybag& rhs) const{
        if (m_livre == rhs.m_livre &&
            m_solidus == rhs.m_solidus &&
            m_denier == rhs.m_denier) {
            return std::partial_ordering::equivalent;
        }
        if (m_livre <= rhs.m_livre &&
            m_solidus <= rhs.m_solidus &&
            m_denier <= rhs.m_denier) {
            return std::partial_ordering::less;
        }
        if (m_livre >= rhs.m_livre &&
            m_solidus >= rhs.m_solidus &&
            m_denier >= rhs.m_denier) {
            return std::partial_ordering::greater;
        }
        return std::partial_ordering::unordered;
    }
    bool operator==(const Moneybag& rhs) const = default;

    // Rzutowanie na bool
     explicit operator bool() const{
        return m_livre != 0 || m_solidus != 0 || m_denier != 0;
     }
};

// Operacje arytmetyczne implementowane za operacji z klasy
Moneybag operator+(const Moneybag& lhs, const Moneybag& rhs) {
    return Moneybag(lhs) += rhs;
}
Moneybag operator-(const Moneybag& lhs, const Moneybag& rhs){
    return Moneybag(lhs) -= rhs;
}
Moneybag operator*(const Moneybag::coin_number_t scalar, const Moneybag& rhs){
    return Moneybag(rhs) *= scalar;
}
Moneybag operator*(const Moneybag& lhs, const Moneybag::coin_number_t scalar){
    return Moneybag(lhs) *= scalar;
}

std::ostream& operator<<(std::ostream& os, Moneybag const& m){
    os << "("
       << m.livre_number()
       <<(m.livre_number() == 1 ? " livr, " : " livres, ")
       << m.solidus_number()
       <<(m.solidus_number() == 1 ? " solidus, " : " soliduses, ")
       << m.denier_number()
       <<(m.denier_number() == 1 ? " denier" : " deniers")
       << ")";
    return os;
}

// Stałe obiekty inicjalizowane podczas kompilacji
constinit const Moneybag Livre = Moneybag(1, 0, 0);
constinit const Moneybag Solidus = Moneybag(0, 1, 0);
constinit const Moneybag Denier = Moneybag(0, 0, 1);

class Value{
public:
    // Konstruktory
    explicit Value(Moneybag m)
            : v(m.livre_number() * 240 + m.solidus_number() * 12 + m.denier_number()){}
    explicit Value(__uint128_t n) : v(n) {}
    explicit Value() : v(0){}




    // Kopiowanie
    Value &operator=(const Value &) = default;

    // Wypisywanie wartości
    explicit operator std::string () const{
        __uint128_t temp = v;

        std::string str;
        do {
            uint8_t digit = temp % 10;
            str = std::to_string(digit) + str;
            temp = (temp - digit) / 10;
        } while (temp != 0);
        return str;
    }
    // Rzut na int
    operator __uint128_t () const{
        return v;
    }


private:
    __uint128_t v;
};

#endif