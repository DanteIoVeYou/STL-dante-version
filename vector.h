#pragma once
//模拟实现vector类，并完成测试
#include <iostream>
#include <assert.h>
using namespace std;

namespace imdanteking {
    template <class T>
    class vector {
    public:
        //iterator
        typedef T* iterator;
        typedef const T* const_iterator;
        iterator begin() {
            return _start;
        }
        iterator end() {
            return _finish;
        }
        const_iterator cbegin() const {
            return _start;
        }
        const_iterator cend() const {
            return _finish;
        }

        //constructor and destructor
            //默认构造函数
        vector()
            : _start(nullptr)
            , _finish(nullptr)
            , _endOfStorage(nullptr)
        {}
            //带参构造
        explicit vector(int n, const T& x = T()) //数字 3 默认是int类型，前面 n的类型得给个int，不能只给size_t，否则你想带参重载的时候3就会和size_t匹配不上，就跑进了下面的迭代器构造里面，然后导致非法寻址
            :_start(new T[n])
            , _finish(_start + n)
            , _endOfStorage(_start + n)
        {
            for (size_t i = 0; i < n; i++) {
                _start[i] = x;
            }
        }
            //用迭代器区间构造
        template <class InputInerator>
        vector(InputInerator first, InputInerator last) 
            : _start(nullptr)
            , _finish(nullptr)
            , _endOfStorage(nullptr)
        {
          /*size_t sz = last - first;
            _start = new T[sz];
            _finish = _start + sz;
            _endOfStorage = _start + sz;
            for (int i = 0; i < sz; i++) {
                *(_start + i) = *(first + i);
            }*/
            while (first != last) {
                push_back(*first);
                first++;
            }
        }
            //拷贝构造
        vector(const vector& v) 
            :_start(nullptr)
            , _finish(nullptr)
            , _endOfStorage(nullptr) 
        {
            vector tmp(v.cbegin(), v.cend());
            swap(tmp);
        }
            //析构函数
        ~vector() {
            delete[] _start;
            _start = nullptr;
            _finish = nullptr;
            _endOfStorage = nullptr;
        }
            //赋值重载
        vector& operator=(vector v) {
            swap(v);
            return *this;
        }
        //capacity
            //size()
        size_t size() const {
            return _finish - _start;
        }
            //capacity()
        size_t capacity() const {
            return _endOfStorage - _start;
        }
        bool empty() {
            return size() == 0;
        }
            //reverse()扩容
        void reserve(size_t n) {
            size_t sz = size();
            T* tmp = new T[n];
            memcpy(tmp, _start, size()*sizeof(T));
            delete[] _start;
            _start = tmp;
            _finish = _start + sz;
            _endOfStorage = _start + n;
        }
            //resize
        void resize(size_t n, const T& x = T()) {
            if (n <= size()) {
                _finish = _start + n;
            }
            else {
                if (n > capacity()) {
                    reserve(n);
                }
                for (size_t i = size(); i < n; i++) {
                    _start[i] = x;
                    _finish++;
                }
            }
        }
        //access
        T& operator[](size_t pos) {
            assert(pos < size());
            return _start[pos];
        }
        const T& operator[](size_t pos) const {
            assert(pos < size());
            return _start[pos];
        }
        //modify
            // insert
        iterator insert(iterator pos, const T& x) {
            assert(pos >= _start && pos <= _finish);
            if (_finish == _endOfStorage) {
                size_t len = pos - _start;
                size_t new_capacity = (_start == _finish) ? 4 : 2 * (_endOfStorage - _start);
                reserve(new_capacity);
                pos = _start + len;
            }
            for (iterator i = _finish; i >= pos + 1; i--) {
                *i = *(i - 1);
            }
            *pos = x;
            _finish++;
            return pos;
        }
            //push_back
        void push_back(const T& x) {
            insert(_finish, x);  
        }
        iterator erase(iterator pos) {
            assert(!empty());
            for (vector::iterator i = pos; i < end() - 1; i++) {
                *i = *(i + 1);
            }
            _finish--;
            return pos;
        }
        iterator erase(iterator first, iterator last) {
            assert(first >= _start && last <= _finish);
            size_t epoc = _finish - last + 1;
            size_t len = last - first;
            for (vector::iterator i = first; i < end() - len; i++) {
                *i = *(i + len);
            }
            _finish -= len;
            return first;
        }
            //pop_back()
        void pop_back() {
            erase(end());
        }
        void clear() {
            erase(begin(), end());
        }
            //swap
        void swap(vector& v2) {
            ::swap(_start, v2._start);
            ::swap(_finish, v2._finish);
            ::swap(_endOfStorage, v2._endOfStorage);
        }
    private:
        T* _start; // 指向数据块头部
        T* _finish; // 指向有效数据尾部
        T* _endOfStorage; //指向存储空间尾部
    };
}
