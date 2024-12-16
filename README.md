Hi!  Welcome to my Quake2 mod!  This mod is heavily based off of the game Aragami by Lince Works.


Once you have Quake 2 downloaded:
  You can do 1 of 2 things
1) The first:  the folder called "OpenMe" has the mod folder inside of it. If you want, you can just drag that "AragamiModFolder1" Folder into the "Quake 2" folder. And have this act as your mod folder
2) The second: You can create a new folder yourself in the "Quake 2" folder (where ever Steam installed it for you)! This new folder will be your mod folder, and you can follow the instructions further below to Build the source code, and move the **gamex86.dll** file into that new folder by yourself :D

Once all the files from the "AragamiMod" branch of the respository have been downloaded to your device's local folder:
- Open the quake2.sln file with Visual Studio
- Make sure the Build Configuration is set to Release and not Debug, and use the Win32 Solution Platform.
- One thing you can do, in order to make sure the "**gamex86.dll**" file (that will sono be created) goes directly into the your mod folder - for the sake of easy building and compiling - is:
  - You can right-click the "game" Project inside of Visual Studio's Solution Explorer ("game" as opposed to "ctf" or "quake2"), go down to Properties. And in - what should be - the first screen that shows up, change the output directory to whichever Mod folder you made for Quake2 (if it's not the first screen that shows up, this setting is in: it's under Configuration Properties -> General).
- Build the solution. And if you didn't follow the previous step, be sure to move the **gamex86.dll** file (which should be in the "game" folder -> "release" folder by default) into your mod folder.

In addition to the **gamex86.dll** file,  inside your mod folder you will NEED the **config.cfg** file that comes from this repository. The **config.cfg** file in question has been placed into the OpenMe folder for convenience. Don't move the folder, just take the config file out of it.


Personal Deliverables List:
- ✔ Replace all the Quake weapons with Ninja weapons    
- ✔ 5 Stealth mechanics  (1) Hide in Darkness (2) Stealth Kills (3) Use sound to lure some enemies away (4) Invisibility makes you.. well, invisible (5) Invisibility becomes more effective with a higher Stealth stat 
- 5 Ninja abilities   (1) Teleport (2) Strength Channeling -- 2x damage  (3) Invisibility   (4) Absolute Silence (no Self-made noises, like jump)  (5) Defense boost..? if you want to count Powerarmor?
- ✔ Energy System (to use the Ninja abilities, etc.)
- RPG elements; no less than 4 stats  (1) Health, obvi  (2) Stealth stat  (3) Defense?? technically!
