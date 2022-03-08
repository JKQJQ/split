data_path="team-10/large/"
echo "Enter Your File Path:"
read prefix_path
echo "${prefix_path}"
echo "${prefix_path}${data_path}"
cmake .
make
./split "${prefix_path}100x1000x1000/" "1" "${prefix_path}${data_path}"
./split "${prefix_path}100x1000x1000/" "2" "${prefix_path}${data_path}"

./merge "${prefix_path}${data_path}"
cp "${prefix_path}${data_path}trade1/prev_price" "${prefix_path}${data_path}trade_merge/prev_price" 
cp "${prefix_path}${data_path}trade1/hook" "${prefix_path}${data_path}trade_merge/hook" 