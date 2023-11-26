#include "Util.h"
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <unistd.h>
#include <cmath>
#include <csignal>
#include <string>
#include <sstream>
#include <spdlog/spdlog.h>

std::optional<std::string> util::ExecuteCmd::GetLine(const std::string &strCmd)
{
    std::string strResult;
    char resultBuffer[MAX_BUFFER_SIZE] = {0};
    FILE* pfileStream = popen(strCmd.c_str(), "r");
    if (pfileStream == nullptr)
    {
        spdlog::error("popen error {}", strerror(errno));
        return std::nullopt;
    }
    while (fgets(resultBuffer, 128, pfileStream))
    {
        if (strlen(resultBuffer))
        {
            char lastChar = resultBuffer[strlen(resultBuffer)-1];
            resultBuffer[strlen(resultBuffer)-1] = lastChar == '\n' ? '\0' : lastChar;
            break;
        }
    }
    pclose(pfileStream);
    strResult = resultBuffer;
    return strResult;
}

std::optional<std::string> util::ExecuteCmd::GetAllInfo(const std::string &strCmd)
{
    char resultBuffer[MAX_BUFFER_SIZE] = {0};
    std::string strResult;
    FILE* pfileStream = popen(strCmd.c_str(), "r");
    if (pfileStream == nullptr)
    {
        spdlog::error("popen error {}", strerror(errno));
        return std::nullopt;
    }
    while (fgets(resultBuffer, MAX_BUFFER_SIZE, pfileStream))
    {
        if (strlen(resultBuffer))
        {
            strResult += resultBuffer;
        }
    }
    pclose(pfileStream);
    return strResult;
}

void util::handle_quit_signal(int signalNum)
{
    char szCwd[MAX_BUFFER_SIZE] = {0};
    getcwd(szCwd, MAX_BUFFER_SIZE);
    switch (signalNum)
    {
    case SIGSEGV:
        spdlog::error("segment fault, there might be problems in code, gen core[{}/core.{}]", szCwd, getpid());
        // dump_core(szCwd);
        break;
    case SIGABRT:
        spdlog::error("signal abort, there might be problems in code, gen core[{}/core.{}]", szCwd, getpid());
        // dump_core(szCwd);
        break;
    case SIGFPE:
        spdlog::error("floating point exception, gen core[{}/core.{}]", szCwd, getpid());
        // dump_core(szCwd);
        break;
    case SIGBUS:
        spdlog::error("illegal memory access, may be memory alignment error, gen core[{}/core.{}]", szCwd, getpid());
        // dump_core(szCwd);
        break;
    case SIGILL:
        spdlog::error("illegal instruction, there might be problems in code, gen core[{}/core.{}]", szCwd, getpid());
        dump_core(szCwd);
        break;
    case SIGINT:
        spdlog::warn("signal keyboard interrupt, quiting...");
        break;
    case SIGTERM:
        spdlog::warn("signal terminate, quiting...");
        break;
    default:
        spdlog::error("recieving signal %d, stopping the instance", signalNum);
        break;
    }
    exit(1);
}

void util::dump_core(const std::string& szCwd)
{
    // remove the previous core file
    std::stringstream ssRmCoreCmd;
    ssRmCoreCmd << "rm -rf " << szCwd << "/core*";
    system(ssRmCoreCmd.str().c_str());
    // gen the core file by cmd
    std::stringstream ssCoreGenCmd;
    ssCoreGenCmd << "gcore -a -o " << szCwd << "/core " << getpid();
    system(ssCoreGenCmd.str().c_str());
}

void util::handle_signal()
{
    // 段错误信号，可能由对内存的非法访问引起
    signal(SIGSEGV, util::handle_quit_signal);
    // abort信号，可以由assert或abort函数引起
    signal(SIGABRT, util::handle_quit_signal);
    // 除零信号，由对浮点数的非法操作引起
    // 比如某一个数除以0
    signal(SIGFPE, util::handle_quit_signal);
    // 用户中断键信号，一般来说是Ctrl+C
    signal(SIGINT, util::handle_quit_signal);
    // 由kill(1)命令发送的终止信号，如有全局变量
    // 可以在收到这个信号时释放资源
    signal(SIGTERM, util::handle_quit_signal);
    // 非法的内存读取，包括读取到了不对齐的内存
    signal(SIGBUS, util::handle_quit_signal);
    // 进程执行了非法硬件指令
    signal(SIGILL, util::handle_quit_signal);
}

std::vector<std::string> util::split(const std::string &strTarget, const std::string &strPattern)
{
    int last_start_pos = 0;
    std::vector<std::string> vecResult;
    for (size_t i = 0; i < strTarget.length(); i++)
    {
        if (strTarget[i] == strPattern[0])
        {
            if (strTarget.substr(i, strPattern.length()) == strPattern && i != 0)
            {
                auto szTemp = strTarget.substr(last_start_pos, i - last_start_pos);
                szTemp == strPattern ? vecResult.emplace_back("") : vecResult.emplace_back(std::move(szTemp));
                last_start_pos = i + strPattern.length();
            }
        }
    }
    vecResult.push_back(strTarget.substr(last_start_pos, strTarget.length() - last_start_pos));
    return vecResult;
}
std::string util::ParsePath(const std::string& strPath)
{
    int last_start_pos = 0;
    std::string strPathCopy = util::RemoveExtraCharInStr(strPath, '/');
    std::string strResult;
    std::list<std::string> liResult;
    auto checker = [&strPathCopy, &last_start_pos, &liResult](int iCurPos, int iLength){
            auto szTemp = strPathCopy.substr(last_start_pos, iLength);
            if (szTemp == ".." )
            {
                if (liResult.back() != "")
                {
                    liResult.pop_back();
                }
            }
            else if (szTemp == ".")
            {
            }
            else
            {
                liResult.push_back(std::move(szTemp));
            }                
            last_start_pos = iCurPos + 1;
    };
    for (size_t i = 0; i < strPathCopy.length(); i++)
    {   
        if (strPathCopy[i] == '/')
        {
            checker(i, i - last_start_pos);
        }
    }
    checker(last_start_pos, strPathCopy.length() - last_start_pos);   
    for (const auto& i : liResult)
        strResult += i + "/";
    if (strResult != "/")
        strResult.erase(strResult.find_last_not_of("/") + 1);
    return strResult;
}
std::string util::RemoveExtraSpaceInStr(const std::string &origin_str)
{
    bool bAlert = false;
    std::string szResult = "";
    for (auto i : origin_str)
    {
        if (i == '\t')
        {
            i = ' ';
        }
        if (!bAlert && i == ' ')
        {
            szResult += i;
            bAlert = true;
        }
        if (bAlert && i != ' ')
        {
            bAlert = false;
        }
        if (bAlert)
        {
            continue;
        }
        szResult += i;
    }    
    return szResult;
}
std::string util::RemoveExtraCharInStr(const std::string &origin_str, char c)
{
    bool bAlert = false;
    std::string szResult = "";
    for (auto i : origin_str)
    {
        if (!bAlert && i == c)
        {
            szResult += i;
            bAlert = true;
        }
        if (bAlert && i != c)
        {
            bAlert = false;
        }
        if (bAlert)
        {
            continue;
        }
        szResult += i;
    }    
    return szResult;
}

int util::FindStrinString(const std::string &target_str, const std::string &origin_str)
{
	for (size_t i = 0; i + target_str.length() < origin_str.length(); i++)
	{
		std::string temp_str = origin_str.substr(i, target_str.length());
		if (temp_str == target_str)
		{
			return i;
		}
	}
	return -1;
}

bool util::ContainAlphaInString(const std::string &strTarget)
{
    bool bRes = false;
    for (auto i: strTarget)
    {
        if ((bRes = isalpha(i)) != 0)
        {
            break;
        }
    }
    return bRes;
}

unsigned long long util::HexToDec(const std::string &strHex)
{
    std::unordered_map<char, int> umapHex;
    char cHexInit = 'A';
    char cDecInit = '0';
    size_t iHexInit = 10;
    for (size_t i = 0; i < iHexInit; i++)
    {
        umapHex.insert(std::make_pair(cDecInit++, i));
    }
    for (size_t i = iHexInit; i < 16; i++)
    {
        umapHex.insert(std::make_pair(cHexInit++, i));
    }
    unsigned long long iRet = 0;
    int x = strHex.length()-1;
    for (auto i : strHex)
    {
        iRet += umapHex[i] * pow( 16.0,(double)x);
        x--;
    }
    return iRet;
}

std::string util::RemoveCharInString(const std::string &strTarget, char ch)
{
    std::string strRet = "";
    for (auto i : strTarget)
    {
        if (i == ch)
        {
            continue;
        }
        strRet += i;
    }
    return strRet;
}

std::string util::RemoveCharInString(const std::string& strTarget, const std::string& chs)
{
    std::string strRet = "";
    for (auto i : strTarget)
    {
        bool bPass = false;
        for (auto c : chs)
        {
            if (bPass)
            {
               break;
            }
            bPass = bPass || (c == i);
        }
        if (bPass)
        {
            continue;
        }
        strRet += i;
    }
    return strRet;
}