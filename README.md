# Discord++ example bot, Echo<sup>(Echo<sup>Echo<sup>Echo<sup>Echo)</sup></sup></sup></sup>

## Community & Support <sup>Some incredibly nice people here!</sup>
[Discord++ Discord Server](https://discord.gg/0usP6xmT4sQ4kIDh)

## How to Get Started <sup>Let's get it sta-arted! Let's get it started in here!</sup>

### Install Prerequisites
#### Install Git
 * If you want to use Git in the command line, run `sudo apt install git`
 * If you'r less terminal-inclined, you can install a Git GUI wrapper. [There's a nice list here.](https://git-scm.com/downloads/guis/)
 ..* I would personally recommend [GitKraken](https://www.gitkraken.com/). The free version has everyhting you need, (although their conflict resolver for Pro is nice,) and you can also get Pro free with [GitHub Education](https://education.github.com/)!
#### <sup>AND</sup> Install C++
 1. Install a C++ compiler
 ..* the typical standard is `gcc`, you can install it with `sudo apt install gcc`
 ..* `clang` is an alternative that I feel has better error statements, you can install it with `sudo apt install clang`
 2. Install CMake with `sudo apt install cmake`
#### <sup>AND</sup> Install Libraries
 * Debian-based (Ubuntu) `sudo apt install build-essential libboost-all-dev libssl-dev libcrypto++-dev libcurl4-openssl-dev`
 * Fedora/RHEL-based `sudo dnf install openssl-devel boost-devel cryptopp-devel cryptopp`
#### <sup>OR</sup> Install Everything at Once
`sup apt install git clang cmake build-essential libboost-all-dev libssl-dev libcrypto++-dev libcurl4-openssl-dev`

### Set Up Repository
#### Fork Echo
 * Click the `Fork` button in the upper-right of the repo's page
 * If you're in an organization, elect the where you want the fork to go
 * Click on your new `Settings` tab, and rename your new repo
#### Clone Your Fork
TODO

### Register a Bot
TODO

### Build your Bot
 1. Create a `build` directory (folder) with `mkdir build`
 2. Enter the folder with `cd build`
 3. Build the bot with `cmake ../`
 4. Run the bot with `./echo_bot`
 ..* You can change the executeable name by modifying the `project` command in `CMakeLists.txt`
 5. ???
 6. Profit! Mention your bot in a scope it can read & write in, it should echo back your message.

## Contributing
 * Echo is pretty simple and probably doesn't need much, but if you have a suggestion or spot an issue, make a pull request on Github!
 * Also, this repo needs better jokes.