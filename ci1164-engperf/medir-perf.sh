#!/bin/bash

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

#for i in 32 50 64 100 128 200 256 300 400 512 1000 1024 2000 2048 3000 4000 4096 5000 10000; do
for i in 32; do
    for g in L3 L2CACHE FLOPS_DP FLOPS_AVX ; do
	echo "n = ${i}; grupo = ${g}"
	likwid-perfctr -O --output $g$i.csv -C 3 -g $g -m ./matmult -n $i

	if [[ $g = "L3" ]]; then
	    grep -E 'multMatPtrVet|L3 bandwidth' $g$i.csv
	    grep -E 'multMatRowVet|L3 bandwidth' $g$i.csv
	    grep -E 'multMatColVet|L3 bandwidth' $g$i.csv
	fi
	
	if [[ $g = "L2CACHE" ]]; then
	    grep -E 'multMatPtrVet|L2 miss ratio' $g$i.csv
	    grep -E 'multMatRowVet|L2 miss ratio' $g$i.csv
	    grep -E 'multMatColVet|L2 miss ratio' $g$i.csv
	fi
	
	if [[ $g = "FLOPS_DP" ]]; then
	    grep -E 'multMatPtrVet|DP MFLOP/s' $g$i.csv
	    grep -E 'multMatRowVet|DP MFLOP/s' $g$i.csv
	    grep -E 'multMatColVet|DP MFLOP/s' $g$i.csv
	fi

	if [[ $g = "FLOPS_AVX" ]]; then
	    grep -E 'multMatPtrVet|AVX DP MFLOP/s' $g$i.csv
	    grep -E 'multMatRowVet|AVX DP MFLOP/s' $g$i.csv
	    grep -E 'multMatColVet|AVX DP MFLOP/s' $g$i.csv
	fi
    
    done
done 

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor
