#!/bin/bash

touch allResults

chmod 777 allResults bashScript.sh simpshScript.sh execlineScript.sh dashScript.sh tcshScript.sh

sleep 1
./bashScript.sh
sleep 1
./simpshScript.sh
sleep 1
./execlineScript.sh
sleep 1
./dashScript.sh
sleep 1
./tcshScript.sh
sleep 1

cat bashBenchmark >> allResults
cat simpshBenchmark >> allResults
cat execlineBenchmark >> allResults
cat dashBenchmark >> allResults
cat tcshBenchmark >> allResults


