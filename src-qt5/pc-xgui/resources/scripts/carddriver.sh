#!/bin/sh

# Check for Monitor name
INMON="0"

while read line
do
  # Check if we are in the device section
  if [ "$INMON" = "0" ]
  then
    echo "$line" | grep "Section" | grep '"Device"' >/dev/null 2>/dev/null
    if [ "$?" = "0" ]
    then
      INMON="1"
    fi
  else 
    # Check if we are leaving the Device section
    echo "$line" | grep "EndSection" >/dev/null 2>/dev/null
    if [ "$?" = "0" ]
    then
      INMON="0"
    else
      echo "$line" | grep -v "#" | grep "Driver" >/dev/null 2>/dev/null
      if [ "$?" = "0" ]
      then
         echo "$line" | cut -d '"' -f 2
	 break
      fi
    fi
    
  fi

done < '/root/xorg.conf.new'
