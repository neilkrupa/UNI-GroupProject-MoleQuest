### How do I get set up? ###

* Download and Install Visual Studio 2013. Make sure it is the 2013 version. It doesn't matter if you use Express or Professional 
* Download SFML (http://www.sfml-dev.org/files/SFML-2.2-windows-vc12-64-bit.zip)
* Follow this tutorial to setup SFML and Visual Studio (http://www.sfml-dev.org/tutorials/2.2/start-vc.php)
* Ignore the part about making the SFML libraries static
* Remember to copy-paste sfml-graphics-d-2.dll sfml-system-d-2.dll sfml-window-d-2.dll into the folder where the .exe gets made by Visual Studio
* You will need to change the build type from Win32 to x64 in Visual Studio
* Clone the source code of this repository 
* Open the MoleQuest.sln with Visual Studio

### Contribution guidelines ###

* Follow the Google C++ Code Style http://google-styleguide.googlecode.com/svn/trunk/cppguide.html
* Name your files .cc and .h
* Every .cc file should have a .h counter-part to keep the code organised and improve performance
* Use 2 spaces for indentation, not tabs. You can edit Visual Studio to insert 2 spaces whenever you hit the tab key.
* Every .h should have include guards (http://google-styleguide.googlecode.com/svn/trunk/cppguide.html#The__define_Guard)
* Lines should be no longer than 80 columns long
* Includes should be added to "stdafx.h" to improve performance as opposed to adding them to the .cc files
* Don't include anything in .h files
* Comment all of your shit. Comments for classes, comment for class variables, comments for every function, and comments when you're not doing anything completely obvious.