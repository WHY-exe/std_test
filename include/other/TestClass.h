#pragma once
#include "Summary.h"
class TestClass: public Summary
{
private:
    int a,b,c;
public:
    // 默认构造函数
    TestClass() = default;
    // 复制构造函数
    TestClass(const TestClass& lv_rhs) = default;
    TestClass& operator=(const TestClass& lv_rhs) = default;
    // 移动构造函数
    TestClass(TestClass&& rv_rhs) = default;
    TestClass& operator=(TestClass&& rv_rhs) = default;
    // 析构函数
    ~TestClass() = default;
    // explictit 的作用：
    // 不允许使用自动类型转换，形如：
    // TestClass tc = {a,b,c};
    explicit TestClass(int a, int b, int c);
    // TestClass tc = {1, 2}是允许的
    TestClass(int a, int b);

    void Summarize() override;
};
