cmake .
make
./split "/Users/gjy/JK_Contest/split/100x10x10/" "1" "/Users/gjy/JK_Contest/split/"
./split "/Users/gjy/JK_Contest/split/100x10x10/" "2" "/Users/gjy/JK_Contest/split/"
./merge "/Users/gjy/JK_Contest/split/"
cp /Users/gjy/JK_Contest/split/trade1/prev_price /Users/gjy/JK_Contest/split/trade_merge/prev_price
