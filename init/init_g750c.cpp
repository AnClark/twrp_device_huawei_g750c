/*
 * Copyright (C) 2015 The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define UNUSED(x) (void)(x)

#include <stdio.h>
#include <string.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include <functional>
#include <string>
#include <android-base/file.h>
#include <android-base/strings.h>

#include "log.h"
#include "property_service.h"
#include "vendor_init.h"

#define APP_INFO "/proc/app_info"

/* Serial number */
#define SERIAL_PROP "ro.serialno"
#define REAL_SERIAL_PROP "usb.serial"

/* Bootloader version */
/* Example: MSM8926C00B309_BOOT */
#define BOOTLOADER_PROP "ro.bootloader"

/** This is a variant of import_kernel_cmdline() from system/core/init/utils.h
 *  Must re-implement because directly including "utils.h" will emit unexpected errors
 */
void my_import_kernel_cmdline(bool in_qemu,
                           const std::function<void(const std::string&, const std::string&, bool)>& fn) {
    std::string cmdline;
    android::base::ReadFileToString("/proc/cmdline", &cmdline);

    for (const auto& entry : android::base::Split(android::base::Trim(cmdline), " ")) {
        std::vector<std::string> pieces = android::base::Split(entry, "=");
        if (pieces.size() == 2) {
            fn(pieces[0], pieces[1], in_qemu);
        }
    }
}


static void import_kernel_nv(std::string name, std::string value, bool in_qemu)
{
	UNUSED(in_qemu);

	prop_info *pi;
	int ret = 0;

	if(!value.length())
		return;

	if(!strncmp(name.c_str(), REAL_SERIAL_PROP, 10)) {
		pi = (prop_info*) __system_property_find(SERIAL_PROP);
		if(pi)
			ret = __system_property_update(pi, value.c_str(), value.length());
		else
			ret = __system_property_add(SERIAL_PROP, strlen(SERIAL_PROP), value.c_str(), value.length());
	}
}

static void get_bootloader_version()
{
	int ret = 0;
	char buf[128] = { 0 };
	char value[32] = { 0 };
	char *tok;
	prop_info *pi;

	FILE* f = fopen(APP_INFO, "rb");
	if (f == NULL) return;

	while (!feof(f)) {
		if (fgets(buf, 128, f) != NULL &&
				strstr(buf, "huawei_sbl1_version") != NULL) {
			tok = strchr(buf, ':');
			if (tok != NULL)
				tok = strtok(tok, ": ");
			if (tok != NULL) {
				snprintf(value, 32, "%s", tok);
				strtok(value, "\n");
			}
		}
	}

	fclose(f);

	if (strlen(value) > 0) {
		pi = (prop_info*) __system_property_find(BOOTLOADER_PROP);
		if(pi)
			ret = __system_property_update(pi, value,
					strlen(value));
		else
			ret = __system_property_add(BOOTLOADER_PROP,
					strlen(BOOTLOADER_PROP),
					value, strlen(value));
	}

}

void vendor_load_properties()
{
	my_import_kernel_cmdline(0, import_kernel_nv);
	get_bootloader_version();
}
