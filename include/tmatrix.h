// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz == 0 || sz > MAX_VECTOR_SIZE)
            throw out_of_range("Vector size should be greater than zero and less than max size");
        pMem = new T[sz];// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        if (arr == nullptr)
            throw out_of_range("TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + s, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        sz = v.sz;
        pMem = new T[sz];
        for (size_t i = 0; i < sz; i++)
            pMem[i] = v.pMem[i];
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        pMem = nullptr;
        swap(*this, v);
    }
    ~TDynamicVector()
    {
        delete[] pMem;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this != &v)
        {
            delete[]pMem;
            pMem = new T[v.sz];
            std::copy(v.pMem, v.pMem + v.sz, pMem);
            sz = v.sz;
        }
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this != &v)
            swap(*this, v);
        return *this;
    }

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind)
    {
        if (ind >= sz || sz<0 || ind>MAX_VECTOR_SIZE)
            throw std::out_of_range("Out of range");
        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        if (ind >= sz || ind<0 || ind>MAX_VECTOR_SIZE)
            throw std::out_of_range("Out of range");
        return pMem[ind];
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind >= sz || ind<0 || ind>MAX_VECTOR_SIZE)
            throw std::out_of_range("Out of range");
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind >= sz || ind<0 || ind>MAX_VECTOR_SIZE)
            throw std::out_of_range("Out of range");
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz == v.sz)
        {
            for (int i = 0; i < sz; i++)
                if (pMem[i] != v.pMem[i])
                    return false;
            return true;
        }
        else
            return false;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this == v);
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector tmp(*this);
        for (int i = 0; i < sz; i++)
            tmp.pMem[i] += val;
        return tmp;
    }
    TDynamicVector operator-(T val)
    {
        TDynamicVector tmp(*this);
        for (int i = 0; i < sz; i++)
            tmp.pMem[i] -= val;
        return tmp;
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector tmp(*this);
        for (int i = 0; i < sz; i++)
            tmp.pMem[i] *= val;
        return tmp;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v) const
    {
        if (sz != v.sz)
            throw length_error("impossible to add different sizes");
        TDynamicVector tmp(*this);
        for (int i = 0; i < sz; i++)
            tmp.pMem[i] += v.pMem[i];
        return tmp;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz)
            throw length_error("impossible to sub different sizes");
        TDynamicVector tmp(*this);
        for (int i = 0; i < sz; i++)
            tmp.pMem[i] -= v.pMem[i];
        return tmp;
    }
    T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
    {
        if (sz != v.sz)
            throw length_error("impossible to mul different sizes");
        T tmp = 0;
        for (int i = 0; i < sz; i++)
            tmp += (pMem[i] * v.pMem[i]);
        return tmp;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (s > MAX_MATRIX_SIZE)
            throw out_of_range("matrix size is too large");
        for (size_t i = 0; i < s; i++)
            pMem[i] = TDynamicVector<T>(s);
        sz = s;
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz)
            return false;
        else
        {
            for (int i = 0; i < sz; i++)
                if (pMem[i] != m.pMem[i])
                    return false;
            return true;
        }
    }
    size_t size() { return sz; }
    TDynamicMatrix<T>& operator=(const TDynamicMatrix<T>& M)
    {

        if (this != &M)
        {
            delete[]pMem;
            pMem = new TDynamicVector<T>[M.sz];
            for (int i = 0; i < M.sz; i++)
                pMem[i] = M.pMem[i];
            sz = M.sz;
        }
        return *this;
    }
    // матрично-скалярные операции
    TDynamicMatrix<T> operator*(const T& val)const
    {
        TDynamicMatrix tmp(sz);
        for (size_t i = 0; i < sz; i++)
            tmp.pMem[i] = pMem[i] * val;
        return tmp;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)const
    {
        if (v.sz != sz)
            throw length_error("impossible operation with different sizes");
        TDynamicVector tmp(sz);
        for (int i = 0; i < sz; i++)
            tmp[i] = pMem[i] * v;
        return tmp;

    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)const
    {
        if (m.sz != sz)
            throw length_error("impossible operation with different sizes");
        TDynamicMatrix tmp(m.sz);
        for (int i = 0; i < m.sz; i++)
            tmp.pMem[i] = pMem[i] + m.pMem[i];
        return tmp;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)const
    {
        if (m.sz != sz)
            throw length_error("impossible operation with different sizes");
        TDynamicMatrix tmp(sz);
        for (int i = 0; i < sz; i++)
            tmp.pMem[i] = pMem[i] - m.pMem[i];
        return tmp;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)const
    {
        if (m.sz != sz)
            throw length_error("impossible operation with different sizes");
        TDynamicMatrix tmp(sz);
        for (int i = 0; i < sz; i++)
            for (int k = 0; k < sz; k++)
                for (int j = 0; j < sz; j++)
                    tmp.pMem[i][j] = pMem[i][j] * m.pMem[k][j];
        return tmp;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (int i = 0; i < v.sz; i++)
            istr >> v.pMem[i];
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (int i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << endl;
        return ostr;
    }
};

#endif