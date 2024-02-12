#include <iostream>

using namespace std;

class DoubleLinkedList {
private:
    class Node {
    public:
        Node *next;
        Node *prev;
        int val;
    };

    Node *head;
    Node *tail;
public:
    DoubleLinkedList() : head(nullptr), tail(nullptr) {

    }

    // DO NOT FORGET THE DESTRUCTOR!!!
    ~DoubleLinkedList() {
        if (head != nullptr) {
            for (Node* cur = head; cur != nullptr;) {
                Node* next = cur->next;
                delete cur;
                cur = next;
            }
        }
    }

    void addStart(int v) {
        Node* tmp = new Node();
        tmp->val = v;
        if (head == nullptr) {
            head = tmp;
            tail = tmp;
            tmp->prev = nullptr;
            tmp->next = nullptr;
        } else {
            head->prev = tmp;
            tmp->next = head;
            tmp->prev = nullptr;
            head = tmp;
        }
    }

    void addEnd(int v) {
        if (head == nullptr)
            return addStart(v);

        Node* tmp = new Node();
        tmp->val = v;
        tail->next = tmp;
        tmp->prev = tail;
        tmp->next = nullptr;
        tail = tmp;
    }

    void removeStart() {
        if (head != nullptr) {
            Node *tmp = head;
            head = head->next;
            head->prev = nullptr;
            delete tmp;
            if (head == nullptr)
                tail = nullptr;
        }
    }

    void removeEnd() {
        if (tail != nullptr) {
            Node *tmp = tail;
            if (tail->prev != nullptr)
                tail->prev->next = nullptr;
            tail = tail->prev;
            delete tmp;
            if (tail == nullptr)
                head = nullptr;
        }
    }

    // insert v before pos. insert(0,v) would insert at the front.
    void insert(int pos, int v) {
        if (pos == 0)
            return addStart(v);
        Node* tmp = new Node();
        tmp->val = v;
        Node* prev = head;
        if (head == nullptr) {
            cerr << "Invalid pos!" << endl;
        } else {
            int i = 1;
            for (; i < pos && prev->next != nullptr; ++i) {
                prev = prev->next;
            }
            if (i != pos)
                cerr << "Invalid pos!" << endl;
            else {
                tmp->next = prev->next;
                prev->next->prev = tmp;
                tmp->prev = prev;
                prev->next = tmp;
                if (prev == tail)
                    tail = tmp;
            }
        }
    }

    // implement to print out the list
    friend ostream &operator<<(ostream &s, const DoubleLinkedList &list) {
        for (Node* cur = list.head; cur != nullptr; cur = cur->next)
            s << cur->val << " ";
        return s;
    }
};

int main() {
    DoubleLinkedList a;
    uint32_t n;
    cout << "Enter an integer: ";
    cin >> n;
    for (int i = 0; i < n; i++)
        a.addStart(i);
    for (int i = 0; i < n; i++)
        a.addEnd(i);
    for (int i = 0; i < 3 * n / 2; i++)
        a.removeStart();
    for (int i = 0; i < n / 2 - 5; i++)
        a.removeEnd();
    cout << a << '\n';
    for (int i = 0; i < 10; i++)
        a.insert(1, i);
    cout << a << '\n';
}