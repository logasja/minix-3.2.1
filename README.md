![alt tag](http://cdns2.freepik.com/free-photo/terminal-windows_318-9332.jpg)

# minix-3.2.1
This is a fork of version 3.2.1 of the respoitory found [here](https://github.com/minix3/minix).

The functionality added to the fork is as follows:
## 1. Process Logger
* Logs start and stop times of most recent process.
```bash
plog start
ls
plog -i 0
Process: 123
	Start:	000000000
	End:	000000000

plog stop
```
* Allows the user to return information by index or pid.
```bash
plog -i 0		//Get item at index 0
plog -p 123		//Get item with pid 123
```
  * User able to retrieve current size of the buffer.
```bash
plog -s
The buffer is of size 0.
```
  * If desired, user is able to manually clear the buffer.
```bash
plog clear
```

## Make Instructions
In order to make the image with most recent patches, pull most recent commmit (or get the most recent patch tarball [here](https://github.com/Jakeman893/minix-3.2.1/releases) and unzip it into any directory besize /usr/src/ (I recommend making a directory in /usr/).
Once in place, run make test in the new directory. This make command will patch the files in /usr/src/, build, and reboot the system for you. Aaaand... Thats all!
