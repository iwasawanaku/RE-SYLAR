#include"http_session.h"
#include"http_parser.h"
namespace sylar {
namespace http {

HttpSession::HttpSession(Socket::ptr sock, bool owner)
    :SocketStream(sock, owner) 
{}
HttpRequest::ptr HttpSession::recvRequest(){
    HttpRequestParser::ptr parser(new HttpRequestParser);
        uint64_t buff_size = HttpRequestParser::GetHttpRequestBufferSize();
    //uint64_t buff_size = 100;
    std::shared_ptr<char> buffer(
            new char[buff_size], [](char* ptr){
                delete[] ptr;
            });
    char* data = buffer.get();
    int offset = 0;
    do {
        int len = read(data + offset, buff_size - offset);// 从socket流中读取数据到data缓冲区.如果长度小于缓冲区大小,则继续读取
        if(len <= 0) {
            return nullptr;
        }
        len += offset;// 加上上一次剩的
        size_t nparse = parser->execute(data, len);// nparse表示已经解析的字节数
        if(parser->hasError()) {
            return nullptr;
        }
        offset = len - nparse;// 剩余字节数
        if(offset == (int)buff_size) {
            return nullptr;
        }
        if(parser->isFinished()) {
            break;
        }
    } while(true);
    int64_t length = parser->getContentLength();
    if(length > 0) {
        std::string body;
        body.reserve(length);

        if(length >= offset) {
            body.append(data, offset);
        } else {
            body.append(data, length);
        }
        length -= offset;
        if(length > 0) {
            if(readFixSize(&body[body.size()], length) <= 0) {
                return nullptr;
            }
        }
        parser->getData()->setBody(body);
    }
    return parser->getData();
}

int HttpSession::sendResponse(HttpResponse::ptr rsp) {
    std::stringstream ss;
    ss << *rsp;
    std::string data = ss.str();
    return writeFixSize(data.c_str(), data.size());
}

}


}