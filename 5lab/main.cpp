#include <iostream>
#include <cassert>
#include <string>

template<typename T ,bool... dems> struct Grid;

template<typename T, bool dem>
struct Grid<T, dem>{
    using size_type = unsigned;
    T * data;
    unsigned size;
/*РАЗМЕР БУДЕТ ПОДАВАТЬСЯ В <>*/

    //Принимет массив готовый
    Grid(T *data, size_type size) :
            data(data), size(size) {}

    Grid() :
            data(new T), size(1) {}

    Grid(T const &t):
            data(new T(t)), size(1) {}

    Grid(size_type size):
            data(new T[size]), size(size){}

    Grid(size_type size, T const &t):
            size(size), data(new T[size])
    {
        for (int i = 0; i < size; ++i) {
            data[i] = t;
        }}

    ~Grid(){delete[] data;}

    Grid(const Grid<T>& other): data(new T[other.size]), size(other.size)
    {
        for (int i = 0; i < other.size; ++i) {
            data[i] = other.data[i];
        }
    } //конструктор копирования

    Grid &operator=( Grid<T>& other){

        Grid<T> bag(other);
        std::swap(this->size, other.size);
        std::swap(this->data, other.data);
        return *this;

    } //копирование присваивание ПОСМОТРИ В ЛЕКЦИИ

    Grid(Grid<T> &&other): size(other.size), data(other.data){
        delete[] other.data;
    }//конструктор перемещения завладевает


    Grid &operator=(Grid<T>&& other){
        Grid<T> bag(std::move(other));
        std::swap(this->size, other.size);
        std::swap(this->data, other.data);
        return *this;

    } //перемещение присваивание Л

    //.............ПРАВИЛО ПЯТИ ВЫШЕ.........

    T operator()(size_type id) const {
        return data[id];
    }



    Grid<T> &operator=(T const &t) {
        for (
                auto it = data, end = data + size;
                it != end; ++it
                )
            *it = t;
        return *this;
    }

    size_type get_size() const { return size; }

    T& operator[](size_type id){
        return data[id];
    }
};

template<typename T , bool dem, bool... dems>
struct Grid<T, dem, dems...>{
    using size_type = unsigned;
    Grid<T, dems...>* data;

    Grid():
            data(new Grid<T, dems...>){}

    Grid(Grid<T, dems...>* data):
            data(data){}


    Grid<T, dems...>& operator[](size_type id){
        return data[id];
    }

    ~Grid(){delete data;}

};

int main() {

    auto d2 = new int[2];
    d2[0] = 20;
    d2[1] = 21;

    auto g1 = Grid<int, true>(1); // 1
    std::cout << "g1: " <<g1[0] << '\n';
    auto g2 = Grid<char, true>(2, 'A');
    std::cout << "g2: "  << g2[0] << '\n'; //A
    auto g3 = g2;
    std::cout <<  "g3: " <<g3[0] << '\n';
    auto g4 = Grid<int, true>(d2, 2); //20 21
    std::cout <<  "g4: " <<g4[0] << ' '<< g4[1] << '\n';

    auto D1 = new Grid<int, true>[2];
    D1[0] = g1; // 1
    D1[1] = g4; // 20 21

    auto G1 = Grid<int, true, true>(D1);
    std::cout << "D1: " << G1[0][0] << ' ' <<G1[1][0] <<  ' ' <<G1[1][1];


    auto t1 =  Grid<int, true>(3, 1);
    auto t2 =  Grid<int, true>(3, 2);
    auto t3 =  Grid<int, true>(3, 3);
    auto t4 =  Grid<int, true>(3, 4);
    auto t5 =  Grid<int, true>(3, 5);
    auto t6 =  Grid<int, true>(3, 6);
    auto t7 =  Grid<int, true>(3, 7);
    auto t8 =  Grid<int, true>(3, 8);
    auto t9 =  Grid<int, true>(3, 9);

    auto T1 = new Grid<int, true>[3];
    auto T2 = new Grid<int, true>[3];
    auto T3 = new Grid<int, true>[3];

    T1[0] = t1; T1[1] = t2; T1[2] = t3;
    T2[0] = t4; T2[1] = t5; T2[2] = t9;
    T3[0] = t7; T3[1] = t8; T3[2] = t9;

    auto G2D1 = Grid<int, true, true>(T1);
    auto G2D2 = Grid<int, true, true>(T2);
    auto G2D3 = Grid<int, true, true>(T3);

    auto TT = new Grid<int, true, true>[3];
    TT[0] = G2D1;
    TT[1] = G2D2;
    TT[2] = G2D3;

    auto G3D = Grid<int, true, true, true>(TT);

    std::cout <<  '\n' << "----3DEM-----" << '\n';

    for (int i = 0; i < 3; ++i) {
        std::cout << '\n';
        for (int j = 0; j < 3; ++j) {
            std::cout << '\n';
            for (int k = 0; k < 3; ++k) {
                std::cout << G3D[i][j][k] << ' ';
            }
        }

    };

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                G3D[i][j][k] = 0;
            }}};

    std::cout <<  '\n' << "___________" <<  '\n';

    for (int i = 0; i < 3; ++i) {
        std::cout << '\n';
        for (int j = 0; j < 3; ++j) {
            std::cout << '\n';
            for (int k = 0; k < 3; ++k) {
                std::cout << G3D[i][j][k] << ' ';
            }
        }

    };


    return 0;
}

//МОЖНО АЗМЕНИТЬ БУЛЕВЫ С ПОМОЩЬЮ make_index_sequens???