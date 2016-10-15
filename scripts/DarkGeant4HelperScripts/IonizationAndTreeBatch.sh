#!/bin/bash


./SplitAndParseDarkGeantData.py

touch DarkGeantData

for i in `seq 1 10000`;
do

	echo -e "\nEvent ${i}\n" >> DarkGeantData
	cat DarkGeantData_${i} >> DarkGeantData

done


