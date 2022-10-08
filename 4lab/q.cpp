#include <iostream>
using std::cout;

int parent(int i)
{return (i - 1) / 2;}
int leftChild(int i)
{return ((2 * i) + 1);}
int rightChild(int i)
{return ((2 * i) + 2);}



template<class T>
struct Comparator{
    virtual bool operator()(T const &, T const &) const = 0;
};

template<typename T>
struct Queue {
    const int MaxSize = 100;
    T *first;
    int NowSize;
    Comparator<T> *comp;

    Queue(Comparator<T> *comp): comp(comp) {
        first = new T[MaxSize];
        NowSize = -1;
    }

    void ShiftUp(int i)
    {
        while (i > 0 && comp->operator()(first[parent(i)], first[i])) {
            std::swap(first[parent(i)], first[i]);
            i = parent(i);
        }
    }

    void shiftDown(int i)
    {
        int maxIndex = i;
        int l = leftChild(i);
        if (l <= NowSize && comp->operator()(first[maxIndex], first[l])) {
            maxIndex = l;
        }


        int r = rightChild(i);
        if (r <= NowSize && comp->operator()(first[maxIndex], first[r])) {
            maxIndex = r;
        }

        if (i != maxIndex) {
            std::swap(first[i], first[maxIndex]);
            shiftDown(maxIndex);
        }
    }


    bool is_empty(){
        if (NowSize == 0){return true;}};
    void push(T new_one){
        if (NowSize == MaxSize-1){
            return;
        };
            NowSize = NowSize + 1;
            first[NowSize] = new_one;

            ShiftUp(NowSize);
    }; //добавить новый
    T peek(){
        return first[0];
    }; //чтение верхнего
    void poll(){
        first[0] = first[NowSize];
        NowSize = NowSize - 1;
        shiftDown(0);
    }; //удаление верхнего

    void free(){
        delete[] first;
    }
};

struct IntNode{
    char name;
    int pr;
    IntNode(char a, int n){name = a; pr = n;}
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

struct IntComparator final: Comparator<int>{
    bool operator()(int const &lha, int const &rha) const override {
        return lha < rha;
    }
};

int main() {
    IntComparator comp1;
    Queue<int> q1(&comp1);
    q1.push(-100);
    q1.push(200);
    q1.push(-50);
    q1.push(10);
    q1.push(1000);

    cout << q1.peek() << '\n';
    q1.poll();
    cout << q1.peek() << '\n';
    q1.poll();
    cout << q1.peek() << '\n';
    q1.poll();
    cout << q1.peek() << '\n';
    q1.poll();


    q1.free();

    cout << 'A' << 'A' << 'A' << 'A' << '\n';

    IntNodeComparator comp2;
    Queue<IntNode> q2(&comp2);
    q2.push(IntNode('e', -100));
    q2.push(IntNode('a', 200));
    q2.push(IntNode('d', -50));
    q2.push(IntNode('b', 10));
    q2.push(IntNode('c', 0));

    cout << q2.peek() << '\n';
    q2.poll();
    cout << q2.peek() << '\n';
    q2.poll();
    cout << q2.peek() << '\n';
    q2.poll();


    q2.free();





    return 0;

}


