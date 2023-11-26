#include "TestClass.h"
#include "iostream"
TestClass::TestClass(int a, int b, int c)
    :
    a(a),
    b(b),
    c(c)
{
}

TestClass::TestClass(int a, int b)
    :
    a(a),
    b(b)
{
}

void TestClass::Summarize()
{
    std::cout 
        << "Summary Message for TestClass: \n"
        << "a = " << a << "\n"
        << "b = " << b << "\n"      
        << "c = " << c << "\n";
}
