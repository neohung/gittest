#include <stdio.h>
#include "libusb.h"
int main(){
	int r;
	libusb_device **devs;
	ssize_t cnt;
	r = libusb_init(NULL);
	printf("r=%d\n",r);
	if (r<0) return r;
	cnt = libusb_get_device_list(NULL, &devs);
	if (cnt < 0) return (int) cnt;
	printf ("cnt=%d\n",(int)cnt);
	libusb_device *dev;
	int i = 0;	
	while ((dev = devs[i++]) != NULL) {
		struct libusb_device_descriptor desc;
		int rr = libusb_get_device_descriptor(dev, &desc);
		if (r < 0) {
			fprintf(stderr, "failed to get dd");
			return rr;
		}
	printf("%04x:%04x (bus %d, device %d)\n",desc.idVendor,desc.idProduct,libusb_get_bus_number(dev),libusb_get_device_address(dev));	
	}
	libusb_free_device_list(devs, 1);
	libusb_exit(NULL);
	return 0;
	printf("This is test\n");
}
