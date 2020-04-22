cmake_minimum_required(VERSION 3.1)
project(GUIprimes)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(wxWidgets_USE_DEBUG ON)
set(wxWidgets_USE_UNICODE ON)

include(${'wx-config --libs all'})
add_executable(GUIprimes
        cApp.cpp
        cApp.h
        cMain.cpp
        cMain.h
        messages.cpp
        messages.h
        utility.cpp
        utility.h)		

