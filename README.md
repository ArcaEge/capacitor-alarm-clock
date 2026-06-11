![capacitor alarm clock](assets/banner.png)

<div align="center">
    <h1>
        capacitor alarm clock
    </h1>
    <p>
        <strong>
            wake up to the bang of a capacitor going off
        </strong>
    </p>
    <p>
        <a href="#features">Features</a> •
        <a href="#demo">Demo</a> •
        <a href="#pcb">PCB</a> •
        <a href="#cad-files">CAD</a> •
        <a href="#building--flashing-firmware">Firmware</a> •
        <a href="#usage">Usage</a>
    </p>
    <img src="assets/cad_image.png" alt="CAD image" width="500" />
    <img src="assets/pcb/render.png" alt="PCB render" width="500" />
</div>

## Why?

Why not?

This was originally inspired by ElectroBOOM's [capacitor alarm video](https://www.youtube.com/watch?v=5dYt34JIDGw); this is like a safer (?), more practical and more useable-ish version of that.

> [!WARNING]
> Take care when using this, and only do so if you know what you're doing. Capacitor explosions are quite violent and the fumes aren't nice to breathe. This project is mostly a high-effort joke and not something practical to use

## Features

- ESP32-powered
  - Configure settings via the webserver
  - Fetch time automatically via NTP
- 128x64 SSD1315 display
- 3 separate capacitor slots
- Up to 3A through the capacitors
  - 10 ohm current limiting resistors to avoid brownouts if the capacitor shorts
- Power via USB-C or barrel jack (12-15V)
- Small size (72x74x36mm)

Here's how it looks:

<img src="assets/assembled2.png" alt="assembled capacitor alarm clock resting on hand" width="500" />

<img src="assets/assembled.png" alt="assembled" width="500" />

<img src="assets/assembled_lid_off.png" alt="assembled" width="500" />

## Demo

Also on YouTube [here](https://youtu.be/eKc19qRxZ5o)

https://github.com/user-attachments/assets/c24133be-e630-4c25-ad7a-87afec26e37d

## PCB

Images of schematics and more are under the [PCB README](pcb/README.md). A BOM is available under [production](production/). I'd recommend using [JLCPCB](https://jlcpcb.com/) as they seem to have the lowest prices.

<a href="pcb/README.md">
    <img src="assets/pcb/front.svg"/>
</a>

## CAD files

CAD files for the shell and PCB are under [`cad/`](cad/). The README there contains more info, but the Onshape project is available [here](https://cad.onshape.com/documents/62d468c7ff14a2e83cb50980/w/ededd05b0c271bca944a2c41/e/b2699bc116bdf7662263df84).

## Building + flashing firmware

To build and flash the firmware, you'll need to use PlatformIO. Install the VSCode extension and open the firmware folder, then follow the instructions in the [firmware README](firmware/README.md).

## Usage

Once flashed and connected to WiFi, the display will show the current time. You can go into the settings by pressing "select" (done by pressing both buttons at once). From there, you can use the left and right buttons to go up and down and set the alarm time, schedule, next capacitor slot and more. You can also go into the "about" page to see the clock's IP.

Once you have the IP, you can go to the web interface at `http://<IP>/`. Note: some browsers might only try HTTPS (looking at you Firefox), so you'll need to manually enter the `http://` part.

> [!NOTE]
> The voltage regulators might heat up a bit during use, this is normal as there's ~12V of voltage drop across them. It might be a better idea to use a buck converter circuit instead of voltage regulators to step down the voltage. I chose voltage regulators to save on board space, but they do get quite hot. A buck converter circuit would also enable the use of higher input voltages, as the limiting factor right now is thermals.

## Sourcing capacitors

When choosing capacitors, you should avoid capacitors with these pressure release slots at the top, as they will reduce the bang. Choose the biggest capacitor you can get that has no top slot.

![capacitor comparison](assets/capacitor_comparison.png)

Also try to go as low as possible with the voltage rating to increase reliability, ~16V is where you should aim. [These capacitors](https://www.lcsc.com/product-detail/C22320.html) from LCSC are pretty good, at $3 for 200.

## Magazine page

This project was submitted to [Hack Club Fallout](https://fallout.hackclub.com)! Here's the page for the Fallout magazine:

<a href="assets/magazine/magazine.pdf">
    <img src="assets/magazine/magazine_lowres.png" alt="magazine page" />
</a>
