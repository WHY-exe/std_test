#include <iostream>
#include "Util.h"
#include <csignal>
#include <spdlog/spdlog.h>
#include "TestClass.h"
#include <initializer_list>
#include <windows.h>
#include <unistd.h>
int main()
{
    util::handle_signal();
    TestClass tc1 = TestClass{1, 2, 3};
    tc1.Summarize();
    TestClass tc2 = {1, 2};
    tc2.Summarize();
    std::cout << "Current Process pid is: " << GetCurrentProcessId() << std::endl;
    sleep(60);    
    return 0;
}