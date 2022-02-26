cmake_minimum_required(VERSION 3.21)
project(TreeFire)

set(CMAKE_CXX_STANDARD 14)

add_executable(TreeFire main.cpp src/Arena.cpp headers/Arena.h src/SFMLHandling.cpp headers/SFMLHandling.h src/Field.cpp headers/Field.h)


set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR D:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(headers /usr/include d:/SFML/include)
target_link_libraries(TreeFire sfml-system sfml-window sfml-graphics sfml-audio)