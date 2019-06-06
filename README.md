# BootVar
```
Get Boot Variables in UEFI Shell, e.g. Boot0000, Boot0001 ...
```

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
Boot0000 : USB: ADATA USB Flash Drive 
FilePath Length 27 
FilePath.Type 05 
FilePath.SubType 01 
BBS(HD,USB: ADATA USB Flash Drive) 

Boot0001 : UEFI USB: ADATA USB Flash Drive 
FilePath Length 1C 
FilePath.Type 02 
FilePath.SubType 01 
PciRoot(0x0)/Pci(0x10,0x7)/USB(0x3,0x0) 

Boot0002 : Internal EDK Shell 
FilePath Length 2C 
FilePath.Type 04 
FilePath.SubType 07 
Fv(92E111AA-5F63-49D5-96C7-947422BDD1AA)/FvFile(C57AD6B7-0515-40A8-9D21-551652854E37) 
```
