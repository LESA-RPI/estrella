/*
* Copyright (c) 2009, Björn Rehm (bjoern@shugaa.de)
* All rights reserved.
* 
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
* 
*  * Redistributions of source code must retain the above copyright notice, this
*    list of conditions and the following disclaimer.
*  * Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*  * Neither the name of the author nor the names of its contributors may be
*    used to endorse or promote products derived from this software without
*    specific prior written permission.
* 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdio.h>
#include "estrella.h"
#include "dll_list.h"

int main(int argc, char *argv[]) 
{
    int rc;
    int i;
    dll_list_t devices;
    dll_iterator_t it;
    void *device = NULL;
    unsigned int numdevices = 0;

    dll_init(&devices);

    rc = estrella_find_devices(&devices);
    if (rc != 0) {
        printf("Unable to search for usb devices\n");
        return 1;
    }

    rc = dll_count(&devices, &numdevices);
    if ((rc != EDLLOK) || (numdevices == 0)) {
        printf("No devices found\n");
        return 1;
    }

    i = 0;
    dll_iterator_init(&it, &devices);
    while (dll_iterator_next(&it, (void**)&device, NULL) == EDLLOK) {
        estrella_dev_t *dev = (estrella_dev_t*)device;

        printf("DEVICE %d\n", i);

        switch (dev->devicetype) {
            case ESTRELLA_DEV_USB:
                printf("   type:         USB\n");
                printf("   bus:          %s\n", dev->spec.usb.bus);
                printf("   device:       %d\n", dev->spec.usb.devnum);
                printf("   vendor id:    0x%04x\n", dev->spec.usb.vendorid);
                printf("   product id:   0x%04x\n", dev->spec.usb.productid);
                printf("   manufacturer: %s\n", dev->spec.usb.manufacturer);
                printf("   product:      %s\n", dev->spec.usb.product);
                printf("   serial:       %s\n", dev->spec.usb.serialnumber);


                break;
            default:
                printf("   type:    LPT\n");
                break;
        }
    }

    dll_clear(&devices);

    return 0;
}
