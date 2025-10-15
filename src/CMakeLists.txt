cmake_minimum_required(VERSION 3.16)

project(MazeCPP VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        view/View.cpp
        view/View.h
)

file(GLOB_RECURSE SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/common/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/common/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/view/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/view/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/model/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/model/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/model/generation_strategy/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/model/generation_strategy/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/model/generation_strategy/generation_config/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/model/generation_strategy/generation_config/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/model/path_finder/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/model/path_finder/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/controller/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/controller/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/common/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/model/file_worker/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/model/file_worker/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/model/error_handler/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/model/error_handler/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/model/randomizer/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/model/randomizer/*.cpp"
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/view/
    ${CMAKE_CURRENT_SOURCE_DIR}/model/
    ${CMAKE_CURRENT_SOURCE_DIR}/model/generation_strategy/
    ${CMAKE_CURRENT_SOURCE_DIR}/model/generation_strategy/generation_config/
    ${CMAKE_CURRENT_SOURCE_DIR}/model/path_finder/
    ${CMAKE_CURRENT_SOURCE_DIR}/controller/
    ${CMAKE_CURRENT_SOURCE_DIR}/common/
    ${CMAKE_CURRENT_SOURCE_DIR}/model/file_worker
    ${CMAKE_CURRENT_SOURCE_DIR}/model/error_handler
    ${CMAKE_CURRENT_SOURCE_DIR}/model/randomizer
)

message(STATUS "Собранные исходники:")
foreach(file ${SOURCES})
  message(STATUS "  ${file}")
endforeach()

add_executable(MazeCPP
  main.cpp
  ${SOURCES}
)


target_link_libraries(MazeCPP PRIVATE Qt6::Widgets)


set_target_properties(MazeCPP PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS MazeCPP
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MazeCPP)
endif()
