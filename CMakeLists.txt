cmake_minimum_required(VERSION 3.7)
project(ProjetImgAnal)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(ProjetImgAnal.exe main.cpp)
target_link_libraries(ProjetImgAnal.exe ${OpenCV_LIBS})

add_executable(OpenCvImgDisplay.exe src/imageDisplay.cpp)
target_link_libraries(OpenCvImgDisplay.exe ${OpenCV_LIBS})

add_executable(OpenCvCompareVideo.exe src/compareVideo.cpp)
target_link_libraries(OpenCvCompareVideo.exe ${OpenCV_LIBS})

add_executable(OpenCvWebcam.exe src/webcam.cpp)
target_link_libraries(OpenCvWebcam.exe ${OpenCV_LIBS})

add_executable(FirstProgram.exe src/FirstProgram/main.cpp
        src/FirstProgram/Webcam.cpp
        src/FirstProgram/Webcam.h)
target_link_libraries(FirstProgram.exe ${OpenCV_LIBS})
