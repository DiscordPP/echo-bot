# Discord++ example bot, Echo<sup>Echo<sup>Echo</sup></sup>

## Community & Support <sup>Some incredibly nice people here!</sup>
[Discord++ Discord Server](https://discord.gg/0usP6xmT4sQ4kIDh)

## How to Get Started <sup>Let's get it sta-arted! Let's get it started in here!</sup>

### Install Prerequisites
#### Install Git
 * If you want to use Git in the command line, run `sudo apt install git`
 * If you're less terminal-inclined, you can install a Git GUI wrapper. [There's a nice list here.](https://git-scm.com/downloads/guis/)
    * I would personally recommend [GitKraken](https://www.gitkraken.com/). The free version has everyhting you need, (although their conflict resolver for Pro is nice,) and you can also get Pro free with [GitHub Education](https://education.github.com/)!
#### <sup>AND</sup> Install C++
 1. Install a C++ compiler
    * the typical standard is `gcc`, you can install it with `sudo apt install gcc`
    * `clang` is an alternative that I feel has better error statements, you can install it with `sudo apt install clang`
 2. Install CMake with `sudo apt install cmake`
#### <sup>AND</sup> Install Libraries
 * Debian-based (Ubuntu) `sudo apt install build-essential libboost-all-dev libssl-dev libcrypto++-dev libcurl4-openssl-dev`
 * Fedora/RHEL-based `sudo dnf install openssl-devel boost-devel cryptopp-devel cryptopp`
#### <sup>OR</sup> Install Everything at Once
`sup apt install git clang cmake build-essential libboost-all-dev libssl-dev libcrypto++-dev libcurl4-openssl-dev`

### Set Up Repository
#### Fork Echo <sup>Optional, I guess</sup>
 * Click the 'Fork' button in the upper-right of the repo's page
 * If you're in an organization, elect the where you want the fork to go
 * Click on your new 'Settings' tab, and rename your new repo
 
#### Clone the Code
Run `git clone --recursive https://github.com/discordpp/echo-bot.git` in your desired directory. If you made a fork, replace `discordpp` and `echo-bot` ass applicable.

### Register a Bot
 1. Go to Discord's [Developer Portal 'Application' page](https://discordapp.com/developers/applications/), it will prompt you to sign in <sup>By the way, do you have 2FA enabled? It's a really good idea, especially with bots on your account</sup>
 2. Click 'New Application', and enter a name for your bot
 3. Click on 'Bot' under 'Settings' on the right, click 'Add Bot', and then 'Yes, do it!'
    * Make note of the 'Copy' button under 'Token', we'll get back to this later
    * Also, come back and click the 'regenerate' button if anyone ever gets a hold of your bot's token
    * If you want to give your bot an avatar, I'd recommend doing it both on the 'General Information' landing page and here on the 'Bot' page, it makes things less confusing if you ever need to come back.

### Add your Bot to a Server
 1. Copy `https://discordapp.com/api/oauth2/authorize?client_id=[ID]&scope=bot&permissions=[permissions]` to somewhere, such as notepad
 1. Go back to the 'General Information' page of your application
 2. Click 'Copy' under 'Client ID', and paste it into your URL, taking care to replace the word and brackets
 3. Go to the 'Bot' page
 4. Select the permissions you want your bot to have from under 'Bot Permissions'
    * You probably want at least 'Send Messages', `2048`
 5. Click the 'Copy' button under 'Permissions Integer', and paste it in your URL, make sure you get the brackets like before
 6. Paste the URL into a web btowser, select a server to add it to, and click 'Authorize'
 

### Build your Bot
 1. Create a `build` directory (folder) with `mkdir build`
 2. Enter the folder with `cd build`
 3. Go back to your Application's 'bot' page from before, and copy the token. Run `echo Bot [token] > token.dat`, replacing the brackets and the word token
 4. Build the makefiles with `cmake ../`
 5. Build the bot with `make`
 6. Run the bot with `./echo_bot`
    * You can change the executable name by modifying the `project` command in `CMakeLists.txt`
 7. ???
 8. Profit! Mention your bot in a scope it can read & write in, it should echo back your message.

## Contributing
 * Echo is pretty simple and probably doesn't need much, but if you have a suggestion or spot an issue, make a pull request on Github!
 * Also, this repo needs better jokes.
