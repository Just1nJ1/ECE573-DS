/**
 * Authors: Haochen Ji, Rui Zhang
 */

#include <iostream>

using namespace std;

class GrowArray {
private:
    int* p;
    uint32_t size; // the number of elements used
    uint32_t capacity; // the amount of memory
    void checkGrow() {
        if (size < capacity) {
            return;
        }

        int* old = p;
        p = new int[capacity * 2];
        for (int i = 0; i < capacity; ++i) {
            p[i] = old[i];
        }

        capacity *= 2;
    }
public:
    //write constructor, destructor
    explicit GrowArray(unsigned int size) : p(new int[size]), size(0), capacity(size) {
        if (capacity > 10000)
            cerr << "Warning: Size > 10000! Potentially negative size value" << endl;
    }
    ~GrowArray() { delete [] p; }

    //copy constructor + 10%
    GrowArray(const GrowArray& orig) : p(new int[orig.capacity]), size(orig.size), capacity(orig.capacity) {
        for (int i = 0; i < size; ++i)
            p[i] = orig.p[i];
    }

    //double ended?  + 20% (SEE circularbuffer)
    void addEnd(int v) { //O(n)
        checkGrow();
        p[size++] = v;
    }

    void addStart(int v) { //O(n)
        checkGrow();
        for (int i = (int)size; i > 0; --i) {
            p[i] = p[i - 1];
        }
        p[0] = v;
        size++;
    }
    void removeStart() { //O(n)
        for (int i = 0; i < size - 1; ++i)
            p[i] = p[i + 1];
        size--;
    }

    void removeEnd() { //O(1)
        p[--size] = 0;
    }

    uint32_t getSize() const { //O(1)
        return size;
    }

    void removeEvens() { //O(n)
        int count = 0;
        for (int i = 0; i < size; ++i)
            if (p[i] % 2 == 1)
                p[count++] = p[i];
        size = count;
    }

    friend ostream& operator<<(ostream& out, const GrowArray& array) {
        out << "Size: " << array.size << ", Capacity: " << array.capacity << endl;
        for (int i = 0; i < array.size; ++i)
            out << array.p[i] << (i == array.size - 1 ? "" : " ");
        return out;
    }

    GrowArray& operator=(const GrowArray& other) {
        if (this != &other) {
            delete[] p;
            size = other.size;
            capacity = other.capacity;
            p = new int[capacity];
            for (int i = 0; i < size; ++i)
                p[i] = other.p[i];
        }
        return *this;
    }
};

int main() {
    GrowArray a(5); // empty list, with 5 elements
    const int n = 10;
    for (int i = 0; i < n; i++)   //O(n)
        a.addEnd(i); // really fast!
    cout << a << '\n';

    for (int i = 0; i < n; i++)    //O(n)
        a.addEnd(i); // every time you need to grow, double
    cout << a << '\n';

    a.addStart(5);
    cout << a << '\n';

    for (int i = 0; i < n/2; i++) //O(n)
        a.removeEnd();
    cout << a << '\n';

    for (int i = 0; i < n/2; i++)
        a.removeStart();
    cout << a << '\n';


    a.removeEvens();

    cout << a << '\n';
}
