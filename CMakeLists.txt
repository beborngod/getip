cmake_minimum_required(VERSION 3.5)

project(getip LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.73.0 REQUIRED COMPONENTS system thread regex program_options)

add_executable(getip ParceSocket.cxx main.cxx)

target_link_libraries(getip PUBLIC Boost::system Boost::thread Boost::regex Boost::program_options)