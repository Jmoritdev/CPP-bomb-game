# Sample
A game made for the intake assessment at NHTV

this game was coded in visual studio community 2015.

I used SDL2 as the base for this game (https://www.libsdl.org/). <br>
I have worked through the entirety of Beginning c++ Through Game Programming by Michael Dawson (Fourth edition) for learning c++, 
and followed this (http://lazyfoo.net/tutorials/SDL/index.php) tutorial for working with SDL2.

I also used a header from this tutorial such as Texture.h and bits and pieces of code such as the collision detection and basic movement. 
Everything else was made entirely by me.

# How to run this game in visual studio (2015) from a ZIP file

Extract it.

Open the project in visual studio.

All settings should be correct from the start. If not, follow the installation instructions below.

Now run the project in Debug x86 mode and it should run fine. 
If it doesn't, please check if your virus scanner doesn't block anything.

# How to run this game in visual studio (2015) from Github

Clone it in visual studio from this link: https://github.com/Jmoritdev/Sample.git

Open it.

Right click the project and select properties.

Go to Configuration Properties -> VC++ Directories and edit the "Include directories".
Add the following lines: <br>
.\Dependencies\SDL2_image-2.0.1\include <br>
.\Dependencies\SDL2_ttf-2.0.14\include <br>
.\Dependencies\SDL2-2.0.5\include <br>
And click OK.

Now edit the Library directories.
Do the same as before, only with these lines instead: <br>
.\Dependencies\SDL2_image-2.0.1\lib\x86 <br>
.\Dependencies\SDL2_ttf-2.0.14\lib\x86 <br>
.\Dependencies\SDL2-2.0.5\lib\x86 <br>
And click OK.

Go to Configuration Properties -> Linker -> Input and edit the "Additional dependencies".
Copy and paste these lines into the first textfield: <br>
SDL2_image.lib <br>
SDL2.lib <br>
SDL2_ttf.lib <br>
SDL2main.lib <br>

Click "Apply".

Now run the project in Debug x86 mode and it should run fine. 
If it doesn't, please check if your virus scanner doesn't block anything.

# Controls

WASD to move. <br>
Arrow keys to shoot a bomb.

# Contact

For questions please email: z.jmorit@gmail.com

Please do see some of my other projects at www.github.com/Jmoritdev for more of my work.

Thanks for reading!
