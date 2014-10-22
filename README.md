### PRIME indicator

Light and clean indicator for switching between integrated intel and dedicated nvidia graphic cards under linux (Ubuntu 14.04 tested only). Automates `prime-select` switch from NVIDIA Optimus drivers and quits from the currently working gnome session. PRIME indicator is written in pure C under Ubuntu 14.04 using GTK+2.0 libraries, because libappindicator-0.1 requires older ones. If you have any suggestions about fow to use GTK+3 instead GTK+2, please send me the feedback.

### How to install

At first, you need compile PRIME indicator binary file under your distribution. As easiest way is to install build-essential packages. Next to the build-essential, you require additional libraries - libgtk2.0 and libappindicator. Below command shows how to install all required to build dependencies:

```
$ sudo apt-get install build-essential libappindicator-dev libgtk2.0-dev
```

Then you can start the _make_ process like:

```
you@computer:~/prime-indicator$ make
```

After successfuly build process, install the required PRIME indicator files using _install_ script with root permissions, giving --for parameters as user names who can switch GPUs:

```
you@computer:~/prime-indicator$ sudo install --for meuser user2nd user3th
```

Et voila! Now restart the gnome session (logout).

### Localize

Currently and generally, _PRIME indicator_ at this moment supports only two languages - english as basic, and polish from localize file. If you're interested in making any translations, send me the translated .po file, i'll attach it in updated installation script.

### Another stuff

_PRIME indicator_ allows two versions - with quit menu option, and without it by default. To show the quit option, use this command:

```
$ ./prime-indicator --with-quit
```

To show indicator version:

```
$ ./prime-indicator --version
```

Help arguments like --help are not provided with the program. It's just not needed.

### License

Fell freely to reuse the code. The indicator idea (and icons :) based on Python version of the indicator, which you can find under git repo of beidl - https://github.com/beidl/prime-indicator/blob/master/prime-indicator 

Greetings
