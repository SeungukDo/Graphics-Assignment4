#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#include <GLFW/glfw3.h>
#else
#include <GL/glew.h>
#include <GL/GL.h>
#endif
//#include <GL/freeglut.h>
#include "shader.h"

#include "objects/player.h"
#include "objects/enemy.h"
#include "objects/bullet.h"
#include "objects/item.h"
#include "mode.h"
#include "hit.h"
#include "view.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const GLuint WIDTH = 800;
const GLuint HEIGHT = 600;
GLFWwindow* window;

Player player = Player();
EnemyList enemy_list = EnemyList();
BulletList player_bullets = BulletList(PLAYER);
BulletList enemy_bullets = BulletList(ENEMY);
ItemList item_list = ItemList();
Gamemode mode = NORMAL;
LineRendering line_rendering = HIDING;
Shading shading = GOURAUD;
Diffuse diffuse = D_DISABLE;
NormalMap normal_map = N_DISABLE;
float planet = 0.0f;
float planet2 = 0.0f;
glm::mat4 dir_light = glm::mat4(1.f);
float light_angle = 0.f;
float applied_light_angle = 0.f;
glm::vec3 point_light = glm::vec3(0.f);

Viewmode view = TPS;
int over = 0;

extern GLuint VBO;
extern GLuint VAO;
extern GLuint EBO;
extern GLuint grid_buffer;
extern GLuint plane_buffer;
extern GLuint plane_buffer2;
extern GLuint planet_buffer;
extern GLuint shaderProgram;
extern GLuint WIN;
extern GLuint LOSE;
GLuint Texture;
GLuint TextureID;

std::vector<glm::vec3> vertices_player;
std::vector<glm::vec2> uvs_player;
std::vector<glm::vec3> normals_player; // Won't be used at the moment.
std::vector<glm::vec3> vertices_enemy;
std::vector<glm::vec2> uvs_enemy;
std::vector<glm::vec3> normals_enemy; // Won't be used at the moment.
std::vector<glm::vec3> vertices_planet;
std::vector<glm::vec2> uvs_planet;
std::vector<glm::vec3> normals_planet; // Won't be used at the moment.
std::vector<glm::vec3> vertices_grid;
std::vector<glm::vec3> vertices_player_bullets;
std::vector<glm::vec3> winwin;
std::vector<glm::vec3> loselose;

void camera_control();
void camera_control2();
void proj_control(int w, int h);
void isWire();
void drawRect(glm::mat4 inn, glm::vec4 color);
void drawPlayer(glm::mat4 inn, glm::vec4 color);
void drawEnemy(glm::mat4 inn, glm::vec4 color);
void drawGrid();
void Planett();
void drawPlanet(glm::mat4 inn, glm::vec4 color);
void determineColor(glm::vec4* player_color, glm::vec4* enemy_color);
void InitTexture();

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

static void display()
{
    isWire();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgram);
    if (over == 0) {
        camera_control();



        Position player_position = player.get_position();
        Position enemy_position = enemy_list.getEnemy().get_position();
        std::vector <Position> player_bullet_positions;
        std::vector <Position> enemy_bullet_positions;
        std::vector<Position> item_positions;
        glm::mat4 inn = glm::mat4(1.f);
        glm::vec4 player_color = glm::vec4(1.f, 1.f, 1.f, 1.f);
        glm::vec4 enemy_color = glm::vec4(1.f, 1.f, 1.f, 1.f);
        int i;
        GLuint MatrixID = glGetUniformLocation(shaderProgram, "transform");

        glm::mat4 ModelMatrix_player = glm::translate(inn, glm::vec3(player_position.x, 0.0f, player_position.y + 0.05)) * glm::scale(inn, glm::vec3(0.03f, 0.03f, 0.03f)) * glm::rotate(inn, 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 ModelMatrix_enemy = glm::translate(inn, glm::vec3(enemy_position.x, 0.0f, enemy_position.y)) * glm::scale(inn, glm::vec3(0.03f, 0.03f, 0.03f));

        determineColor(&player_color, &enemy_color);

        glBindTexture(GL_TEXTURE_2D, Texture);

        // Draw Grid
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, grid_buffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
        drawGrid();

        // Draw Player
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, plane_buffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, plane_normal);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, plane_uv);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);

        drawPlayer(ModelMatrix_player, player_color);

        // Draw Planet
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, planet_buffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, planet_normal);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
        Planett();

        // Draw Enemy
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, plane_buffer2);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, plane_normal2);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, plane_uv2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);

        drawEnemy(ModelMatrix_enemy, enemy_color);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        GLint use_texture_loc = glGetUniformLocation(shaderProgram, "useTexture");
        glUniform1i(use_texture_loc, false);

        // Player Bullet
        player_bullet_positions = player_bullets.get_bullet_positions();
        for (i = 0; i < player_bullet_positions.size(); i++) {
            Position bullet_position = player_bullet_positions[i];
            inn = glm::translate(glm::mat4(1.f), glm::vec3(bullet_position.x, 0.f, bullet_position.y));
            inn = glm::scale(inn, glm::vec3(0.01f, 0.01f, 0.01f));
            drawPlanet(inn, glm::vec4(1.f, 0.5f, 0.f, 1.f));
        }

        // Enemy Bullet
        enemy_bullet_positions = enemy_bullets.get_bullet_positions();
        for (i = 0; i < enemy_bullet_positions.size(); i++) {
            Position bullet_position = enemy_bullet_positions[i];

            inn = glm::translate(glm::mat4(1.f), glm::vec3(bullet_position.x, 0.f, bullet_position.y));
            inn = glm::scale(inn, glm::vec3(0.01f, 0.01f, 0.01f));
            drawPlanet(inn, glm::vec4(1.f, 0.5f, 1.f, 1.f));
        }

        // Item
        item_positions = item_list.get_item_positions();
        for (i = 0; i < item_positions.size(); i++) {
            Position item_position = item_positions[i];

            inn = glm::translate(glm::mat4(1.f), glm::vec3(item_position.x, 0.f, item_position.y));
            inn = glm::scale(inn, glm::vec3(0.01f, 0.01f, 0.01f));
            drawPlanet(inn, glm::vec4(0.1f, 0.1f, 0.1f, 1.f));
        }

        GLint pr_matrix_loc = glGetUniformLocation(shaderProgram, "projection");
        glm::mat4 pr = glm::mat4(1.f);

        int h;
        int w;
        glfwGetWindowSize(window ,&w, &h);

        //GLfloat h = glutGet(GLUT_WINDOW_HEIGHT);
        //GLfloat w = glutGet(GLUT_WINDOW_WIDTH);

        pr = glm::frustum(-0.5, 0.5, -0.5 * h / w, 0.5 * h / w, 0.5, 7.0);
        if (view == FPS) {
            pr = glm::translate(pr, glm::vec3(0.f, 0.3f, 0.4f));
        }
        glUniformMatrix4fv(pr_matrix_loc, 1, GL_FALSE, glm::value_ptr(pr));

        glm::vec4 light_vec = glm::vec4(2.5 - 7.5 * cos(applied_light_angle), abs(7.5 * sin(applied_light_angle)), 0.f, 0.f);
        bool inbool = (shading == GOURAUD);
        GLint amb_vec_loc = glGetUniformLocation(shaderProgram, "AmbientProduct");
        GLint dif_vec_loc = glGetUniformLocation(shaderProgram, "DiffuseProduct");
        GLint spec_vec_loc = glGetUniformLocation(shaderProgram, "SpecularProduct");
        GLint light_vec_loc = glGetUniformLocation(shaderProgram, "LightPosition");
        GLint plight_vec_loc = glGetUniformLocation(shaderProgram, "PLightPosition");
        GLint shi_float_loc = glGetUniformLocation(shaderProgram, "Shininess");
        GLint gr_bool_loc = glGetUniformLocation(shaderProgram, "Gouraud");

        glUniform4f(amb_vec_loc, 1.f, 1.f, 1.f, 1.f);
        glUniform4f(dif_vec_loc, 1.f, 1.f, 1.f, 1.f);
        glUniform4f(spec_vec_loc, 1.f, 1.f, 1.f, 1.f);
        glUniform4f(light_vec_loc, light_vec.x, light_vec.y, light_vec.z, light_vec.a);
        glUniform1f(shi_float_loc, 1.f);
        glUniform4f(plight_vec_loc, point_light.x, point_light.y, point_light.z, 1.f);
        glUniform1f(shi_float_loc, 50.f);
        glUniform1i(gr_bool_loc, inbool);
    }
    else if (over == 1) {
        camera_control2();
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, WIN);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

        glm::mat4 inn = glm::mat4(1.f);
        inn = glm::translate(inn, glm::vec3(3.f, 0.f, 0.5f));
        inn = glm::rotate(inn, glm::radians(180.f), glm::vec3(0.f, 0.f, 1.f));
        GLint tr_matrix_loc = glGetUniformLocation(shaderProgram, "transform");
        GLint vertexC = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexC, 0.f, 0.f, 0.f, 1.f);

        glUniformMatrix4fv(tr_matrix_loc, 1, GL_FALSE, glm::value_ptr(inn));
        glDrawArrays(GL_LINES, 0, winwin.size());
    }
    else {
        camera_control2();
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, LOSE);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

        glm::mat4 inn = glm::mat4(1.f);
        inn = glm::translate(inn, glm::vec3(3.f, 0.f, 1.f));
        inn = glm::rotate(inn, glm::radians(180.f), glm::vec3(0.f, 0.f, 1.f));
        
        GLint tr_matrix_loc = glGetUniformLocation(shaderProgram, "transform");
        GLint vertexC = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexC, 0.f, 0.f, 0.f, 1.f);

        glUniformMatrix4fv(tr_matrix_loc, 1, GL_FALSE, glm::value_ptr(inn));
        glDrawArrays(GL_LINES, 0, loselose.size());
    }
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void reshape(GLFWwindow* window, int w, int h) {
    glViewport(0, 0, w, h);
}

void Init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        if (mode == ALLPASS) mode = NORMAL;
        else mode = ALLPASS;
    } else if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        if (mode == ALLFAIL) mode = NORMAL;
        else mode = ALLFAIL;
    } else if (key == GLFW_KEY_V && action == GLFW_PRESS) {
        view_change();
    } else if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        if (line_rendering == SHOWING) line_rendering = HIDING;
        else line_rendering = SHOWING;
    } else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        if (shading == GOURAUD) shading = PHONG;
        else shading = GOURAUD;
    } else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        if (diffuse == D_ENABLE) diffuse = D_DISABLE;
        else diffuse = D_ENABLE;
    } else if (key == GLFW_KEY_N && action == GLFW_PRESS) {
        if (normal_map == N_ENABLE) normal_map = N_DISABLE;
        else normal_map = N_ENABLE;
    } else if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        player.move_up(0.05);
    } else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
        player.move_down(0.05);
    } else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        player.move_left(0.05);
    } else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        player.move_right(0.05);
    }
}

void timer_func() {
    enemy_list.getEnemy().shoot();
    if (enemy_list.getIndex() != 0) { enemy_list.move_2(); }

    //glutTimerFunc(1300, timer_func, 1);
}

void timer_func2(int a) {
    player_bullets.move_bullets();
    enemy_bullets.move_bullets();
    enemy_list.move();
    item_list.move_items();
    planet += 0.5;
    planet2 += 1;

    dir_light = glm::translate(dir_light, glm::vec3(-5.f, 0.f, 0.f));
    dir_light = glm::rotate(dir_light, glm::radians(applied_light_angle), glm::vec3(0.f, 0.f, 1.f));
    
    light_angle += 180 / 5000;
    applied_light_angle = 180.f - abs(180 - light_angle);

    check_hit();
    check_get_item();
    //glutTimerFunc(10, timer_func2, 1);
}

int main(int argc, char** argv) {
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    window = glfwCreateWindow( WIDTH, HEIGHT, "hello", NULL, NULL);
    if(!window) {
        std::cout <<  "Failed to create window" << std::endl;
        glfwTerminate();
        exit(0);
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, reshape);
#ifndef __APPLE__
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }
#endif
    Init();
    glfwSetKeyCallback(window, keyboard);
    //glutKeyboardFunc(keyboard);
    //glutSpecialFunc(specialkeyboard);
    //glutIdleFunc(idle_func);
    //glutTimerFunc(1300, timer_func, 1);            // Enemy shoots every 500ms
    //glutTimerFunc(10, timer_func2, 1);

    InitBuffer();
    InitShaders();
    InitTexture();


    do {
        glBindTexture(GL_TEXTURE_2D, Texture);
        display();
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
            glfwWindowShouldClose(window) == 0);
    return 0;
}

void camera_control() {
    Position player_position = player.get_position();
    GLint mv_matrix_loc = glGetUniformLocation(shaderProgram, "model_view");
    glm::mat4 mv = glm::mat4(1.f);
    mv = glm::lookAt(glm::vec3(player_position.x, 0.7f, player_position.y - 0.2f), glm::vec3(player_position.x, -0.05f, player_position.y + 1.f), glm::vec3(0.f, 1.f, 0.f));
    glUniformMatrix4fv(mv_matrix_loc, 1, GL_FALSE, glm::value_ptr(mv));
}

void camera_control2() {
    Position player_position = player.get_position();
    GLint mv_matrix_loc = glGetUniformLocation(shaderProgram, "model_view");
    glm::mat4 mv = glm::mat4(1.f);
    mv = glm::lookAt(glm::vec3(2.5, 0.7, 0.0), glm::vec3(2.5, -0.05, 2.5), glm::vec3(0, 0, 1));
    glUniformMatrix4fv(mv_matrix_loc, 1, GL_FALSE, glm::value_ptr(mv));
}

void drawGrid() {
    glm::mat4 inn = glm::mat4(1.f);
    GLint tr_matrix_loc = glGetUniformLocation(shaderProgram, "transform");
    GLint vertexC = glGetUniformLocation(shaderProgram, "ourColor");
    glUniform4f(vertexC, 0.f, 0.f, 0.f, 1.f);
    glUniformMatrix4fv(tr_matrix_loc, 1, GL_FALSE, glm::value_ptr(inn));

    GLint use_texture_loc = glGetUniformLocation(shaderProgram, "useTexture");
    glUniform1i(use_texture_loc, false);

    glDrawArrays(GL_LINES, 0, vertices_grid.size());
}

void drawRect(glm::mat4 inn, glm::vec4 color) {
    GLint tr_matrix_loc = glGetUniformLocation(shaderProgram, "transform");

    glm::mat4 tran = glm::mat4(1.0f);
    tran = glm::translate(tran, glm::vec3(0.f, 0.f, 0.2f));
    tran = glm::scale(tran, glm::vec3(0.2f, 0.2f, 0.15f));
    tran = glm::rotate(tran, glm::radians(0.f), glm::vec3(0.f, 1.f, 0.f));
    tran = inn * tran;
    glUniformMatrix4fv(tr_matrix_loc, 1, GL_FALSE, glm::value_ptr(tran));

    GLint vertexC = glGetUniformLocation(shaderProgram, "ourColor");
    glUniform4f(vertexC, color.x, color.y, color.z, 1.f);

    glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);
}

void drawPlayer(glm::mat4 inn, glm::vec4 color) {
    glBindVertexArray(plane_buffer);
    GLint tr_matrix_loc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(tr_matrix_loc, 1, GL_FALSE, glm::value_ptr(inn));

    GLint vertexC = glGetUniformLocation(shaderProgram, "ourColor");
    glUniform4f(vertexC, color.x, color.y, color.z, 1.f);

    GLint use_texture_loc = glGetUniformLocation(shaderProgram, "useTexture");
    glUniform1i(use_texture_loc, false);

    glDrawArrays(GL_TRIANGLES, 0, vertices_player.size());
}

void drawEnemy(glm::mat4 inn, glm::vec4 color) {
    glBindVertexArray(plane_buffer2);
    GLint tr_matrix_loc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(tr_matrix_loc, 1, GL_FALSE, glm::value_ptr(inn));

    GLint vertexC = glGetUniformLocation(shaderProgram, "ourColor");
    glUniform4f(vertexC, color.x, color.y, color.z, 1.f);

    GLint use_texture_loc = glGetUniformLocation(shaderProgram, "useTexture");
    glUniform1i(use_texture_loc, true);

    glDrawArrays(GL_TRIANGLES, 0, vertices_enemy.size());
}

void Planett() {
    glm::mat4 inn = glm::mat4(1.f);
    glm::mat4 gg = glm::translate(inn, glm::vec3(2.5f, -1.2f, 2.5f));
    gg = glm::scale(gg, glm::vec3(0.3f, 0.3f, 0.3f));
    drawPlanet(gg, glm::vec4(0.5, 0.5, 0.0, 1.0));
    gg = glm::rotate(gg, glm::radians(planet), glm::vec3(0.f, 1.f, 0.f));
    gg = glm::translate(gg, glm::vec3(3.f, 0.f, 3.f));
    gg = glm::scale(gg, glm::vec3(0.3f, 0.3f, 0.3f));
    drawPlanet(gg, glm::vec4(0.5, 0.0, 0.0, 1.0));
    gg = glm::rotate(gg, glm::radians(planet * 2), glm::vec3(1.f, -1.f, 0.f));
    gg = glm::translate(gg, glm::vec3(3.f, 0.f, 3.f));
    gg = glm::scale(gg, glm::vec3(0.3f, 0.3f, 0.3f));
    drawPlanet(gg, glm::vec4(0.0, 0.5, 0.0, 1.f));

    /*gg = glm::translate(inn, glm::vec3(3.0, 1.2, 4.0));
    gg = glm::scale(gg, glm::vec3(0.3f, 0.3f, 0.3f));
    drawPlanet(gg, glm::vec4(0.5, 0.5, 0.0, 1.0));
    gg = glm::rotate(gg, glm::radians(planet), glm::vec3(0.f, 1.f, 0.f));
    gg = glm::translate(gg, glm::vec3(3.f, 0.f, 3.f));
    gg = glm::scale(gg, glm::vec3(0.3f, 0.3f, 0.3f));
    drawPlanet(gg, glm::vec4(0.0, 0.8, 0.4, 1.0));
    gg = glm::rotate(gg, glm::radians(planet * 2), glm::vec3(1.f, 1.f, 0.f));
    gg = glm::translate(gg, glm::vec3(20.f, 0.f, 20.f));
    gg = glm::scale(gg, glm::vec3(0.3f, 0.3f, 0.3f));
    drawPlanet(gg, glm::vec4(0.5, 0.5, 0.5, 1.f));*/

    glm::vec4 aa = glm::vec4(0.f, 0.f, 0.f, 1.f);
    aa = gg * aa;
    point_light = glm::vec3(aa.x, aa.y, aa.z);

    std::cout << point_light.x << " + " << point_light.y << " + " << point_light.z << std::endl;
}

void drawPlanet(glm::mat4 inn, glm::vec4 color) {
    glBindVertexArray(planet_buffer);
    GLint tr_matrix_loc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(tr_matrix_loc, 1, GL_FALSE, glm::value_ptr(inn));

    GLint vertexC = glGetUniformLocation(shaderProgram, "ourColor");
    glUniform4f(vertexC, color.x, color.y, color.z, 1.f);

    GLint use_texture_loc = glGetUniformLocation(shaderProgram, "useTexture");
    glUniform1i(use_texture_loc, false);

    glDrawArrays(GL_TRIANGLES, 0, vertices_planet.size());
}

void determineColor(glm::vec4* player_color, glm::vec4* enemy_color) {
    switch (player.getHP()) {
    case 3:
        *player_color = glm::vec4(0.f, 1.f, 0.f, 1.f);
        break;
    case 2:
        *player_color = glm::vec4(0.2f, 0.8f, 0.8f, 1.f);
        break;
    case 1:
        *player_color = glm::vec4(0.f, 0.f, 1.f, 1.f);
        break;
    default:
        *player_color = glm::vec4(0.f, 0.f, 0.f, 1.f);
        break;
    }

    switch (enemy_list.getIndex()) {
    case 0:
        *enemy_color = glm::vec4(1.f, 1.f, 0.f, 1.f);
        break;
    case 1:
        *enemy_color = glm::vec4(1.f, 0.5f, 0.f, 1.f);
        break;
    case 2:
        *enemy_color = glm::vec4(1.f, 0.f, 0.f, 1.f);
        break;
    case 3:
        *enemy_color = glm::vec4(0.8f, 0.2f, 0.8f, 1.f);
        break;
    case 4:
        *enemy_color = glm::vec4(0.35f, 0.2f, 0.8f, 1.f);
        break;
    default:
        *enemy_color = glm::vec4(0.f, 0.f, 0.f, 1.f);
        break;
    }
}

void isWire() {
    if (line_rendering == HIDING) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void InitTexture() {
    glGenTextures(1, &Texture);
    glBindTexture(GL_TEXTURE_2D, Texture);
// 텍스처 wrapping/filtering 옵션 설정(현재 바인딩된 텍스처 객체에 대해)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 텍스처 로드 및 생성
    int width, height, nrChannels;
    unsigned char *data = stbi_load("../Diffuse.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}