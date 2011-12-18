/* 
 * File:   cUdev.cpp
 * Author: scuzzy
 * 
 * Created on 18 December 2011, 10:58 PM
 */

#include "cUdev.h"

cUdev::cUdev()
{

	std::list<std::string>::iterator it;

	std::list<std::string> devices = findDevices("Reverseorder");

	std::cout << "DEVICES: " << devices.size() << std::endl;

	for(it = devices.begin(); it != devices.end(); it ++)
	{
		std::cout << "DEVICE: " << *it << std::endl;
	}
}
std::list<std::string> cUdev::findDevices(std::string mnfturer)
{
	struct udev *udev;
	struct udev_enumerate *enumerate;
	struct udev_list_entry *devices, *dev_list_entry;
	struct udev_device *dev;

	std::list<std::string> devs;

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
			std::string manufacturer(udev_device_get_sysattr_value(dev, "manufacturer"));
			std::cout << "Manufacturer: " << manufacturer << std::endl;
			std::cout << "Device PATH: " << deviceNodePath << std::endl;
			if(manufacturer.compare(mnfturer) == 0)
			{
				devs.push_front(deviceNodePath);
			}
		}

		/*
		printf("  VID/PID: %s %s\n",
				  udev_device_get_sysattr_value(dev, "idVendor"),
				  udev_device_get_sysattr_value(dev, "idProduct"));
		printf("  %s\n  %s\n",
				  udev_device_get_sysattr_value(dev, "manufacturer"),
				  udev_device_get_sysattr_value(dev, "product"));
		printf("  serial: %s\n",
				  udev_device_get_sysattr_value(dev, "serial"));
		 */
		udev_device_unref(dev);
	}

	udev_enumerate_unref(enumerate);

	udev_unref(udev);

	return devs;
}

cUdev::~cUdev()
{
}

