#!/bin/bash
# 
# getprosjs.sh - update all projects of an organization in GitHub/Lab
#
#   Copyright (c) 2014, Francisco José Monaco <moanco@icmc.usp.br>
#
#   This file is part of POSIXeg-solved
#
#   POSIXeg-solved is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.


# CONFIGURATION
#
# The list of projects to be updated is obtained from PROJLIST file (blank lines
# and lines starting with '#' are discarted). Projects are cloned from 
# GITRUL/<project_name> into PROJDIR/<project_name>, if a local respository is not
# found in that directory; otherwise, the project is pulled. Errors are reported in
# file LOGFILE.

PROJLIST=projs.txt
GITURL=git@github.com:SOII-2016
LOGFILE=getprojs.log
PROJDIR=/tmp/projs

# For here on, you don't probably need to touch.

nprojs=0			# Number of projects (total)
nclone=0			# Number of repositories to clone
npull=0	         		# Number of repositories to pull
nerrors=0			# Number of errors found

rm -f $LOGFILE			# Remove previous logs

# Look for PROJFILE
if ! test -f $PROJLIST ; then
    echo "Can't find $PROJLIST"
    exit 1
fi


# Prepare destination directory

if ! test -d $PROJDIR; then
    install -d $PROJDIR
    if test $? -ne 0; then
	echo "Can't create $PROJDIR"
	exit 1
    fi
fi

# Start cloning attempts

while read proj || test -n "$proj" ; do

    # Discard blank and comment lines
    if (! test -n "$proj") || (! test "${proj:0:1}" != "#"); then 
	continue
    fi
    
    nprojs=$((nprojs+1))


    if test -d $PROJDIR/$proj; then
	
	# Local repository found: trying to clone.

	npull=$((npull+1))
	echo -n "Trying to pull $proj..."
	(cd $PROJDIR/$proj && git pull &> /dev/null)
	
	# Report errors
	if test $? -ne 0; then
	    echo "FAILED"
	    echo "Faild to pull $proj " >> $LOGFILE
	    nerrors=$((nerrors+1))
	else
	    echo "Done."
	fi


    else

	# Loca repository not found: trying to clone.

	nclone=$((nclone+1))
	
	# Try to clone
	echo -n "Trying to cone $proj..."
	git clone $GITURL/$proj $PROJDIR/$proj 2> /dev/null
	
	# Report errors
	if test $? -ne 0; then
	    echo "FAILED"
	    echo "Faild to clone $proj" >> $LOGFILE
	    nerrors=$((nerrors+1))
	else
	    echo "Done."
	fi


    fi
    

    
done < $PROJLIST

echo 
if test $nerrors -gt 0; then
    echo "Tried to clone $nclone and pull $npull of $nprojs repositories"
    echo "Got $nerrors errors; see $LOGFILE"
else
    echo "Sucessfully updated " $((nclone+npull)) " of $nprojs repositories"
fi
echo 

