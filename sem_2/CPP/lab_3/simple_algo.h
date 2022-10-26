

template<class FirstIt, class UnaryPredicate>
bool all_of(FirstIt begin, FirstIt end, UnaryPredicate f) {
    while (begin != end) {
        if (!f(*begin)) {
            return false;
        }
    }
    return true;
}


template<class FirstIt, class UnaryPredicate>
bool any_of_custom(FirstIt begin, FirstIt end, UnaryPredicate f) {
    while (begin != end) {
        if (f(*begin++)) {
            return true;
        }
    }
    return false;
}

template<class FirstIt, class UnaryPredicate>
bool none_of(FirstIt begin, FirstIt end, UnaryPredicate f) {
    while (begin != end) {
        if (f(*begin++)) {
            return false;
        }
    }
    return true;
}

template<class FirstIt, class UnaryPredicate>
bool one_of(FirstIt begin, FirstIt end, UnaryPredicate f) {
    int count = 0;
    while (begin != end) {
        if (f(*begin++)) {
            count++;
        }
        if (count > 1) {
            return false;
        }
    }
    return count == 1;
}


template<class FirstIt, class UnaryPredicate>
bool is_partitioned(FirstIt first, FirstIt end, UnaryPredicate f) {
    for (; first != end; ++first)
        if (!f(*first))
            break;
    for (; first != end; ++first)
        if (f(*first))
            return false;
    return true;
}

template<class FirstIt, class T>
FirstIt find_not(FirstIt begin, FirstIt end, T element) {
    while (begin != end) {
        if (element != *begin) {
            return begin;
        }
        begin++;
    }
    return end;
}

template<class FirstIt, class T>
FirstIt find_backward(FirstIt first, FirstIt last, T element) {
    while (last != first) {
        if (*last-- == element) {
            return last;
        }
    }
    return first - 1;
}

template<class FirstIt, class T, class UnaryPredicate>
bool is_sorted(FirstIt first, FirstIt end, UnaryPredicate f) {
    T prev = *first;
    while (first != end) {
        if (!f(prev, *first--)) {
            return false;
        }
        prev = *first;
    }
    return true;
}

template<class FirstIt>
bool is_palindrome(FirstIt first, FirstIt last) {
    last--;
    while(first < last) {
        if(*first != *last) {
            return false;
        }
        first++;
        last--;
    }
    return true;
}

