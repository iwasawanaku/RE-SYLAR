#ifndef SYLAR_HTTP_HTTP_SERVER_H
#define SYLAR_HTTP_HTTP_SERVER_H

#include<memory>
#include"sylar/tcp_server.h"
#include"http_session.h"
#include"servlet.h"
namespace sylar{
namespace http{

class HttpServer: public TcpServer{
    public:
    typedef std::shared_ptr<HttpServer> ptr;
    HttpServer(bool keepalive=false,
               sylar::IOManager* worker = IOManager::GetThis(),
               sylar::IOManager* accept_worker = IOManager::GetThis());
    ServletDispatch::ptr getServletDispatch() const { return m_dispatch;}
    void setServletDispatch(ServletDispatch::ptr v) { m_dispatch = v;}
    
    protected:
    virtual void handleClient(Socket::ptr client) override;
    private:
    bool m_isKeepalive;
    ServletDispatch::ptr m_dispatch;
};

}
}



#endif


