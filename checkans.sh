


data_path="team-10/"
echo "Enter Your File Path:"
prefix_path='/data/'
echo "Enter Your File Size (small/medium/large):"
read Size

N="10"
if  [ "$Size" == "small" ]
then N="10"
fi
if  [ "$Size" == "medium" ]
then N="100"
fi
if  [ "$Size" == "large" ]
then N="1000"
fi


zstd -T4 -D --decompress /data/team-10/large/test2_compress/* --output-dir-flat /data/team-10/large/test2/
path="${prefix_path}${data_path}test2/"
cd ${path}
rm -rf *.zst
rm -rf *.success
for ((i=1;i < 11; i++))
do
    for ((j=1;j < 51; j++))
    do
        touch "stock${i}_${j}.zst.success"
        echo success > "stock${i}_${j}.zst.success"
    done
done

cmake .
make
input_path="${data_path}${Size}/" #test or large
output_path="${data_path}${Size}/"

rm -rf ${prefix_path}${output_path}order_merge/*
echo "${prefix_path}${output_path}order_merge/*"

./merge "${prefix_path}${input_path}" "${N}" "${N}"
#cp "${prefix_path}${output_path}order1/prev_price" "${prefix_path}${output_path}order_merge/prev_price" 
#cp "${prefix_path}${output_path}order1/hook" "${prefix_path}${output_path}order_merge/hook" 
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