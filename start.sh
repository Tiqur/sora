#!/bin/sh

# Start search
parallel LD_LIBRARY_PATH=/opt/arrayfire/lib64 ./sora ::: $(seq $THREADS) &

# Ping server every second
while sleep 2; do
  CONNECTED_USERS=$(curl -s -X GET -H "Content-Type: application/json" -d "{\"user\": \"${USER}\"}" http://149.28.75.54/api)
  printf "\033c \033[0;0H---Slime Chunk Cluster Finder---
Uptime: $(date +"%T")
Connected users: $CONNECTED_USERS
Threads: $THREADS"
done

