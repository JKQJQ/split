#!/bin/bash
######## VARIABLES ################
INPUT_ORDER_FILE_1=/data/team-10/large/test1/
INPUT_ORDER_FILE_2=/data/team-10/large/test2/
OUTPUT_ORDER_MERGE_FILE=/data/team-10/large/order_merge/
N=1000 #small: 10 medium: 100 large:1000
######### END ###############
cmake .
make

rm -rf ${OUTPUT_ORDER_MERGE_FILE}/*

./merge ${INPUT_ORDER_FILE_1} ${INPUT_ORDER_FILE_2}  ${OUTPUT_ORDER_MERGE_FILE} ${N} ${N}
echo ${OUTPUT_ORDER_MERGE_FILE}
g++ /home/team-10/exchange-simulation/merge_cuo.cpp -o /home/team-10/exchange-simulation/merge_cuo -O2 && /home/team-10/exchange-simulation/merge_cuo
cmp -l /data/team-10/my_ans_large/trade1 /data/100x1000x1000/trade1
cmp -l /data/team-10/my_ans_large/trade2 /data/100x1000x1000/trade2
cmp -l /data/team-10/my_ans_large/trade3 /data/100x1000x1000/trade3
cmp -l /data/team-10/my_ans_large/trade4 /data/100x1000x1000/trade4
cmp -l /data/team-10/my_ans_large/trade5 /data/100x1000x1000/trade5
cmp -l /data/team-10/my_ans_large/trade6 /data/100x1000x1000/trade6
cmp -l /data/team-10/my_ans_large/trade7 /data/100x1000x1000/trade7
cmp -l /data/team-10/my_ans_large/trade8 /data/100x1000x1000/trade8
cmp -l /data/team-10/my_ans_large/trade9 /data/100x1000x1000/trade9
cmp -l /data/team-10/my_ans_large/trade10 /data/100x1000x1000/trade10