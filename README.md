# USB Device Logger Kernel Module

This is a simple Linux kernel module that logs USB device connection and removal events. It logs the device name and the date when a USB device is plugged in or removed from the system. The log is saved to a specified file, and the module uses the kernel's USB notification system to capture the device events.

## Features

- Logs USB device connection and removal events.
- Logs the device name and the date of the event.
- Writes log messages to a specified file (`/home/<yourusername>/usblog.txt`).
- Supports the following USB device types: USB HID and USB storage devices.

## Requirements

- A Linux system with kernel headers installed.
- A kernel that supports the USB subsystem.

## Installation

### 1. Clone the Repository

Clone this repository to your local machine:

```bash
git clone https://github.com/by3lish/usblogmaster.git
cd usb-logger
```

### 2. Build the Module

Before building the module, make sure you have the necessary kernel headers installed. On Debian-based systems, you can install them using:

```bash
sudo apt-get install linux-headers-$(uname -r)
```

To build the module, simply run:

```bash
make
```

### 3. Install the Module

After the module is built, you can install it by running:

```bash
sudo make install
```

This will load the kernel module using `insmod`.

### 4. Uninstall the Module

To remove the module from the system:

```bash
sudo make uninstall
```

This will unload the module using `rmmod`.

## Usage

Once the module is loaded, it will begin logging USB device events to the log file located at `/home/<yourusername>/usblog.txt`.

The log entries will look like this:

```
Device Plugged In: Name='USB Storage Device', Type='USB', Date='01.12.2024'
Device Removed: Name='USB Storage Device'
```

Make sure to change the `LOG_FILE_PATH` in the source code to your desired location for the log file. 

## Makefile

The Makefile includes the following targets:

- **all**: Builds the kernel module.
- **clean**: Cleans up build artifacts.
- **install**: Installs (loads) the module.
- **uninstall**: Uninstalls (removes) the module.

## License

This project is licensed under the GPL-2.0 License - see the [LICENSE](LICENSE) file for details.

## Author

- [By3lish](https://github.com/by3lish)
