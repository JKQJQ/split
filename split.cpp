#include <iostream>
#include <cstring>
#include <bits/stdc++.h>
#include "H5Cpp.h"
#include "common.h"
// #include "split.h"
using namespace H5;
using namespace std;


const int NX = 500;
int NY = 1000;
int NZ = 1000; 

const int kStkN = 10;
int kN = NX * NY * NZ / kStkN;
const int RANK_OUT = 3;
string prefix_path = "/Users/gjy/JK_Contest/split/100x10x10/";
string output_prefix_path = "/Users/gjy/JK_Contest/split/";
string trade_id = "1";

vector<vector<Order>> order_stk;
vector<int> prev_close(kStkN);
vector<int> hook(kStkN * 100 * 4);
void QuickSort() {
  for (int i = 0; i < kStkN; ++i) {
    sort(order_stk[i].begin(), order_stk[i].end(), [&](Order order1, Order order2) {
      return order1.order_id < order2.order_id;
    });
  }
}
void CountingSort() {
  for (int i = 0; i < kStkN; ++i) {
    vector<int> address(kN * 2 + 1, -1);
    for (int j = 0; j < order_stk[i].size(); ++j) {
      #ifdef Test
        assert(address[order_stk[i][j].order_id] == -1);
      #endif
      address[order_stk[i][j].order_id] = j; //address[3] = 0
    }
    vector<Order> tmp = order_stk[i];
    int k = 0;
    for (int j = 1; j <= kN * 2; ++j) {
      if (address[j] == -1) continue;
      order_stk[i][k++] = tmp[address[j]]; 
    }
    assert(k == kN);   
  }
}

void ReadHdf5Int(
  string dataset_name, 
  string csv_name, 
  string id, 
  int NX, 
  int NY, 
  int NZ
  ) {
  string path = prefix_path + dataset_name + id + ".h5";
  H5std_string FILE_NAME(path);
  H5std_string DATASET_NAME(csv_name);
  int size = NX * NY * NZ;
  int *data_read = new int [size];
  memset(data_read, 0, sizeof(int) * size);

  H5File file(FILE_NAME, H5F_ACC_RDONLY);
  DataSet dataset = file.openDataSet(DATASET_NAME);
  DataSpace dataspace = dataset.getSpace();
  int rank = dataspace.getSimpleExtentNdims();
  hsize_t dims_out[3] = {1, 1, 1};
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

  vector<int> stk[kStkN];
  for (int i = 0; i < dims_out[0]; ++i) {
    for (int j = 0; j < dims_out[1]; ++j) {
      for (int k = 0; k < dims_out[2]; ++k) {
        int stk_code = i % kStkN;
        stk[stk_code].push_back(data_read[i * dims_out[1] * dims_out[2] + j * dims_out[2] + k]);
      }
    }     
  }
  for (int i = 0; i < kStkN; ++i) {
    for (int j = 0; j < stk[i].size(); ++j) {
      if (csv_name == "order_id") order_stk[i][j].order_id = stk[i][j];
      if (csv_name == "volume") order_stk[i][j].volume = stk[i][j];
      if (csv_name == "direction") order_stk[i][j].combined |= (stk[i][j] == 1?1:0) << 3;
      if (csv_name == "type") order_stk[i][j].combined |= stk[i][j];
      if (csv_name == "prev_close") prev_close[i] = round(stk[i][j] * 100);
      if (csv_name == "hook") hook[i * 100 * 4 + j] = stk[i][j];
    }
  }
  delete[] data_read;  
}

void ReadHdf5Double(string dataset_name, string csv_name, string id, int NX, int NY, int NZ) {
  string path = prefix_path + dataset_name + id + ".h5";
  cout << path << " " << dataset_name << endl;
  H5std_string FILE_NAME(path);
  H5std_string DATASET_NAME(csv_name);
  int size = NX * NY * NZ;
  double *data_read = new double [size];
  memset(data_read, 0, sizeof(double) * size);

  H5File file(FILE_NAME, H5F_ACC_RDONLY);
  DataSet dataset = file.openDataSet(DATASET_NAME);
  DataSpace dataspace = dataset.getSpace();
  int rank = dataspace.getSimpleExtentNdims();
  hsize_t dims_out[3] = {1, 1, 1};
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
  for (int i = 0; i < 3; ++i) cout << dimsm[i] << " " << dims_out[i] << endl;
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

  dataset.read(data_read, PredType::NATIVE_DOUBLE, memspace, dataspace);
  //read from file to memory, you can set offset in memory space

  vector<double> stk[kStkN];
  for (int i = 0; i < dims_out[0]; ++i) {
    for (int j = 0; j < dims_out[1]; ++j) {
      for (int k = 0; k < dims_out[2]; ++k) {
        int stk_code = i % kStkN;
        stk[stk_code].push_back(data_read[i * dims_out[1] * dims_out[2] + j * dims_out[2] + k]);
      }
    }     
  }
  for (int i = 0; i < kStkN; ++i) {
    for (int j = 0; j < stk[i].size(); ++j) {
      if (dataset_name == "price") {
        order_stk[i][j].combined |=  i << 4;
        order_stk[i][j].price = round(stk[i][j] * 100); //floor 0.01
      }
    }
  }
  delete[] data_read;  
}

void OutputOrderBinaryFile(int stk_id) {
  #ifdef Test
    for (int i = 0; i < kN; ++i) {
      bool output_flag = i < 3;
      OutputOrder(order_stk[stk_id][i], output_flag, kN);
    }
  #endif
  assert(order_stk[stk_id].size() == kN);
  assert(kN % kSplitN == 0);
  int length = kN / kSplitN;
  for (int i = 0; i < kSplitN; ++i) {
    string binary_file_path = output_prefix_path + "test" + trade_id + "/" "stock" + to_string(stk_id + 1) +  "_" + to_string(i + 1);
    cout << "binary_file_path=" << binary_file_path << endl;
    std::ofstream outfile(binary_file_path, std::ios::out | std::ios::binary);


    outfile.write((char *)(&order_stk[stk_id][length * i]), sizeof(Order) * length);
    outfile.close(); 
  }

}


void OutputIntBinaryFile(vector<int> &V, string file_name) {
  string binary_file_path = output_prefix_path + "test" + trade_id + "/" + file_name; 
  std::ofstream outfile(binary_file_path, std::ios::out | std::ios::binary);
  for (auto v : V) {
    outfile.write((char *)(&v), sizeof(int));
  }
  outfile.close(); 
}

int main(int argc,char **argv) {
  
  prefix_path = argv[1];
  trade_id = argv[2];
  output_prefix_path = argv[3];
  NY = atoi(argv[4]);
  NZ = atoi(argv[5]);
  kN = NX * NY * NZ / kStkN;
  order_stk = vector<vector<Order>>(kStkN, vector<Order>(kN));
  vector<string> dataset_name_vec{"order_id", "direction", "type", "volume"};
    
  for (auto dataset_name : dataset_name_vec)
    ReadHdf5Int(dataset_name, dataset_name, trade_id, NX, NY, NZ);
  ReadHdf5Double("price", "price", trade_id, NX, NY, NZ);
  ReadHdf5Int("price", "prev_close", trade_id, kStkN, 1, 1);
  ReadHdf5Int("hook", "hook", "", kStkN, 100, 4);
  QuickSort();

  for (int i = 0; i < kStkN; ++i)
    OutputOrderBinaryFile(i);
  OutputIntBinaryFile(prev_close, "prev_price");
  OutputIntBinaryFile(hook, "hook");
  for (int i = 0; i < 10; ++i) cout << hook[i] << endl;
  return 0;
}

