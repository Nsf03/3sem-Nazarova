#include <iostream>
struct Point{
    unsigned long long const x, y;

    Point(unsigned long long x, unsigned long long y):
            x(x), y(y) {}

    Point minx(Point const &rha) const {
        return Point(rha.x < x ? rha.x : x, y);
    }

    Point miny(Point const &rha) const {
        return Point(x, rha.y < y ? rha.y : y);
    }

    Point maxx(Point const &rha) const {
        return Point(rha.x > x ? rha.x : x, y);
    }

    Point maxy(Point const &rha) const {
        return Point(x, rha.y > y ? rha.y : y);
    }

    void print() const {
        std::cout << '(' << x << ',' << y << ')' ;
    }
};

struct Rectangle{
    Point point;

     //Конструктор нулевого прямоугольника
     Rectangle():
        point(0,0){}
     //Конструктор заданного прямоугольника

     Rectangle(Point const &point):
        point(point){}

     //К-р копирования
     Rectangle(const Rectangle &ref_rect):
        point(ref_rect.point){}

    Rectangle operator+(Rectangle const &rect) const{
         Point new_point = Point(point.minx(rect.point).x, point.miny(rect.point).y);
         return (Rectangle(new_point));
     }

    Rectangle operator*(Rectangle const &rect) const{
        Point new_point = Point(point.maxx(rect.point).x, point.maxy(rect.point).y);
        return (Rectangle(new_point));
    }

    void print() const{
         std::cout << '(' << point.x << ' ' << point.y << ')' << std::endl;
     }

    //Деструктор (стандартный)
    ~Rectangle() = default;
};

int main() {
    Point p_10_5 = Point(10, 5);
    Point p_3_20 = Point(3, 20);
    Rectangle rect_0_0 = Rectangle();
    Rectangle rect_10_5 = Rectangle(p_10_5);
    Rectangle rect_3_20 = Rectangle(p_3_20);

    (rect_0_0+rect_10_5).print();
    (rect_0_0*rect_3_20).print();
    (rect_3_20+rect_10_5).print();
    (rect_10_5*rect_3_20).print();
    (rect_3_20+rect_3_20).print();
    (rect_3_20*rect_3_20).print();


    return 0;
}
