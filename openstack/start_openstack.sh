#!/bin/bash

# rabbitmq
sudo service rabbitmq-server restart

# glance
cd /opt/stack/glance
/opt/stack/glance/bin/glance-registry --config-file=/etc/glance/glance-registry.conf > \
/var/log/nova/glance-registry.log 2>&1 &
echo "glance-registery started"
/opt/stack/glance/bin/glance-api --config-file=/etc/glance/glance-api.conf > \
/var/log/nova/glance-registry.log 2>&1 &
echo "Waiting for glance-api to start..."
if ! timeout 60 sh -c "while ! wget --no-proxy -q -O- http://127.0.0.1:9292;
do sleep 1; done"; then
        echo "glance-api failed to start"
        exit 1
fi

# keystone
cd /opt/stack/keystone
/opt/stack/keystone/bin/keystone-all --config-file /etc/keystone/keystone.conf --log-config /etc/keystone/logging.conf -d --debug > \
/var/log/nova/keystone.log 2>&1 &
echo "Waiting for Keystone to start..."
if ! timeout 60 sh -c "while ! wget --no-proxy -q -O- http://127.0.0.1:5000;
do sleep 1; done"; then
        echo "keystone failed to start"
        exit 1
fi

# nova
cd /opt/stack/nova/bin
./nova-api > /var/log/nova/nova-api.log 2>&1 &
echo "Waiting for nova-api to start..."
if ! timeout 60 sh -c "while ! wget --no-proxy -q -O- http://127.0.0.1:8774;
do sleep 1; done"; then
        echo "nova-api failed to start"
        exit 1
fi
sg libvirtd /opt/stack/nova/bin/nova-compute > /var/log/nova/nova-compute.log 2>&1 &
echo "nova-compute started"
./nova-cert > /var/log/nova/nova-cert.log 2>&1 &
echo "nova-cert started"
./nova-scheduler > /var/log/nova/nova-scheduler.log 2>&1 &
echo "nova-scheduler started"
cd /opt/stack/noVNC
./utils/nova-novncproxy --config-file /etc/nova/nova.conf --web . > \
/var/log/nova/nova-novncproxy.log 2>&1 &
cd /opt/stack/nova/bin
./nova-xvpvncproxy --config-file /etc/nova/nova.conf > \
/var/log/nova/nova-xvpvncproxy.log 2>&1 &
echo "nova vncproxies started"
./nova-consoleauth > /var/log/nova/nova-consoleauth.log 2>&1 &
./nova-network > /var/log/nova/nova-network.log 2>&1 &
echo "nova-network started"
./nova-objectstore > /var/log/nova/nova-objectstore.log 2>&1 &
echo "started nova-objectstore"

# cinder 
cd /opt/stack/cinder
/opt/stack/cinder/bin/cinder-api --config-file /etc/cinder/cinder.conf > \
/var/log/nova/cinder-api.log 2>&1 &
/opt/stack/cinder/bin/cinder-volume --config-file /etc/cinder/cinder.conf > \
/var/log/nova/cinder-volume.log 2>&1 &
/opt/stack/cinder/bin/cinder-scheduler --config-file /etc/cinder/cinder.conf > \
/var/log/nova/cinder-scheduler.log 2>&1 &
echo "started cinder services"

# apache for horizon
sudo service apache2 restart
echo "restarted apache - horizon"

