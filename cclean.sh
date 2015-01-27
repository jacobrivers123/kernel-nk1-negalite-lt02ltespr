#!/bin/sh

export PARENT=`readlink -f .`
export INITRAMFS=$PARENT/compiled
export INSTALLER=$PARENT/compiled/installer

echo " "
export USE_CCACHE=1
export CCACHE_DIR=/usr/arm-cortex_a15-linux-gnueabihf-linaro_4.9.3/bin-ccache
export PATH=/usr/arm-cortex_a15-linux-gnueabihf-linaro_4.9.3/bin-ccache:/usr/arm-cortex_a15-linux-gnueabihf-linaro_4.9.3/bin:$PATH
ccache -M 25G

echo " "
echo "**************************************************************"
echo "**************************************************************"
echo "                Cleaning Up Old Install Files                 "
echo "**************************************************************"
echo "**************************************************************"
echo " "
if [ -e $PARENT/build.log ]; then
	echo "  CLEAN   build.log"
	rm $PARENT/build.log
fi
if [ -e $INITRAMFS/zImage ]; then
	echo "  CLEAN   zImage"
	rm $INITRAMFS/zImage
fi
if [ -e $INITRAMFS/*.zip ]; then
	echo "  CLEAN   kernel.zip"
	rm $INITRAMFS/*.zip
fi;
if [ -e $INSTALLER/kernel/boot.img ]; then
	echo "  CLEAN   boot.img"
	rm $INSTALLER/kernel/boot.img
fi;
if [ -e $INSTALLER/system/lib/modules/adsprpc.ko ]; then
	echo "  CLEAN   adsprpc.ko"
	rm $INSTALLER/system/lib/modules/adsprpc.ko
fi;
if [ -e $INSTALLER/system/lib/modules/ansi_cprng.ko ]; then
	echo "  CLEAN   ansi_cprng.ko"
	rm $INSTALLER/system/lib/modules/ansi_cprng.ko
fi;
if [ -e $INSTALLER/system/lib/modules/exfat_fs.ko ]; then
	echo "  CLEAN   exfat_fs.ko"
	rm $INSTALLER/system/lib/modules/exfat_fs.ko
fi;
if [ -e $INSTALLER/system/lib/modules/exfat_core.ko ]; then
	echo "  CLEAN   exfat_core.ko"
	rm $INSTALLER/system/lib/modules/exfat_core.ko
fi;
if [ -e $INSTALLER/system/lib/modules/frandom.ko ]; then
	echo "  CLEAN   frandom.ko"
	rm $INSTALLER/system/lib/modules/frandom.ko
fi;
if [ -e $INSTALLER/system/lib/modules/gspca_main.ko ]; then
	echo "  CLEAN   gspca_main.ko"
	rm $INSTALLER/system/lib/modules/gspca_main.ko
fi;
if [ -e $INSTALLER/system/lib/modules/mcdrvmodule.ko ]; then
	echo "  CLEAN   mcdrvmodule.ko"
	rm $INSTALLER/system/lib/modules/mcdrvmodule.ko
fi;
if [ -e $INSTALLER/system/lib/modules/mckernelapi.ko ]; then
	echo "  CLEAN   mckernelapi.ko"
	rm $INSTALLER/system/lib/modules/mckernelapi.ko
fi;
if [ -e $INSTALLER/system/lib/modules/qce40.ko ]; then
	echo "  CLEAN   qce40.ko"
	rm $INSTALLER/system/lib/modules/qce40.ko
fi;
if [ -e $INSTALLER/system/lib/modules/qcrypto.ko ]; then
	echo "  CLEAN   qcrypto.ko"
	rm $INSTALLER/system/lib/modules/qcrypto.ko
fi;
if [ -e $INSTALLER/system/lib/modules/radio-iris-transport.ko ]; then
	echo "  CLEAN   radio-iris-transport.ko"
	rm $INSTALLER/system/lib/modules/radio-iris-transport.ko
fi;
if [ -e $INSTALLER/system/lib/modules/reset_modem.ko ]; then
	echo "  CLEAN   reset_modem.ko"
	rm $INSTALLER/system/lib/modules/reset_modem.ko
fi;
if [ -e $INSTALLER/system/lib/modules/scsi_wait_scan.ko ]; then
	echo "  CLEAN   scsi_wait_scan.ko"
	rm $INSTALLER/system/lib/modules/scsi_wait_scan.ko
fi;
if [ -e $INSTALLER/system/lib/modules/prima/prima_wlan.ko ]; then
	echo "  CLEAN   prima_wlan.ko"
	rm $INSTALLER/system/lib/modules/prima/prima_wlan.ko
fi;
if [ -e $INSTALLER/system/etc/firmware/wlan/prima/WCNSS_qcom_cfg.ini ]; then
	echo "  CLEAN   WCNSS_qcom_cfg.ini"
	rm $INSTALLER/system/etc/firmware/wlan/prima/WCNSS_qcom_cfg.ini
fi;
if [ -e $INSTALLER/system/etc/firmware/wlan/prima/WCNSS_cfg.dat ]; then
	echo "  CLEAN   WCNSS_cfg.dat"
	rm $INSTALLER/system/etc/firmware/wlan/prima/WCNSS_cfg.dat
fi;

echo " "
echo "**************************************************************"
echo "**************************************************************"
echo "               Cleaning Up Old Compiled Files                 "
echo "**************************************************************"
echo "**************************************************************"
echo " "
make mrproper
make clean
