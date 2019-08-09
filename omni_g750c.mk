# Copyright (C) 2015 The CyanogenMod Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Boot animation
TARGET_SCREEN_HEIGHT := 1280
TARGET_SCREEN_WIDTH := 720

# Inherit the base device config stuff.
# This can prevent profman error while building boot image preferences.
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)

# Inherit some common Omni stuff.
$(call inherit-product, vendor/omni/config/phone-xxhdpi-4096-dalvik-heap.mk)

# Inherit device configuration
$(call inherit-product, device/huawei/g750c/g750c.mk)

PRODUCT_NAME := omni_g750c
PRODUCT_DEVICE := g750c
PRODUCT_BRAND := huawei
PRODUCT_MANUFACTURER := Huawei
PRODUCT_MODEL := HUAWEI B199

PRODUCT_BUILD_PROP_OVERRIDES += \
	PRODUCT_NAME=B199 \
	BUILD_FINGERPRINT=Huawei/B199/hwB199:6.0/HuaweiB199/C00B321:user/release-keys \
	PRIVATE_BUILD_DESC="g750-c00-user 6.0 GRJ90 C00B321 release-keys"
