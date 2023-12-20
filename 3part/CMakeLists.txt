cmake_minimum_required(VERSION 2.6)

PROJECT (my3part)

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

SET(BOOST_LIB_SRC ${PROJECT_SOURCE_DIR}/boost/libs)

INCLUDE_DIRECTORIES(3part/boost)
INCLUDE_DIRECTORIES(3part/boost/boost)

#boost lib
AUX_SOURCE_DIRECTORY(${BOOST_LIB_SRC}/regex/src boost_regex_lib_src)
AUX_SOURCE_DIRECTORY(${BOOST_LIB_SRC}/serialization/src boost_serialization_lib_src)
AUX_SOURCE_DIRECTORY(${BOOST_LIB_SRC}/smart_ptr/extras/src boost_smart_ptr_extras_lib_src)
AUX_SOURCE_DIRECTORY(${BOOST_LIB_SRC}/system/src boost_system_lib_src)
AUX_SOURCE_DIRECTORY(${BOOST_LIB_SRC}/test/src boost_test_lib_src)
AUX_SOURCE_DIRECTORY(${BOOST_LIB_SRC}/thread/src boost_thread_lib_src)
AUX_SOURCE_DIRECTORY(${BOOST_LIB_SRC}/atomic/src boost_atomic_lib_src)
AUX_SOURCE_DIRECTORY(${BOOST_LIB_SRC}/chrono/src boost_chrono_lib_src)
AUX_SOURCE_DIRECTORY(${BOOST_LIB_SRC}/date_time/src boost_date_time_lib_src)
AUX_SOURCE_DIRECTORY(${BOOST_LIB_SRC}/exception/src boost_exception_lib_src)
AUX_SOURCE_DIRECTORY(${BOOST_LIB_SRC}/filesystem/src boost_filesystem_lib_src)
AUX_SOURCE_DIRECTORY(${BOOST_LIB_SRC}/mpi/src boost_mpi_lib_src)

IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
AUX_SOURCE_DIRECTORY(${BOOST_LIB_SRC}/thread/src/win32 boost_thread_lib_src2)
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Windows")

IF(CMAKE_SYSTEM_NAME MATCHES "Linux")
AUX_SOURCE_DIRECTORY(${BOOST_LIB_SRC}/thread/src/pthread boost_thread_lib_src2)
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

#AUX_SOURCE_DIRECTORY(${BOOST_LIB_SRC}/thread/src/win32 boost_thread_lib_src2)
SET(BOOST_SRC  
	${boost_regex_lib_src}
	${boost_serialization_lib_src}
	${boost_smart_ptr_extras_lib_src}
	${boost_system_lib_src}
	${boost_test_lib_src}
	${boost_thread_lib_src}
	${boost_thread_lib_src2}
	${boost_atomic_lib_src}
	${boost_chrono_lib_src}
	${boost_date_time_lib_src}
	${boost_exception_lib_src}
	${boost_filesystem_lib_src}
	${boost_mpi_lib_src}
)



IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
ADD_LIBRARY(libboost STATIC ${BOOST_SRC})
#set_target_properties
SET_TARGET_PROPERTIES(libboost PROPERTIES COMPILE_FLAGS "/EHa" )
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Windows")

IF(CMAKE_SYSTEM_NAME MATCHES "Linux")
ADD_LIBRARY(boost STATIC ${BOOST_SRC})
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")



IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
#add_subdirectory(zlib_win)
#add_subdirectory(mysql_win)
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
#add_subdirectory(mysql)

#add_subdirectory(curl)

IF(CMAKE_SYSTEM_NAME MATCHES "Linux")
#add_subdirectory(curl)
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

#IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
#add_subdirectory(curl)
#ENDIF (CMAKE_SYSTEM_NAME MATCHES "Windows")

#add_subdirectory(hiredis_master)




