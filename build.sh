echo "Enter Your File Path:"
read prefix_path
echo "${prefix_path}"
cmake .
make
./split "${prefix_path}100x10x10/" "1" "${prefix_path}"
./split "${prefix_path}100x10x10/" "2" "${prefix_path}"
./merge "${prefix_path}"
cp "${prefix_path}trade1/prev_price" "${prefix_path}trade_merge/prev_price" 
