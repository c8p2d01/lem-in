#!/bin/bash

PFAD=$(pwd | awk -F '/' '{print $NF}')
PFAD2="lem-in"
if [[ $PFAD == $PFAD2 ]]
then
	DIR="./tester/"
	# handle input
	cat > $DIR"raw"
else
	DIR="./"
fi

# extract end node -> the only duplicate allowed
END=$(cat $DIR"raw" | grep "TESTER" | awk -F ':' '{printf $NF}')

# extract lines of useful output (needs improvements against nodenames containing the L key)
cat $DIR"raw" | grep "L" > $DIR"lines"
LINES=$(cat $DIR"lines" | wc -l)

echo $LINES " lines of output"

rm $DIR"all_steps" $DIR"dup_test"
for ((c=1; c<=$LINES; c++))
do
	# # print each line
	#cat $DIR"lines" | sed -n $c\p

	# turn each line into its own file, to exame the combined steps of a line together
	cat $DIR"lines" | sed -n $c\p | xargs -n1 > $DIR"single_line"

	# extract the rooms the ans move to and check if there are any duplicates except the end node
	cat $DIR"single_line" | grep -v "$END" | awk -F'-' '{print $NF}' | awk -v line=$c 'a[$0]++{print line" dupes"; exit(1)}' && echo "no dupes" >> $DIR"dup_test"

	# collect all steps in another file
	cat $DIR"lines" | sed -n $c\p | xargs -n1 >> $DIR"all_steps"
done

# sum up the duplication results
DUP=$(cat $DIR"dup_test" | sort | uniq)

# count how many ants appear in the output
ANTS=$(cat $DIR"all_steps" | awk -F'-' '{print $1}' | sort | uniq | wc -l)

# count how many ants ended up at the end
ARRIVED=$(cat $DIR"all_steps" | grep "$END" | wc -l)

echo $DUP
echo $ANTS " ants started, " $ARRIVED " arrived at the end node"
echo "in this quick check path validity is not checked, but if no dupes are detected, no node is in dual use at any point."

# delete all files except "tester.sh" from this directory
ls */*| grep "tester/" | grep -v "tester.sh" | xargs rm
