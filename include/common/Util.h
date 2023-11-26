#pragma once
#include <string>
#include <vector>
#include <string.h>
#include <list>
#include <optional>
#ifndef MAX_BUFFER_SIZE
#define MAX_BUFFER_SIZE (int)1024
#endif

namespace util
{
    namespace ExecuteCmd
    {
        std::optional<std::string> GetLine(const std::string& strCmd);
        std::optional<std::string> GetAllInfo(const std::string& strCmd);
    };
    void                     handle_quit_signal(int signalNum);
    void                     dump_core(const std::string& szCwd);
    void                     handle_signal();
    std::vector<std::string> split(const std::string& strTarget, const std::string& strPattern);
    std::string              RemoveExtraSpaceInStr(const std::string& origin_str);
    std::string              RemoveExtraCharInStr(const std::string& origin_str, char c);
    std::string              ParsePath(const std::string& strPath);
    
    bool                     ContainAlphaInString(const std::string& strTarget);
    std::string              DecToHex(int iDec);
    unsigned long long       HexToDec(const std::string& strHex);
    std::string              RemoveCharInString(const std::string& strTarget, char ch);
    std::string              RemoveCharInString(const std::string& strTarget, const std::string& chs);
    int                      FindStrinString(const std::string& target_str, const std::string& origin_str);
};