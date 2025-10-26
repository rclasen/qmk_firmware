for flashing:

# hold boot button on RPI while connecting USB
# or double-tap reset

sudo mount /dev/sdb1 /media/cdrom -ouid=$EUID
make eeleft # eeright
sudo umount /media/cdrom
