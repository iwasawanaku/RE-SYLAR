#ifndef __SYLAR_UTIL_H__
#define __SYLAR_UTIL_H__
#include <string>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdint.h>
#include<vector>

namespace sylar {

pid_t GetThreadId();
uint32_t GetFiberId();

void Backtrace(std::vector<std::string>& bt, int size = 64, int skip = 2);// 获取当前调用栈
std::string BacktraceToString(int size = 64, int skip = 2, const std::string& prefix = "");// 获取当前调用栈的字符串形式。
}

#endif
