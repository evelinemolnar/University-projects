#
#Scrieti un script bash care sorteaza descrescator dupa dimensiune toate 
#fisierele date ca argumente la linia de comanda.
#(intai verificati daca un argument fisier)
#!/bin/bash
if [ -z "$1" ]; then
    echo "No parameters given"
    exit 1
fi

for f in $@; do
  
  if test -f $f; then
    du -k $f
  else
    echo "Argumentul $f nu e un fisier" 
  fi
done | sort -n -r
