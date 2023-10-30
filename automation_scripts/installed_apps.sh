#!/bin/bash

# Define the output file for the report

voutputFile="installed_apps.txt"

# check the operating system

if [[ "$OSTYPE" == "mysys" || "$OSTYPE" == "cygwin" ]]; then

# Run the 'wmic' command to get the list of installed_apps

wmic product get Name, Version /format:csv > "$voutputFile"

# Display the list in tabular form on standard output

awk -F ',' 'NR==1{h=$0; next} {print} END{print ""; print "Installed Applications List:"; print h}' "$voutputFile" | column -t -s ','

else 
	if [ -x "$(command -v dpkg)" ]; then
		package_manager="dpkg -l"
	elif [ -x "$(command -v rpm)" ]; then
		package_manager="rpm -qa"
	else
		echo "Unsupported package manager."
		exit 1
	fi
fi
