#ifndef RETURN_CODE_H
#define RETURN_CODE_H

#include <stdint.h>

/*
 * 0 - Success
 * 1-100 - System 
 */
typedef int32_t ErrorCode;

/*
enum ErrorCode {
    GLOBAL_SUCCESS = 0,
    GLOBAL_FAIL = -1,
    GLOBAL_NOT_IMPLEMENTED = -2,
    GLOBAL_NULLPTR_INPUT = -3
};

class ReturnCode {

public:
    ReturnCode(ErrorCode code, std::string msg) : _errCode(code), _errMsg(msg){}
    ReturnCode() : _errCode(GLOBAL_SUCCESS), _errMsg("NO ERROR"){}

    //void operator = (ReturnCode rc);
    bool operator == (int rc) { return _errCode == rc; };
    operator bool() { return _errCode != GLOBAL_SUCCESS; };
    const char* string() { return _errMsg.c_str(); };

private:
    ErrorCode _errCode;
    std::string _errMsg;
};
*/

#define SUCCESS 0
#define NOT_IMPLEMENTED 2
#define NULLPTR_INPUT 3
//#define CHECK_CODE(rc) if( rc != SUCCESS ) { std::cerr << rc << std::endl; return false; } else 

#endif