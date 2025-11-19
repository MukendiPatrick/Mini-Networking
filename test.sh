#!/bin/bash

RED="\033[31m"
GRN="\033[32m"
CYN="\033[36m"
NC="\033[0m"

pass() { echo -e "${GRN}PASS${NC}"; }
fail() { echo -e "${RED}FAIL${NC}"; }

echo -e "${CYN}Running NetworkBasics Tests...${NC}"

# ----------------------------------------------------
# Section 1: TCP server builds and starts
# ----------------------------------------------------
echo -n "1. Starting tcp_server... "
./tcp_server > /dev/null 2>&1 &
SERVER_PID=$!
sleep 0.5

if ps -p $SERVER_PID > /dev/null; then
    pass
else
    fail
    exit 1
fi

# ----------------------------------------------------
# Section 2: TCP client connects
# ----------------------------------------------------
echo -n "2. Client connects to server... "
echo "hello" | ./tcp_client > /dev/null 2>&1
if [ $? -eq 0 ]; then pass; else fail; fi

kill $SERVER_PID 2>/dev/null
sleep 0.2

# ----------------------------------------------------
# Section 3: Echo correctness
# ----------------------------------------------------
./tcp_server > /dev/null 2>&1 &
SERVER_PID=$!
sleep 0.2

echo -n "3. Echo check... "
OUTPUT=$(printf "test123" | ./tcp_client | grep "test123")
if [[ "$OUTPUT" != "" ]]; then pass; else fail; fi

kill $SERVER_PID 2>/dev/null
sleep 0.2

# ----------------------------------------------------
# Section 4: UDP demo
# ----------------------------------------------------
echo -n "4. UDP demo runs... "
./udp_demo > /dev/null 2>&1
if [ $? -eq 0 ]; then pass; else fail; fi

echo -e "${CYN}All tests completed.${NC}"
