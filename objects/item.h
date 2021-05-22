#ifndef ITEM_H
#define ITEM_H
#define ITEM_SPEED 0.002f
#define ITEM_LENGTH 0.05f
#include "object.h"
#include <vector>

enum ItemType{
  INCREASE_BULLET
};

class Item : public Object{
private:
  ItemType item_type;
public:
  Item(Position _position, ItemType _item_type = INCREASE_BULLET){
    position.x = _position.x;
    position.y = _position.y;
    item_type = _item_type;
  }
};

class ItemList {
private:
  std::vector<Item> item_list;
public:
  int get_size() {
    return item_list.size();
  }
  Item get_item(int i) {
    return item_list[i];
  }
  std::vector<Position> get_item_positions() {
    std::vector<Position> item_positions;
    for (int i = 0; i < item_list.size(); i++) {
      item_positions.push_back(item_list[i].get_position());
    }
    return item_positions;
  }
  void move_items() {
    for (int i = 0; i < item_list.size(); i++) {
      item_list[i].move_down(ITEM_SPEED);
    }
  }
  void remove_item(int i) {
    item_list.erase(item_list.begin() + i);
  }
  void create_item(Position position, ItemType item_type = INCREASE_BULLET) {
    item_list.push_back(Item(position, item_type));
  }
};

extern ItemList item_list;
#endif