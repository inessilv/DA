cmake_minimum_required(VERSION 3.20)
project(Da_T1)

set(CMAKE_CXX_STANDARD 14)

# Build the Google tests
set(GOOGLETEST_PATH lib/googletest-master)
add_subdirectory(${GOOGLETEST_PATH})

file(GLOB CENARIOS_FILES CONFIGURE_DEPENDS "Cenarios/*.cpp")

add_executable(Cenarios main.cpp ${CENARIOS_FILES})

