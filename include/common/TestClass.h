#pragma once
class TestClass
{
private:
    int a, b, c;
public:
    explicit TestClass(int a, int b, int c)
        :
        a(a),
        b(b),
        c(c)
    {};
    ~TestClass() = default;
};
