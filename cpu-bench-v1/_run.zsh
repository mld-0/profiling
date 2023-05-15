#!/usr/bin/env zsh

set -o errexit   # abort on nonzero exitstatus
set -o nounset   # abort on unbound variable
set -o pipefail  # don't hide errors within pipes

microtime() { python3 -c 'import time; print(int(time.time_ns()/1000000))' }

run_benchmark() {
    local name="$1"
    local output="$(./$name)"
	local runtime=$(echo "$output" | awk '{print $(NF-1)}')
	runtimes+=( "$runtime" )
	total_runtime=( $( perl -E "say $total_runtime + $runtime" ) )
	outputs+=( "$output" )
}

funcs=( integer-arithemetic float-arithmetic memory-access matrix-multiply parallel-float parallel-sin basic-instructions random-access )

gpp=g++
gpp_args=( -std=c++17 -O3 )

runtimes=()
outputs=()
total_runtime=0

main() 
{
	#	Build Binaries
	echo "build: $gpp ${gpp_args[@]}"
	startTime=$( microtime )
	for func in "${funcs[@]}"; do
		$gpp ${gpp_args[@]} -o "$func" "$func.cpp" -lpthread
	done
	endTime=$( microtime )
	elapsedTime=$( perl -E "say $endTime - $startTime" )
	echo "build time: $elapsedTime ms"


	#	Run Binaries
	startTime=$( microtime )
	for f in "${funcs[@]}"; do
		run_benchmark "$f"
	done
	endTime=$( microtime )
	elapsedTime=$( perl -E "say $endTime - $startTime" )
	runtime_overhead=$( perl -E "printf('%.1f', $elapsedTime - $total_runtime/1000.0)" )
	echo "run time: $elapsedTime ms (overhead: $runtime_overhead ms)"


	#	Delete binaries
	for func in "${funcs[@]}"; do
		rm "$func"
	done


	#	Report percentage runtimes:
	i=1
	runtime_percents=()
	for runtime in "${runtimes[@]}"; do
		runtime_percents+=( "$( perl -E "printf('%.1f', ($runtime / $total_runtime) * 100.0)" )" )
	done
	while [[ $i -le ${#outputs[@]} ]]; do
		echo -n "${outputs[$i]}"
		echo -n " "
		echo "(${runtime_percents[$i]}%)"
		((i++))
	done


	#	Finish
	echo "DONE"
	exit 0
}	

main "$@"

