#!/sbin/sh

busybox rm -r /system/lib/modules
busybox rm /system/etc/init.qcom.post_boot.sh 
busybox rm /system/etc/perf-boot.sh
busybox rm /system/etc/post-init.sh 
busybox mkdir -p /system/lib/modules
