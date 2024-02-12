cmake_minimum_required(VERSION 3.20)
project(smtm)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(src SRC_DIR)
aux_source_directory(deps/getopt GETOPT_DIR)
add_executable(${PROJECT_NAME} ${SRC_DIR} ${GETOPT_DIR})

find_package(lua REQUIRED)
find_package(inih REQUIRED)
target_link_libraries(${PROJECT_NAME} lua::lua inih::inih)
