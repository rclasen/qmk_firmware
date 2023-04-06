for flashing:

# hold reset button on RPI while connecting USB

sudo mount /dev/sdb1 /media/cdrom -ouid=$EUID
make uf2-flash-left
sudo umount /media/cdrom
