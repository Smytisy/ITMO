//
// Created by mailo on 01.03.2022.
//

#include <iostream>
#include <map>


template<int N>
class Polynomial
{
private:
    int field[N]{};
public:

    constexpr Polynomial(std::initializer_list<int> init_list){
        int count = 0;
        for(auto i: init_list) {
            field[count] = i;
            ++count;
        }
    }

    ~Polynomial() = default;

    constexpr int getPoint(int x) const {
        int sum = 0;
        for(int i = 0; i < N; ++i) {
            sum+=  pow(x, i) * field[i];
        }
        return sum;
    }

    constexpr int pow(int param, int degree) const {
        int result = 1;
        for(int i = 0; i < degree; ++i) {
            result *= param;
        }
        return result;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Polynomial& value){
        for (int i = 0; i < N; ++i) {
            stream << value.field[i] << "x^" << i << ' ';
        }
        return stream;
    };

};



