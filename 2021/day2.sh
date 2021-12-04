#!/bin/bash
input="./input_day2"
forward="0"
down="0"
up="0"

forward=$(grep "forward" $input | cut -d " " -f 2 | awk '{s+=$1} END {print s}')
down=$(grep "down" $input | cut -d " " -f 2 | awk '{s+=$1} END {print s}')
up=$(grep "up" $input | cut -d " " -f 2 | awk '{s+=$1} END {print s}')
pos=$((up-down))
pos=${pos#-}
echo $((pos*forward))
aim="0"
forward="0"
down="0"
up="0"
sum="0"

while :
do
  read -r line1
  if [[ "$line1" == "" ]]; then break; fi
  step=$(echo $line1| cut -d " " -f 1)
  value=$(echo $line1| cut -d " " -f 2)

  if [[ $step = "forward" ]]; then
    current=$((value*aim))
    current=${current#-}
    sum=$((sum+current))
  fi
  if [[ $step = "up" ]]; then
    aim=$((aim-value))
  fi
  if [[ $step = "down" ]]; then
    aim=$((aim+value))
  fi

done < "$input"

forward=$(grep "forward" $input | cut -d " " -f 2 | awk '{s+=$1} END {print s}')

echo $((forward*sum))