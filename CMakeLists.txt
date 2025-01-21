cmake_minimum_required(VERSION 3.14) # Проверка версии CMake.
# Если версия установленной программы
# старее указаной, произойдёт аварийный выход.


include(FindPkgConfig)
set(CMAKE_FIND_FRAMEWORK LAST)

#-----------------------------------------------------------------------
project(mainPro)
set(TARGET_EXE ${PROJECT_NAME})
message("Cmake pro: " ${TARGET_EXE})

#set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)


# Specify the configuration file from which the header file will be generated
#configure_file (config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h @ONLY)

#Пример сообщения
string(TIMESTAMP testProjectBuild "%Y%m%d%H%M")
message(${TARGET_EXE} " buld timeStamp: "  ${testProjectBuild})

pkg_search_module(DBUS_CXX REQUIRED dbus-c++-1)
pkg_search_module(JSONCPP REQUIRED jsoncpp)


set (HPP_INCLUDES_DIR ${TARGET_EXE})
set (CPP_SOURCES ${TARGET_EXE}/${TARGET_EXE}.cpp
${TARGET_EXE}/procStarter.cpp
)

#сначала add_executable
add_executable(${TARGET_EXE} ${CPP_SOURCES}) # Исполняемый файл

#затем опции
target_compile_options(${TARGET_EXE} PRIVATE
            ${DBUS_CXX_CFLAGS}
            ${JSONCPP_CFLAGS}
)

target_include_directories(${TARGET_EXE} PRIVATE ${HPP_INCLUDES_DIR})


#-----------------------------------------------------------------------
project(serviceServer)
set(TARGET_EXE ${PROJECT_NAME})
message("Cmake pro: " ${TARGET_EXE})



# Specify the configuration file from which the header file will be generated
#configure_file (config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h @ONLY)

#Пример сообщения
string(TIMESTAMP testProjectBuild "%Y%m%d%H%M")
message(${TARGET_EXE} " buld timeStamp: "  ${testProjectBuild})

pkg_search_module(DBUS_CXX REQUIRED dbus-c++-1)

set (HPP_INCLUDES_DIR ${TARGET_EXE})
set (CPP_SOURCES ${TARGET_EXE}/${TARGET_EXE}.cpp
${TARGET_EXE}/DbusServer.cpp)

set(${TARGET_EXE}-adaptor echo-introspect)
add_custom_target(convert-adaptor ALL
        COMMAND dbusxx-xml2cpp ${${TARGET_EXE}-adaptor}.xml --adaptor=${${TARGET_EXE}-adaptor}.h
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_EXE}
)
# add_custom_command(
#     OUTPUT echo-introspect.h
#     COMMAND dbusxx-xml2cpp ${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_EXE}/echo-introspect.xml --proxy=${TARGET_EXE}/echo-introspect.xml
#     DEPENDS ${TARGET_EXE}/echo-introspect.xml
#     COMMENT "Generating D-Bus Notifications proxy interface"
#    )


#сначала add_executable
add_executable(${TARGET_EXE} ${CPP_SOURCES}) # Исполняемый файл

#затем опции
target_compile_options(${TARGET_EXE} PRIVATE
            ${DBUS_CXX_CFLAGS}
)


target_include_directories(${TARGET_EXE} PRIVATE ${HPP_INCLUDES_DIR})

target_link_libraries(${TARGET_EXE}
${DBUS_CXX_LIBRARIES}
pthread
)
# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

#-----------------------------------------------------------------------
project(serviceClient)
set(TARGET_EXE ${PROJECT_NAME})
message("Cmake pro: " ${TARGET_EXE})



# Specify the configuration file from which the header file will be generated
#configure_file (config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h @ONLY)

#Пример сообщения
string(TIMESTAMP testProjectBuild "%Y%m%d%H%M")
message(${TARGET_EXE} " buld timeStamp: "  ${testProjectBuild})

pkg_search_module(DBUS_CXX REQUIRED dbus-c++-1)
pkg_search_module(JSONCPP REQUIRED jsoncpp)

set (HPP_INCLUDES_DIR ${TARGET_EXE})
set (CPP_SOURCES ${TARGET_EXE}/${TARGET_EXE}.cpp
${TARGET_EXE}/DbusClient.cpp)


set(${TARGET_EXE}-converter echo-introspect)
add_custom_target(convert ALL
        COMMAND dbusxx-xml2cpp ${${TARGET_EXE}-converter}.xml --proxy=${${TARGET_EXE}-converter}.h
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_EXE}
)
# add_custom_command(
#     OUTPUT echo-introspect.h
#     COMMAND dbusxx-xml2cpp ${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_EXE}/echo-introspect.xml --proxy=${TARGET_EXE}/echo-introspect.xml
#     DEPENDS ${TARGET_EXE}/echo-introspect.xml
#     COMMENT "Generating D-Bus Notifications proxy interface"
#    )


#сначала add_executable
add_executable(${TARGET_EXE} ${CPP_SOURCES}) # Исполняемый файл

#затем опции
target_compile_options(${TARGET_EXE} PRIVATE
            ${DBUS_CXX_CFLAGS}
            ${JSONCPP_CFLAGS}
)


target_include_directories(${TARGET_EXE} PRIVATE ${HPP_INCLUDES_DIR})

target_link_libraries(${TARGET_EXE}
${DBUS_CXX_LIBRARIES}
pthread
)
# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

#-----------------------------------------------------------------------
project(desktopNotifyer)
set(TARGET_EXE ${PROJECT_NAME})
message( "Cmake pro: " ${TARGET_EXE})



# Specify the configuration file from which the header file will be generated
#configure_file (config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h @ONLY)

#Пример сообщения
string(TIMESTAMP testProjectBuild "%Y%m%d%H%M")
message(${TARGET_EXE} " buld timeStamp: "  ${testProjectBuild})

pkg_search_module(DBUS_CXX REQUIRED dbus-c++-1)
pkg_search_module(JSONCPP REQUIRED jsoncpp)


set (HPP_INCLUDES_DIR ${TARGET_EXE} ${DBUS_CXX_INCLUDE_DIRS})
set (CPP_SOURCES ${TARGET_EXE}/${TARGET_EXE}.cpp
${TARGET_EXE}/dbus_con.cpp
)



#сначала add_executable
add_executable(${TARGET_EXE} ${CPP_SOURCES}) # Исполняемый файл

target_include_directories(${TARGET_EXE} PRIVATE ${HPP_INCLUDES_DIR})

#затем опции
target_compile_options(${TARGET_EXE} PRIVATE
            ${DBUS_CXX_CFLAGS}
            ${JSONCPP_CFLAGS}
)

target_link_libraries(${TARGET_EXE}
            ${DBUS_CXX_LIBRARIES}
)


#-----------------------------------------------------------------------)
add_subdirectory(dBusService)