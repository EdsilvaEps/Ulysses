#!/bin/bash

# installation script for UlyssesApp services

# add a way to get the python path
PYTHON='/usr/bin/python3'
SCRIPTLOC='/home/edson/Documents/Ulysses/Ulysses-scripts/ulyDaemon.py'
# searchPython()

rm -rf /etc/systemd/system/ulyssesd.service
# create systemd file for python
echo "Installing daemon"

echo "[Unit]" > /etc/systemd/system/ulyssesd.service
echo -e "Description=Ulysses App Daemon\n" >> /etc/systemd/system/ulyssesd.service

echo "[Service]" >> /etc/systemd/system/ulyssesd.service
echo "ExecStart=$PYTHON $SCRIPTLOC" >> /etc/systemd/system/ulyssesd.service
echo -e "Restart=always\n" >> /etc/systemd/system/ulyssesd.service

echo "[Install]" >> /etc/systemd/system/ulyssesd.service
echo "WantedBy=multi-user.target" >> /etc/systemd/system/ulyssesd.service

sudo systemctl enable ulyssesd.service
sudo systemctl start ulyssesd.service