//
// Created by mailo on 01.03.2022.
//

#include <iostream>
#include <map>

class Polynomial {
private:



    std::map<int, double> linComb_;

public:
    Polynomial();
    explicit Polynomial(double num);
    Polynomial(std::initializer_list<std::pair<int, double>> pairs);
    void Print();
    ~Polynomial();
    Polynomial(const Polynomial& other);

    //
    Polynomial &operator=(const Polynomial &other);

    //
    bool operator==(Polynomial &other);
    bool operator!=(Polynomial &other);

    //
    Polynomial& operator+(Polynomial &other);

    Polynomial& operator-(Polynomial &other);

    Polynomial operator-=(Polynomial &other);

    Polynomial operator+=(Polynomial &other);


    //
    Polynomial& operator*(double num);

    Polynomial& operator/(double num);

    Polynomial operator*=(double num);

    Polynomial operator/=(double num);
    //
    Polynomial& operator-();
    //
    friend std::ostream& operator<<(std::ostream& stream, const Polynomial& value);
    friend std::istream& operator>>(std::istream& stream, Polynomial& value);
    //
    double operator[](int i);

    // + 1
    Polynomial& operator*(Polynomial &other);
    Polynomial operator*=(Polynomial &other);

    // + 1
    Polynomial Derivative();

};

std::istream& operator>>(std::istream& stream, const Polynomial& value);
std::ostream& operator<<(std::ostream& stream, const Polynomial& value);


