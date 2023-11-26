#pragma once
#include <exception>
#include <string>
#include <cerrno>
#include <cstring>
class Exception : public std::exception
{
public:
    Exception(int lineNum, const char* filePath, const char* errType, const char* errInfo);
    ~Exception() = default;
    const char*        what()        const noexcept override;
    int                GetLine()     const noexcept;
    const std::string& GetFilePath() const noexcept;
    const std::string& GetErrInfo()  const noexcept;
    const std::string& GetErrType()  const noexcept;
private:
    int         m_lineNum;
    std::string m_filePath;
    std::string m_errType;
    std::string m_errInfo;
};