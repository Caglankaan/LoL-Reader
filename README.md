# LoL-Reader

LoL-Reader is a tool to read real-time League of Legends statistics from memory. 

### Installation - Compile
```bash
 g++ *.cpp -L. -lPsapi -w -o program
```
It only need psapi library to run.

### Examples
This tool is working perfectly on League of Legends version 11.24 . When new version arrives most probably offsets had to be recalculate again. To calculate offsets there is already a good explanation on [unknowncheats.me](https://www.unknowncheats.me/forum/league-of-legends/320116-dump-lol-addresses-guide.html).

We have few different options. 
![Alt text](imgs/1.png?raw=true "Title")

First one is getting statistics for our current character. It displays:

* Character current/maximum health
* Character current/maximum mana
* Character attack values (base, bonus, ability power etc.)
* Character movement speed
* Character armour values (total, bonus)
* Hero level
* Hero name
* Character position in x,y,z format.


Example output:
![Alt text](imgs/2.png?raw=true "Title")

Second one third one is responsible to print same values for whole our team characters or enemy team characters.

![Alt text](imgs/3.png?raw=true "Title")
![Alt text](imgs/4.png?raw=true "Title")

And there is also a function which returns same values for the closest enemy or team mate.

![Alt text](imgs/5.png?raw=true "Title")
![Alt text](imgs/6.png?raw=true "Title")

With the help of this since we already know our current position and the closest (or any) enemies current position we can say that we basically have a wallhack for league of legends. This tool is not responsible to print closest enemy into the screen but it can found them even if the enemies are invisible.