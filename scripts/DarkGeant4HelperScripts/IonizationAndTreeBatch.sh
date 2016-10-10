#!/bin/bash

./SplitGeant4Output.py

N=2
(
for i in `seq 1 10000`;
do

	./ParseSplitGeant4Output.py -read Event_${i} -tree -output-ionization DarkGeantData_${i} > tree_${i} &

done
)

touch DarkGeantData

for i in `seq 1 10000`;
do

	echo -e "\nEvent ${i}\n" >> DarkGeantData
	cat DarkGeantData_${i} >> DarkGeantData

done


