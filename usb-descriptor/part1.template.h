__code uint8_t g_DescriptorConfiguration[] = {
	// ------------------------------------------------------------------------
	// Configuration descriptor (two interfaces)
	// ------------------------------------------------------------------------
	0x09, 0x02, 0x43, 0x00, 0x02, 0x01, 0x00, 0xa0, 0x32,

	// ------------------------------------------------------------------------
	// The following is the interface 0 (CDC interface) descriptor
	// ------------------------------------------------------------------------

	// CDC interface descriptor (one endpoint)
	0x09, 0x04, 0x00, 0x00, 0x01, 0x02, 0x02, 0x01, 0x00,

	// ------------------------------------------------------------------------
	// The following is the function descriptor
	// ------------------------------------------------------------------------

	// Function descriptor (header)
	0x05, 0x24, 0x00, 0x10, 0x01,

	// Management descriptor (no data class interface) 03 01
	0x05, 0x24, 0x01, 0x00, 0x00,

	// Support Set_Line_Coding, Set_Control_Line_State, Get_Line_Coding, Serial_State
	0x04, 0x24, 0x02, 0x02,

	// CDC interface numbered 0; data class interface number 1
	0x05, 0x24, 0x06, 0x00, 0x01,

	// Interrupt upload endpoint descriptor
	0x07, 0x05, 0x81, 0x03, 0x10, 0x00, 0x40,

	// ------------------------------------------------------------------------
	// The following is the interface 1 (data interface) descriptor
	// ------------------------------------------------------------------------

	// Data interface descriptor
	0x09, 0x04, 0x01, 0x00, 0x02, 0x0a, 0x00, 0x00, 0x00,

	// Endpoint descriptor
	0x07, 0x05, 0x02, 0x02, 0x40, 0x00, 0x00,

	// Endpoint descriptor
	0x07, 0x05, 0x82, 0x02, 0x40, 0x00, 0x00,
};

// ----------------------------------------------------------------------------
// String descriptor
// ----------------------------------------------------------------------------

// Language descriptor: English
unsigned char __code g_DescriptorLanguage[] = { 0x04, 0x03, 0x09, 0x04 };

