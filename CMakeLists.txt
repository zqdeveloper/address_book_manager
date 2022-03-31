cmake_minimum_required(VERSION 3.5)
project(address_book_manager VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)


find_package(Qt6 COMPONENTS Sql REQUIRED)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui REQUIRED)

if(NOT DEFINED ${QXLSX_PARENTPATH})
        set(QXLSX_PARENTPATH ${CMAKE_CURRENT_SOURCE_DIR})
endif(NOT DEFINED ${QXLSX_PARENTPATH})

if(NOT DEFINED ${QXLSX_HEADERPATH})
        set(QXLSX_HEADERPATH ${CMAKE_CURRENT_SOURCE_DIR}/QXlsx/header)
endif(NOT DEFINED ${QXLSX_HEADERPATH})

if(NOT DEFINED ${QXLSX_SOURCEPATH})
        set(QXLSX_SOURCEPATH ${CMAKE_CURRENT_SOURCE_DIR}/QXlsx/source)
endif(NOT DEFINED ${QXLSX_SOURCEPATH})


message("Current Path of QXlsx")
message(${PROJECT_NAME})
message(${QXLSX_PARENTPATH})
message(${QXLSX_HEADERPATH})
message(${QXLSX_SOURCEPATH})

include_directories(${QXLSX_HEADERPATH})

file(GLOB QXLSX_CPP "${QXLSX_SOURCEPATH}/*.cpp")
file(GLOB QXLSX_H "${QXLSX_HEADERPATH}/*.h")

set(SRC_FILES ${QXLSX_CPP})
list(APPEND SRC_FILES ${QXLSX_H})

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp mainwindow.h
        entity/person.h  entity/person.cpp
        db/persondao.h db/persondao.cpp
        window/personinfo.h window/personinfo.cpp
        window/createperson.h window/createperson.cpp
        utils/excelfileutils.h utils/excelfileutils.cpp
)

list(APPEND PROJECT_SOURCES ${SRC_FILES})

add_executable(address_book_manager ${PROJECT_SOURCES})
target_include_directories(address_book_manager PRIVATE  ${QXLSX_HEADERPATH} ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(address_book_manager PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(address_book_manager PRIVATE Qt6::Sql)
target_link_libraries(address_book_manager PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::GuiPrivate)

set_target_properties(address_book_manager PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(address_book_manager)
endif()
