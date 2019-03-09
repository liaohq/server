aux_source_directory(. SRC_DIR )
#include_directories("../")
#include_directories("../../")
set(INCLUDE_DIR	"."  )

#Loop Dir
foreach(INCLUDE_DIR ${INCLUDE_DIR} )
	file(GLOB_RECURSE CURRENT_HEADERS ${INCLUDE_DIR}/*.h )
endforeach()

add_library(LuaLib ${SRC_DIR} ${CURRENT_HEADERS})

get_cmake_property(LAST_CMAKE_LIBRARY_OUTPUT_DIR CMAKE_LIBRARY_OUTPUT_DIRECTORY)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../Common/Luaclib/ )
add_library(mylua SHARED ${SRC_DIR} ${CURRENT_HEADERS})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LAST_CMAKE_LIBRARY_OUTPUT_DIR} )

