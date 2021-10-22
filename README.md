# SC (Simple Chat)
SC (Simple Chat) is a secure and serverless chat application for Unix based platforms. Messages are encrypted and broadcasted to the broadcast address using the UDP protocol. Any user within the same network is able to read the messages and respond back. Users can only read messages if it was originally encrypted with the same key as theirs, otherwise messages will not appear on their chat room window.

### Download prebuilt binaries
**Linux x64**
```
sudo curl https://raw.githubusercontent.com/miladfarca/sc/master/prebuilt/sc-linux-x64 -o /usr/local/bin/sc && sudo chmod +x /usr/local/bin/sc
```
**macOS x64**
```
curl https://raw.githubusercontent.com/miladfarca/sc/master/prebuilt/sc-macos-x64 -o /usr/local/bin/sc && chmod +x /usr/local/bin/sc
```

### Encryption
All messages are encrypted with `AES-256-CBC` using a default key. Users are
strongly recommended to reset it to their own key when loading the app.

Users wishing to communicate with each other need to use the same key.

### Commands
To enter a command simply initiate your chat with `:` and enter a command from this list:
| Command | Action |
|---|---|
| :q | Quit |
| :c | Clear chat room window |
| :key [new key] | Change your key |
| :name [new name] | Change your username |

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
sudo /usr/libexec/ApplicationFirewall/socketfilterfw --add /usr/local/bin/sc
sudo /usr/libexec/ApplicationFirewall/socketfilterfw --unblockapp /usr/local/bin/sc
```