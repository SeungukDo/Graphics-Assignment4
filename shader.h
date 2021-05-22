#ifndef _SHADER_H_
#define _SHADER_H_

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#include <GLFW/glfw3.h>
#else
#include <GL/glew.h>
#include <GL/GL.h>
#endif
//#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "objloader.hpp"
#pragma warning(disable:4996)

GLuint VBO;
GLuint plane_buffer;
GLuint plane_normal;
GLuint plane_buffer2;
GLuint plane_normal2;
GLuint grid_buffer;
GLuint planet_buffer;
GLuint planet_normal;
GLuint WIN;
GLuint LOSE;
GLuint VAO;
GLuint EBO;
GLuint shaderProgram;

extern std::vector<glm::vec3> vertices_player;
extern std::vector<glm::vec2> uvs_player;
extern std::vector<glm::vec3> normals_player; // Won't be used at the moment.
extern std::vector<glm::vec3> vertices_enemy;
extern std::vector<glm::vec2> uvs_enemy;
extern std::vector<glm::vec3> normals_enemy; // Won't be used at the moment.
extern std::vector<glm::vec3> vertices_planet;
extern std::vector<glm::vec2> uvs_planet;
extern std::vector<glm::vec3> normals_planet; // Won't be used at the moment.
extern std::vector<glm::vec3> vertices_grid;
extern std::vector<glm::vec3> vertices_player_bullets;
extern std::vector<glm::vec3> winwin;
extern std::vector<glm::vec3> loselose;

static char* readShaderSource(const char* shaderFile) {
    std::ifstream myfile(shaderFile);
    myfile.seekg(0, std::ios::end);
    size_t size = myfile.tellg();
    std::string buffer(size, ' ');
    myfile.seekg(0);
    myfile.read(&buffer[0], size);

    char* cstr = new char[buffer.length()];
    strcpy(cstr, buffer.c_str());

    return cstr;
}

void InitBuffer() {

    // Airplane
    loadOBJ("../FA-18F.obj", vertices_player, uvs_player, normals_player);
    loadOBJ("../FA-18F.obj", vertices_enemy, uvs_enemy, normals_enemy);
    loadOBJ("../cloud.obj", vertices_planet, uvs_planet, normals_planet);

    GLfloat vertices[] =
    {
        -1.f, 1.f, -1.f,    // 0
        -1.f, 1.f, 1.f,     // 1
        1.f, 1.f, -1.f,     // 2
        1.f, 1.f, 1.f,      // 3
        -1.f, -1.f, -1.f,   // 4
        -1.f, -1.f, 1.f,    // 5
        1.f, -1.f, -1.f,    // 6
        1.f, -1.f, 1.f      // 7
    };
    winwin.push_back(glm::vec3(0.3, 0.0, 0.6));
    winwin.push_back(glm::vec3(0.325, 0.0, 0.5));
    winwin.push_back(glm::vec3(0.325, 0.0, 0.5));
    winwin.push_back(glm::vec3(0.35, 0.0, 0.6));
    winwin.push_back(glm::vec3(0.35, 0.0, 0.6));
    winwin.push_back(glm::vec3(0.375, 0.0, 0.5));
    winwin.push_back(glm::vec3(0.375, 0.0, 0.5));
    winwin.push_back(glm::vec3(0.4, 0.0, 0.6));

    winwin.push_back(glm::vec3(0.5, 0.0, 0.6));
    winwin.push_back(glm::vec3(0.5, 0.0, 0.5));

    winwin.push_back(glm::vec3(0.475, 0.0, 0.6));
    winwin.push_back(glm::vec3(0.525, 0.0, 0.6));

    winwin.push_back(glm::vec3(0.475, 0.0, 0.5));
    winwin.push_back(glm::vec3(0.525, 0.0, 0.5));

    winwin.push_back(glm::vec3(0.6, 0.0, 0.5));
    winwin.push_back(glm::vec3(0.6, 0.0, 0.6));
    winwin.push_back(glm::vec3(0.6, 0.0, 0.6));
    winwin.push_back(glm::vec3(0.675, 0.0, 0.5));
    winwin.push_back(glm::vec3(0.675, 0.0, 0.5));
    winwin.push_back(glm::vec3(0.675, 0.0, 0.6));

    GLfloat win_letters[] = {
        0.3, 0.0, 0.6,
        0.325, 0.0, 0.5,
        0.325, 0.0, 0.5,
        0.35, 0.0, 0.6,
        0.35, 0.0, 0.6,
        0.375, 0.0, 0.5,
        0.4, 0.0, 0.6,

        0.5, 0.0, 0.6,
        0.5, 0.0, 0.5,

        0.475, 0.0, 0.6,
        0.525, 0.0, 0.6,

        0.475, 0.0, 0.5,
        0.525, 0.0, 0.5,

        0.6, 0.0, 0.5,
        0.6, 0.0, 0.6,
        0.6, 0.0, 0.6,
        0.675, 0.0, 0.5,
        0.675, 0.0, 0.5,
        0.675, 0.0, 0.6
    };

    loselose.push_back(glm::vec3(0.25, 0.0, 0.6));
    loselose.push_back(glm::vec3(0.25, 0.0, 0.5));
    loselose.push_back(glm::vec3(0.25, 0.0, 0.5));
    loselose.push_back(glm::vec3(0.325, 0.0, 0.5));

    loselose.push_back(glm::vec3(0.4, 0.0, 0.6));
    loselose.push_back(glm::vec3(0.4, 0.0, 0.5));
    loselose.push_back(glm::vec3(0.4, 0.0, 0.5));
    loselose.push_back(glm::vec3(0.475, 0.0, 0.5));
    loselose.push_back(glm::vec3(0.475, 0.0, 0.5));
    loselose.push_back(glm::vec3(0.475, 0.0, 0.6));
    loselose.push_back(glm::vec3(0.475, 0.0, 0.6));
    loselose.push_back(glm::vec3(0.4, 0.0, 0.6));

    loselose.push_back(glm::vec3(0.625, 0.0, 0.6));
    loselose.push_back(glm::vec3(0.55, 0.0, 0.6));
    loselose.push_back(glm::vec3(0.55, 0.0, 0.6));
    loselose.push_back(glm::vec3(0.55, 0.0, 0.55));
    loselose.push_back(glm::vec3(0.55, 0.0, 0.55));
    loselose.push_back(glm::vec3(0.625, 0.0, 0.55));
    loselose.push_back(glm::vec3(0.625, 0.0, 0.55));
    loselose.push_back(glm::vec3(0.625, 0.0, 0.5));
    loselose.push_back(glm::vec3(0.625, 0.0, 0.5));
    loselose.push_back(glm::vec3(0.55, 0.0, 0.5));

    loselose.push_back(glm::vec3(0.775, 0.0, 0.6));
    loselose.push_back(glm::vec3(0.7, 0.0, 0.6));
    loselose.push_back(glm::vec3(0.7, 0.0, 0.6));
    loselose.push_back(glm::vec3(0.7, 0.0, 0.5));
    loselose.push_back(glm::vec3(0.7, 0.0, 0.5));
    loselose.push_back(glm::vec3(0.775, 0.0, 0.5));

    loselose.push_back(glm::vec3(0.7, 0.0, 0.55));
    loselose.push_back(glm::vec3(0.775, 0.0, 0.55));

    GLfloat lose_letters[] = {
        0.25, 0.0, 0.6,
        0.25, 0.0, 0.5,
        0.25, 0.0, 0.5,
        0.325, 0.0, 0.5,

        0.4, 0.0, 0.6,
        0.4, 0.0, 0.5,
        0.4, 0.0, 0.5,
        0.475, 0.0, 0.5,
        0.475, 0.0, 0.5,
        0.475, 0.0, 0.6,
        0.475, 0.0, 0.6,
        0.4, 0.0, 0.6,

        0.625, 0.0, 0.6,
        0.55, 0.0, 0.6,
        0.55, 0.0, 0.6,
        0.55, 0.0, 0.55,
        0.55, 0.0, 0.55,
        0.625, 0.0, 0.55,
        0.625, 0.0, 0.55,
        0.625, 0.0, 0.5,
        0.625, 0.0, 0.5,
        0.55, 0.0, 0.5,

        0.775, 0.0, 0.6,
        0.7, 0.0, 0.6,
        0.7, 0.0, 0.6,
        0.7, 0.0, 0.5,
        0.7, 0.0, 0.5,
        0.775, 0.0, 0.5,

        0.7, 0.0, 0.55,
        0.775, 0.0, 0.55
    };

    GLuint indices[] = {  // note that we start from 0!
        0, 1, 2,
        1, 2, 3,

        4, 5, 6,
        5, 6, 7,

        0, 2, 4,
        2, 4, 6,

        1, 5, 3,
        3, 5, 7,

        0, 1, 4,
        1, 4, 5,

        2, 3, 6,
        3, 6, 7
    };

    float iii = -5;
    while (iii <= 10) {
        vertices_grid.push_back(glm::vec3(iii, -0.1, -5.f));
        vertices_grid.push_back(glm::vec3(iii, -0.1, 10.f));
        iii += 0.1;
    }
    iii = -5;
    while (iii <= 10) {
        vertices_grid.push_back(glm::vec3(-5.f, -0.1, iii));
        vertices_grid.push_back(glm::vec3(10.f, -0.1, iii));
        iii += 0.1;
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &grid_buffer);
    glGenBuffers(1, &plane_buffer);
    glGenBuffers(1, &plane_buffer2);
    glGenBuffers(1, &planet_buffer);
    glGenBuffers(1, &plane_normal);
    glGenBuffers(1, &plane_normal2);
    glGenBuffers(1, &planet_normal);
    glGenBuffers(1, &WIN);
    glGenBuffers(1, &LOSE);

    glBindBuffer(GL_ARRAY_BUFFER, plane_buffer);    //  player
    glBufferData(GL_ARRAY_BUFFER, vertices_player.size() * sizeof(glm::vec3), &vertices_player[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, plane_normal);    //  player
    glBufferData(GL_ARRAY_BUFFER, normals_player.size() * sizeof(glm::vec3), &normals_player[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, plane_buffer2);    //  enemy
    glBufferData(GL_ARRAY_BUFFER, vertices_enemy.size() * sizeof(glm::vec3), &vertices_enemy[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, plane_normal2);    //  enemy
    glBufferData(GL_ARRAY_BUFFER, normals_enemy.size() * sizeof(glm::vec3), &normals_enemy[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, planet_buffer);    //  planet
    glBufferData(GL_ARRAY_BUFFER, vertices_planet.size() * sizeof(glm::vec3), &vertices_planet[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, planet_normal);    //  planet
    glBufferData(GL_ARRAY_BUFFER, normals_planet.size() * sizeof(glm::vec3), &normals_planet[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, grid_buffer);    //  grid
    glBufferData(GL_ARRAY_BUFFER, vertices_grid.size() * sizeof(glm::vec3), &vertices_grid[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, WIN);    //  grid
    glBufferData(GL_ARRAY_BUFFER, winwin.size() * sizeof(glm::vec3), &winwin[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, LOSE);    //  grid
    glBufferData(GL_ARRAY_BUFFER, loselose.size() * sizeof(glm::vec3), &loselose[0], GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void InitShaders() {
    shaderProgram = glCreateProgram();

    GLuint vertexShader;
    GLchar ss[] = "../v_shader.glsl";
    GLchar* str = readShaderSource(ss);

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &str, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR:SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        exit(-1);
    }

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    GLchar ff[] = "../f_shader.glsl";
    GLchar* str2 = readShaderSource(ff);
    glShaderSource(fragmentShader, 1, &str2, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);


    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR:SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR:SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glUseProgram(shaderProgram);
    glLinkProgram(shaderProgram);
}

#endif