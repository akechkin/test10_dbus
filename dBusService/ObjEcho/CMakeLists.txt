cmake_minimum_required(VERSION 3.14) # Проверка версии CMake.
# Если версия установленной программы
# старее указаной, произойдёт аварийный выход.

project(ObjEcho)
set(TARGET_EXE ${PROJECT_NAME})


set(${TARGET_EXE}_INPUT_XML echo-introspect.xml)
set(${TARGET_EXE}_OUTPUT_H ${TARGET_EXE}-adaptor.h)

add_custom_target(convert-adaptor-${TARGET_EXE} ALL
        COMMAND dbusxx-xml2cpp ${${TARGET_EXE}_INPUT_XML} --adaptor=${${TARGET_EXE}_OUTPUT_H}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# add_custom_command(
#     OUTPUT echo-introspect.h
#         COMMAND dbusxx-xml2cpp ${${TARGET_EXE}_INPUT_XML} --adaptor=${${TARGET_EXE}_OUTPUT_H}
#         DEPENDS ${${TARGET_EXE}_INPUT_XML}
#     COMMENT "------------ Generating D-Bus Notifications adaptor interface ----------"
#    )


