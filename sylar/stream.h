#ifndef __SYLAR_STREAM_H__
#define __SYLAR_STREAM_H__

#include<memory>
#include<string>
#include"bytearray.h"

namespace sylar{

class Stream{
    public:
    typedef std::shared_ptr<Stream> ptr;
    virtual ~Stream(){}

    virtual int read(void* buffer, size_t length) = 0;
    virtual int read(ByteArray::ptr ba, size_t length) = 0;
    virtual int readFixSize(void* buffer, size_t length);// 确保读取length大小
    virtual int readFixSize(ByteArray::ptr ba, size_t length);// 确保读取length大小
    virtual int write(const void* buffer, size_t length) = 0;
    virtual int write(ByteArray::ptr ba, size_t length) = 0;
    virtual int writeFixSize(const void* buffer, size_t length);// 确保写入length大小
    virtual int writeFixSize(ByteArray::ptr ba, size_t length);// 确保写入length大小

    virtual void close()=0;

};

}


#endif