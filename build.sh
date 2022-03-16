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

