#!/bin/bash

# Merge main into jbagger
git checkout jbagger
git pull origin main
git merge main

# Check for conflicts
if [ $? -ne 0 ]; then
    echo "Conflict encountered. Please resolve conflicts and commit the changes."
    exit 1
fi

# Push changes to jbagger
git commit -m "Merge 'main' into 'jbagger'"
git push origin jbagger
echo "Merge successful!"