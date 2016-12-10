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

## 2. State Logger
* Logs the state transitions of processes specified by the user
```bash
statlog start
statlog add 740
ls
PID740  1479846379      --------------      R----E--F-----
PID740  1479846379      R----E--F-----      R-Z--E--F-----
PID740  1479846379      R-Z--E--F-----      R----E--F-----
statlog pause
```
* User able to clear the ids to be tracked.
```bash
statlog clear
```

## 3. CTSS-like Scheduler
* Modifies the default scheduling algorithm to provide a CTSS like scheduling policy.
  * This only applies to the first three queues (aka nice 0-2)
* Additionally changes made to "ps"
  * Show number of context switches per process
  * Show current quantum assigned to process
## Make Instructions
With the patch.tar file:

```bash
tar -xvf patch.tar
cd patch
make test #if you wish to only get the functionality
#or
make full #to get changes to command modules such as "ps"
```

In order to make the image with most recent patches, pull most recent commmit (or get the most recent patch tarball [here](https://github.com/Jakeman893/minix-3.2.1/releases) and unzip it into any directory besize /usr/src/ (I recommend making a directory in /usr/).
Once in place, run *make test* in the new directory. This make command will patch the files in /usr/src/, build the kernel, and reboot the system for you.

> Note: If commands in the bin were changed (as they were in the CTSS-like Scheduler) a full build will need to be run. For this, run make full.
> However often this is not necessary as most commands are only needed for debugging purposes.