#ifndef __SYLAR_MACRO_H__
#define __SYLAR_MACRO_H__

#include<string.h>
#include<assert.h>
#include"util.h"

#define SYLAR_ASSERT(X) \
    if(!(X)) { \
        SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "ASSERTION: " << #X \
            << "\nbacktrace:\n" << sylar::BacktraceToString(100, 2, "    "); \
        assert(false); \
    }

#define SYLAR_ASSERT2(X, W) \
    if(!(X)) { \
        SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "ASSERTION: " << #X << " - " << W \
            << "\nbacktrace:\n" << sylar::BacktraceToString(100, 2, "    "); \
        assert(false); \
    }

#endif