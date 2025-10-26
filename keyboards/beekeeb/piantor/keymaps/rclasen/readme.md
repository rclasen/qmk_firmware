for flashing:

# hold reset button on RPI while connecting USB

sudo mount /dev/sdb1 /media/cdrom -ouid=$EUID
make eeleft # eeright
sudo umount /media/cdrom
