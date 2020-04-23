cmake_minimum_required(VERSION 3.1)
project(GUIprimes
        DESCRIPTION "Find prime numbers "
        LANGUAGES  CXX)
# set(wxWidgets_CONFIG_EXECUTABLE:FILEPATH=/usr/bin/wx-config)
find_package(wxWidgets REQUIRED base core)
message ("now it located WXwidgets")
include(${wxWidgets_USE_FILE})
add_executable(GUIprimes.exe
        cApp.cpp
        cApp.h
        cMain.cpp
        cMain.h
        messages.cpp
        messages.h
        utility.cpp
        utility.h)		
