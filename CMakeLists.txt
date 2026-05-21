cmake_minimum_required(VERSION 4.0)

install(DIRECTORY include/ 
    DESTINATION ${CMAKE_INSTALL_PREFIX}/reed
)

message("prefix: ${CMAKE_INSTALL_PREFIX}")
message("prefix: ${CMAKE_INSTALL_INCLUDEDIR}")