#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
class Vector {
private:
    T* data;
    size_t m_size;
    size_t m_capacity;

    void reallocate(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < m_size; ++i)
            new_data[i] = std::move(data[i]);
        delete[] data;
        data = new_data;
        m_capacity = new_capacity;
    }

public:
    Vector() : data(nullptr), m_size(0), m_capacity(0) {}


    Vector(const Vector& other)
        : data(new T[other.m_capacity]),
          m_size(other.m_size),
          m_capacity(other.m_capacity) {
        for (size_t i = 0; i < m_size; ++i)
            data[i] = other.data[i];
    }

    Vector(Vector&& other) noexcept
        : data(other.data), m_size(other.m_size), m_capacity(other.m_capacity) {
        other.data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    Vector& operator=(const Vector& other) {
        if (this == &other) return *this;
        delete[] data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        data = new T[m_capacity];
        for (size_t i = 0; i < m_size; ++i)
            data[i] = other.data[i];
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this == &other)
					 return *this;
        delete[] data;
        data = other.data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        other.data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
        return *this;
    }

    ~Vector() { delete[] data; }

    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }

    T& at(size_t index) {
        if (index >= m_size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    const T& at(size_t index) const {
        if (index >= m_size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    size_t size() const { return m_size; }
    size_t capacity() const { return m_capacity; }
    bool empty() const { return m_size == 0; }



    void push_back(const T& value) {
        if (m_size == m_capacity)
            reallocate(m_capacity == 0 ? 1 : m_capacity * 2);
        data[m_size++] = value;
    }

    void push_back(T&& value) {
        if (m_size == m_capacity)
            reallocate(m_capacity == 0 ? 1 : m_capacity * 2);
        data[m_size++] = std::move(value);
    }
		
		void pop_back() {
			if (m_size > 0) {
					--m_size;
					data[m_size].~T();
			}
		}


    void clear() { 
			for (size_t i = 0; i < m_size; ++i)
					data[i].~T(); 
			m_size = 0;
		}
 
};
