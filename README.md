## MapleStory Global v176.1 Localhost Enabler

- NGS Removed
- MSCRC Patched
- Nexon Logging Removed
- Multi Client Enabled
- Discord Rich Presence Support

Launched via the following...

    MapleStory.exe GameLaunching 8.31.99.141 8484

## Gallery
![SpiritMS](https://media.discordapp.net/attachments/631249406775132182/848053274606436392/1c73723041ce0f3e18de43abb6a5526b.png)

## Notes:
This repository is a fork of [Client176](https://github.com/RajanGrewal/Client176) created by [RajanGrewal](https://github.com/RajanGrewal).

This repository adds Discord Rich Presence support. 
The open source version of this Repo currently doesn't provide support for in-game information relay. 

Meaning you cannot show your in-game Character's stats (I.E. Level, Map, Job).

## Discord RPC Config (IMPORTANT)
1. Changing the client id. Navigate to ``Global.h`` and change ``RPC_CLIENT_ID`` to your desired client ID.
    - For more info on how to get a Discord RPC Client ID. Please naviate to the [Discord Developer Portal](https://discord.com/developers/docs/intro)
    - This is not a tutorial on how to setup Discord Specific APIs
2. Navigate to ``EntryPoint.cpp`` and in the StartRPC() function, please change any current configurations to your liking.
3. Build the project in Visual Studio on x86 Release, which will output an ``ijl15.dll``.

## Possible Errors
- Linker Error, ``Cannot find ::core``. This is caused by your Visual Studio not compiling a lib file that is required for this project.
    - Specifically ``discord_game_sdk.dll.lib``
    - To rectify this problem, start by downloading Discord's Official SDK Library [Here](https://discord.com/developers/docs/game-sdk/sdk-starter-guide).
        1. Extract all the contents of ``discord_game_sdk.zip`` into a new folder (that you create, it can be any name).
        2. In the folders, you will find ``lib`` directory, this is the directory that will store that .lib file you will input into Visual Studio's Linker.
        3. In Visual Studio Right Click the Project named ``Client176`` in ``Solution Explorer`` and select ``properties``.
        4. Navigate to Linker -> Input
        5. Hit the little downwards pointing arrow in the ``Additional Dependencies`` section and then click ``Edit``
        6. Paste in the directory where your ``discord_game_sdk.dll.lib`` is located, for example mine is ``D:\discord-rpc-master\lib\x86\discord_game_sdk.dll.lib`` so that is what I put in
        7. Now navigate to ``VC++ Directories`` in the same properties UI and in the ``Library Directories`` section add the path to ``discord_game_sdk.dll.lib`` location but not the file itself. For example, mine would be ``D:\discord-rpc-master\lib\x86`` so I would input that.
        8. Click apply and you should be good to go!
 
- Discord RPC is not working when I launch game!
    - You may be missing a dll file in your game folder (maplestory game folder). Add ``discord_game_sdk.dll`` found in your ``lib\x86`` directory into your maplestory game files.
    - If you aren't missing a dll, it might just take a second for the RPC to load on initial launch, so be patient!

- ~~Game does not launch if I don't have Discord Open!~~
    - ~~Unfortunately, even with ``NoRequireDiscord`` CreateFlag, it seems the game won't launch if you don't have discord open! Currently no solution to fixing this problem yet, stay tuned~~
   
    -Seldom fixed as of commit [``c5a935aa91e3956b22a7d9377be05ea027d74762``](https://github.com/TEAM-SPIRIT-Productions/AuthHook176_RPC/commit/c5a935aa91e3956b22a7d9377be05ea027d74762). From testing, it might be inconsistent, stay tuned for a more concrete fix to this issue. If you want it to work 100% of the time please remove the FindWindowA() check in ``EntryPoint.cpp``
