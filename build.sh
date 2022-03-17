#!/bin/bash
######## VARIABLES ################
# SPLIT_FILE=/data/100x1000x1000/
# TRADER_ID=1
# OUTPUT_FILE=/data/team-10/large/test${TRADER_ID}
# N=1000 #small: 10 medium: 100 large:1000

SPLIT_FILE=/data/100x10x10/
TRADER_ID=1
OUTPUT_FILE=/data/team-10/small/test${TRADER_ID}
N=10 #small: 10 medium: 100 large:1000
######### END ###############

######## TEST_VARIABLES ################
# ANNOTHE_TRADER_ID=2
# ANOTHER_OUTPUT_FILE=/data/team-10/large/test${ANNOTHE_TRADER_ID}

ANNOTHE_TRADER_ID=2
ANOTHER_OUTPUT_FILE=/data/team-10/small/test${ANNOTHE_TRADER_ID}
######### END ###############
cmake .
make
./split ${SPLIT_FILE} ${TRADER_ID} ${OUTPUT_FILE} ${N}  ${N}
./split ${SPLIT_FILE} ${ANNOTHE_TRADER_ID} ${ANOTHER_OUTPUT_FILE} ${N}  ${N}


