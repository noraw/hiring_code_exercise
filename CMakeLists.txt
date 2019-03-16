cmake_minimum_required (VERSION 3.0)
project (CodeExercise)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# defaulting release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

if(WIN32)
  list(APPEND CMAKE_PREFIX_PATH "C:/Qt/5.9/msvc2015_64" "C:/Qt/5.9.1/msvc2017_64")
elseif(APPLE)
  list(APPEND CMAKE_PREFIX_PATH "/Users/norawillett/Qt/5.12.1/clang_64")
  #list(APPEND CMAKE_PREFIX_PATH "/usr/local/opt/qt5")
endif()

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

mark_as_advanced(Qt5Core_DIR)
mark_as_advanced(Qt5Gui_DIR)
mark_as_advanced(Qt5Widgets_DIR)

qt5_wrap_cpp(CodeExercise_MOC_SRC
  include/glwidget.hpp
  include/window.hpp
  include/mainwindow.hpp
  )

add_executable(CodeExercise
  src/glwidget.cpp
  src/main.cpp
  src/window.cpp
  src/mainwindow.cpp
  src/logo.cpp
  src/uv_sphere.cpp
  ${CodeExercise_MOC_SRC}
  )

target_include_directories(CodeExercise PUBLIC include)
target_link_libraries(CodeExercise PUBLIC Qt5::Widgets Qt5::Core)

