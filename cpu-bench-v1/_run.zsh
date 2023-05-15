#!/usr/bin/env zsh

set -o errexit   # abort on nonzero exitstatus
set -o nounset   # abort on unbound variable
set -o pipefail  # don't hide errors within pipes

gpp=g++
gpp_args=( -std=c++17 -O3 )
echo "gpp=($gpp), gpp_args=(${gpp_args[@]})"

startTime=$( python3 -c 'import time; print(int(time.time_ns()/1000000))' )
$gpp ${gpp_args[@]} -o integer-arithemetic integer-arithemetic.cpp
$gpp ${gpp_args[@]} -o float-arithmetic float-arithmetic.cpp
$gpp ${gpp_args[@]} -o memory-access memory-access.cpp
$gpp ${gpp_args[@]} -o matrix-multiply matrix-multiply.cpp
$gpp ${gpp_args[@]} -o parallel-float parallel-float.cpp
$gpp ${gpp_args[@]} -o parallel-sin parallel-sin.cpp
$gpp ${gpp_args[@]} -o basic-instructions basic-instructions.cpp
$gpp ${gpp_args[@]} -o random-access random-access.cpp
endTime=$( python3 -c 'import time; print(int(time.time_ns()/1000000))' )
elapsedTime=$( perl -E "say $endTime - $startTime" )
echo "build time: $elapsedTime ms"

startTime=$( python3 -c 'import time; print(int(time.time_ns()/1000000))' )
./integer-arithemetic
./float-arithmetic
./memory-access
./matrix-multiply
./parallel-float
./parallel-sin
./basic-instructions
./random-access
endTime=$( python3 -c 'import time; print(int(time.time_ns()/1000000))' )
elapsedTime=$( perl -E "say $endTime - $startTime" )
echo "run time: $elapsedTime ms"

rm integer-arithemetic
rm memory-access
rm matrix-multiply
rm float-arithmetic
rm parallel-float
rm parallel-sin
rm basic-instructions
rm random-access

