#!/bin/bash
top -n 1 > tmp
cat tmp | awk 'NR>7{print  "pid->" $2 "\tcpu->" $10 "\tmem->" $11}'

