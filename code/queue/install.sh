#!/bin/bash
cp ./main /usr/local/bin/APSSafeService
cp ./APSSafeService /etc/init.d/
cd /etc/init.d/
chmod +x APSSafeService