#include <iostream>

template<typename T>
struct Node{
    T name;
    Node* next = nullptr;
    unsigned int pr;
};

template<typename T>
struct Queue{
    Node<T>* first = nullptr;
    Node<T>* last = nullptr;


    bool isEmpty(Queue<T> q){
        return q.first == nullptr;
    }
    void push(Queue<T> *q, T name0, unsigned int pr0){
        auto node = new Node<T>;
        node->name = name0;
        node->pr = pr0;
        if (isEmpty(*q)) {
            q->first = node;
            q->last = node;
            return;
        }
        if (node->pr < q->last->pr){ //если вообще хуже всех (меняем last)
            (q->last)->next = node;
            q->last = node;
            return;}

        if (node->pr > q->first->pr){
            node->next = q->first; //если самый лучший, то становится сразу первым
            q->first = node;
            return;
        }

        auto p = q->first;
        while(true){
            if (p->next->pr < node->pr){
                node->next = p->next;
                p->next = node;
                return;
            }
            p = p->next;
        }
    }
    void pop(Queue<T> *q){
        if (isEmpty(*q)){
            return;
        }
        if (q->first->next == nullptr){
            delete q->first;
            q->first = nullptr;
            q->last = nullptr;
            return;
        }
        auto node = q->first->next;
        delete q->first;
        q->first=node;
        return;
    }
    void print(Queue<T> *q){
        if (isEmpty(*q)){return;}
        auto p = q->first;
        std::cout << p->name;
        while (p!= q->last){
            p = p->next;
            std::cout << p->name;
        }
        std::cout << std::endl;
    }

};

int main(){
    Queue<char> q;
    q.push(&q,'r', 5);
    q.push(&q,'i', 6);
    q.push(&q,'p', 2);
    q.push(&q,'t', 10);
    q.push(&q,'v', 7);
    q.push(&q,'e', 8);

    q.print(&q);
    q.pop(&q);
    q.print(&q);


    return 0;
}