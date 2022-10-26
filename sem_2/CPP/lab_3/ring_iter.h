//#include "ring_buffer.h"

template<typename T>
class ring_iter : public std::iterator<std::random_access_iterator_tag, T> {

private:
    T *_value;
    T *_end;
    T *_start;
    //size_t _size{};
    size_t _capacity{};

public:
    using difference_type = typename std::iterator<std::random_access_iterator_tag, T>::difference_type;

    difference_type operator-(const ring_iter &obj) const {
        return _value - obj._value;
    }

    ring_iter(T *start, T *value, T *end, size_t capacity): _start(start), _value(value), _end(end), _capacity(capacity) {}

    ring_iter(const ring_iter &obj) = default;

    bool operator==(const ring_iter &it) const {
        return _value == it._value;
    }

    bool operator!=(const ring_iter &it) const {
        return _value != it._value;
    }

    typename ring_iter::reference operator*() {
        return *_value;
    }

    ~ring_iter() = default;

    T *operator->() {
        return _value;
    }

    ring_iter& operator+=(size_t i) {
        _value = _start + (_value - _start + i) % _capacity;
        return *this;
    }

    ring_iter& operator-=(size_t i) {
        //_value = _start + (_value - _start - i + _capacity) % _capacity;
        int end = (_end - _start);
        _value = _start + (_value - _start - i + end) % end;
        return *this;
    }


    ring_iter& operator++() {
        if (_value == _end) {
            _value = _end;
        } else {
            _value = _value + 1;
        }

        //_value = _start + (_value - _start + 1 + _capacity) % _capacity;
        return *this;
    }

    ring_iter operator++(int) {
        ring_iter<T> temp(_start, _value, _end,  _capacity);
        temp += 1;
        return temp;
    }

    ring_iter& operator--() {

        if (_value - _start <= 0) {
            _value = _start;
        } else {
            _value = _value - 1;
        }


        return *this;
    }

    ring_iter operator--(int) {
        ring_iter<T> temp(_start, _value,_end, _capacity);
        temp -= 1;
        return temp;
    }


    ring_iter operator+(int i) {
        //_value = _start + (_value - _start + i + _capacity) % _capacity;
        //_value = _value + i;
        ring_iter<T> temp(_start, _value + i, _end, _capacity);
        return temp;
    }

    ring_iter operator-(int i) {
        //_value = _start + (_value - _start - i + _capacity) % _capacity;
//        _value = _value - i;
//        return *this;
        ring_iter<T> temp(_start, _value - i, _end, _capacity);
        return temp;

    }


    T &operator[](size_t i) {
        return *(*this + i);
    }


    bool operator<(const ring_iter &it) const {
        return _value < it._value;
    }

//    bool operator<=(const ring_iter &it) const {
//        return _value <= it._value;
//    }
//
//    bool operator>(const ring_iter &it) const {
//        return _value > it._value;
//    }
//
//    bool operator>=(const ring_iter &it) const {
//        return _value >= it._value;
//    }


    typedef std::random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
};






