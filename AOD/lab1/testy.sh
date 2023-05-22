#!/bin/bash
# NOTE : Quote it else use array to avoid problems #
g++ -Wall zad2/topsort.cpp -o zad2/topsort
g++ -Wall zad3/trojan.cpp -o zad3/trojan
g++ -Wall zad4/bipartite.cpp -o zad4/bipartite


rm wyniki2.txt
FILES="2/*"
for f in $FILES
do
  echo "Processing $f file..."
  echo "Wyniki dla pliku $f" >> wyniki2.txt
  zad2/./topsort $f >> wyniki2.txt
  echo "" >> wyniki2.txt
  echo "--------------------------------------------------------" >> wyniki2.txt
  echo "" >> wyniki2.txt
  
  # take action on each file. $f store current file name
done

rm wyniki3.txt
FILES3="3/*"
for f in $FILES3
do
  echo "Processing $f file..."
  echo "Wyniki dla pliku $f" >> wyniki3.txt
  zad3/./trojan $f >> wyniki3.txt
  echo "" >> wyniki3.txt
  echo "--------------------------------------------------------" >> wyniki3.txt
  echo "" >> wyniki3.txt
  
  # take action on each file. $f store current file name
done

rm wyniki4.txt
FILES4="4/*"
for f in $FILES4
do
  echo "Processing $f file..."
  echo "Wyniki dla pliku $f" >> wyniki4.txt
  zad4/./bipartite $f >> wyniki4.txt
  echo "" >> wyniki4.txt
  echo "--------------------------------------------------------" >> wyniki4.txt
  echo "" >> wyniki4.txt
  
  # take action on each file. $f store current file name
done
