1080p 30 fps
==============

The PSTV hdmi encoder supports 1080p30 but it was never officially added to the list of supported resolutions.

This takes care of that by overriding the 480p mode and outputing 1080p30 instead.
The downside is that the framerate is halved and that some monitors (notably FreeSync monitors)
do not support it.
The upside is that we get 2x integer scale and progressive scan.


How to use
==========

Download the 1080p.skprx file : https://github.com/gameblabla/pstv_1080p/raw/simp/1080p.skprx

Now go into FTP mode in PSVShell and connect to it with Filezilla or any other FTP client with the assigned IP address and port.

Copy 1080p.skprx to ur0:tai/

Edit the file in ur0:/tai/config.txt and add it below *KERNEL like this :

*KERNEL
ur0:tai/1080p.skprx

Reboot.

Now if you switch to any video mode in the settings, it will switch to 1080p 30.


TODO
====

Add a check.
