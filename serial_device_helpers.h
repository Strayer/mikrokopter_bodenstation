#ifndef SERIAL_DEVICE_HELPERS_H
#define SERIAL_DEVICE_HELPERS_H

#include <vector>
#include <iostream>
#include <string>

#include <objbase.h>
#include <initguid.h>
#include <SetupAPI.h>

class SerialPort
{

};

std::vector<SerialPort> getSerialPortList()
{
	HDEVINFO hDevInfo = INVALID_HANDLE_VALUE;
	SP_DEVICE_INTERFACE_DETAIL_DATA *pDetData = NULL;
	// Create a device information set that will be the container for
	// the device interfaces.
	GUID *guidDev = (GUID*) &GUID_DEVINTERFACE_COMPORT;

	hDevInfo = SetupDiGetClassDevs(&GUID_DEVINTERFACE_COMPORT,
		NULL,
		NULL,
		DIGCF_PRESENT | DIGCF_DEVICEINTERFACE
	);

	if(hDevInfo == INVALID_HANDLE_VALUE)
		throw "holy cow!";

	// Enumerate the serial ports
	BOOL bOk = TRUE;
	SP_DEVICE_INTERFACE_DATA ifcData;
	DWORD dwDetDataSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA) + 256;
	pDetData = (SP_DEVICE_INTERFACE_DETAIL_DATA*) new char[dwDetDataSize];
	// This is required, according to the documentation. Yes,
	// it's weird.
	ifcData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
	pDetData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
	for (DWORD ii=0; bOk; ii++)
	{
		bOk = SetupDiEnumDeviceInterfaces(hDevInfo,
			NULL, &GUID_DEVINTERFACE_COMPORT, ii, &ifcData);
		if (bOk) {
			// Got a device. Get the details.
			SP_DEVINFO_DATA devdata = {sizeof(SP_DEVINFO_DATA)};
			bOk = SetupDiGetDeviceInterfaceDetail(hDevInfo,
				&ifcData, pDetData, dwDetDataSize, NULL, &devdata);
			if (bOk) {
				std::string strDevPath(pDetData->DevicePath);
				// Got a path to the device. Try to get some more info.
				TCHAR fname[256];
				TCHAR desc[256];
				BOOL bSuccess = SetupDiGetDeviceRegistryProperty(
					hDevInfo, &devdata, SPDRP_FRIENDLYNAME, NULL,
					(PBYTE)fname, sizeof(fname), NULL);
				bSuccess = bSuccess && SetupDiGetDeviceRegistryProperty(
					hDevInfo, &devdata, SPDRP_DEVICEDESC, NULL,
					(PBYTE)desc, sizeof(desc), NULL);

				if (bSuccess) {
					// Add an entry to the array
	//				SSerInfo si;
	//				si.strDevPath = strDevPath;
	//				si.strFriendlyName = fname;
	//				si.strPortDesc = desc;
	//				si.bUsbDevice = bUsbDevice;
	//				asi.Add(si);
					std::cout << strDevPath << std::endl << fname << std::endl << desc << std::endl << std::endl;
				}

			}
		}
	}

	return std::vector<SerialPort>();
}

#endif // SERIAL_DEVICE_HELPERS_H
