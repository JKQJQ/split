#include<iostream>
using namespace std;
#define Test 1
struct Trade {
    int stk_code;
    int bid_id;
    int ask_id;
    double price;
    int volume;
}__attribute__((packed));

struct Order {
    int order_id;
    int price;
    int volume;
    unsigned char combined;
}__attribute__((packed));

const int kSplitN = 50;

inline void OutputOrder(Order order, bool flag, int kN) {
  int order_id = order.order_id;
  int price = (order.price) * 1000;
  int volume = order.volume;
  unsigned char ch = order.combined;
  int dir = ((ch >> 3) & 1) ? 1 : 2;
  int type = (ch & 7);
  int stk_code = ch >> 4; 
  assert(order_id >= 1 && order_id <= kN * 2);
  assert(price >= 0);
  assert(volume >= 0);
  assert(dir == 1 || dir == 2);
  assert(type >= 0 && type < 6);
  assert(stk_code >= 0 && stk_code < 10);
  if  (flag) {
    cout << order_id << " " << price << " " << volume << " " << stk_code << " " << dir <<" " << type << endl;
  }
}