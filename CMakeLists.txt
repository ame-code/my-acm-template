cmake_minimum_required(VERSION 4.0)

project(acm-template)

install(DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include/acm/" DESTINATION include)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/base.h" DESTINATION include)