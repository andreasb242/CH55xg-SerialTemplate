#!/usr/bin/env python3

import json
import os

path = os.path.dirname(os.path.realpath(__file__))

with open(path + '/usb-descriptor.json', 'r') as f:
	descriptor = json.load(f)

def printTextDescriptor(out, text, var):
	textByte = text.encode('utf-16')
	length = 0

	formattedText = ''

	for b in textByte[2:]:
		if formattedText == '':
			formattedText += '\t'
		else:
			if length % 18 == 0:
				formattedText += ',\n\t'
			else:
				formattedText += ', '

		if b < 128 and b > 30:
			formattedText += "'" + chr(b) + "'"
		else:
			formattedText += str(b)
		length = length + 1


	out.write('unsigned char __code ' + var + '[] = {\n')
	out.write('\t' + str(length + 2) + ', // Length of the whole array including this byte\n')
	out.write('\t3,\n')
	out.write(formattedText + '\n')
	out.write('};\n')
	out.write('\n')

with open(path + '/usb-descriptor.h', 'w') as out:
	out.write('/**\n')
	out.write(' * USB Descriptors\n')
	out.write(' *\n')
	out.write(' * ** Automatically generated! **\n')
	out.write(' * ** Do not change, change usb-descriptor.json! **\n')
	out.write(' */\n')
	out.write('\n')
	out.write('#pragma once\n')
	out.write('\n')
	out.write('#include "../lib/inc.h"\n')
	out.write('\n')
	out.write('// Device descriptor\n')
	out.write('\n')
	out.write('__code uint8_t g_DescriptorDevice[] = {\n')
	out.write('\t0x12, 0x01, 0x10, 0x01,\n')
	out.write('\t0x02, 0x00, 0x00, DEFAULT_ENDP0_SIZE,\n')
	out.write('\n')
	out.write('\t// ' + descriptor['vendor-info'] + '\n')
	out.write('\t// Vendor\n')
	out.write('\t')

	vendorId = descriptor['vendor']
	out.write('0x' + vendorId[2:4] + ', 0x' + vendorId[0:2] + ',')
	
	out.write('\n')
	out.write('\n')

	out.write('\t// ' + descriptor['product-info'] + '\n')
	out.write('\t// Product\n')
	out.write('\t')

	productId = descriptor['product']
	out.write('0x' + productId[2:4] + ', 0x' + productId[0:2] + ',')

	out.write('\n')
	out.write('\n')
	out.write('\t0x00, 0x01, 0x01, 0x02,\n')
	out.write('\t0x03, 0x01\n')
	out.write('};\n')
	out.write('\n')

	file1 = open(path + '/part1.template.h', 'r')
	while True:
		line = file1.readline()
		# end of file is reached
		if not line:
			break

		out.write(line)

	file1.close() 


	out.write('// Serial number string descriptor\n')
	out.write('// Use this as identifier for Linux and Windows,\n')
	out.write('// the Name is the only Attribute displayed on Windows\n')
	
	printTextDescriptor(out, descriptor['serial-text'], 'g_DescriptorSerial')

	out.write('// Product string descriptor\n')
	printTextDescriptor(out, descriptor['product-text'], 'g_DescriptorProduct')

	out.write('// Manufacturer string descriptor\n')
	printTextDescriptor(out, descriptor['manufacturer-text'], 'g_DescriptorManufacturer')



