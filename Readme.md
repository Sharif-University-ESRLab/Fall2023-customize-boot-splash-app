![Logo](https://github.com/Sharif-University-ESRLab/Fall2023-customize-boot-splash-app/assets/135590004/d60ad01b-e5f0-471b-8ae7-e089b127e924)
![Screenshot from 2024-01-25 14-12-28](https://github.com/Sharif-University-ESRLab/Fall2023-customize-boot-splash-app/assets/135590004/caf828f0-2d42-4c35-971a-55c867916659)


# Customize Bootsplash Image

This is an application written in UEFI that takes a path from user and updates the bootsplash logo.

## Tools
- Qemu
- UEFI
- EDK2
- ImageMagick


## Implementation Details

In our main loop, we check the user input. Depending on the command "rename Logo \*new_path\*" or "Rename \*new_logo_path\*" we either change the current Logo to the new path the user provides or create the new specified Logo. It's important to note that the user must first change the current Logo to a checkpoint they decide on before choosing a new logo. We decided to give the user the freedom to choose the checkpoint's name so that they have more control over the process and can change the logo to the original logo if needed.

![main-loop](https://github.com/Sharif-University-ESRLab/Fall2023-customize-boot-splash-app/assets/135590004/76323a97-2da8-4154-8a34-6849f0c2351f)

We have some helper functions in order to achieve this goal. 

The function below handles how we get the input from the user. We consider the buffer's content and its size to parse the result.

![getinput](https://github.com/Sharif-University-ESRLab/Fall2023-customize-boot-splash-app/assets/135590004/f43ac787-e0c7-4914-91db-af7b521cb0d3)

Here we print the options for the user. This way the user can check what options they have to choose from and what name to choose for the previous logo.

![printoptions](https://github.com/Sharif-University-ESRLab/Fall2023-customize-boot-splash-app/assets/135590004/e1c36cb2-a32c-4026-9431-b4cb509e6f47)

Finally, our main method lies in the function below where we rename the specified files to the given paths. (further details in the code folder)

![rename](https://github.com/Sharif-University-ESRLab/Fall2023-customize-boot-splash-app/assets/135590004/97715144-6448-4c92-af35-afdbafa769ba)

## How to Run

### Sample run of our method:

![step1](https://github.com/Sharif-University-ESRLab/Fall2023-customize-boot-splash-app/assets/135590004/5452d153-0ced-4773-9cdb-26b1e686bbfc)
![step2](https://github.com/Sharif-University-ESRLab/Fall2023-customize-boot-splash-app/assets/135590004/499f172c-8bd8-4cae-b1bf-d6958880b8fc)
![step3](https://github.com/Sharif-University-ESRLab/Fall2023-customize-boot-splash-app/assets/135590004/2b75a28c-01ed-4810-8a93-9daa09b492ab)
![step4](https://github.com/Sharif-University-ESRLab/Fall2023-customize-boot-splash-app/assets/135590004/36719d3e-3b19-4077-8d07-0d08ba068723)
![step5](https://github.com/Sharif-University-ESRLab/Fall2023-customize-boot-splash-app/assets/135590004/2a64d9f3-a968-437e-b120-de14c03cb194)

![RUN VIDEO](https://github.com/Sharif-University-ESRLab/Fall2023-customize-boot-splash-app/assets/135590004/56244a82-a428-4193-882e-00f67eef2d71)


#### Build Project

```bash
  git clone https://github.com/Sharif-University-ESRLab/Fall2023-customize-boot-splash-app.git
  export FIRMWARE=./Build/OvmfX64/RELEASE_GCC5/FV/OVMF.fd
  export DRIVE=./MdeModulePkg/Logo
  mkdir -p $DRIVE
  qemu-system-x86_64 -drive if=pflash,format=raw,readonly,file=Build/OvmfX64/RELEASE_GCC5/FV/OVMF_CODE.fd     -drive if=pflash,format=raw,file=Build/OvmfX64/RELEASE_GCC5/FV/OVMF_VARS.fd -drive file=fat:rw:$DRIVE  -net none
  build --platform=OvmfPkg/OvmfPkgX64.dsc --arch=X64 --buildtarget=RELEASE --tagname=GCC5
  qemu-system-x86_64 -drive if=pflash,format=raw,readonly,file=Build/OvmfX64/RELEASE_GCC5/FV/OVMF_CODE.fd     -drive if=pflash,format=raw,file=Build/OvmfX64/RELEASE_GCC5/FV/OVMF_VARS.fd -drive file=fat:rw:$DRIVE  -net none
```

#### Run server
Your text comes here
```bash
  pyhton server.py -p 8080
```

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `-p` | `int` | **Required**. Server port |



## Results
In this section, you should present your results and provide an explanation for them.

Using image is required.

## Related Links
Some links related to your project come here.
 - [EDK II](https://github.com/tianocore/edk2)
 - [ESP32 Pinout](https://randomnerdtutorials.com/esp32-pinout-reference-gpios/)
 - [Django Doc](https://docs.djangoproject.com/en/5.0/)


## Authors
Authors and their github link come here.
- [@Author1](https://github.com/Sharif-University-ESRLab)
- [@Author2](https://github.com/Sharif-University-ESRLab)

