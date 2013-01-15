#include <stdio.h>
#include "libusb.h"
int main(){

	int r;
	libusb_device **devs;
	libusb_device *target_usb;
	struct libusb_device_handle *handle = NULL;
	ssize_t cnt;
	uint16_t vendor_ID = 0x1e3d;
	uint16_t product_ID = 0x2093;
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
		}else if (desc.idVendor == vendor_ID && desc.idProduct == product_ID){
			printf("device found!\n");
			target_usb = dev;
			break;
		}
	printf("%04x:%04x (bus %d, device %d)\n",desc.idVendor,desc.idProduct,libusb_get_bus_number(dev),libusb_get_device_address(dev));	
	}
   if (target_usb) {
                r = libusb_open(target_usb, &handle);
                if (r < 0){
                        handle = NULL;
			printf("open fail~~~~\n");
		}
        }

//	int r = 1;
//	r = libusb_init(NULL);
//	static struct libusb_device_handle *devh = NULL;
//	devh = libusb_open_device_with_vid_pid(NULL, 0x1e3d, 0x2093);
//	r = libusb_claim_interface(devh, 0);
//	if (r < 0) {
//		fprintf(stderr, "usb_claim_interface error %d\n", r);
//		return r;
//	}
libusb_free_device_list(devs, 1);
	libusb_exit(NULL);
	return 0;
	printf("This is test\n");
}
