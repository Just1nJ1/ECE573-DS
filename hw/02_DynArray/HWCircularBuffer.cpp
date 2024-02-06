/*
    For circular buffer, do your own test
    equivalent to what we do for Dynamic Array
    test each method and make sure it works!


*/

#include <iostream>

using namespace std;

class CircularBuffer {
private:
    int* data;
    int capacity;
    int head;
    int tail;
    void checkGrow() {
        if ((head + capacity) % capacity == (tail + capacity) % capacity) {
            int* old = data;
            data = new int[capacity * 2];
            for (int i = head; i < tail; ++i)
                data[(i + capacity * 2) % (capacity * 2)] = old[(i + capacity) % capacity];

            capacity *= 2;
            delete [] old;
        }
    }
public:
    explicit CircularBuffer(int capacity) : data(new int[capacity]), capacity(capacity), head(0), tail(0) {}
    ~CircularBuffer() { delete [] data; }
    CircularBuffer(const CircularBuffer& orig) : data(new int[orig.capacity]), capacity(orig.capacity), head(orig.head), tail(orig.tail) {
        for (int i = head; i != tail; ++i)
            data[(i + capacity) % capacity] = orig.data[(i + capacity) % capacity];
    }

    void addEnd(int v) {
        checkGrow();
        data[tail++] = v;
    }

    void addStart(int v) {
        checkGrow();
        data[(--head + capacity) % capacity] = v;
    }

    void removeStart() {
        head++;
    }

    void removeEnd() {
        tail--;
    }

    uint32_t getSize() const {
        return tail - head;
    }

    void removeEvens() {
        int count = head;
        for (int i = head; i < tail; ++i)
            if (data[(i + capacity) % capacity] % 2 == 1)
                data[(count++ + capacity) % capacity] = data[(i + capacity) % capacity];
        tail = count;
    }

    friend ostream& operator<<(ostream& out, const CircularBuffer& buffer) {
        out << "Size: " << buffer.tail - buffer.head << ", Capacity: " << buffer.capacity << endl;
#ifdef DEBUG
        out << "Head: " << buffer.head << ", Tail: " << buffer.tail << endl;
#endif
        out << "Head to Tail: \t";
        for (int i = buffer.head; i < buffer.tail; ++i)
            out << buffer.data[(i + buffer.capacity) % buffer.capacity] << " ";
        out << endl;

        out << "In memory: \t\t";
        for (int i = 0; i < buffer.capacity; ++i)
            out << buffer.data[i] << " ";
        out << endl;
        return out;
    }
};

int main() {
    CircularBuffer a(5);
    const int n = 10;
    cout << "=====Adding " << n << " numbers into a by addEnd=====" << endl;
    for (int i = 0; i < n; i++)
        a.addEnd(i);
    cout << a << '\n';

    cout << "=====Adding " << n << " numbers into a by addStart=====" << endl;
    for (int i = 0; i < n; i++)
        a.addStart(i);
    cout << a << '\n';

    cout << "=====Adding 5 into a by addStart=====" << endl;
    a.addStart(5);
    cout << a << '\n';


    cout << "=====Removing " << n/2 << " numbers from a by removeEnd=====" << endl;
    for (int i = 0; i < n/2; i++)
        a.removeEnd();
    cout << a << '\n';

    cout << "=====Removing " << n/2 << " numbers from a by removeStart=====" << endl;
    for (int i = 0; i < n/2; i++)
        a.removeStart();
    cout << a << '\n';

    cout << "=====Removing even numbers from a by removeEvens=====" << endl;
    a.removeEvens();

    cout << a << '\n';
}