cmake_minimum_required(VERSION 3.10)
project(GravityGUI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)


add_executable(${PROJECT_NAME} 
	src/main.cpp
	src/GravityModel.h
	src/GravityModel.cpp
	src/Render.h
	src/Render.cpp
	src/Grid.h
	src/Grid.cpp
	src/Cell.h
	src/Cell.cpp
	src/GProfile.h
	src/GProfile.cpp)


set(SFML_DIR "external/SFML-2.6.0/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.6 COMPONENTS graphics audio REQUIRED)
if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(${PROJECT_NAME} sfml-audio sfml-graphics sfml-window sfml-system)
endif()

set_target_properties (${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR}/bin/Debug/)
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR}/bin/Release/)