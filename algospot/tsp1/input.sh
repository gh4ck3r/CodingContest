#!/bin/bash
nCase=$(($1))
nCity=$(($2))

echo "Generating $nCase with $nCity cities" >&2

declare -a cities;
for ((city=0; city < $nCity; ++city));do
  cities[$city]="$((RANDOM%100)) $((RANDOM%100))"
done

echo $nCase
for ((case=0; case < $nCase; ++case));do
  echo $nCity
  for ((from=0; from < $nCity; ++from)); do
    read fromX fromY <<< ${cities[$from]};
    for ((to=0; to < $nCity; ++to)); do
      if [[ $from = $to ]];then
        echo -n "0 ";
        continue;
      fi
      read toX toY <<< ${cities[$to]}
      bc -l <<< "scale=10; sqrt($(($fromX - $toX))^2 + $(($fromY - $toY))^2) " | tr -d '\n'
      echo -n " "
    done
    echo
  done
done
