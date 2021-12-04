#!/bin/bash
input="./input_day3"
gamma=""
epsilon=""
oxygen=""
co2=""
cp $input tmpOxygen
cp $input tmpCO2

for ((i=1;i<=12;i++));
do
  cat input_day3 | cut -c$i | grep 0 > tmpList0
  cat input_day3 | cut -c$i | grep 1 > tmpList1
  bit0=$(cat tmpList0 | wc -l)
  bit1=$(cat tmpList1 | wc -l)

  if [[ $bit0 -gt $bit1 ]]; then
    gamma=$gamma"0"
    epsilon=$epsilon"1"
  else
    gamma=$gamma"1"
    epsilon=$epsilon"0"
  fi
 
  if [[ $oxygen == "" ]]; then
    countO=$(cat tmpOxygen | wc -l)
    if [[ $countO == 1 ]]; then
      oxygen=$(cat tmpOxygen)
    else
      bit0Oxygen=$(awk -F '' '$'$i' == "0"' tmpOxygen | wc -l)
      bit1Oxygen=$(awk -F '' '$'$i' == "1"' tmpOxygen | wc -l)
      if [[ $bit0Oxygen -gt $bit1Oxygen ]]; then
        awk -F '' '$'$i' == "0"' tmpOxygen > tmp
      else
        awk -F '' '$'$i' == "1"' tmpOxygen > tmp
      fi
      cp tmp tmpOxygen
      countO=$(cat tmpOxygen | wc -l)
      if [[ $countO == 1 ]]; then
        oxygen=$(cat tmpOxygen)
      fi
    fi
  fi

  if [[ $co2 == "" ]]; then
    countC=$(cat tmpCO2 | wc -l)
    if [[ $countC == 1 ]]; then
      co2=$(cat tmpCO2)
    else
      bit0CO2=$(awk -F '' '$'$i' == "0"' tmpCO2 | wc -l)
      bit1CO2=$(awk -F '' '$'$i' == "1"' tmpCO2 | wc -l)

      if [[ $bit0CO2 -gt $bit1CO2 ]]; then
        awk -F '' '$'$i' == "1"' tmpCO2 > tmp
      else
        awk -F '' '$'$i' == "0"' tmpCO2 > tmp
      fi
      cp tmp tmpCO2
      countC=$(cat tmpCO2 | wc -l)
      if [[ $countC == 1 ]]; then
        co2=$(cat tmpCO2)
      fi
    fi
  fi
done

binGamma=$(echo 'obase=10;ibase=2;'$gamma|bc)
binEpsilon=$(echo 'obase=10;ibase=2;'$epsilon|bc)

binOxygen=$(echo 'obase=10;ibase=2;'$oxygen|bc)
binCO2=$(echo 'obase=10;ibase=2;'$co2|bc)

echo $((binGamma*binEpsilon))
echo $((binOxygen*binCO2))

rm tmpList0 tmpList1 tmpCO2 tmpOxygen tmp