#include "Exception.h"
#include <sstream>
Exception::Exception(int lineNum, const char *filePath, const char* errType, const char *errInfo)
    :
    m_lineNum(lineNum),
    m_filePath(filePath),
    m_errType(errType),
    m_errInfo(errInfo)
{
}

const char *Exception::what() const noexcept
{
    std::stringstream ss;
    ss << "An exception was caugth while program is running" << std::endl
       << "File: " << m_filePath << std::endl
       << "Line: " << m_lineNum << std::endl
       << "Error Type: " << m_errType << std::endl
       << "Error Info: " << m_errInfo << std::endl;
    return ss.str().c_str();
}

int Exception::GetLine() const noexcept
{
    return m_lineNum;
}

const std::string &Exception::GetFilePath() const noexcept
{
    return m_filePath;
}

const std::string &Exception::GetErrInfo() const noexcept
{
    return m_errInfo;
}

const std::string &Exception::GetErrType() const noexcept
{
    return m_errType;
}
