cmake_minimum_required(VERSION 3.19)
project(graphics_2021)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)

#freeglut 라이브러리 설정
set(GLUT_LIBRARIES libglut.3.dylib)
set(GLUT_INCLUDE_DIRS /usr/local/Cellar/freeglut/3.2.1_1/include)
set(GLUT_LIBRARY_DIRS /usr/local/Cellar/freeglut/3.2.1_1/lib)

#GLEW 라이브러리 설정
set(GLEW_LIBRARIES libGLEW.dylib)
set(GLEW_INCLUDE_DIRS /usr/local/Cellar/glew/2.2.0_1/include)
set(GLEW_LIBRARY_DIRS /usr/local/Cellar/glew/2.2.0_1/lib)

#GLFW 라이브러리 설정
set(GLFW_LIBRARIES libglfw.dylib)
set(GLFW_INCLUDE_DIRS /usr/local/Cellar/glfw/3.3.4/include)
set(GLFW_LIBRARY_DIRS /usr/local/Cellar/glfw/3.3.4/lib)

#GLAD 라이브러리 설정
set(GLAD_INCLUDE_DIRS /usr/local/include)

#GLM 라이브러리 설정
set(GLM_INCLUDE_DIRS /usr/local/Cellar/glm/0.9.9.8/include)

#OPENGL 라이브러리 설정
set(GL_INCLUDE_DIRS /System/Library/Frameworks/OpenGL.framework/Headers)

INCLUDE_DIRECTORIES ( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${GLAD_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GL_INCLUDE_DIRS})
ADD_COMPILE_OPTIONS ( "-g" )

LINK_LIBRARIES( ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES})
LINK_DIRECTORIES ( ${OPENGL_LIBRARY_DIRS} ${GLUT_LIBRARY_DIRS} ${GLEW_LIBRARY_DIRS} ${GLFW_LIBRARY_DIRS})

add_executable(graphics_2021
        objects/bullet.h
        objects/enemy.h
        objects/item.h
        objects/object.h
        objects/player.h
        hit.cpp
        hit.h
        main.cpp
        mode.h
        objloader.cpp
        objloader.hpp
        shader.h
        view.h)
