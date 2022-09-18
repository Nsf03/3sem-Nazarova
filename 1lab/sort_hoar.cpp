#include <iostream>

template<class T>

unsigned long partition(T data[], unsigned long l, unsigned long r, long mid) {
    while (true) {
        while (data[l] < mid) {
            l = l+1;}
        while (data[r] > mid) {
            r = r-1;}
        if (r <= l){
            return r;
        }
        std::swap(data[l++], data[r--]);
    }
}

template<class T>
void hoare_sort(T data[], unsigned long l, unsigned long r){
    if (l>=r){
        return;
    }
    unsigned long split = partition(data, l, r, data[(l+r)/2]);
    hoare_sort(data, l, split);
    hoare_sort(data, split+1, r);
}

int main() {
    long A[10] = {10, -3, 12, 5, 7, 14, 8, 63, 0, 12};
    hoare_sort(A, 0, 10);
    for (int i = 0; i < 10; i++) {
        std::cout << A[i] << std::endl;
    }

    char B[7] = {'z', 'e', 't', 'a', 'g', 'a', 'c'};
    hoare_sort(B, 0, 6);
    for (int i = 0; i < 7; i++) {
        std::cout << (int)B[i] << std::endl;
    }

    return 0;

}

