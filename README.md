# Mendax-Binder
A useful and efficient file binder.  I created this for educational purposes after researching some file binding techniques.
Not only can it bind two exes (Windows only), but this program also obfuscates ths two exes.  Its output file is usually fully undetectable among 68.7% of the antivirus software used on VirusTotal.

## How it Works
This program always binds itself to the two other files.  This way, when the binded application runs, the program first checks if the application is correctly binded.  If it is, it runs the two applications.

## Usage
So far, only CLI is supported.  Here are the options:
 * -1: First input file
 * -2: Second input file
 * -o: Name for the output file
 * -h: Displays this help message
 * -v: Displays version number
 
 Users can either choose to download the executable from the releases section, clone the repo, or compile mendax.c with MinGW's gcc.
 Remember that this program is only for EDUCATIONAL PURPOSES.  I am not responsible if you ruin your own computer or get in serious trouble for creating malware.
 
 ## Authors
* **Will Liu** - *Creator* - [BitsByWill](https://github.com/BitsByWill)

## What's Next
* Better obfuscation
* Make a GUI
* Bind more than two files
* Patch up any issues (Let me know of any issues please!)

## License
This project is licensed under the GNU GPLv3 - see the [LICENSE](LICENSE) file for details
