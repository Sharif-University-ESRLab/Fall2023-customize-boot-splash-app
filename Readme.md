
![Logo](https://github.com/Sharif-University-ESRLab/Fall2023-customize-boot-splash-app/assets/135590004/d60ad01b-e5f0-471b-8ae7-e089b127e924)


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

## How to Run

In this part, you should provide instructions on how to run your project. Also if your project requires any prerequisites, mention them. 

#### Examples:
#### Build Project
Your text comes here
```bash
  build --platform=OvmfPkg/OvmfPkgX64.dsc --arch=X64 --buildtarget=RELEASE --tagname=GCC5
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

