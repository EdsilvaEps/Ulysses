#!/bin/bash

# linux installation script for UlyssesApp services 

# add a way to get the python path
SYSHOME=$(echo $HOME)
ULYSSESFILE='ulysses.desktop'
SCRIPTLOC=$SYSHOME'/ulyDaemon.py' # make this flexible
ULYSSESPATH=$SYSHOME'/Documents/Ulysses/build-UlyssesApp-Desktop_Qt_6_4_0_GCC_64bit-Debug/UlyssesApp'
CONFIGDIR=$SYSHOME'/.config/autostart'
# searchPython()

if test -f "$CONFIGDIR"; then
    echo "$CONFIGDIR exists."
    sudo rm -rf $CONFIGDIR/$ULYSSESFILE
else
    echo "$CONFIGDIR does not exist, creating..."
    mkdir $CONFIGDIR
fi

# create .desktop file for UlyssesApp
echo "Installing UlyssesApp"

echo "[Desktop Entry]" >> $CONFIGDIR/$ULYSSESFILE
echo "Type=Application" >> $CONFIGDIR/$ULYSSESFILE
echo "Name=UlyssesApp" >> $CONFIGDIR/$ULYSSESFILE
echo "Exec=$ULYSSESPATH" >> $CONFIGDIR/$ULYSSESFILE
echo "Comment=Ulysses Interface Initializer" >> $CONFIGDIR/$ULYSSESFILE
echo "X-GNOME-Autostart-enabled=true" >> $CONFIGDIR/$ULYSSESFILE