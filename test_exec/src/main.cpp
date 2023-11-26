#include <iostream>
#include "Util.h"
#include <csignal>
#include <spdlog/spdlog.h>

int main()
{
    util::handle_signal();
    spdlog::info("hello world");
    return 0;
}