
#include <compare>
#include <initializer_list>
#include <memory>
#include <utility>


const size_t DEFAULT_CAPACITY = 10;

template <typename T, typename Alloc = std::allocator<T>>

class Vector {
private:
    friend class VectorIterator;

    class VectorIterator {
    public:
        friend Vector;

        using value_type = T;
        using pointer_type = value_type*;
        using reference_type = value_type&;
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;

        VectorIterator(const VectorIterator&) : ptr_(nullptr){};

        VectorIterator& operator=(const VectorIterator& other) {
            if (this != &other) {
                ptr_ = other.ptr_;
            }
            return *this;
        }

        reference_type operator*() const {
            return *ptr_;
        }
        pointer_type operator->() const {
            return ptr_;
        }
        VectorIterator& operator++() {
            ++ptr_;
            return *this;
        }
        VectorIterator operator++(int) {
            VectorIterator copy = *this;
            ++ptr_;
            return copy;
        }

        VectorIterator& operator--() {
            --ptr_;
            return *this;
        }

        VectorIterator operator--(int) {
            VectorIterator copy = *this;
            --ptr_;
            return copy;
        }

        VectorIterator& operator+=(const difference_type& other) noexcept {
            ptr_ += other;
            return *this;
        }

        VectorIterator& operator-=(const difference_type& other) noexcept {
            ptr_ -= other;
            return *this;
        }

        VectorIterator operator-(const difference_type& other) const noexcept {
            return (VectorIterator(ptr_ - other));
        }

        VectorIterator operator+(const difference_type& other) const noexcept {
            return (VectorIterator(ptr_ + other));
        }

    private:
        T* ptr_;
        explicit VectorIterator(T* ptr) : ptr_(ptr) {}
    };

public:
    Vector() {};

    explicit Vector(size_t count) {
        this->reserve(count > DEFAULT_CAPACITY ? count : DEFAULT_CAPACITY);
        size_ = count;
        for (size_t i = 0; i < count; ++i) {
            AllocTraits::construct(alloc_, arr_ + i, 0);
        }
    }

    Vector(size_t count, const T& value) {
        this->reserve(count > DEFAULT_CAPACITY ? count : DEFAULT_CAPACITY);
        size_ = count;
        for (size_t i = 0; i < count; ++i) {
            AllocTraits::construct(alloc_, arr_ + i, value);
        }
    }

    Vector(const Vector& other) : Vector(other.size_) {
        alloc_ = AllocTraits::select_on_container_copy_construction(other.alloc_);
        for (size_t i = 0; i < other.size_; ++i) {
            AllocTraits::construct(alloc_, arr_ + i, other.arr_[i]);
        }
    }

    Vector& operator=(const Vector& other) {
        if (this == &other) {
            return *this;
        }
        Alloc new_alloc = AllocTraits::propagate_on_container_copy_assignment::value ? other.alloc_ : alloc_;
        size_t i = 0;
        T* new_arr = AllocTraits::allocate(new_alloc, other.cap_ > DEFAULT_CAPACITY ? other.cap_ : DEFAULT_CAPACITY);
        try {
            for (; i < other.size_; ++i) {
                AllocTraits::construct(new_alloc, new_arr + i, other.arr_[i]);
            }
        } catch (...) {
            for (size_t j = 0; j < i; ++j) {
                AllocTraits::destroy(new_alloc, new_arr + j);
            }
            AllocTraits::deallocate(new_alloc, new_arr, other.cap_ > DEFAULT_CAPACITY ? other.cap_ : DEFAULT_CAPACITY);
            throw;
        }
        for (size_t i = 0; i < size_; ++i) {
            AllocTraits::destroy(alloc_, arr_ + i);
        }
        AllocTraits::deallocate(alloc_, arr_, cap_);

        arr_ = new_arr;
        size_ = other.size_;
        cap_ = other.cap_;
        alloc_ = new_alloc;  // no throw

        return *this;
    }

    Vector(std::initializer_list<T> init) {
        this->reserve(init.size() > DEFAULT_CAPACITY ? init.size() : DEFAULT_CAPACITY);
        for (auto& elem : init) {
            this->push_back(elem);
        }
    }

    VectorIterator begin() {
        return VectorIterator(arr_);
    }

    VectorIterator end() {
        return VectorIterator(arr_ + size_);
    }

    T& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("index out of range");
        }
        return arr_[index];
    }

    const T& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("index out of range");
        }
        return arr_[index];
    }

    T& operator[](size_t pos) {
        return arr_[pos];
    }

    T& front() const noexcept {
        return arr_[0];
    }

    T& back() const noexcept {
        return arr_[size_ - 1];
    }

    T* data() const noexcept {
        return arr_;
    }

    bool empty() const noexcept {
        return (size_ == 0);
    }

    size_t size() const noexcept {
        return size_;
    }

    size_t capacity() const noexcept {
        return cap_;
    }

    void shrink_to_fit() {
        if (cap_ > size_) {
            T* new_arr = AllocTraits::allocate(alloc_, size_);
            size_t i = 0;

            try {
                for (; i < size_; ++i) {
                    AllocTraits::construct(alloc_, new_arr + i, std::move(arr_[i]));
                }
            } catch (...) {
                for (size_t j = 0; j < i; ++j) {
                    AllocTraits::destroy(alloc_, new_arr + j);
                }
                AllocTraits::deallocate(alloc_, new_arr, size_);
                throw;
            }

            for (size_t i = 0; i < size_; ++i) {
                AllocTraits::destroy(alloc_, arr_ + i);
            }
            AllocTraits::deallocate(alloc_, arr_, cap_);

            arr_ = new_arr;
            cap_ = size_;
        }
    }

    void reserve(size_t new_cap) {
        if (new_cap <= cap_) {
            return;
        }

        T* new_arr = AllocTraits::allocate(alloc_, new_cap);

        size_t i = 0;

        try {
            for (; i < size_; ++i) {
                AllocTraits::construct(alloc_, new_arr + i, arr_[i]);
            }
        } catch (...) {
            for (size_t j = 0; j < i; ++j) {
                AllocTraits::destroy(alloc_, new_arr + j);
            }
            AllocTraits::deallocate(alloc_, new_arr, new_cap);
            throw;
        }
        AllocTraits::deallocate(alloc_, arr_, cap_);
        arr_ = new_arr;
        cap_ = new_cap;
    }

    void clear() noexcept {
        if (size_ == 0) {
            return;
        }
        for (size_t i = 0; i < size_; ++i) {
            AllocTraits::destroy(alloc_, arr_ + i);
        }
        size_ = 0;
    }

    void insert(size_t pos, T value) {  
        if (pos > size_ + 1) {
            return;
        }
        if (pos < 0) {
            return;
        }
        if (size_ + 1 > cap_) {
            this->reserve(size_ * 2);
        }
        for (size_t i = size_; i > pos; --i) {
            arr_[i] = arr_[i - 1];
        }
        ++size_;
        arr_[pos] = value;
    }

    void erase(size_t begin_pos, size_t end_pos) {
        size_t num_to_erase = end_pos - begin_pos;
        if (num_to_erase <= 0) {
            return;
        }
        if (begin_pos > size_ || end_pos > size_) {
            return;
        }
        for (size_t i = begin_pos; i < size_ - num_to_erase; ++i) {
            arr_[i] = arr_[i + num_to_erase];
        }
        size_ -= num_to_erase;
    }

    void push_back(const T& value) {
        if (cap_ == size_) {
            reserve(cap_ > 0 ? cap_ * 2 : DEFAULT_CAPACITY);
        }

        AllocTraits::construct(alloc_, arr_ + size_, value);
        ++size_;
    }

    void pop_back() {
        if (size_ != 0) {
            AllocTraits::destroy(alloc_, arr_ + (--size_));
        }
    }

    void resize(size_t count, const T& value = T()) {
        if (count > cap_) {
            this->reserve(count);
        }
        for (size_t i = size_; i < count; ++i) {
            AllocTraits::construct(alloc_, arr_ + i, value);
        }
        size_ = count;
    }

    std::strong_ordering operator<=>(const Vector& other) const {
        size_t min_size = std::min(size_, other.size());
        for (size_t i = 0; i < min_size; ++i) {
            if (auto cmp = data()[i] <=> other.data()[i]; cmp != 0) {
                return cmp;
            }
        }
        return size_ <=> other.size();
    }

    bool operator==(const Vector& other) {
        if (size_ != other.size()) {
            return false;
        }

        for (int i = 0; i < size_; ++i) {
            if (arr_[i] != other.arr_[i]) {
                return false;
            }
        }
        return true;
    }
    
    ~Vector() {
        for (size_t i = 0; i < size_; ++i) {
            AllocTraits::destroy(alloc_, arr_ + i);
        }
        AllocTraits::deallocate(alloc_, arr_, cap_);
    }

private:
    T* arr_ = nullptr;
    size_t size_ = 0;
    size_t cap_ = 0;
    Alloc alloc_;

    using AllocTraits = std::allocator_traits<Alloc>;
};

