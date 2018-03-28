#!/bin/sh
cd ../sipApp_tkj/
make clean
make
cd ../test/
mv ../sipApp_tkj/bin/libUserAgent.so /home/rootfs/vt/fs_k2268s/mnt/user_rootfs/usr/lib

# compile 
#make -f  Makefile_copy.testser clean
#make -f  Makefile_copy.testser
#cp -R bin/mips /home/rootfs/vt/fs_k2268s/mnt/user_rootfs/usr/sbin/
