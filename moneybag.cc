#include "moneybag.h"

using coin_number_t = Moneybag::coin_number_t;

Moneybag::Moneybag(coin_number_t l, coin_number_t s , coin_number_t d) : m_livre(l), m_solidus(s), m_denier(d) {}

Moneybag::Moneybag(const Moneybag & m) : m_livre(m.m_livre), m_solidus(m.m_solidus), m_denier(m.m_denier) {}

coin_number_t Moneybag::livre_number() const {
    return m_livre;
}

coin_number_t Moneybag::solidus_number() const{
    return m_solidus;
}

coin_number_t Moneybag::denier_number() const{
    return m_denier;
}

Moneybag operator+(const Moneybag& lhs, const Moneybag& rhs){
    return {lhs.m_livre + rhs.m_livre, lhs.m_solidus + rhs.m_solidus,  lhs.m_denier + rhs.m_denier};
}

Moneybag operator-(const Moneybag& lhs, const Moneybag& rhs){
    return {lhs.m_livre - rhs.m_livre,  lhs.m_solidus - rhs.m_solidus, lhs.m_denier - rhs.m_denier};
}

Moneybag operator*(const Moneybag& lhs, const coin_number_t scalar){
    return {scalar * lhs.m_livre  , scalar *  lhs.m_solidus, scalar * lhs.m_denier};
}

Moneybag operator*(const coin_number_t scalar, const Moneybag& rhs){
    return rhs * scalar;
}

Moneybag &Moneybag::operator+=(const Moneybag &rhs) {
    m_livre += rhs.m_livre;
    m_solidus += rhs.m_solidus;
    m_denier += rhs.m_denier;
    return *this;
}

Moneybag &Moneybag::operator-=(const Moneybag &rhs) {
    m_livre -= rhs.m_livre;
    m_solidus -= rhs.m_solidus;
    m_denier -= rhs.m_denier;
    return *this;
}

Moneybag &Moneybag::operator*=(coin_number_t t) {
    m_livre *= t;
    m_solidus *= t;
    m_denier *= t;
    return *this;
}

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

Moneybag::operator bool() const {
    return m_livre != 0 || m_solidus != 0 || m_denier != 0;
}

Moneybag &Moneybag::operator=(const Moneybag &rhs) {
    m_livre = rhs.m_livre;
    m_solidus = rhs.m_solidus;
    m_denier = rhs.m_denier;
    return *this;
}

bool Moneybag::operator==(const Moneybag &rhs) const {
    return m_livre == rhs.m_livre && m_solidus == rhs.m_solidus && m_denier == rhs.m_denier ;
}

bool Moneybag::operator<=(const Moneybag & rhs) const {
    if(m_livre <= rhs.m_livre && m_solidus <= rhs.m_solidus && m_denier <= rhs.m_denier)
        return  true;
    else
        return false;
}

bool Moneybag::operator>=(const Moneybag & rhs) const {
    if(m_livre >= rhs.m_livre && m_solidus >= rhs.m_solidus && m_denier >= rhs.m_denier){
        return  true;
    }else{
        return false;
    }
}

std::partial_ordering Moneybag::operator<=>(const Moneybag & rhs) const {
    if(*this <= rhs)
        return std::partial_ordering::less;
    if(*this >= rhs)
        return std::partial_ordering::greater;
    return std::partial_ordering::unordered;
}

Value::Value(Moneybag m) : v(m.livre_number() * 240 +
                             m.solidus_number() * 12 + m.denier_number()){};

Value::Value(Moneybag::coin_number_t n) : v(n) {}

Value::Value() : v(0){}

Value::operator Moneybag::coin_number_t () const {
    return v;
}

Value::operator std::string() const {
    return std::to_string(v);
}

