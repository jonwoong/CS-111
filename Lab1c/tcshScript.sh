#!/bin/tcsh -f

touch randomFileA randomFileB 
touch resultFile1 resultFile2 resultFile3
touch tcshBenchmark
base64 /dev/urandom | head -c 10000000 > randomFileA
base64 /dev/urandom | head -c 10000000 > randomFileB

echo "TCSH: Running benchmark 1"
echo "TCSH Benchmark 1:\n" >> tcshBenchmark
set count = 0
while ($count<5)
	(/usr/bin/time -p cat randomFileA | sort | tr A-Z a-z > resultFile1) |& cat >> tcshBenchmark
	printf "\n" >> tcshBenchmark
	set count=`expr $count + 1`
end
printf "\n" >> tcshBenchmark

echo "TCSH: Running benchmark 2"
echo "TCSH Benchmark 2:\n" >> tcshBenchmark
set count = 0
while ($count<5)
	(/usr/bin/time -p sort randomFileA | cat > resultFile1 && sort randomFileB | cat > resultFile2 && comm resultFile1 resultFile2 > resultFile3) |& cat >> tcshBenchmark
	printf "\n" >> tcshBenchmark
	set count=`expr $count + 1`
end
printf "\n" >> tcshBenchmark

echo "TCSH: Running benchmark 3"
echo "TCSH Benchmark 3:\n" >> tcshBenchmark
set count = 0
while ($count<5)
	(/usr/bin/time -p sort randomFileA | cat > resultFile1 && sort randomFileB | cat > resultFile2 && wc randomFileA randomFileB > resultFile3) |& cat >> tcshBenchmark
	printf "\n" >> tcshBenchmark
	set count=`expr $count + 1`
end
printf "\n" >> tcshBenchmark

rm randomFileA randomFileB
rm resultFile1 resultFile2 resultFile3