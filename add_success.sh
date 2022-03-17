#!/bin/bash
path="/data/team-10/large/order2_compress/"
cd ${path}
rm -rf *.success
for ((i=0;i < 10; i++))
do
    for ((j=1;j < 51; j++))
    do
        touch "stock${i}_${j}.zst.success"
        echo success > "stock${i}_${j}.zst.success"
    done
done