#!/bin/sh

# Check if there are enough arguments
if [ $# -lt 1 ]; then
    # Find 'naredbi.txt' in the current directory and subdirectories
    dat=$(find . -name "naredbi.txt" | head -1)

    # If 'naredbi.txt' exists
    if [ -n "$dat" ]; then
        # Copy 'naredbi.txt' to the current directory
        cp "$dat" .

        # Find 'actions.txt'
        actions=$(find . -name "actions.txt")

        # If 'actions.txt' exists
        if [ -n "$actions" ]; then
            # Execute the Python script with 'naredbi.txt' and 'actions.txt'
            execute=$(python prva.py naredbi.txt "$actions")

            # Loop through each command returned by the Perl script
            for command in $execute; do
                # Execute the command and capture its output
                tekst=$($command)

                # Check if the output is empty (success)
                if [ -z "$tekst" ]; then
                    echo "OK $command"
                else
                    echo "ERROR $command"
                fi
