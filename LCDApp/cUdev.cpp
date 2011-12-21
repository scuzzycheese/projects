/* 
 * File:   cUdev.cpp
 * Author: scuzzy
 * 
 * Created on 18 December 2011, 10:58 PM
 */

#include "cUdev.h"

cUdev::cUdev()
{

	/*
	std::list<std::string> devices = getLCDDevices();
	for(std::list<std::string>::iterator it = devices.begin(); it != devices.end(); it ++)
	{
		std::cout << "LCD DEVICE: " << *it << std::endl;
	}

	devices = getBootloaderDevices();
	for(std::list<std::string>::iterator it = devices.begin(); it != devices.end(); it ++)
	{
		std::cout << "BOOTLOADER DEVICE: " << *it << std::endl;
	}
	 */
}

std::map<std::string, udev_device *> cUdev::findDevices()
{
	struct udev *udev;
	struct udev_enumerate *enumerate;
	struct udev_list_entry *devices, *dev_list_entry;
	struct udev_device *dev;

	std::map<std::string, udev_device *> ttyDevs;

	udev = udev_new();
	if(!udev)
	{
		std::cout << "Can't create udev!" << std::endl;
		exit(1);
	}

	enumerate = udev_enumerate_new(udev);
	udev_enumerate_add_match_subsystem(enumerate, "tty");
	//udev_enumerate_add_match_property(enumerate, "ID_VENDOR", "Reverseorder");
	udev_enumerate_scan_devices(enumerate);
	devices = udev_enumerate_get_list_entry(enumerate);

	udev_list_entry_foreach(dev_list_entry, devices)
	{
		const char *path;

		path = udev_list_entry_get_name(dev_list_entry);
		dev = udev_device_new_from_syspath(udev, path);

		std::string deviceNodePath(udev_device_get_devnode(dev));

		dev = udev_device_get_parent_with_subsystem_devtype(dev, "usb", "usb_device");

		if(dev)
		{
			ttyDevs[deviceNodePath] = dev;
		}

	}

	udev_enumerate_unref(enumerate);

	udev_unref(udev);

	return ttyDevs;
}

std::list<std::string> cUdev::getLCDDevices()
{
	std::map<std::string, udev_device *> devices = findDevices();

	std::list<std::string> devs;

	for(std::map<std::string, udev_device *>::iterator device = devices.begin(); device != devices.end(); device ++)
	{

		const char *devManufacturer = udev_device_get_sysattr_value(device->second, "manufacturer");
		if(devManufacturer)
		{
			std::string manufacturer(devManufacturer);
			std::cout << "Manufacturer: " << manufacturer << std::endl;
			std::cout << "Device PATH: " << device->first << std::endl;
			if(manufacturer.compare("Reverseorder") == 0)
			{
				devs.push_front(device->first);
			}
		}

		udev_device_unref(device->second);
	}
	return devs;
}

std::list<std::string> cUdev::getBootloaderDevices()
{
	std::map<std::string, udev_device *> devices = findDevices();

	std::list<std::string> devs;

	for(std::map<std::string, udev_device *>::iterator device = devices.begin(); device != devices.end(); device ++)
	{

		const char *devId = udev_device_get_sysattr_value(device->second, "idProduct");
		if(devId)
		{
			std::string productID(devId);
			std::cout << "Product ID: " << productID << std::endl;
			std::cout << "Device PATH: " << device->first << std::endl;
			if(productID.compare("204a") == 0)
			{
				devs.push_front(device->first);
			}
		}
		udev_device_unref(device->second);
	}
	return devs;
}

cUdev::~cUdev()
{
}

