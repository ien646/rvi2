read -p "`echo $'\n.'` THIS WILL RESET THE WORKING DIRECTORY TO THE LATEST COMMIT `echo $'\n.'` CONTINUE? (Y/N) " -n 1 -r
echo    # (optional) move to a new line
if [[ $REPLY =~ ^[Yy]$ ]]
then
    git clean -d -x -f
	git reset --hard
fi
