#ifndef HIT_H
#define HIT_H
#include "objects/bullet.h"
#include "objects/player.h"
#include "objects/enemy.h"

void check_hit();
bool is_in_hitbox(Position, Position, Direction);
void check_get_item();
#endif