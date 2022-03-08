#include <bits/stdc++.h>
#include "common.h"

using namespace std;


const int NX = 500;
const int NY = 10;
const int NZ = 10; 
const int kStkN = 10;
const int kN = NX * NY * NZ / kStkN;
vector<int> prev_close(kStkN);
Order* order_stk[2]; 
void OutputOrder(Order order, bool flag) {
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
void ReadOrderBinaryFile(string file_path, Order* order_stk, int i) {


  string stk_file_path = file_path + "stock" + to_string(i);

  std::ifstream infile(stk_file_path, std::ios::in | std::ios::binary);
  infile.read((char *)order_stk, sizeof(Order) * kN);
  infile.close();
}
void Merge(Order* order_stk1, Order* order_stk2, string file_path, int stk_id) {
  Order* merge_order_stk = new Order[kN * 2];
  // for (int i = 0; i < kN; ++i) merge_order_stk[i] = order_stk1[i];
  // for (int i = 0; i < kN; ++i) merge_order_stk[i + kN] = order_stk2[i];
  // sort(merge_order_stk, merge_order_stk + kN * 2, [&](Order order1, Order order2){
  //   return order1.order_id < order2.order_id;
  // });

  int i = 0, j = 0, k = 0;
  while (i < kN || j < kN) {
    if (j == kN) {
      merge_order_stk[k++] = order_stk1[i++];
    } else
    if (i == kN) {
      merge_order_stk[k++] = order_stk2[j++];
    } else 

    if (i < kN && j < kN) {
      if (order_stk1[i].order_id < order_stk2[j].order_id) {
        merge_order_stk[k++] = order_stk1[i++];
      } else {
        merge_order_stk[k++] = order_stk2[j++];
      }
    }
  }
  cout << i << "  " << j << " " << k <<  " " << kN << endl;
  assert(k == i + j);
  assert(k == kN * 2);
  for (i = 0; i < kN * 2; ++i) {
    bool output_flag = i < 3;
    OutputOrder(merge_order_stk[i], output_flag);
  }
  string stk_file_path = file_path + "stock" + to_string(stk_id);
  std::ofstream outfile(stk_file_path, std::ios::out | std::ios::binary);
  outfile.write((char *)merge_order_stk, sizeof(Order) * kN * 2);
  outfile.close(); 
  delete merge_order_stk;
} 

int main(int argc, char **argv) {
  string prefix_path = argv[1];  //"/Users/gjy/JK_Contest/split/";
  string path1 = prefix_path + "trade1/";
  string path2 = prefix_path + "trade2/";       
  string output_path = prefix_path + "trade_merge/";

  for (int i = 0; i < kStkN; ++i) { 
    for (int j = 0; j < 2; ++j) {
        order_stk[j] = new  Order[kN];
    }
    ReadOrderBinaryFile(path1, order_stk[0], i);
    ReadOrderBinaryFile(path2, order_stk[1], i); 
    Merge(order_stk[0], order_stk[1], output_path, i);
    for (int j = 0; j < 2; ++j) {
        delete order_stk[j];
    }
  }

  
}
