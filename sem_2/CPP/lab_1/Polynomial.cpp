//
// Created by mailo on 01.03.2022.
//

#include "Polynomial.h"
#include <regex>

Polynomial::Polynomial(std::initializer_list<std::pair<int, double>> pairs) {
    for (const std::pair<int, double> &pair: pairs) {
        this->linComb_.insert(pair);
    }
}

Polynomial::Polynomial(double num) {
    this->linComb_.insert(std::make_pair(0, num));
}

Polynomial::Polynomial() = default;

Polynomial::~Polynomial() = default;

Polynomial::Polynomial(const Polynomial &other) : linComb_(other.linComb_) {}

//

Polynomial &Polynomial::operator=(const Polynomial &other) = default;


bool Polynomial::operator==(Polynomial &other) {
    bool flag = true;
    std::map<int, double>::iterator it;
    for (auto &pair: other.linComb_) {
        it = this->linComb_.find(pair.first);
        if (it != this->linComb_.end()) {
        } else {
            flag = false;
        }
    }
    return (this->linComb_.max_size() == other.linComb_.max_size()) && flag;
}

bool Polynomial::operator!=(Polynomial &other) {
    return !Polynomial::operator==(other);
}


Polynomial &Polynomial::operator-() {
    for (auto &pair: this->linComb_) {
        pair.second = -pair.second;
    }
    return *this;
}

Polynomial &Polynomial::operator+(Polynomial &other) {
    std::map<int, double>::iterator it;
    for (auto &pair: other.linComb_) {
        it = this->linComb_.find(pair.first);
        if (it != this->linComb_.end()) {
            it->second += pair.second;
        } else {
            this->linComb_.insert(std::make_pair(pair.first, pair.second));
        }
    }
    return *this;
}

Polynomial &Polynomial::operator-(Polynomial &other) {
    std::map<int, double>::iterator it;
    for (auto &pair: other.linComb_) {
        it = this->linComb_.find(pair.first);
        if (it != this->linComb_.end()) {
            it->second -= pair.second;
        } else {
            this->linComb_.insert(std::make_pair(pair.first, -pair.second));
        }
    }
    return *this;
}


Polynomial Polynomial::operator-=(Polynomial &other) {
    return Polynomial::operator-(other);
}

Polynomial Polynomial::operator+=(Polynomial &other) {
    return Polynomial::operator+(other);
}


//

Polynomial &Polynomial::operator*(double num) {
    for (auto &pair: this->linComb_) {
        pair.second *= num;
    }
    return *this;
}

Polynomial Polynomial::operator*=(double num) {
    return Polynomial::operator*(num);
}

Polynomial &Polynomial::operator/(double num) {
    for (auto &pair: this->linComb_) {
        pair.second = pair.second / num;
    }
    return *this;
}

Polynomial Polynomial::operator/=(double num) {
    return Polynomial::operator/(num);
}


void Polynomial::Print() {
    for (auto &pair: this->linComb_) {
        std::cout << pair.second << "x^" << pair.first << ' ';
    }
    std::cout << std::endl;
}

std::ostream &operator<<(std::ostream &stream, const Polynomial &value) {
    for (auto &pair: value.linComb_) {
        if (pair.second != 0) {
            stream << pair.second;
            if (pair.first != 0) {
                stream << "x^";
                stream << pair.first;
            }
            stream << ' ';
        }
    }
    std::cout << std::endl;
    return stream;
}

std::istream &operator>>(std::istream &stream, Polynomial& value) {
    std::string poly_string;
    stream >> poly_string;
    std::regex poly_parse(R"(\-?[0-9\.]*x\^?[0-9]*|\-?[\d\.]+)");
    std::regex splite(R"([-\d\.]+|^)");
    auto iter = std::sregex_iterator(poly_string.begin(), poly_string.end(), poly_parse);
    auto iter_end = std::sregex_iterator();
    std::string poly_mini;
    for (; iter != iter_end; ++iter) {
        poly_mini = iter->str();
        auto iter_mini = std::sregex_iterator(poly_mini.begin(), poly_mini.end(), splite);
        double p1 = 1;
        int p2 = 0;
        p1 = stoi(iter_mini->str());
        ++iter_mini;
        p2 = stoi(iter_mini->str());
        value.linComb_.insert(std::make_pair(p2, p1));
    }
    return stream;
}

double Polynomial::operator[](int i) {
    if (this->linComb_.max_size() < i) {
        return 0;
    } else {
        int j = 0;
        for (auto &pair: this->linComb_) {
            ++j;
            if (j == i) {
                return pair.second;
            }
        }
    }
    return 0;
}


// +1 ball
Polynomial &Polynomial::operator*(Polynomial &other) {
    std::map<int, double>::iterator it;
    Polynomial out = Polynomial();
    for (auto &pair1: this->linComb_) {
        for (auto &pair2: other.linComb_) {
            std::pair<int, double> into;
            into.first = pair1.first + pair2.first;
            into.second = pair1.second * pair2.second;
            it = out.linComb_.find(into.first);
            if (it != out.linComb_.end()) {
                it->second += into.second;
            } else {
                out.linComb_.insert(into);
            }
        }
    }
    this->linComb_ = out.linComb_;
    return *this;
}

Polynomial Polynomial::operator*=(Polynomial &other) {
    return Polynomial::operator*(other);
}


// +1 ball
Polynomial Polynomial::Derivative() {
    std::map<int, double> out;
    for (auto &pair: this->linComb_) {
        if (pair.first - 1 >= 0) {
            out.insert(std::make_pair(pair.first - 1, pair.first * pair.second));
        }
    }
    this->linComb_ = out;
    return *this;
}



//

