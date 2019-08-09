# Copyright (C) 2015 The CyanogenMod Project
# Copyright (C) 2014 The Android Open-Source Project
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

# Charging
PRODUCT_PACKAGES += \
    charger_res_images

# Encryption
PRODUCT_PACKAGES += \
    keystore.msm8226

# Init
PRODUCT_COPY_FILES += \
    todo:todo

# Thermal
PRODUCT_PACKAGES += \
    thermal-engine-8226.conf


$(call inherit-product,frameworks/native/build/phone-xhdpi-2048-dalvik-heap.mk)

# inherit from the non-open-source side, if present
$(call inherit-product-if-exists, vendor/huawei/g750c/g750c-vendor.mk)
