#include <iostream>
#include <cstring>
#include <bits/stdc++.h>
#include "H5Cpp.h"

using namespace H5;
using namespace std;




const H5std_string FILE_NAME("/Users/gjy/JK_Contest/exchange-simulation/100x10x10/order_id1.h5");
const H5std_string DATASET_NAME("order_id");

const int NX = 500;
const int NY = 10;
const int NZ = 10; 
const int kStkN = 10;
const int RANK_OUT = 3;
string prefix_path = "/Users/gjy/JK_Contest/split/100x10x10/";
string trade_id = "1";
struct Order {
    int order_id;
    int price;
    int volume;
    char combined;
}__attribute__((packed));
vector<vector<Order>> order_stk(kStkN, vector<Order>(NX * NY * NZ / kStkN));
vector<int> prev_close(kStkN);
void CountintSort() {
  for (int i = 0; i < kStkN; ++i) {
    sort(order_stk[i].begin(), order_stk[i].end(), [&](Order order1, Order order2) {
      return order1.order_id < order2.order_id;
    });
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
  cout << path << " " << prefix_path << " " << dataset_name << endl;
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
      if (csv_name == "prev_close") prev_close[i] = stk[i][j];
    }
  }
  delete[] data_read;  
}

void ReadHdf5Double(string dataset_name, string id, int NX, int NY, int NZ) {
  string path = prefix_path + dataset_name + id + ".h5";
  cout << path << " " << dataset_name << endl;
  H5std_string FILE_NAME(path);
  H5std_string DATASET_NAME(dataset_name);
  int size = NX * NY * NZ;
  double *data_read = new double [size];
  memset(data_read, 0, sizeof(double) * size);

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
        order_stk[i][j].price = (int)stk[i][j] * 100; //floor 0.01
      }
    }
  }
  delete[] data_read;  
}

void OutputOrderBinaryFile(int stk_id) {
  FILE *fid;
  string binary_file_path = prefix_path + trade_id + "/" "stock" + to_string(stk_id);
  fid = fopen(binary_file_path.c_str(),"wb");
  for (auto order : order_stk[stk_id]) {
    fwrite(&order,sizeof(Order),1,fid);
  }
  fclose(fid);
}


void OutputPrevCloseBinaryFile() {
  FILE *fid;
  string binary_file_path = prefix_path + trade_id + "/"  + "prev_price";
  cout <<  binary_file_path<<endl;
  fid = fopen(binary_file_path.c_str(),"wb");
  for (auto price : prev_close) {
    fwrite(&price,sizeof(int),1,fid);
    cout << price << endl;
  }
  fclose(fid);
}
int main(int argc,char **argv) {
  
  prefix_path = argv[1];
  trade_id = argv[2];
  vector<string> dataset_name_vec{"order_id", "direction", "type", "volume"};
    
  for (auto dataset_name : dataset_name_vec)
    ReadHdf5Int(dataset_name, dataset_name, trade_id, NX, NY, NZ);
  ReadHdf5Double("price", trade_id, NX, NY, NZ);
  ReadHdf5Int("price", "prev_close", trade_id, 10, 1, 1);
  CountintSort();
  for (int i = 0; i < 1; ++i) 
    for (int j = 0; j < 10; ++j) {
      Order o = order_stk[i][j];
      cout << o.price << " " << (int)o.combined << " " << o.order_id << endl;
    }
  for (int i = 0; i < kStkN; ++i)
    OutputOrderBinaryFile(i);
  OutputPrevCloseBinaryFile();
  return 0;
}

