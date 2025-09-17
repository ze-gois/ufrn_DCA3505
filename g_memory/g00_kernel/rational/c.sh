#!/bin/zsh

# Find all directories except the current one and iterate over them
for dir in $(find . -mindepth 1 -maxdepth 1 -type d); do
    echo "Entering directory: $dir"
    cd "$dir" || { echo "Failed to enter $dir"; exit 1; }

    # Run make and check for errors
    if make; then
        echo "Successfully compiled in $dir"
    else
        echo "Compilation failed in $dir"
        exit 1
    fi

    cd - > /dev/null || { echo "Failed to return to parent directory"; exit 1; }
done
