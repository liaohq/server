#定义cmake 最低版本
cmake_minimum_required(VERSION 2.8)

#项目名称
set(PROJECT_NAME "Logicserver")
project(${PROJECT_NAME})

#源文件目录
aux_source_directory(. SOURCE_DIR)

# 设置用debug还是release模式。debug允许断点，而release更快
set( CMAKE_BUILD_TYPE Release )

# 设置编译选项
# 允许c++11标准、O3优化、多线程。match选项可避免一些cpu上的问题
# 编译器暂时不支持 -std=c++11 -03 -march=native -g -gstabs+ 优化 
IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -O0 -gdwarf-2 -ldl" )
ENDIF()



###################### 编辑开始 ######################



#依赖库名
set(LIB_SRC  )

#windows系统依赖库名
SET(LIB_SRC_WINDOWS "")

#Linux系统依赖库名
set(LIB_SRC_LINUX  "pthread" "libprotobuf.a" "libuv.a" "libmysqlclient.a" "libhiredis.a" "liblua.a")

#依赖库名(项目子目录库)
list(APPEND LIB_SRC "BaseLib" "NetLib" "MyTestLib" "PoolLib" "TableLib" "SqlLib" "PacketLib" "LuaLib" "DBLib")



#头文件路径
set(INCLUDE_DIR "../Common"
				"." 
				"../Tools/protobuf/include"
				"../Tools/libuv/include"
				"../Tools/mysql/include"
				"../Tools/redis/include"
				"../Tools/lua/include")

#库文件路径
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../Tools/protobuf/lib			
		    ${CMAKE_CURRENT_SOURCE_DIR}/../Tools/libuv/lib
			${CMAKE_CURRENT_SOURCE_DIR}/../Tools/mysql/lib
			${CMAKE_CURRENT_SOURCE_DIR}/../Tools/lua/lib
			${CMAKE_CURRENT_SOURCE_DIR}/../Tools/redis/lib) 

#子目录，以库的形式包含
set(SUB_DIR "../Common/Base"
			"../Common/Net"
			"../Common/Test"
			"../Common/Pool"
			"../Common/Table"
			"../Common/Sql"
			"../Common/Packet"
			"../Common/Lua-Src"
			"../Common/DB"
			)


#宏定义
set(DEFINITIONS "USE_MY_TEST"
				"USE_PROTOBUF"
				"USE_LIBUV"
				"USE_MYSQL"
				"USE_REDIS"
				"_CRT_SECURE_NO_WARNINGS"
				)
				



###################### 编辑结束 ######################

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
	list(APPEND LIB_SRC	${LIB_SRC_LINUX})
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
	list(APPEND LIB_SRC	${LIB_SRC_WINDOWS})
ENDIF()


#需要链接的库文件目录
foreach(LIB_DIR ${LIB_DIR} )
	link_directories(${LIB_DIR})
endforeach()

#需要链接的依赖库
#foreach(LIB_SRC ${LIB_SRC})
#	link_libraries(${LIB_SRC})
#endforeach()

#宏定义
foreach(DEFINITIONS ${DEFINITIONS})
	add_definitions(-D${DEFINITIONS})
endforeach()

#指定头文件路径
include_directories(${CMAKE_SOURCE_DIR}/${INCLUDE_DIR})

#所有文件
SET(ALL_FILES )

#根目录
foreach(INCLUDE_DIR ${INCLUDE_DIR} )
	STRING( REPLACE "../" "" IncludeDirPathName ${INCLUDE_DIR} )
	STRING( REPLACE "." "Main" IncludeDirPathName ${IncludeDirPathName} )
	file(GLOB CURRENT_HEADERS ${CMAKE_SOURCE_DIR}/${INCLUDE_DIR}/*.h ${CMAKE_SOURCE_DIR}/${INCLUDE_DIR}/*.cpp)
	STRING( REPLACE "/" "\\" IncludeDirSubPathName ${IncludeDirPathName})
	source_group(${IncludeDirSubPathName} FILES ${CURRENT_HEADERS})
	list(APPEND ALL_FILES ${CURRENT_HEADERS})
endforeach()

#子目录
foreach(SUB_DIR ${SUB_DIR})
	STRING( REPLACE "../" "" SubPathName ${SUB_DIR} )
	add_subdirectory( ${CMAKE_SOURCE_DIR}/${SUB_DIR} ${SubPathName})

	file(GLOB_RECURSE CURRENT_HEADERS ${CMAKE_SOURCE_DIR}/${SUB_DIR}/*.h ${CMAKE_SOURCE_DIR}/${SUB_DIR}/*.cpp)

	STRING( REPLACE "/" "\\" PathName ${SubPathName})
	source_group(${PathName} FILES ${CURRENT_HEADERS})
	list(APPEND ALL_FILES ${CURRENT_HEADERS})
endforeach()


#source_group("Include" FILES ${CURRENT_HEADERS})
#MESSAGE(${ALL_FILES})
#list(REMOVE_DUPLICATES ALL_FILES)
add_executable(${PROJECT_NAME}  ${ALL_FILES})


#增加静态库或动态库
foreach(LIB_SRC ${LIB_SRC})
	target_link_libraries(${PROJECT_NAME} ${LIB_SRC})
endforeach()



