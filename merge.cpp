#include <bits/stdc++.h>
#include "common.h"

using namespace std;


const int NX = 500;
const int NY = 10;
const int NZ = 10; 
const int kStkN = 10;
const int kN = NX * NY * NZ / kStkN;
vector<int> prev_close(kStkN);
vector<Order*> order_stk[2]; 
Order merge_order_stk[kStkN][kN * 2];
void ReadOrderBinaryFile(string file_path, vector<Order*> &order_stk) {

  for (int i = 0; i < kStkN; ++i) {
    string stk_file_path = file_path + "stock" + to_string(i);
    order_stk[i] = new struct Order[kN];
    std::ifstream infile(stk_file_path, std::ios::in | std::ios::binary);
    infile.read((char *)order_stk[i], sizeof(Order) * kN);
    infile.close();
    //for (int j = 0; j < kStkN; ++j) {
      //cout << (order_stk[i] + j)->price << " " << (order_stk[i] + j)->order_id << endl;
    //}
  } 
}
void Merge(Order* order_stk1, Order* order_stk2, int i, Order merge_order_stk[]) {
  for (int i = 0; i < kN; ++i) merge_order_stk[i] = order_stk1[i];
  for (int i = 0; i < kN; ++i) merge_order_stk[i + kN] = order_stk2[i];
  sort(merge_order_stk, merge_order_stk + kN * 2, [&](Order order1, Order order2){
    return order1.order_id < order2.order_id;
  });
} 
void WriteOrderBinaryFile(string file_path) {
  for (int i = 0; i < kStkN; ++i) {
    string stk_file_path = file_path + "stock" + to_string(i);
    std::ofstream outfile(stk_file_path, std::ios::out | std::ios::binary);
    outfile.write((char *)merge_order_stk, sizeof(Order) * kN * 2);
    outfile.close(); 
  }
} 
int main(int argc, char **argv) {
  string prefix_path = argv[1];  //"/Users/gjy/JK_Contest/split/";
  string path1 = prefix_path + "trade1/";
  string path2 = prefix_path + "trade2/";       
  string output_path = prefix_path + "trade_merge/";
  for (int i = 0; i < 2; ++i) {
    order_stk[i] = vector<Order*>(kN);
    //merge_order_stk = vector<Order*>(kN * 2);
  }
  ReadOrderBinaryFile(path1, order_stk[0]);
  ReadOrderBinaryFile(path2, order_stk[1]);
  for (int i = 0; i < kStkN; ++i) {  
    Merge(order_stk[0][i], order_stk[1][i], i, merge_order_stk[i]);
  }
  
  WriteOrderBinaryFile(output_path);
  
}
