# TWRP device tree for HUAWEI B199 (g750c)

This repository is yet another TWRP device tree for Huawei Maimang B199 (g750c). 

TWRP and MoKee used to provide official supports for this model, so we could download recovery and MoKee ROMs from their official site several years ago.

However, one day, **both of them weirdly deleted the only device trees from their GitHub repository**. Uh-hah. Is this model erased from the earth? What did they think? Absurd!

Luckily, [cm-mirror](https://github.com/cm-mirror/android_device_huawei_g750c) kept a backup so that I can bring B199 back to life.

## Features

- Full TWRP functionality
- ADB support based on FunctionFS
- Made for TWRP >= 3.2.3

## How to build

1. Download Omni 8.1 source. [Follow this guide](https://github.com/omnirom/android#getting-started) but replace `android-9.0` with `android-8.1`. You can also build with the newest `android-9.0`.
2. **Clone the [kernel source](https://github.com/AnClark/android_kernel_huawei_msm8628) into Omni source's `kernel/huawei/msm8628` folder, and checkout branch `mkp`.**
3. Run the following commands in Omni source's root:

```
  source build/envsetup.sh
  lunch omni_g750c-userdebug
  make recoveryimage
```

4. When succeed, you will get the built recovery image on the bottom of stdout.

## Credits

- Original maintainer:  [@xjljian](https://github.com/xjljian)
- The HERO who rescued the device tree:  [@cm-mirror](https://github.com/cm-mirror/)
- Original kernel maintainer: @MoKee