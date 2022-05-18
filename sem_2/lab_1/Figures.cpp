//
// Created by mailo on 10.03.2022.
//

#include <iostream>
#include <vector>
#include <math.h>
#include "Polynomial.h"

class Point {

public:
    explicit Point(double x = 0, double y = 0)
            : x_(x), y_(y) {
        //std::cout << "ctor() Point" << std::endl;
    }

    Point(const Point &other)
            : x_(other.x_), y_(other.y_) {
        //std::cout << "copy ctor" << std::endl;
    }

    Point &operator=(const Point &other) {
        x_ = other.x_;
        y_ = other.y_;
        return *this;
    }

    double Get_x() const {
        return x_;
    }

    double Get_y() const {
        return y_;
    }

    Point Turn(int N, int count, Point &centre) const {
        Point tmp;
        //Point abstractPoint(points_[0].Get_x() - centre.Get_x(), points_[0].Get_y() - centre.Get_y());
        tmp.x_ = (x_ - centre.Get_x()) * cos(M_PI * 2 / N * count) - (y_ - centre.Get_y()) * sin(M_PI * 2 / N * count);
        tmp.y_ = (x_ - centre.Get_x()) * sin(M_PI * 2 / N * count) + (y_ - centre.Get_y()) * cos(M_PI * 2 / N * count);

        tmp.x_ += centre.Get_x();
        tmp.y_ += centre.Get_y();

        return tmp;
    }

    double Determinate(Point &other) const {
        return (x_ * other.Get_y() - y_ * other.Get_x());
    }

    bool isParallel(Point &other) const {
        return this->x_ / other.Get_x() == this->y_ / other.y_;
    }

private:
    double x_;
    double y_;
};

class BrokenLine {
public:
    explicit BrokenLine() {
        N_ = 0;
    }

    static bool checkParallel(Point &a1, Point &a2, Point &b1, Point &b2) {
        Point v1 = Point(a1.Get_x() - a2.Get_x(), a1.Get_y() - a2.Get_y());
        Point v2 = Point(b1.Get_x() - b2.Get_x(), b1.Get_y() - b2.Get_y());
        return v1.isParallel(v2);
    }

    static bool isLine(Point &t1, Point &t2, Point &t3) {
        return (t1.Get_x() - t2.Get_x()) / (t3.Get_x() - t2.Get_x()) ==
               (t1.Get_y() - t2.Get_y()) / (t3.Get_y() - t2.Get_y());
    }

    // ctor
    BrokenLine(std::initializer_list<Point> points) {
        N_ = 0;
        for (const Point &point: points) {
            points_.push_back(point);
            ++N_;
        }
    }

    // ctor copy
    BrokenLine(const BrokenLine &other)
            : points_(other.points_), N_(other.N_) {
    }

    // operator =
    BrokenLine &operator=(const BrokenLine &other) = default;

    static double SegmentLength(const Point &t1, const Point &t2) {
        return sqrt(pow(t1.Get_x() - t2.Get_x(), 2) + pow(t1.Get_y() - t2.Get_y(), 2));
    }

    double Perimeter() {
        double P = 0;
        for (int i = 0; i < points_.size() - 1; ++i) {
            P += SegmentLength(points_[i], points_[i + 1]);
        }
        P += SegmentLength(points_[0], points_[points_.size() - 1]);
        return P;
    }

    void Print() {
        for (Point &point: points_) {
            std::cout << point.Get_x() << ' ' << point.Get_y() << std::endl;
        }
    }

protected:
    std::vector<Point> points_;
    int N_;
};

class ClosedBL : public BrokenLine {
public:

    explicit ClosedBL() {
        N_ = 0;
    }

    ClosedBL(std::initializer_list<Point> points) {
        N_ = 0;
        for (const Point &point: points) {
            points_.push_back(point);
            ++N_;
        }
    }

    // ctor copy
    ClosedBL(const ClosedBL &other) : BrokenLine(other) {}

    ClosedBL &operator=(const ClosedBL &other) {
        points_ = other.points_;
        N_ = other.N_;
        std::cout << "ctor copy" << std::endl;
        return *this;
    }

    void Push(double x, double y) {
        points_.emplace_back(x, y);
        ++N_;
    }
};


class Polygon : public ClosedBL {
public:
    explicit Polygon() {
        N_ = 0;
    }

    // ctor
    Polygon(std::initializer_list<Point> points) {
        N_ = 0;
        if (points.size() < 3) {
            std::cerr << "Wrong number of points!" << std::endl;
        }
        for (const Point &point: points) {
            points_.push_back(point);
            ++N_;
        }
        if(!this->checkPolygon(Polygon())) {
            std::cerr << "Wrong points!" << std::endl;
        }
    }

    // + 1 ball
    bool checkPolygon(Polygon polygon) {
        Point vector1 = Point(points_[1].Get_x() - points_[0].Get_x(), points_[1].Get_y() - points_[0].Get_y());
        Point vector2;
        Point vector_tmp = Point(points_[0].Get_x() - points_[points_.size() - 1].Get_x(), points_[0].Get_y() - points_[points_.size() - 1].Get_y());
        bool flag;
        if (vector1.Determinate(vector_tmp) < 0) {
            flag = true;
        } else {
            flag = false;
        }
        for (int i = 2; i < points_.size(); ++i) {
            vector2 = Point(points_[i].Get_x() - points_[i - 1].Get_x(), points_[i].Get_y() - points_[i - 1].Get_y());
            if (vector1.Determinate(vector2) < 0 == flag) {
                return false;
            }
            vector1 = vector2;
        }
        return true;
    }


    Polygon(const Polygon &other) : ClosedBL(other) {}

    Polygon &operator=(const Polygon &other) {
        points_ = other.points_;
        N_ = other.N_;
        return *this;
    }

    double Area() {
        double sum = 0;
        for (int i = 0; i < points_.size() - 1; i++) {
            sum += points_[i].Determinate(points_[i + 1]);
        }
        sum += points_[points_.size() - 1].Determinate(points_[0]);
        return abs(sum / 2);
    }

};

class Triangle : public Polygon {
public:
    Triangle(std::initializer_list<Point> points) {
        N_ = 3;
        for (const Point &point: points) {
            points_.push_back(point);
            --N_;
        }
        if (N_ != 0) {
            std::cerr << "Wrong number of points!" << std::endl;
        } else {
            N_ = 3;
        }
        if (isLine(points_[0], points_[1], points_[2])) {
            std::cerr << "It's Line!" << std::endl;
        }
    }

    Triangle(const Triangle &other)
            : Polygon(other) {}

    Triangle &operator=(const Triangle &other) {
        points_ = other.points_;
        return *this;
    }

};


// + 1 ball
class Trapezoid : public Polygon {

public:
    explicit Trapezoid(Point& A, Point& D, Point& O, double k) {
        if(checkPolygon(Polygon({A, D, O})) && k > 0 && k < 1) {
            std::cerr << "Wrong Points or k!";
        }
        Point B = Point((1 + k) * O.Get_x() - k * D.Get_x(), (1 + k) * O.Get_y() - k * D.Get_y());
        Point C = Point((1 + k) * O.Get_x() - k * A.Get_x(), (1 + k) * O.Get_y() - k * A.Get_y());

        points_.push_back(A);
        points_.push_back(B);
        points_.push_back(C);
        points_.push_back(D);

    }

    Trapezoid(const Trapezoid &other)
            : Polygon(other) {}
};


// + 1 ball

class RegPolygon : public Polygon {
public:

    RegPolygon(int N, std::initializer_list<Point> points) { // size(points) == 2 first = point second = centre
        if (points.size() != 2) {
            std::cerr << "Wrong number of points!" << std::endl;
        }

        for (const Point &point: points) {
            points_.push_back(point);
        }

        center_ = points_[1];
        points_.pop_back();


        for (int i = 1; i < N; i++) {
            points_.push_back(points_[0].Turn(N, i, center_));
        }
    }

    RegPolygon(const RegPolygon &other) : Polygon(other) {}

private:
    Point center_;
};