#include <iostream>
#include <vector>
#include "ring_buffer.h"
#include <algorithm>
#include "simple_algo.h"

bool comp(int a, int b) {
    return a < b;
}

bool comp_of(int a) {
    return a > 4;
}

void print(ring_buf<int> &a) {
    for (auto elem: a) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
}



int main() {
    ring_buf<int> a(5);

    a = {5, 9, 7, 3, 2};
    print(a);
    //a.resize(9);
    //print(a);

    a.push_front(77);
    print(a);

    a.push_back(33);
    print(a);


    std::sort(a.begin(), a.end());
    print(a);


    std::vector<int> d;
    d = {1, 2, 3, 5, 3, 2, 1};
    std::cout << (is_palindrome(d.begin(), d.end()) ? "YES" : "NO") << std::endl;
    std::cout << *find_backward(d.begin(), d.end(), 3) << std::endl;
    std::cout << *find_not(d.begin(), d.end(), 1) << std::endl;
    std::cout << (any_of_custom(d.begin(), d.end(), comp_of) ? "YES" : "NO") << std::endl;



//    a.push_back(-1);
//    print(a);
//    a.push_back(-1);
//    print(a);
//
//    a.push_front(-9);
//    print(a);
//    a.push_front(-3);
//    print(a);
//
//    a.resize(a.capacity() + 2);
//    a.push_front(-9);
//    print(a);
//    a.push_front(-3);
//    print(a);
//
//    std::sort(a.begin(), a.end());
//    print(a);
//
//    std::reverse(a.begin(), a.end());
//    print(a);
//
//    a.pop_back();
//    print(a);
//
//    a.pop_front();
//    print(a);
//
//    a.push_front(90);

    //std::cout << ((a.begin() - 1) == a.end() ? "YES" : "NO") << std::endl;

//    for(int i = 0; i < a.capacity() + 20; ++i) {
//        std::cout << i - 10 << ':' << ' ' << *(a.begin() - 10 + i ) << std::endl;
//    }



//    std::vector<int> d(5);
//    d = {2, 4, 5, 6, 3};
//    std::cout << ((d.begin() - 1) == d.end() ? "YES" : "NO") << std::endl;
//    std::cout << *d.begin() << std::endl;
//    std::cout << *(d.begin() - 1) << std::endl;
//    std::cout << *d.end() << std::endl;
//    std::sort(d.begin() - 1, d.end() + 1);
//    for (auto i: d) {
//        std::cout << i << ' ';
//    }
//    d.begin()--;
//    std::cout << std::endl;



//    ring_buf<int> buf_1(5), buf_2(5);
//    buf_1 = {1, 1, 1, 1, 1};
//    buf_2 = {2, 2, 2, 2, 2};
//    ring_buf<int> *p1 = &buf_1;
//    ring_buf<int> *p2 = &buf_2;
//    std::iter_swap(p1, p2);
//    print(buf_1);


//    a.push_back(22);
//    print(a);
//    a.push_back(11);
//    print(a);
//    a.push_back(111);
//    print(a);
//
//    a.push_front(124);
//    print(a);
//    a.pop_front();
//    print(a);
//    a.pop_back();
//    print(a);




//    std::sort(a.begin(), a.end());
//    print(a);

//    std::vector<int> vec = {2, 4, 5, 1, 0};
//    std:: cout << vec.end() - vec.begin() << std::endl;
//    vec.resize(10);
//    std:: cout << vec.end() - vec.begin() << std::endl;

    return 0;
}
