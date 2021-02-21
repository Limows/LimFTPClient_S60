# Limowski App Manager

Small Application Manager for legacy devices (Symbian S60 version) written in C++ with Qt 4.6.3

## Assembly

You need the following stuff to build this program:

 - QtSDK for Symbian 1.1.2
 - Symbian S60 SDK
 - QuaZip (you can get it [here])

First you need to build a QuaZip library.
 
## Installation

You need the following stuff to install this program:

 - Qt for Symbian 4.6.3

## Usage

### Choosing app for install

 Click on the application name in the list
 
### Downloading app installation

 Click on the "Download" button and after downloading choose whether to install the application
 
### Deleting installed app

### Update manager

 Click the update menu item. 
 After verification, the manager will offer to download the new version, if it exists.
 After downloading, close the program and run the file "Update.sis" from your Downloading directory

## Supported functions

 - Listing available for device applications
 - Downloading app package
 - Unpacking package
 
## OS Support

 - Symbian S60v3
 - Symbian S60v5
 - Symbian^3
 
## Used projects

 - QuaZip (version 0.5)

## Tested devices

 - Nokia N95
 - Nokia E72
 - Nokia N8
 - Nokia E90 (Not working)

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/Limows/LimowsFTPClient_S60.

## License

This project is licensed under the terms of the [2-Clause BSD License](https://opensource.org/licenses/BSD-2-Clause).


[here]: https://github.com/stachenov/quazip/tree/936844eb691491f7a9cbfd842a4326b9d384441f