## The very first run
Q: **What do I do now that I have this stuff?**  
A: Take a look at the doc dir.  You'll need to install things  
   1. **(read doc/INSTALLING)**  
   1. Then startup the mud  
   1. Then login as someone (the first player will be an admin)  
   1. You will also probably want to look at the lib/doc directory  

## Debugging
### No Mud, No Output
Q: **When I run startmud it returns with no errors what do I do?**  
A: Look at lib/logs/gurba-driver.log  

### Something wrong with local_config.h
Q: **When trying to start the mud, it complains about the file local_config.h not being there and then terminates.**  
A: You didn't follow the directions for configuring the mud and installing the driver. 
   1. **read and follow doc/INSTALLING**  
      (Note: This has changed use to be called mudname.h, if your getting this problem now reread INSTALLING and send me an email if your still having problems.)\

### I broke something! Lots of output!!!
Q: **When starting the mud, I get output like this:**  

```
  Mar 10 13:00:16 ** DGD 1.2.157-NET-05 running GurbaLib v0.41.
  Mar 10 13:00:16 ** Initializing...
  Mar 10 13:00:16 ** Preloading...
  Mar 10 13:00:16 ** Setting up events
  Mar 10 13:00:16 ** Setting up daemons
  Mar 10 13:00:16 ** Opening telnet port...
  /daemons/imud_d.c, 73: syntax error
    55 initialize        /kernel/sys/driver
  Failed to compile "/daemons/imud_d.c"
  Object: /kernel/sys/driver, program: /kernel/sys/driver, line 55
   210 call_object       /kernel/sys/driver
  Failed to compile "/daemons/imud_d.c"
  Config error: initialization failed
```
A: The file lib/kernel/include/local_config.h does not define the **IMUD_NAME** macro, probably because you created an empty file there or removed that macro.  

### Unexplained crashing after tweaking the Makefile
Q: **I changed the Makefile to build dgd with -O or -O2 and now it crashes.**  
A: Don't do this. It is not supported and the possible gain it could give is very small.  

### Upgrading the mudlib causes headache!
Q: **I upgraded my mudlib, and now things don't work, what do I do?**  
A: Look at **doc/UPGRADING**  

### Wtf?!! Why aren't my new commands useable?
Q: **I've added a command but it's not available even tho it updated just fine?**  
A: As an admin give the **rehash** command.  
