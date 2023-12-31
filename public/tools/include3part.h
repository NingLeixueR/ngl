#ifndef INCLUDE_3PART_H
#define INCLUDE_3PART_H

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include <boost/pool/pool.hpp> 
#include <boost/pool/object_pool.hpp>    
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/system/error_code.hpp>
#include <boost/bind/bind.hpp>
#include <boost/date_time.hpp>
#include <ctime>
#include <strstream>
#include <iostream>
#include <string>
#include <mysql.h>

//#include "log.h"

#ifdef WIN32
#define snprintf _snprintf
#endif //WIN32

#endif //INCLUDE_3PART_H