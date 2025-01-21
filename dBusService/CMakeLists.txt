cmake_minimum_required(VERSION 3.14) # Проверка версии CMake.
# Если версия установленной программы
# старее указаной, произойдёт аварийный выход.


include(FindPkgConfig)
set(CMAKE_FIND_FRAMEWORK LAST) # правильные пути include

#-----------------------------------------------------------------------
project(dBusService)
set(TARGET_EXE ${PROJECT_NAME})
message("Cmake pro: " ${TARGET_EXE})

pkg_search_module(DBUS_CXX REQUIRED dbus-c++-1)
pkg_search_module(X11_LIB REQUIRED x11)
pkg_search_module(LIBSYSTEMD REQUIRED IMPORTED_TARGET libsystemd)

#Generate xml to .h adaptor
add_subdirectory(ObjEcho)
add_subdirectory(ObjKeyboard)

set(HPP_INCLUDES_DIR
        ObjEcho
        Logger
        ../mainPro
)
set(CPP_SOURCES
        ${TARGET_EXE}.cpp
        ObjEcho/ObjEcho.cpp
        ObjKeyboard/ObjKeyboard.cpp
        ObjKeyboard/KeyboardDriver/captureKeyboard.c
        Logger/Logger.c
        ../mainPro/procStarter.cpp
)



#сначала add_executable
add_executable(${TARGET_EXE} ${CPP_SOURCES}) # Исполняемый файл

#затем опции
target_compile_options(${TARGET_EXE} PRIVATE
            ${DBUS_CXX_CFLAGS}
            ${X11_LIB_CFLAGS}
)


target_include_directories(${TARGET_EXE} PRIVATE ${HPP_INCLUDES_DIR})

target_link_libraries(${TARGET_EXE}
${DBUS_CXX_LIBRARIES}
${X11_LIB_LIBRARIES}
pthread
PkgConfig::LIBSYSTEMD
)
# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
