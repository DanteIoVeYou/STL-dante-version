#pragma once
#include <iostream>
#include <assert.h>
using namespace std;

namespace imdanteking {
	typedef basic_string<char> string;
	template<class T>
	class basic_string {
	public:
		//迭代器
		typedef T* iterator;
		iterator begin() {
			return _str;
		}
		iterator end() {
			return _str + _size;
		}
		//const 迭代器
		//size()接口
		size_t size() const{
			return _size;
		}
		//capacity()接口
		size_t capacity() const {
			return _capacity;
		}
		//swap
		void swap(basic_string& str) {
			::swap(_size, str._size);
			::swap(_capacity, str._capacity);
			::swap(_str, str._str);
		}

	
		
		//全缺省带参默认构造函数
		basic_string(const T* s = "")
			:_size(strlen(s))
			,_capacity(strlen(s)) 
		{
			_str = new T[_size + 1];
			strcpy(_str, s);
		}

		//析构函数
		~basic_string() {
			delete[] _str;
			_str = nullptr;
			_size = 0;
			_capacity = 0;
		}

		////拷贝构造(传统写法)
		//basic_string(const basic_string& str) {
		//	if (this != &str) {
		//		_size = str._size;
		//		_capacity = str._capacity;
		//		_str = new T[_size + 1];
		//		strcpy(_str, str._str);
		//	}
		//}
		//拷贝构造(现代写法)
		basic_string(const basic_string& str)
			: _str(nullptr)
			{
				if (this != &str) {
					basic_string tmp(str._str);
					swap(tmp);
			}
		}

		//赋值重载(现代写法1)
		//basic_string& operator=(const basic_string& str) {
		//	if (this != &str) {
		//		basic_string tmp(str);
		//		swap(tmp);
		//		return *this;
		//	}
		//}
		//赋值重载(现代写法2)
		basic_string& operator=(basic_string str) {
			swap(str);
			return *this;
		}

		//增容函数

		void reserve(int new_capacity) {
			T* tmp = new T[new_capacity + 1];//多开的一个T的大小用来存'\0'
			strcpy(tmp, _str);
			delete[] _str;
			_str = tmp;
			tmp = nullptr;
			_capacity = new_capacity;
		}
		void resize(size_t n, T c = '\0') {
			if (n <= _size) {
				_str[n] = '\0';
				_size = n;
			}
			else {

				if (n > _capacity) {
					reserve(n);	
				}
				for (size_t i = _size; i < n; i++) {
					_str[i] = c;
				}
				_str[n] = '\0'; 
				_size = n;
			}
		}
		//push_back尾插一个字符
		void push_back(const T c) {
			if (_size == _capacity) {
				size_t new_capacity = _capacity == 0 ? 4 : 2 * _capacity;
				reserve(new_capacity);
			}
			_str[_size] = c;
			_size++;
			_str[_size] = '\0';
		}
		// 复用push_back  重载+=字符
		void operator+=(const T c) {
			push_back(c);
		}
		//append尾插字符串
		void append(const T* str) {
			size_t len = strlen(str);
			if (_size + len > _capacity) {
				reserve(_size + len);
			}
			strcpy(_str + _size, str);
			_str[_size + len] = '\0';
			_size += len;
		}
		//复用append，重载+=字符串
		void operator+=(const T* str) {
			append(str);
		}
		//重载[]
		T& operator[](size_t pos) {
			assert(pos < _size);
			return _str[pos];
		}
		const T& operator[](size_t pos) const{
			assert(pos < _size);
			return _str[pos];
		}
		// 清除
		void clear() {
			_str[0] = '\0';
			_size = 0;
		}
		// 取出字符串指针
		const T* c_str() const {
			return _str;
		}
		// 判空
		bool empty() const {
			return _size == 0;
		}
		//< <= > <= == !=的重载
		bool operator<(const basic_string& str) {
			size_t end = 0;
			while (end < _size && end < str._size) {
				if (_str[end] > str._str[end]) {
					return false;
				}
				else if(_str[end] < str._str[end]){
					return true;
				}
				end++;
			}
			if (end == str._size) {
				return false;
			}
			else {
				return true;
			}
		}
		bool operator==(const basic_string& str) {
			if (_size != str._size) {
				return false;
			}
			size_t end = 0;
			while (end < _size && end < str._size) {
				if (_str[end] != str._str[end]) {
					return false;
				}
				end++;
			}
			return true;
		}
		bool operator!=(const basic_string& str) {
			return !(*this == str);
		}
		bool operator>(const basic_string& str) {
			return !((*this < str) || (*this == str));
		}
		bool operator<=(const basic_string& str) {
			return !(*this > str);
		}
		bool operator>=(const basic_string& str) {
			return !(*this < str);
		}
		//find
		size_t find(const T c, size_t pos = 0) const {
			assert(pos < _size);
			for (size_t i = pos; i < _size; i++) {
				if (_str[i] == c) {
					return i;
				}
			}
			return npos;
		}
		size_t find(const T* s, size_t pos = 0) const {
			assert(pos < _size);
			T* ret = strstr(_str + pos, s);
			if (ret == nullptr) {
				return npos;
			}
			else {
				while (*ret != _str[pos]) {
					pos++;
				}
				return pos;
			}
		}
		//insert
		basic_string& insert(size_t pos, const T c) {
			assert(pos <= _size);
			if (_size == _capacity) {
				size_t new_capacity = _capacity == 0 ? 4 : 2 * _capacity;
				reserve(new_capacity);
			}
			_size++;
			size_t end = _size + 1;
			while (end > pos) {
				_str[end] = _str[end - 1];
				end--;
			}
			_str[pos] = c;
			return *this;
		}
		basic_string& insert(size_t pos, const T* s) {
			assert(pos <= _size);
			size_t len = strlen(s);
			if (len + _size > _capacity) {
				reserve(len + _size);
			}
			size_t end = _size + len;
			while (end - len + 1 > pos) {
				_str[end] = _str[end - len];
				end--;
			}
			_size += len;
			memcpy(begin() + pos, s, len * sizeof(T));
			return *this;
		}
		//erase
		iterator erase(size_t pos, size_t len = npos) {
			assert(pos < _size);
			if (pos + len >= _size) {
				_str[pos] = '\0';
			}
			else {
				strcpy(begin() + pos, begin() + pos + len);
			}
			_size = strlen(_str);
			return begin() + pos;
		}
		//substr
		basic_string substr(size_t pos, size_t n = npos) {
			assert(pos < _size);
			basic_string tmp;
			tmp.resize(_size);
			if (pos + n >= _size || n == npos) {
				strcpy(tmp._str, _str + pos);
				_size -= pos + 1;
			}
			else {
				strcpy(tmp._str, _str + pos);
				*(tmp._str + n) = '\0';
				_size = n;
			}
			return tmp;
		}
		//operator+
		basic_string operator+(const basic_string& str) {
			basic_string ret(*this);
			ret += str._str;
			return ret;
		}
		basic_string operator+(const T* s) {
			basic_string ret(*this);
			ret += s;
			return ret;
		}
	private:
		T* _str;
		size_t _size;
		size_t _capacity;
		static const size_t npos = -1;
	};
	ostream& operator<<(ostream& out, const basic_string<char>& str) {
		for (size_t i = 0; i < str.size(); i++) {
			out << str[i];
		}
		return out;
	}
	istream& operator>>(istream& in, basic_string<char>& str) {
		str.clear();
		char ch;
		ch = in.get();
		while (ch != ' ' && ch != '\n') {
			str += ch;
			ch = in.get();
		}
		return in;
	}
	istream& getline(istream& in, basic_string<char>& str) {
		str.clear();
		char ch;
		ch = in.get();
		while (ch != '\n') {
			str += ch;
			ch = in.get();
		}
		return in;
	}
}