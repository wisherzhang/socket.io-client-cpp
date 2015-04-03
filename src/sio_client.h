//
//  sio_client.h
//
//  Created by Melo Yao on 3/25/15.
//

#ifndef __SIO_CLIENT__H__
#define __SIO_CLIENT__H__
#include <string>
#include <functional>
#include "sio_message.h"
#include "sio_socket.h"

namespace sio {
    
    class client_impl;
    
    class client {
    public:
        enum close_reason
        {
            close_reason_normal,
            close_reason_drop
        };
        
        typedef std::function<void(void)> con_listener;
        
        typedef std::function<void(close_reason const& reason)> close_listener;
        
        typedef std::function<bool(event& ev)> event_filter;
        
        
        client();
        ~client();
        
        //set listeners and event bindings.
        void set_open_listener(con_listener const& l);
        
        void set_fail_listener(con_listener const& l);
        
        void set_close_listener(close_listener const& l);
        
        void clear_con_listeners();
        
        // Client Functions - such as send, etc.
        void connect(const std::string& uri);
        
        void reconnect(const std::string& uri);
        
        socket::ptr const& socket(const std::string& nsp = "");
        
        // Closes the connection
        void close();
        
        void sync_close();
        
        bool opened() const;
        
        std::string const& get_sessionid() const;
        
    private:
        client_impl* m_impl;
    };
    
}


#endif // __SIO_CLIENT__H__
