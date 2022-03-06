#include <iostream>
#include <cstring>
#include <bits/stdc++.h>
#include "H5Cpp.h"
#include "../common.h"
using namespace H5;
using namespace std;

template<class TH> void _dbg(const char *sdbg, TH h){ cerr<<sdbg<<'='<<h<<endl; }
template<class TH, class... TA> void _dbg(const char *sdbg, TH h, TA... a) {
  while(*sdbg!=',')cerr<<*sdbg++;
  cerr<<'='<<h<<','; _dbg(sdbg+1, a...);
}

template<class T> ostream &operator<<(ostream& os, vector<T> V) {
  os << "["; for (auto vv : V) os << vv << ","; return os << "]";
}
template<class L, class R> ostream &operator<<(ostream &os, pair<L,R> P) {
  return os << "(" << P.first << "," << P.second << ")";
}
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)


const H5std_string FILE_NAME("/Users/gjy/JK_Contest/exchange-simulation/100x10x10/order_id1.h5");
const H5std_string DATASET_NAME("order_id");

const int NX = 500;
const int NY = 10;
const int NZ = 10; 

const int kSIZE = NX * NY * NZ;
const int RANK_OUT = 3;


void CountintSort() {
  //for (int i = 0; i < v.size(); ++i) {
    
  //}
}
void ReadHdf5(string dataset_name, string id) {
  string path = "/Users/gjy/JK_Contest/exchange-simulation/100x10x10/" + dataset_name + id + ".h5";
  cout << path << " " << dataset_name << endl;
  H5std_string FILE_NAME(path);
  H5std_string DATASET_NAME(dataset_name);
  int *data_read = new int [kSIZE];
  memset(data_read, 0, sizeof(int) * kSIZE);

  H5File file(FILE_NAME, H5F_ACC_RDONLY);
  DataSet dataset = file.openDataSet(DATASET_NAME);
  DataSpace dataspace = dataset.getSpace();
  int rank = dataspace.getSimpleExtentNdims();
  hsize_t dims_out[3];
  dataspace.getSimpleExtentDims(dims_out, NULL);

  printf("rank %d, shape (%llu, %llu, %llu)\n", rank, dims_out[0], dims_out[1], dims_out[2]);

  hsize_t offset[3];
  hsize_t count[3];
  offset[0] = 0;
  offset[1] = 0;
  offset[2] = 0;
  count[0] = NX;
  count[1] = NY;
  count[2] = NZ;
  dataspace.selectHyperslab(H5S_SELECT_SET, count, offset); //select in file, this api can set api

  hsize_t dimsm[3];
  dimsm[0] = NX;
  dimsm[1] = NY;
  dimsm[2] = NZ;
  for (int i = 0; i < 3; ++i) assert(dimsm[i] == dims_out[i]);
  DataSpace memspace(RANK_OUT, dimsm);

  hsize_t offset_out[3];
  hsize_t count_out[3];
  offset_out[0] = 0;
  offset_out[1] = 0;
  offset_out[2] = 0;
  count_out[0] = NX;
  count_out[1] = NY;
  count_out[2] = NZ;
  memspace.selectHyperslab(H5S_SELECT_SET, count_out, offset_out); // select in memory

  dataset.read(data_read, PredType::NATIVE_INT, memspace, dataspace);
  //read from file to memory, you can set offset in memory space

  vector<int> stk[10];
  for (int i = 0; i < dims_out[0]; ++i) {
    for (int j = 0; j < dims_out[1]; ++j) {
      for (int k = 0; k < dims_out[2]; ++k) {
        int stk_code = i % 10;
        stk[stk_code].push_back(data_read[i * dims_out[1] * dims_out[2] + j * dims_out[2] + k]);
      }
    }     
  }
  for (int i = 0; i < 10; ++i) {
    sort(stk[i].begin(), stk[i].end());
    
  }
  delete[] data_read;  
}
int main() {
  vector<string> dataset_name_vec = {"order_id", "price", "direction", "type", "volume"};  
  for (auto dataset_name : dataset_name_vec)
    ReadHdf5(dataset_name, "1");
  return 0;
}

