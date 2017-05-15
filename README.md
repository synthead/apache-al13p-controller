## Summary and goals

This project aims to provide a drop-in controller upgrade for the Apache AL13P to obtain one-pass toner transfers for PCBs.  This bad-ass controller will feature:

* Arduino-powered electronics for ease of development and community support
* Better controls and interface for more comprehensive operation
* A PID-backed thermostat for more consistent temperature control
* Super swanky touchscreen support (maybe!)

## Why make new controller?

Toner transfer is an important aspect of etching PCBs, and laminators make transferring toner to copper clad quick and easy.  But there's a catch: a lot of laminators don't get hot enough and/or take enough time to do a single-pass transfer.  As a workaround, the board could be fed through the laminator 10-20 times, but this isn't always effective.

As you'd imagine, it's fairly common for DIY hobbyists to modify laminators to get a little hotter for one-pass transfers.  This is sometimes done by swapping passive components, but more comprehensive implmentations can be achieved by modifying or replacing the laminator's controller (if it has one).

One of the more popular laminators for toner transfers is the Apache AL13P, which is is ideal for PCB work because:

* It's affordable (US-based auctions on eBay reguarly end at $25-50)
* It's 13" wide for large PCBs
* It uses metal gears for better heat tolerance
* It has two sets of powered, opposing silicone rollers for high pressure
* It has a control panel as its own PCB with a display, inputs, and a controller that's easily replaced

With this controller upgrade, you'll be able to increase the heat to an ideal temperature for one-pass toner transfers with the perks of much nicer controls, better heat control, and hopefully, decent community support (that's you!).
