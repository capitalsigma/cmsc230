RESULT_BASE=../results
INPUT=../input
EX=../code/main.out

make -C ../code main



for x in $(seq 1 2)
do
	for s in 16 32 64 128 256 512 1024
	do
		P="${EX} ${INPUT}/${s}_node.txt"
		${P} >> ${RESULT_BASE}/serial-$s.txt
		for t in 1 2 4 6 8 16 32 64
		do
			${P} ${t} >> ${RESULT_BASE}/par-$s-$t.txt
		done
	done
done
		
		
