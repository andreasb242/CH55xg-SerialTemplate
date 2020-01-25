#!/usr/bin/env python3


import usb.core
import usb.util
import sys
import json
import os
import time

path = os.path.realpath(os.path.dirname(os.path.realpath(__file__)) + '/../usb-descriptor')

with open(path + '/usb-descriptor.json', 'r') as f:
	descriptor = json.load(f)

vendor = int('0x' + descriptor['vendor'], 16)
product = int('0x' + descriptor['product'], 16)

dev = usb.core.find(idVendor = vendor, idProduct = product)
if dev is None:
    print('Device (' + hex(vendor) + '/' + hex(product) + ') not found, may not running')
    sys.exit()

try:
	# Detach interfaces if Linux already attached a driver on it.
	for itf_num in [0, 1]:
		#itf = usb.util.find_descriptor(dev.get_active_configuration(), bInterfaceNumber=itf_num)

		if dev.is_kernel_driver_active(itf_num):
			dev.detach_kernel_driver(itf_num)
		usb.util.claim_interface(dev, itf_num)

except usb.core.USBError as ex:
    print('Could not access USB Device')

    if str(ex).startswith('[Errno 13]') and platform.system() == 'Linux':
        print('No access to USB Device, configure udev or execute as root (sudo)')
        print('For udev create /etc/udev/rules.d/99-ch55x.rules')
        print('with one line:')
        print('---')
        print('SUBSYSTEM=="usb", ATTR{idVendor}=="' + format(vendor, '04x') + '", ATTR{idProduct}=="' + format(product, '04x') + '", MODE="666"')
        print('---')
        print('Restart udev: sudo service udev restart')
        print('Reconnect device, should work now!')
        sys.exit(2)

    traceback.print_exc()
    sys.exit(2)

try:
	RESET_DEVICE_TO_BOOTLOADER = 0x65
	result = dev.ctrl_transfer(0x21, RESET_DEVICE_TO_BOOTLOADER, 0x01, 0, None)

except usb.core.USBError as ex:
    print('Exception occured, probably is the device now resetted, all OK!')
    
    # Sleep, so the device is detected
    time.sleep(1)











