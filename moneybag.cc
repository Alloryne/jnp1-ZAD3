#include "moneybag.h"

using coin_number_t = Moneybag::coin_number_t;

// Konstruktory
constexpr Moneybag::Moneybag(   coin_number_t l, 
                                coin_number_t s , 
                                coin_number_t d)
    : m_livre(l), m_solidus(s), m_denier(d) {} 

// Akcesory
constexpr coin_number_t Moneybag::livre_number() const {
    return m_livre;
}

constexpr coin_number_t Moneybag::solidus_number() const {
    return m_solidus;
}

constexpr coin_number_t Moneybag::denier_number() const {
    return m_denier;
}

// Operacje arytmetyczne
Moneybag &Moneybag::operator+=(const Moneybag &rhs) {
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

Moneybag &Moneybag::operator-=(const Moneybag &rhs) {
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

Moneybag &Moneybag::operator*=(coin_number_t t) {
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

// Operacje arytmetyczne zaimplementowane za pomocą powyższych
Moneybag operator+(const Moneybag& lhs, const Moneybag& rhs) {
    return Moneybag(lhs) += rhs;
}

Moneybag operator-(const Moneybag& lhs, const Moneybag& rhs) {
    return Moneybag(lhs) -= rhs;
}

Moneybag operator*(const Moneybag& lhs, const coin_number_t scalar) {
    return Moneybag(lhs) *= scalar;
}

Moneybag operator*(const coin_number_t scalar, const Moneybag& rhs) {
    return Moneybag(rhs) *= scalar;
}

// Wypisywanie
std::ostream &operator<<(std::ostream & os, const Moneybag & m) {
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



// Porównywanie
std::partial_ordering Moneybag::operator<=>(const Moneybag & rhs) const {
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

// Rzutowanie na bool
constexpr Moneybag::operator bool() const {
    return m_livre != 0 || m_solidus != 0 || m_denier != 0;
}

// Klasa Value
// Konstruktory
Value::Value(Moneybag m) 
    : v(m.livre_number() * 240 + m.solidus_number() * 12 + m.denier_number()) 
    {};

Value::Value(__uint128_t n) : v(n) {}

Value::Value() : v(0){}

// Porównywanie obiektu Value z liczbą całkowitą nieujemną
std::strong_ordering Value::operator<=>(__uint128_t c) const {
    return this->v <=> c;
    
};
constexpr bool Value::operator==(const __uint128_t c) const {
    return (this->v == c);
};

Value::operator std::string() const {
    __uint128_t temp = v;

    std::string str;
    do {
        uint8_t digit = temp % 10;
        str = std::to_string(digit) + str;
        temp = (temp - digit) / 10;
    } while (temp != 0);
    return str;
}

