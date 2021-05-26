#!/bin/sh

systemctl status lxd > /dev/null 2>&1
LXDRUNNING=$?

if [ $LXDRUNNING -ne 0 ]; then
   systemctl start lxd > /dev/null 2>&1
fi

cat <<EOF | lxd init --preseed
config: {}
cluster: null
networks: []
storage_pools:
- config: {}
  description: ""
  name: default
  driver: dir
profiles:
  - name: default
    description: Default LXD profile  for OpenNebula
    config:
       limits.cpu: "1"
       limits.cpu.allowance: 50%
       limits.memory: 512MB
       security.idmap.base: "100000"
       security.idmap.isolated: "true"
       security.idmap.size: "65536"
    devices:
      root:
        path: /
        pool: default
        type: disk
EOF
