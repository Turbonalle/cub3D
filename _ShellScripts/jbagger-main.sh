#!/bin/bash

# Merge jbagger into main
git checkout main
git pull origin jbagger
git merge jbagger

# Check for conflicts
if [ $? -ne 0 ]; then
    echo "Conflict encountered. Please resolve conflicts and commit the changes."
    exit 1
fi

# Push changes to main
git commit -m "Merge 'jbagger' into 'main'"
git push origin main
echo "Merge successful!"