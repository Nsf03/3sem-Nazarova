#include <iostream>

template<class T>
struct Comparator{
    virtual bool operator()(T const &, T const &) const = 0;
};


struct IntComparator final: Comparator<int>{
    bool operator()(int const &lha, int const &rha) const override {
        return lha < rha;
    }
};

struct IntNode{
    char name;
    int pr;
    IntNode(char a, int p){name = a; pr = p;}
    IntNode() = default;

};

std::ostream& operator<<(std::ostream& output_place, const IntNode& in){
    output_place << in.name;
    return output_place;
}

struct IntNodeComparator final: Comparator<IntNode>{
    bool operator()(IntNode const &n1, IntNode const &n2) const override{
        return (n1.pr<n2.pr);
    }
};

struct LongComparator final: Comparator<long>{
    bool operator()(long const &lha, long const &rha) const override {
        return lha > rha;
    }
};

template<class T>
unsigned long partition(T data[], unsigned long l, unsigned long r, T mid, Comparator<T> *comp) {
    while (true) {
        while (comp->operator()(data[l],mid)) {
            l = l+1;}
        while (comp->operator()(mid, data[r])) {
            r = r-1;}
        if (r <= l){
            return r;
        }
        std::swap(data[l++], data[r--]);
    }
}



template<class T>
void hoare_sort(T data[], unsigned long l, unsigned long r, Comparator<T> *comp){
    if (l>=r){
        return;
    }
    unsigned long split = partition(data, l, r, data[(l+r)/2], comp);
    hoare_sort(data, l, split, comp);
    hoare_sort(data, split+1, r, comp);
}

int main() {
    IntComparator comp;
    int A[10] = {10, -3, 12, 5, 7, 14, 8, 63, 0, 12};
    hoare_sort(A, 0, 10, &comp);
    for (int i : A) {
        std::cout << i << ' ' << ' ';
    }
    std::cout << std::endl;

    LongComparator comp2;
    long B[4] = {3, 10, 18, 5};;
    hoare_sort(B, 0, 4, &comp2);
    for (long i : B) {
        std::cout << i << ' ' << ' ';
    }
    std::cout << std::endl;

    IntNodeComparator comp3;
    IntNode C[5] = {IntNode('a', 120), IntNode('d', -50), IntNode('C', -10), IntNode('e', -100), IntNode('B', 30)};
    hoare_sort(C, 0, 5, &comp3);
    for (IntNode i : C) {
        std::cout << i << ' ' << ' ';
    }
    std::cout << std::endl;


    return 0;

}
