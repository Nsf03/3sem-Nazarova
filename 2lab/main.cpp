#include <iostream>
#include <string>
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

    Rectangle operator*(Rectangle const &rect) const{
        Point new_point = Point(point.minx(rect.point).x, point.miny(rect.point).y);
        return (Rectangle(new_point));
    }

    Rectangle operator+(Rectangle const &rect) const{
        Point new_point = Point(point.maxx(rect.point).x, point.maxy(rect.point).y);
        return (Rectangle(new_point));
    }

    //Деструктор (стандартный)
    ~Rectangle() = default;
};

std::ostream& operator<<(std::ostream& output_place, const Rectangle& rect){
    output_place << '(' << rect.point.x << ' ' << rect.point.y << ')' << std::endl;
}
std::string erase_spaces(std::string string){
    while (string.find(' ', 0) != -1){
        auto pos = string.find(' ', 0);
        string = string.erase(pos, 1);
    }
    return string;
}

Rectangle str_to_rect(std::string string){
    std::string x;
    std::string y;
    auto pos_comma = string.find(',', 0);
    auto len = string.length();
    x.assign(string, 1, pos_comma-1);
    y.assign(string, pos_comma+1, len-pos_comma-2);
    auto x0 = (unsigned long long)stoi(x);
    auto y0 = (unsigned long long)stoi(y);
    Point point = Point(x0, y0);
    Rectangle rect = Rectangle(point);
    return rect;
}

Rectangle mult_func(std::string string){
    auto pos_mult = string.find('*', 0);
    if (pos_mult == -1){return str_to_rect(string);};
    std::string str1;
    std::string str2;
    str1.assign(string, 0, pos_mult);
    str2.assign(string, pos_mult+1);
    return (str_to_rect(str1)* mult_func(str2));
}

Rectangle plus_func (std::string string){
    auto pos_plus = string.find('+', 0);
    if (pos_plus == -1){return mult_func(string);};
    std::string str1;
    std::string str2;
    str1.assign(string, 0, pos_plus);
    str2.assign(string, pos_plus+1);
    return (mult_func(str1)+ plus_func(str2));

}

Rectangle counter(std::string string){
    string = erase_spaces(string);
    return plus_func(string);
}



int main() {

    std::string expression;
    std::getline (std::cin, expression);

    auto r = counter(expression);
    std::cout << r;

    //Ввод выражения в консоль


    std::string test1 = "(15, 0) +(12, 2)*(0,0) + (3, 1)"; //(15, 1)
    std::string test2 = "(0, 0)+ (0,0) +(1, 3)*(2, 2)"; //(1, 2)
    std::string test3 = "   (3   ,4) + (12  , 1)   "; //(12, 4)
    std::cout << counter(test1) << '\n';
    std::cout << counter(test2) << '\n';
    std::cout << counter(test3) << '\n';



    Point p_10_5 = Point(10, 5);
    Point p_3_20 = Point(3, 20);
    Rectangle rect_0_0 = Rectangle();
    Rectangle rect_10_5 = Rectangle(p_10_5);
    Rectangle rect_3_20 = Rectangle(p_3_20);

    /*std::cout << rect_3_20;
    std::cout << (rect_0_0+rect_10_5);
    std::cout << (rect_0_0*rect_3_20);
    std::cout << (rect_3_20+rect_10_5);
    std::cout << (rect_10_5*rect_3_20);
    std::cout << (rect_3_20+rect_3_20);
    std::cout << (rect_3_20*rect_3_20);*/


    return 0;
}
