#!/bin/bash

BACKUPDIR=../backup

install -d $BACKUPDIR

ACTION="$1"
ACT_BACKUP="back"
ACT_SAVE="save"
ACT_RESTORE="restore"

if test "$ACTION" == "$ACT_BACKUP"; then

    #Remove tempfiles
    for i in $(find .) ; do
	if test -z ${i%%*~}; then
	    rm $i;
	fi
    done

    tar zcvf $BACKUPDIR/current.tgz *
    echo "Backed up current state in    $BACKUPDIR/current.tgz"
    echo
    exit 0
    
fi

if test "$ACTION" == "$ACT_SAVE"; then

    cp -f $BACKUPDIR/current.tgz $BACKUPDIR/safe.tgz
    echo "Backed up last saved state in $BACKUPDIR/safe.tgz"
    echo  
    exit 0
fi


if test "$ACTION" == "$ACT_RESTORE"; then
    echo -n "Restore last saved current state (y/n)? "
    read x
    if test "$x" == "y" || test "$x" == "Y"; then
	rm -r *
	cp $BACKUPDIR/bach.sh .
	cp $BACKUPDIR/current.tgz .
	tar zxvf current.tgz
	rm current.tgz
	echo "Restored previous state."
    else
	echo "Aborted"
    fi
    exit 0
fi



echo
echo "Usage back.sh <back|save|restore>"
echo 
echo "      $ACT_BACKUP:    bakcup current state"
echo "      $ACT_SAVE:   saving previous backup and backup current state" 
echo "      $ACT_RESTORE: restore current state"
echo 
exit 1
