# Simple Chat
simple-chat is a secure and serverless chat application for Unix based platforms. Messages are encrypted and broadcasted to the broadcast address using the UDP protocol. Any user within the same network is able to read the messages and respond back. Users can only read messages if it was originally encrypted with the same key as theirs, otherwise messages will not appear on their chat room window.

### Installation on Linux
```
snap install simple-chat
```
https://snapcraft.io/simple-chat

### Encryption
All messages are encrypted with `AES-256-CBC` using a default key. Users are
strongly recommended to reset it to their own key when loading the app.

Users wishing to communicate with each other need to use the same key.

### Usage
```
simple-chat [options]:
 --help              print usage and exit
 --process-only      disables the gui and usage of commands (expect for .scrc)
 --silent            disables all the text output
 --version           print version and exit
```

### Commands
To enter a command simply initiate your chat with `:` and enter a command from this list:
| Command | Action |
|---|---|
| :address [new address] | Change broadcast address |
| :c | Clear chat room window |
| :help | Print this list |
| :info | Print username, address and port|
| :key [new key] | Change your key |
| :name [new name] | Change your username |
| :port [new port] | Change port (only usable with the ~/.scrc file) |
| :q | Quit |
| :ref | Refresh chat room window |

### .scrc file
You can also place your commands, not including `:`, inside the `~/.scrc` file which will be read during initialization.

### Build
Project can be built with `make`.
Dependencies are `libcurses`, `libpthread` and `libcrypto`.

On Mac you might need to use the following flags to set the openssl path for gcc and the linker (@version might need to be changed):
```
-I/usr/local/opt/openssl@1.1/include
-L/usr/local/opt/openssl@1.1/lib
```
You also might need to unblock it on your firewall:
```
sudo /usr/libexec/ApplicationFirewall/socketfilterfw --add /usr/local/bin/simple-chat
sudo /usr/libexec/ApplicationFirewall/socketfilterfw --unblockapp /usr/local/bin/simple-chat
```