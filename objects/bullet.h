#ifndef BULLET_H
#define BULLET_H
#define BULLET_RADIUS 0.05f
#define BULLET_SPEED 0.0075f
#include "./object.h"

enum BulletType {
    NORMAL_UP,
    NORMAL_DOWN,
    NORMAL_RIGHT,
    NORMAL_LEFT,
    NORMAL_UPRIGHT,
    NORMAL_UPRIGHT15,
    NORMAL_UPLEFT,
    NORMAL_UPLEFT15,
    NORMAL_DOWNRIGHT,
    NORMAL_DOWNRIGHT15,
    NORMAL_DOWNLEFT,
    NORMAL_DOWNLEFT15,
};

class Bullet : public Object {
private:
    BulletType bullet_type;
public:
    Bullet(Position _position, BulletType _bullet_type) {
        position = _position;
        bullet_type = _bullet_type;
    };

    BulletType get_bullet_type() {
        return bullet_type;
    }
};

class BulletList {
private:
    std::vector <Bullet> bullet_list;
    Owner owner;

public:
    BulletList(Owner _owner) { owner = _owner; }

    int get_size() { return bullet_list.size(); }
    Bullet get_bullet(int i) { return bullet_list[i]; }
    void erase_bullet(int i) { bullet_list.erase(bullet_list.begin() + i); }
    void shoot(std::vector<BulletType> bullet_types, Position position) {
        for (int i = 0; i < bullet_types.size(); i++) {
            bullet_list.push_back(Bullet(position, bullet_types[i]));
        }
    }

    void move_bullets() {

        std::vector<Bullet>::iterator iter = bullet_list.begin();

        while (iter != bullet_list.end()) {
            BulletType d = iter->get_bullet_type();

            switch (d) {
            case NORMAL_UP:
                iter->move_up(BULLET_SPEED);
                if (iter->get_position().y + BULLET_SPEED >= 4.95) {
                    iter = bullet_list.erase(iter);
                }
                else {
                    iter++;
                }
                break;

            case NORMAL_DOWN:
                iter->move_down(BULLET_SPEED);
                if (iter->get_position().y - BULLET_SPEED <= 0.05) {
                    iter = bullet_list.erase(iter);
                }
                else {
                    iter++;
                }
                break;

            case NORMAL_UPRIGHT:
                iter->move_up(BULLET_SPEED * cos(45 * (PI / 180)));
                iter->move_right(BULLET_SPEED * cos(45 * (PI / 180)));
                if (iter->get_position().y + BULLET_SPEED >= 4.95) {
                    iter = bullet_list.erase(iter);
                }
                else if (iter->get_position().x + BULLET_SPEED >= 4.95) {
                    iter = bullet_list.erase(iter);
                }
                else {
                    iter++;
                }
                break;

            case NORMAL_UPRIGHT15:
                iter->move_up(BULLET_SPEED * cos(15 * (PI / 180)));
                iter->move_right(BULLET_SPEED * sin(15 * (PI / 180)));
                if (iter->get_position().y + BULLET_SPEED >= 4.95) {
                    iter = bullet_list.erase(iter);
                }
                else if (iter->get_position().x + BULLET_SPEED >= 4.95) {
                    iter = bullet_list.erase(iter);
                }
                else {
                    iter++;
                }
                break;

            case NORMAL_UPLEFT:
                iter->move_up(BULLET_SPEED * cos(45 * (PI / 180)));
                iter->move_left(BULLET_SPEED * cos(45 * (PI / 180)));
                if (iter->get_position().y + BULLET_SPEED >= 4.95) {
                    iter = bullet_list.erase(iter);
                }
                else if (iter->get_position().x - BULLET_SPEED <= 0.05) {
                    iter = bullet_list.erase(iter);
                }
                else {
                    iter++;
                }
                break;

            case NORMAL_UPLEFT15:
                iter->move_up(BULLET_SPEED * cos(15 * (PI / 180)));
                iter->move_left(BULLET_SPEED * sin(15 * (PI / 180)));
                if (iter->get_position().y + BULLET_SPEED >= 4.95) {
                    iter = bullet_list.erase(iter);
                    return;
                }
                else if (iter->get_position().x - BULLET_SPEED <= 0.05) {
                    iter = bullet_list.erase(iter);
                    return;
                }
                else {
                    iter++;
                }
                break;

            case NORMAL_DOWNRIGHT:
                iter->move_down(BULLET_SPEED * cos(45 * (PI / 180)));
                iter->move_right(BULLET_SPEED * cos(45 * (PI / 180)));
                if (iter->get_position().y - BULLET_SPEED <= 0.05) {
                    iter = bullet_list.erase(iter);
                }
                else if (iter->get_position().x + BULLET_SPEED >= 4.95) {
                    iter = bullet_list.erase(iter);
                }
                else {
                    iter++;
                }
                break;

            case NORMAL_DOWNRIGHT15:
                iter->move_down(BULLET_SPEED * cos(15 * (PI / 180)));
                iter->move_right(BULLET_SPEED * sin(15 * (PI / 180)));
                if (iter->get_position().y - BULLET_SPEED <= 0.05) {
                    iter = bullet_list.erase(iter);
                    return;
                }
                else if (iter->get_position().x + BULLET_SPEED >= 4.95) {
                    iter = bullet_list.erase(iter);
                    return;
                }
                else {
                    iter++;
                }
                break;

            case NORMAL_DOWNLEFT:
                iter->move_down(BULLET_SPEED * cos(45 * (PI / 180)));
                iter->move_left(BULLET_SPEED * cos(45 * (PI / 180)));
                if (iter->get_position().y - BULLET_SPEED <= 0.05) {
                    iter = bullet_list.erase(iter);
                }
                else if (iter->get_position().x - BULLET_SPEED <= 0.05) {
                    iter = bullet_list.erase(iter);
                }
                else {
                    iter++;
                }
                break;

            case NORMAL_DOWNLEFT15:
                iter->move_down(BULLET_SPEED * cos(15 * (PI / 180)));
                iter->move_left(BULLET_SPEED * sin(15 * (PI / 180)));
                if (iter->get_position().y - BULLET_SPEED <= 0.05) {
                    iter = bullet_list.erase(iter);
                    return;
                }
                else if (iter->get_position().x + BULLET_SPEED <= 0.05) {
                    iter = bullet_list.erase(iter);
                    return;
                }
                else {
                    iter++;
                }
                break;

            default:
                break;
            }
        }
    }

    std::vector <Position> get_bullet_positions() {
        std::vector <Position> positions;
        for (int i = 0; i < bullet_list.size(); i++) {
            positions.push_back(bullet_list[i].get_position());
        }
        return positions;
    }
};

extern BulletList player_bullets;
extern BulletList enemy_bullets;

/*
bool isHit(float bx, float by, float tx, float ty, Owner owner) {
        int i = -1;
        if (owner == PLAYER) i = 1;

        return (((bx + i * BULLET_RADIUS / 2 > tx + PLAYER_WIDTH / 10) &&
            (bx + i * BULLET_RADIUS / 2 < tx + 9 * PLAYER_WIDTH / 10) &&
            (i * by + BULLET_RADIUS / 2 < i * ty) &&
            (i * by + BULLET_RADIUS / 2 > i * ty - PLAYER_HEIGHT / 10)) ||
            ((bx + i * BULLET_RADIUS / 2 > tx + 2 * PLAYER_WIDTH / 5) &&
                (bx + i * BULLET_RADIUS / 2 < tx + 3 * PLAYER_WIDTH / 5) &&
                (i * by + BULLET_RADIUS / 2 < i * ty - PLAYER_HEIGHT / 10) &&
                (i * by + BULLET_RADIUS / 2 > i * ty - 4 * PLAYER_HEIGHT / 5)));
}
*/
#endif