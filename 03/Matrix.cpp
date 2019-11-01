#include <iostream>
using namespace std;

class Row {
public:
    Row (int *p, int columns) : len(columns) {
        ptr = p;
    }
///////////////
    const int& operator[](size_t i) const {
        if (i >= len) {
            throw out_of_range("Matrix doesn't have as many rows");
        }
        return ptr[i];
    }
///////////////
    int &operator[](size_t i) {
        if (i >= len) {
            throw out_of_range("Matrix doesn't have as many rows");
        }
        return ptr[i];
    }
///////////////
private:
    int *ptr;
    const int len;
};


class Matrix{
public:
    const pair<int, int> shape;
    Matrix (int n, int m) : shape(n , m), size(n * m) {
        ptr = (int*)malloc(n * m * sizeof(int));
        rows = (int**)malloc(n * sizeof(*rows));
        for (size_t i = 0; i < n; i++) {
            rows[i] = ptr + i * m;
        }
    }
///////////////
    size_t getrows() {
        return shape.first;
    }
///////////////
    size_t getcolumns() {
        return shape.second;
    }
///////////////
    void operator=(int val) {
        for (size_t i = 0; i < size; i++) {
            ptr[i] = val;
        }
    }
///////////////
    const Row& operator[](size_t i) const {
        if (i >= shape.first) {
            throw out_of_range("Matrix doesn't have as many rows");
        }
        return Row(rows[i], shape.second);
    }
///////////////
    Row operator[](size_t i) {
        if (i >= shape.first) {
            throw out_of_range("Matrix doesn't have as many rows");
        }
        return Row(rows[i], shape.second);
    }
///////////////
    bool operator==(const Matrix &jopa) {
        if (shape != jopa.shape) {
            return false;
        }
        for (size_t i = 0; i < size; i++) {
            if (ptr[i] != jopa.ptr[i])
                return false;
        }
        return true;
    }
///////////////
    bool operator!=(const Matrix &jopa) {
        return !(operator==(jopa));
    }
///////////////
    void operator*=(int val) {
        for (size_t i = 0; i < size; ++i) {
            ptr[i] *= val;
        }
    }
///////////////
    ~Matrix() {
        free(ptr);
        free(rows);
    }
///////////////

private:
    const int size;
    int *ptr, **rows;
};

ostream& operator<<(ostream& out, const Matrix &jopa) {
    for (int i = 0 ; i < jopa.shape.first; i++) {
        for (int j = 0; j < jopa.shape.second; j++) {
            out << jopa[i][j] << " ";
        }
        out << "\n";
    }

    return out;
}
int main() {
    try {
        const size_t rows = 5;
        const size_t cols = 7;

        Matrix m(rows, cols);
        cout << "size: (" << m.getrows() << ", " << m.getcolumns() << ')' << endl << m << endl;

        m[0][0] = 0;
        m[0][5] = 17;
        cout << m << endl << "Matrix[1][2] = " << m[1][2] << endl << endl;

        m *= 2;
        cout << m << endl;

        const Matrix m_const(rows, cols);

        if (m == m_const) {
            cout << "equal" << endl;
        }
        if (m != m_const) {
            cout << "not equal" << endl;
        }

        cout << m_const[5][0];
    } catch(exception &e) {
        cout << e.what() << endl;
        return 1;
    }
    return 0;
}