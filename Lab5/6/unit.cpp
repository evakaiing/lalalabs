#include "vector.cpp"

#include <fmt/core.h>
#include <gtest/gtest.h>

#include <chrono>
#include <future>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <memory>


class VectorTest : public testing::Test {
protected:
    void SetUp() override {
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        vec.push_back(4);
        vec.push_back(5);
        vec.push_back(6);
        vec.push_back(7);
        assert(vec.size() == sz);
    }

    Vector<int> vec;
    const size_t sz = 7;
};

TEST(EmptyVectorTest, DefaultConstructor) {
    Vector<int> vec;
    ASSERT_TRUE(vec.empty()) << "Default vector isn't empty!";
    ASSERT_EQ(vec.capacity(), 0) << "Vector should not allocate memory in the default constructor!";
    ASSERT_EQ(vec.data(), nullptr) << "Vector should not allocate memory in the default constructor!";
}

TEST(EmptyVectorTest, AssignIntConstructor) {
    Vector<int> vec(10, 5);
    ASSERT_EQ(vec.size(), 10);
    for (size_t i = 0; i < 10; ++i) {
        ASSERT_EQ(vec[i], 5);
    }
}



TEST(EmptyVectorTest, Init_list) {
    Vector<int> vec({1, 2, 3, 4, 5, 6, 7, 8, 9});
    for (size_t i = 0; i < vec.size(); ++i) {
        ASSERT_EQ(vec[i], i + 1);
    }
}


TEST(EmptyVectorTest, JustReserve) {
    Vector<int> vec;
    vec.reserve(100);
    ASSERT_EQ(vec.capacity(), 100);
    ASSERT_EQ(vec.size(), 0);
    for (size_t i = 0; i < 99; ++i) {
        vec.push_back(1);
    }
    ASSERT_EQ(vec.capacity(), 100);
    ASSERT_EQ(vec.size(), 99);
}

TEST(EmptyVectorTest, ReserveWithRealloc) {
    Vector<int> vec({1, 2, 3, 4, 5, 6, 7, 8, 9});
    vec.reserve(100);
    ASSERT_EQ(vec.capacity(), 100);
    ASSERT_EQ(vec.size(), 9);
    for (size_t i = 0; i < vec.size(); ++i) {
        ASSERT_EQ(vec[i], i + 1);
    }
}

TEST(EmptyVectorTest, ReserveWithNoEffect) {
    Vector<int> vec({1, 2, 3, 4, 5, 6, 7, 8, 9});
    vec.reserve(1);
    ASSERT_EQ(vec.capacity(), 10);
    ASSERT_EQ(vec.size(), 9);
    for (size_t i = 0; i < vec.size(); ++i) {
        ASSERT_EQ(vec[i], i + 1);
    }
}



TEST_F(VectorTest, CopyConstructor) {
    Vector<int> vec1 = vec;
    ASSERT_NE(&vec1, &vec) << "Copy constructor must do copy!\n";
    ASSERT_EQ(vec1.size(), vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        ASSERT_EQ(vec1[i], vec[i]) << "Values must be equal!";
    }
}


TEST_F(VectorTest, RawData) {
    auto data = vec.data();
    for (size_t i = 0; i < vec.size(); ++i) {
        ASSERT_EQ(*(data + i), i + 1);
    }
}


TEST_F(VectorTest, VectorClear) {
    size_t old_cap = vec.capacity();
    vec.clear();
    ASSERT_EQ(vec.capacity(), old_cap);
    ASSERT_EQ(vec.size(), 0);
}

TEST_F(VectorTest, InsertFront) {
    vec.insert(0, 0);
    ASSERT_EQ(vec.size(), sz + 1);
    for (size_t i = 0; i < vec.size(); ++i) {
        ASSERT_EQ(vec[i], i);
    }
}

TEST_F(VectorTest, InsertBack) {
    vec.insert(sz, sz + 1);
    ASSERT_EQ(vec.size(), sz + 1);
    for (size_t i = 0; i < vec.size(); ++i) {
        ASSERT_EQ(vec[i], i + 1);
    }
}

TEST_F(VectorTest, InsertMid) {
    vec.insert(sz / 2, 0);
    ASSERT_EQ(vec.size(), sz + 1);
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i == sz / 2) {
            ASSERT_EQ(vec[i], 0);
        } else if (i < sz / 2) {
            ASSERT_EQ(vec[i], i + 1);
        } else {
            ASSERT_EQ(vec[i], i);
        }
    }
}

TEST_F(VectorTest, InsertWithResize) {
    size_t cur_cap = vec.capacity();
    for (size_t i = sz; i < cur_cap; ++i) {
        vec.push_back(i + 1);
    }

    size_t pos = vec.size() / 2;
    vec.insert(pos, 0);
    ASSERT_NE(cur_cap, vec.capacity());
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i == vec.size() / 2) {
            ASSERT_EQ(vec[i], 0);
        } else if (i < vec.size() / 2) {
            ASSERT_EQ(vec[i], i + 1);
        } else {
            ASSERT_EQ(vec[i], i);
        }
    }
}

TEST_F(VectorTest, VectorPopBack) {
    vec.pop_back();
    ASSERT_EQ(vec.size(), sz - 1);
    for (size_t i = 0; i < vec.size(); ++i) {
        ASSERT_EQ(vec[i], i + 1);
    }
}

TEST_F(VectorTest, VectorEraseAll) {
    size_t old_cap = vec.capacity();
    vec.erase(0, sz);
    ASSERT_EQ(vec.capacity(), old_cap);
    ASSERT_EQ(vec.size(), 0);
}

TEST_F(VectorTest, VectorEraseFront) {
    size_t old_cap = vec.capacity();
    vec.erase(0, 1);
    ASSERT_EQ(vec.capacity(), old_cap);
    ASSERT_EQ(vec.size(), sz - 1);
    for (size_t i = 0; i < vec.size(); ++i) {
        ASSERT_EQ(vec[i], i + 2);
    }
}

TEST_F(VectorTest, VectorEraseBack) {
    size_t old_cap = vec.capacity();
    vec.erase(sz - 1, sz);
    ASSERT_EQ(vec.capacity(), old_cap);
    ASSERT_EQ(vec.size(), sz - 1);
    for (size_t i = 0; i < vec.size(); ++i) {
        ASSERT_EQ(vec[i], i + 1);
    }
}

TEST_F(VectorTest, VectorEraseMid) {
    size_t old_cap = vec.capacity();
    std::vector<int> a = {1, 2, 5, 6, 7};
    vec.erase(sz / 2 - 1, sz / 2 + 1); // 2 - 4
    ASSERT_EQ(vec.capacity(), old_cap);
    ASSERT_EQ(vec.size(), sz - 2);
    for (size_t i = 0; i < vec.size(); ++i) {
        ASSERT_EQ(vec[i], a[i]);
    }
}

TEST_F(VectorTest, VectorEraseNoneExistingPositions) {
    size_t old_cap = vec.capacity();
    vec.erase(sz + 1, sz + 3); // no effect
    ASSERT_EQ(vec.capacity(), old_cap);
    ASSERT_EQ(vec.size(), sz);
    for (size_t i = 0; i < vec.size(); ++i) {
        ASSERT_EQ(vec[i], i + 1);
    }
}

TEST_F(VectorTest, VectorResizeGreaterThenCurrent) {
    size_t old_cap = vec.capacity();
    size_t old_size = vec.size();
    vec.resize(old_size + old_cap, 0);
    ASSERT_NE(vec.capacity(), old_cap);
    ASSERT_EQ(vec.size(), old_size + old_cap);
    for (size_t i = 0; i < old_size; ++i) {
        ASSERT_EQ(vec[i], i + 1);
    }
    for (size_t i = old_size; i < vec.size(); ++i) {
        ASSERT_EQ(vec[i], 0);
    }
}

TEST_F(VectorTest, VectorResizeEqualCurrent) {
    size_t old_cap = vec.capacity();
    size_t old_size = vec.size();
    vec.resize(old_size, 0); // no effect
    ASSERT_EQ(vec.capacity(), old_cap);
    ASSERT_EQ(vec.size(), old_size);
    for (size_t i = 0; i < old_size; ++i) {
        ASSERT_EQ(vec[i], i + 1);
    }
}

TEST_F(VectorTest, VectorResizeLessThenCurrent) {
    size_t old_cap = vec.capacity();
    size_t old_size = vec.size();
    vec.resize(old_size - 4, 0); // reducing
    ASSERT_EQ(vec.capacity(), old_cap);
    ASSERT_EQ(vec.size(), old_size - 4);
    for (size_t i = 0; i < old_size - 4; ++i) {
        ASSERT_EQ(vec[i], i + 1);
    }
}

TEST(VectorComparisonTest, SpaceshipOperator) {
    Vector<int> vec1({1, 2, 3, 4, 5});
    Vector<int> vec2({1, 2, 3, 4, 6});  
    Vector<int> vec3({1, 2, 3, 4, 5});  
    Vector<int> vec4({1, 2, 3});        

    // vec1 < vec2
    ASSERT_TRUE((vec1 <=> vec2) == std::strong_ordering::less);

    // vec2 > vec1
    ASSERT_TRUE((vec2 <=> vec1) == std::strong_ordering::greater);

    // vec1 == vec3
    ASSERT_TRUE((vec1 <=> vec3) == std::strong_ordering::equal);

    // vec1 > vec4 
    ASSERT_TRUE((vec1 <=> vec4) == std::strong_ordering::greater);

    // vec4 < vec1
    ASSERT_TRUE((vec4 <=> vec1) == std::strong_ordering::less);
}


TEST(VectorComparisonTest, EqualOperator) {
    Vector<int> vec1({1, 2, 3, 4, 5});
    Vector<int> vec2({1, 2, 3, 4, 6});  
    Vector<int> vec3({1, 2, 3, 4, 5});         

    // vec1 < vec2
    ASSERT_TRUE((vec1 == vec2) == false);

    // vec2 > vec1
    ASSERT_TRUE((vec3 == vec1) == true);
}


TEST_F(VectorTest, ShrinkToFit) {
    Vector<int> vec({1, 2, 3, 4, 5});

    ASSERT_EQ(vec.size(), 5);
    ASSERT_GE(vec.capacity(), 5);

    vec.reserve(20);
    ASSERT_EQ(vec.size(), 5);
    ASSERT_EQ(vec.capacity(), 20);

    vec.shrink_to_fit();
    ASSERT_EQ(vec.size(), 5);
    ASSERT_EQ(vec.capacity(), 5);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}