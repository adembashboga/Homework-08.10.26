#include <iostream>
#include <cstdlib>
using namespace std;

class A 
{
public:
    int x;
    A(int val = 0) : x(val) {}

    A operator+(const A& o) const { return A(x + o.x); }
    A operator-(const A& o) const { return A(x - o.x); }
    A operator*(const A& o) const { return A(x * o.x); }
    A operator/(const A& o) const { return A(x / o.x); }

    bool operator<(const A& o) const { return x < o.x; }

    friend std::ostream& operator<<(std::ostream& out, const A& a) 
    {
        return out << a.x;
    }
};

template <typename T>
class Matrix 
{
public:
    int r, c;
    T** data;

    Matrix(int rows, int cols) : r(rows), c(cols) 
    {
        data = new T * [r];
        for (int i = 0; i < r; ++i) data[i] = new T[c]();
    }

    ~Matrix() 
    {
        for (int i = 0; i < r; ++i) delete[] data[i];
        delete[] data;
    }

    void fillRandom() 
    {
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                data[i][j] = T(rand() % 10 + 1);
    }

    void print() const 
    {
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) std::cout << data[i][j] << "\t";
            std::cout << "\n";
        }
    }

    Matrix operator+(const Matrix& o) const 
    {
        Matrix res(r, c);
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                res.data[i][j] = data[i][j] + o.data[i][j];
        return res;
    }

    T findMax() const 
    {
        T m = data[0][0];
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                if (m < data[i][j]) m = data[i][j];
        return m;
    }
};

int main() 
{
    Matrix<int> m1(2, 2), m2(2, 2);
    m1.fillRandom();
    m2.fillRandom();

    std::cout << "Matrix 1:\n";
    m1.print();

    std::cout << "Sum:\n";
    (m1 + m2).print();

    std::cout << "Max in m1: " << m1.findMax() << "\n";

    Matrix<A> ma(2, 2);
    ma.fillRandom();
    std::cout << "\nMatrix A:\n";
    ma.print();
    std::cout << "Max in Matrix A: " << ma.findMax() << "\n";
}