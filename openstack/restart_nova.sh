#!/bin/bash

# kill existing nova-compute processes
ps -ef | grep -v grep | grep nova-compute |  awk '{print $2}' | xargs sudo kill -9
echo "nova-compute stopped"

# start nova-compute
cd /opt/stack/nova/bin
sg libvirtd /opt/stack/nova/bin/nova-compute > /var/log/nova/nova-compute.log 2>&1 &
echo "nova-compute started"

