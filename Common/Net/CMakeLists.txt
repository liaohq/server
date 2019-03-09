aux_source_directory(. SRC_DIR )
#include_directories("../")
#include_directories("../../")
set(INCLUDE_DIR	"."  )

#Loop Dir
foreach(INCLUDE_DIR ${INCLUDE_DIR} )
	file(GLOB_RECURSE CURRENT_HEADERS ${INCLUDE_DIR}/*.h )
endforeach()

add_library(NetLib ${SRC_DIR} ${CURRENT_HEADERS})

