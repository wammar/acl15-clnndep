#ifndef __TPARSER_MAT_H__
#define __TPARSER_MAT_H__

#include <iostream>
#include <vector>

/*
 * A class for vector
 */
template <typename T>
class Vec {
private:
    int nn;
    T * v;
public:
    Vec() : nn(0), v(0) {}

    ~Vec() {
        dealloc();
    }

    // zero-based array
    explicit Vec(const int n) : nn(0), v(0) {
        resize(n);
    }

    // initialize to constant value
    Vec(const T &a, const int n) : nn(n), v(new T[n]) {
        for (int i = 0; i < n; ++ i) {
            v[i] = a;
        }
    }

    // initialize to array
    Vec(const T *a, const int n) : nn(n), v(new T[n]) {
        for (int i = 0; i < n; ++ i) {
            v[i] = *a;
            a ++;
        }
    }

    // copy constructor
    Vec(const Vec<T> &rhs): nn(rhs.nn), v(new T[nn]) {
        for (int i = 0; i < nn; ++ i) {
            v[i] = rhs[i];
        }
    }

    Vec & resize(const int n) {
        if (nn != n) {
            if (v != 0) {
                delete [] (v);
            }
            nn = n;
            v = new T[n];
        }
        return *this;
    }

    Vec & operator=(const Vec &rhs) {
        if (this != &rhs) {
            if (nn != rhs.nn) {
                if (v != 0) {
                    delete [] (v);
                }
                nn = rhs.nn;
                v = new T[nn];
            }

            for (int i = 0; i < nn; ++ i) v[i] = rhs[i];
        }
        return *this;
    }

    Vec & operator=(const T& a) {
        for (int i = 0; i < nn; ++ i) {
            v[i] = a;
        }
        return *this;
    }

    Vec & operator=(const std::vector<T> &a) {
        if (nn != a.size()) {
            if (v != 0) {
                delete [] (v);
            }
            nn = a.size();
            v = new T[nn];
        }

        for (int i = 0; i < nn; ++ i) v[i] = a[i];
        return *this;
    }

    inline T & operator [](const int i) {
        return v[i];
    }

    inline const T & operator [](const int i) const {
        return v[i];
    }

    inline int size() const {
        return nn;
    }

    inline void dealloc() {
        if (v != 0) {
            delete [] (v);
            v = 0;
            nn = 0;
        }
    }

    inline T * c_buf() {
        return v;
    }
};  //  end for class Vec

/*
 * A class for matrix(2d)
 */
template <typename T>
class Mat {
private:
    int nn;
    int mm;
    int tot_sz;
    T ** v;
public:
    ~Mat() {
        dealloc();
    }

    void dealloc() {
        if (v != 0) {
            delete [] (v[0]);
            delete [] (v);
            v = 0;
            nn = 0;
            mm = 0;
            tot_sz = 0;
        }
    }

    T * c_buf() {
        if (v) {
            return v[0];
        } else {
            return 0;
        }
    }

    Mat() : nn(0), mm(0), tot_sz(0), v(0) {}

    Mat & resize(const int n, const int m) {
        if (nn != n || mm != m) {
            dealloc();
            nn = n;
            mm = m;
            tot_sz = n * m;

            v = new T*[n];
            v[0] = new T[tot_sz];

            for (int i = 1; i < n; ++ i) {
                v[i] = v[i - 1] + m;
            }
        }
        return *this;
    }

    Mat(const int n, const int m) 
        : nn(0), mm(0), tot_sz(0), v(0) {
        resize(n, m);
    }

    Mat(const T & a, const int n, const int m) 
        : nn(0), mm(0), tot_sz(0), v(0) {
        resize(n, m);
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                v[i][j] =a;
            }
        }
    }

    Mat(const T * a, const int n, const int m) {
        resize(n, m);
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                v[i][j] = *a;
                ++ a;
            }
        }
    }

    Mat(const Mat & rhs) {
        resize(rhs.nn, rhs.mm);
        for (int i = 0; i < nn; ++ i) {
            for (int j = 0; j < mm; ++ j) {
                v[i][j] = rhs[i][j];
            }
        }
    }

    Mat & operator= (const Mat &rhs) {
        if (this != &rhs) {
            resize(rhs.nn, rhs.mm);

            for (int i = 0; i < nn; ++ i) {
                for (int j = 0; j < mm; ++ j) {
                    v[i][j] = rhs[i][j];
                }
            }
        }
        return *this;
    }

    Mat & operator= (const T & a) {
        for (int i = 0; i < nn; ++ i) {
            for (int j = 0; j < mm; ++ j) {
                v[i][j] = a;
            }
        }
        return *this;
    }

    inline T * operator[] (const int i) {
        return v[i];
    }

    inline const T * operator[] (const int i) const {
        return v[i];
    }

    inline int nrows() const {
        return nn;
    }

    inline int ncols() const {
        return mm;
    }

    inline int total_size() const {
        return tot_sz;
    }
};  //  end for class Mat

/*
 *
 *
 */
template <typename T>
class Mat3 {
private:
    int nn;
    int mm;
    int kk;
    int tot_sz;

    T ***v;
public:
    Mat3() : nn(0), mm(0), kk(0), tot_sz(0), v(0) {}
    ~Mat3() {
        dealloc();
    }

    void dealloc() {
        if (v != 0) {
            delete [] (v[0][0]);
            delete [] (v[0]);
            delete [] (v);
            v = 0;
            nn = 0;
            mm = 0;
            kk = 0;
            tot_sz = 0;
        }
    }

    T * c_buf() {
        if (v) {
            return v[0][0];
        } else {
            return NULL;
        }
    }

    Mat3(const int n, const int m, const int k) 
        : nn(0), mm(0), kk(0), tot_sz(0), v(0) {
        resize(n, m, k);
    }

    Mat3 & resize(const int n, const int m, const int k) {
        if (nn != n || mm != m || kk != k) {
            dealloc();

            nn = n;
            mm = m;
            kk = k;
            tot_sz = n * m * k;

            v = new T**[n];
            v[0] = new T*[n * m];
            v[0][0] = new T[tot_sz];

            int i, j;
            for (j = 1; j < m; ++ j) {
                v[0][j] = v[0][j - 1] + k;
            }

            for (i = 1; i < n; ++ i) {
                v[i] = v[i - 1] + m;
                v[i][0] = v[i - 1][0] + m * k;

                for (j = 1; j < m; ++ j) {
                    v[i][j] = v[i][j - 1] + k;
                }
            }
        }

        return *this;
    }

    Mat3(const T & a, const int n, const int m, const int k)
        : nn(0), mm(0), kk(0), tot_sz(0), v(0) {
        resize(n, m, k);
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                for (int l = 0; l < k; ++ l) {
                    v[i][j][l] = a;
                }
            }
        }
    }

    Mat3(const T * a, const int n, const int m, const int k) {
        resize(n, m, k);
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                for (int l = 0; l < k; ++ l) {
                    v[i][j][l] = *a;
                    ++ a;
                }
            }
        }
    }

    Mat3(const Mat3 & rhs) {
        resize(rhs.nn, rhs.mm, rhs.kk);
        for (int i = 0; i < nn; ++ i) {
            for (int j = 0; j < mm; ++ j) {
                for (int l = 0; l < kk; ++ l) {
                    v[i][j][l] = rhs[i][j][l];
                }
            }
        }
    }

    Mat3 & operator= (const Mat3 &rhs) {
        if (this != &rhs) {
            resize(rhs.nn, rhs.mm, rhs.kk);

            for (int i = 0; i < nn; ++ i) {
                for (int j = 0; j < mm; ++ j) {
                    for (int l = 0; l < kk; ++ l) {
                        v[i][j][l] = rhs[i][j][l];
                    }
                }
            }
        }
        return *this;
    }

    Mat3 & operator= (const T &a) {
        for (int i = 0; i < nn; ++ i) {
            for (int j = 0; j < mm; ++ j) {
                for (int k = 0; k < kk; ++ k) {
                    v[i][j][k] = a;
                }
            }
        }

        return *this;
    }

    inline T** operator[] (const int i) {
        return v[i];
    }

    inline const T * const * operator[] (const int i) const {
        return v[i];
    }

    inline int dim1() const {
        return nn;
    }

    inline int dim2() const {
        return mm;
    }

    inline int dim3() const {
        return kk;
    }

    inline int total_size() const {
        return tot_sz;
    }
};  //  end for class Mat3

template <typename T>
class Mat4 {
private:
    int nn;
    int mm;
    int kk;
    int ll;
    int tot_sz;
    T ****v;

public:
    Mat4() : nn(0), mm(0), kk(0), ll(0), tot_sz(0), v(0) {}

    ~Mat4() {
        dealloc();
    }

    Mat4 & resize(const int n, const int m, const int k, const int l) {
        if (n != nn || m != mm || k != kk || l != ll) {
            dealloc();

            nn = n;
            mm = m;
            kk = k;
            ll = l;
            tot_sz = n * m * k * l;

            v = new T***[n];
            v[0] = new T**[n * m];
            v[0][0] = new T*[n * m * k];
            v[0][0][0] = new T[n * m * k * l];

            int i, j, z;

            for (z = 1; z < k; ++ z) {
                v[0][0][z] = v[0][0][z - 1] + l;
            }

            for (j = 1; j < m; ++ j) {
                v[0][j] = v[0][j - 1] + k;
                v[0][j][0] = v[0][j - 1][0] + k * l;

                for (z = 1; z < k; ++ z) {
                    v[0][j][z] = v[0][j][z - 1] + l;
                }
            }

            for (i = 1; i < n; ++ i) {
                v[i] = v[i - 1] + m;
                v[i][0] = v[i - 1][0] + m * k;
                v[i][0][0] = v[i - 1][0][0] + m * k * l;

                for (z = 1; z < k; ++ z) {
                    v[i][0][z] = v[i][0][z - 1] + l;
                }

                for (j = 1; j < m; ++ j) {
                    v[i][j] = v[i][j - 1] + k;
                    v[i][j][0] = v[i][j - 1][0] + k * l;

                    for (z = 1; z < k; ++ z) {
                        v[i][j][z] = v[i][j][z - 1] + l;
                    }
                }
            }
        }

		return (*this);
    }

    explicit Mat4(const int n, const int m, const int k, const int l) {
        resize(n, m, k, l);
    }

    Mat4 & operator=(const T & a) {
        for (int i = 0; i < nn; ++ i) {
            for (int j = 0; j < mm; ++ j) {
                for (int k = 0; k < kk; ++ k) {
                    for (int l = 0; l < ll; ++ l) {
                        v[i][j][k][l] = a;
                    }
                }
            }
        }
        return *this;
    }

    inline T*** operator[](const int i) {
        return v[i];
    }

    inline const T* const * const * operator[](const int i) const {
        return v[i];
    }

    inline int dim1() const {
        return nn;
    }

    inline int dim2() const {
        return mm;
    }

    inline int dim3() const {
        return kk;
    }

    inline int dim4() const {
        return ll;
    }

    inline int total_size() const {
        return tot_sz;
    }

    inline void dealloc() {
        if (v) {
            delete [] (v[0][0][0]);
            delete [] (v[0][0]);
            delete [] (v[0]);
            delete [] (v);
            v = 0;
            nn = 0;
            mm = 0;
            kk = 0;
            ll = 0;
            tot_sz = 0;
        }
    }

    inline T * c_buf() {
        if (v) {
            return v[0][0][0];
        } else {
            return 0;
        }
    }


private:
    Mat4(const Mat4 & rhs) { }
    Mat4  & operator =(const Mat4 & rhs) {}
};


#endif  // end for __MAT_H__
