# BootVar
Get Boot Variables in UEFI Shell, e.g. Boot0000, Boot0001 ...

# Environment
```
UDK2018
VC2015
```

# Build Steps
```
1. Create "BootVar" folder in UDK\AppPkg.
2. Put BootVar.c and BootVar.inf in "BootVar" folder.
3. Add "AppPkg/Applications/BootVar/BootVar.inf" in "[Components]" of "AppPkg\AppPkg.dsc"
4. Buils it
```

# Run on my motherboard
```
Boot0000: USB: ADATA USB Flash Drive
Boot0001: UEFI USB: ADATA USB Flash Drive
Boot0002: Internal EDK Shell
```
