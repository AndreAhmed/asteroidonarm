Asteroids on ARM M3

A simple simulator has been written using SDL to verify the graphics algorithms before uploading the firmware to the microcontroller.

Code especially the LCD driver needs a lot of refactoring, and optimization, especially copying the framebuffer from the SDRAM to the LCD GRAM, DMA has be to used. Due to lacking of hardware resources, I'm going to postponed that feature now.



[IMG](IMG.md)http://i58.tinypic.com/2qsvv2p.png[/IMG]