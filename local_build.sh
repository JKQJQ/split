echo "Enter Your File Path:"
read prefix_path
echo "${prefix_path}"
cmake .
make
./split "${prefix_path}100x10x10/" "1" "${prefix_path}team-10/"
./split "${prefix_path}100x10x10/" "2" "${prefix_path}team-10/"
./merge "${prefix_path}team-10/"
cp "${prefix_path}team-10/trade1/prev_price" "${prefix_path}team-10/trade_merge/prev_price" 
