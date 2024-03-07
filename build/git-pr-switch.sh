#!/bin/sh
#
# Checkout a (PR) fork branch locally for testing.
#
#

echo
echo "git-pr-switch.sh -- Checkout a (PR) fork branch locally for testing."
echo
echo "Clean up your working directory before running this script."
echo
read -p "Enter fork author username: " FORK_USERNAME
echo $FORK_USERNAME
read -p "Enter fork branch name: " FORK_BRANCH
echo $FORK_BRANCH
FORK_LOCAL=$FORK_BRANCH"-testing"
echo "Creating new local branch for testing: "$FORK_LOCAL" ..."
git checkout -B $FORK_LOCAL
echo "Pulling changes from user's branch into new local branch..."
git pull https://github.com/$FORK_USERNAME/ZealOS.git $FORK_BRANCH


