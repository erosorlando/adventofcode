#!/bin/bash
input="./input"
sumcurrent="0"
sumprevious="100000000000"
line1="0"
line2="0"
line3="0"
counter=0
while :
do
  line1=$line2
  line2=$line3
  read -r line3
  if [[ "$line3" == "" ]]; then break; fi
  if [[ "$line1" == "0" ]]; then continue; fi
  if [[ "$line2" == "0" ]]; then continue; fi
  sumcurrent=$(expr $line1 + $line2 + $line3)

  echo "prev: $sumprevious"
  echo "curr: $sumcurrent
  if [[ "$sumcurrent" -gt "$sumprevious" ]]; then
    echo "$sumcurrent maggiore di $sumprevious"
    let counter++
  fi

  sumprevious="$sumcurrent"
done < "$input"

echo "$counter"