#pragma once

#include <compare>
#include <initializer_list>
#include <memory>
#include <utility>

const size_t DEFAULT_CAPACITY = 10;

template <typename T, typename Alloc = std::allocator<T>>
class Vector {
private:
    class VectorIterator {
    public:
        using value_type = T;
        using pointer_type = value_type*;
        using reference_type = value_type&;
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;

        VectorIterator() : ptr_(nullptr) {}
        VectorIterator(const VectorIterator&) = default;

        VectorIterator& operator=(const VectorIterator&) = default;

        reference_type operator*() const;
        pointer_type operator->() const;
        VectorIterator& operator++();
        VectorIterator operator++(int);
        VectorIterator& operator--();
        VectorIterator operator--(int);
        VectorIterator& operator+=(const difference_type& other);
        VectorIterator& operator-=(const difference_type& other);
        VectorIterator operator+(const difference_type& other) const;
        VectorIterator operator-(const difference_type& other) const;

        difference_type operator-(const VectorIterator& other) const;
        reference_type operator[](const difference_type& index) const;

        bool operator==(const VectorIterator& other) const;
        bool operator!=(const VectorIterator& other) const;
        bool operator<(const VectorIterator& other) const;
        bool operator<=(const VectorIterator& other) const;
        bool operator>(const VectorIterator& other) const;
        bool operator>=(const VectorIterator& other) const;


        // == != < <= > >= * -> []

    private:
        explicit VectorIterator(T* ptr) : ptr_(ptr) {}

        T* ptr_;
        friend class Vector;
    };

public:
    Vector();
    explicit Vector(size_t count);
    Vector(size_t count, const T& value);
    Vector(const Vector& other);
    Vector(Vector&& other);
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other);
    Vector(std::initializer_list<T> init);
    ~Vector();

    VectorIterator begin();
    VectorIterator end();
    T& at(size_t index);
    const T& at(size_t index) const;
    T& operator[](size_t pos);
    const T& operator[](size_t pos) const;
    T& front();
    const T& front() const;
    T& back()t;
    const T& back() const;
    T* data();
    const T* data() const;
    bool empty() const;
    size_t size() const;
    size_t capacity() const;
    void shrink_to_fit();
    void reserve(size_t new_cap);
    void clear();
    void insert(size_t pos, T value);
    void erase(size_t begin_pos, size_t end_pos);
    void push_back(const T& value);
    void pop_back();
    void resize(size_t count, const T& value = T());

    std::strong_ordering operator<=>(const Vector& other) const;
    bool operator==(const Vector& other) const;

private:
    T* arr_;
    size_t size_;
    size_t cap_;
    Alloc alloc_;

    using AllocTraits = std::allocator_traits<Alloc>;
};
