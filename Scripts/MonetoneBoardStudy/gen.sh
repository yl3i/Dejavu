#!/bin/bash
for i in $(seq 2 9) T J Q K A; do
  for j in $(seq 2 9) T J Q K A; do
    if [ "$j" \> "$i" ]; then
      for k in $(seq 2 9) T J Q K A; do
        if [ "$j" \< "$k" ]; then
          echo ${i}s${j}s${k}s:1
        fi
      done
    fi
  done
done
