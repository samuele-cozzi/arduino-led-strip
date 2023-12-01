# arduino-led-strip

## Working on WSL

### Install the USBIPD-WIN project

Based on [Stack Overflow](https://stackoverflow.com/questions/71119369/how-would-i-use-arduino-cli-in-wsl/75958094#75958094) and [Microsoft Documentation](https://learn.microsoft.com/en-us/windows/wsl/connect-usb) follow these steps

Support for connecting USB devices is not natively available in WSL, so you will need to install the open-source usbipd-win project.

- Go to the latest release page for the usbipd-win [project](https://github.com/dorssel/usbipd-win/releases).
- Select the .msi file, which will download the installer. (You may get a warning asking you to confirm that you trust this download).
- Run the downloaded usbipd-win_x.msi installer file.

On Ubuntu, run this command:

```bash
sudo apt install linux-tools-generic hwdata
sudo update-alternatives --install /usr/local/bin/usbip usbip /usr/lib/linux-tools/*-generic/usbip 20
```

At this point a service is running on Windows to share USB devices, and the necessary tools are installed in WSL to attach to shared devices.

### Attach a USB device

Before attaching your USB device, ensure that a WSL command line is open.  This will keep the WSL 2 lightweight VM active.

1. List all of the USB devices connected to Windows by opening PowerShell in *administrator* mode and entering the command:

    ```powershell
    usbipd wsl list
    ```

2. Select the bus ID of the device you’d like to attach to WSL and run this command. You’ll be prompted by WSL for a password to run a sudo command. The Linux distribution to be attached must be your default distribution. (See the [Basic commands for WSL](./basic-commands.md#set-default-linux-distribution) doc to change your default distribution).

    ```powershell
    usbipd wsl attach --busid <busid>
    ```

3. Open Ubuntu (or your preferred WSL command line) and list the attached USB devices using the command:

    ```bash
    lsusb
    ```

    You should see the device you just attached and be able to interact with it using normal Linux tools. Depending on your application, you may need to configure udev rules to allow non-root users to access the device.

4. Once you are done using the device in WSL, you can either physically disconnect the USB device or run this command from PowerShell in *administrator* mode:

    ```powershell
    usbipd wsl detach --busid <busid>
    ```

### Permission to the port

Based to [Stack Overflow](https://stackoverflow.com/questions/27858041/oserror-errno-13-permission-denied-dev-ttyacm0-using-pyserial-from-pyth) 

 Alter the permissions on /dev/ttyACM0 so that world has read and write priviliges (something you may not want to do) - although you may find they reset each time the device is plugged in eg:

```bash
sudo chmod 666 /dev/ttyACM0  
```

