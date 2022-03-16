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
echo "${prefix_path}"
echo "${Size}"
echo "${N}"
data_path="${data_path}${Size}/"
echo "${data_path}"
cmake .
make
./split "${prefix_path}100x${N}x${N}/" "1" "${prefix_path}${data_path}" "${N}" "${N}"
#./split "${prefix_path}100x${N}x${N}/" "2" "${prefix_path}${data_path}" "${N}" "${N}"


zstd -T4 /data/team-10/large/test1/stock* --output-dir-flat /data/team-10/large/test1_compress/
path="${prefix_path}${data_path}test1_compress/"
cd ${path}

rm -rf *.success
for ((i=1;i < 11; i++))
do
    for ((j=1;j < 51; j++))
    do
        touch "stock${i}_${j}.zst.success"
        echo success > "stock${i}_${j}.zst.success"
    done
done