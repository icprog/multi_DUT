#!bin/bash
tftp -g -l /Test/ledsever -r download/ledsever 10.0.0.150
tftp -g -l /Test/TestPerf -r download/TestPerf 10.0.0.150
tftp -g -l /Test/ucp -r download/ucp 10.0.0.150
tftp -g -l /Test/ftpc -r download/ftpc 10.0.0.150
tftp -g -l /Test/iperf -r download/iperf 10.0.0.150
tftp -g -l /Test/test.sh -r download/test.sh 10.0.0.150
cd /Test
chmod 777 *
tftp -g -l /boot/ftdi_sio.ko -r download/ftdi_sio.ko 10.0.0.150
tftp -g -l /boot/usbserial.ko -r download/usbserial.ko 10.0.0.150
tftp -g -l /boot/mv_i2c.ko -r download/mv_i2c.ko 10.0.0.150
