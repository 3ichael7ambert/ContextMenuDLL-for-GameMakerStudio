# ContextMenuDLL-for-GameMakerStudio

A C++ DLL extension for Game Maker Studio to enable Windows right clicking.

To compile .cpp to a .dll, you need to open Developer Terminal or Developer PowerShell, change to the directory and run the following command;

```ps1
cl /LD ContextMenuDLL.cpp /Fe:ContextMenuDLL.dll /link User32.lib
```

x64

```ps1
cl /LD /Fe:ContextMenuDLL.dll ContextMenuDLL.cpp /link /MACHINE:X64 User32.lib
```

Mac OS

```bash
clang -dynamiclib -o ContextMenu.dylib ContextMenuDYLIB.m -framework Cocoa
```

NOTE: MAC OS isn't working atm
