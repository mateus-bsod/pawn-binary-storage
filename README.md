# pawn-binary-storage
This include was created strictly for study purposes, focusing on binary file handling and memory behavior in Pawn.
It is not intended to be a safe, complete, or production-ready data management system and may contain limitations or unhandled edge cases.

> [!WARNING]
> This include requires an increased dynamic memory size due to intensive use of runtime buffers, strings, and binary data handling.
> Before using this library, you must define:
```pawn
#pragma dynamic 65536
```

#

### Functions
```pawn
BIN::Open(const file[])
BIN::Save()
BIN::WriteFloat(key[], Float:value)
BIN::WriteInt(key[], value)
BIN::WriteString(key[], value[])
BIN::BinKeyExists(const key[])
BIN::GetKeyValue(key[])
BIN::GetKeyValueEx(const k[], v[], m = sizeof(v))
BIN::AddKeyValue(const key[], const value[])
BIN::AppendRaw(const buffer[], size)
BIN::ReplaceKeyValue(key[], value[])
BIN::WriteFile(const string[], filemode:mode = io_write)
BIN::ParserBIN(binary[], key[], value[])
BIN::Parser(text[], key[], value[])
BIN::IsBinary(const str[])
BIN::GetCharCountFromBin(const bin[])
BIN::ConvertStr(s[], o[], m = sizeof(o))
BIN::BinStr(const b[], s[], max = sizeof(s))
```

### Example
```pawn
#include <a_samp>
#include <binary>

main(){}

public OnGameModeInit()
{
	BIN::Open("dados.bin");
	BIN::WriteString("creator", "mateus-bsod");
	printf("creator = %s", BIN::GetKeyValue("creator"));
	BIN::WriteString("creator", "mateus-delicia");
	printf("creator = %s", BIN::GetKeyValue("creator"));
	BIN::Save();
	return 1;
}
```

# Others examples: 
[test.pwn](https://github.com/mateus-bsod/pawn-binary-storage/blob/main/test.pwn) | 
[benchmark-dof2.pwn](https://github.com/mateus-bsod/pawn-binary-storage/blob/main/benchmark-dof2.pwn)

# License

pawn-binary-storage exists to extend the life of the Pawn language. The goal of this project is not ownership or control, but evolution. The code is intentionally open, simple, and reusable so anyone can take it, modify it, improve it, and adapt it to their own needs.

pawn-binary-storage is designed to grow alongside SA-MP, extending a_samp.inc with binary storage utilities and abstractions that make Pawn more practical and relevant over time. Reuse, refactoring, and enhancement are not only allowed but encouraged. The project assumes that its best future comes from being shared, studied, and rewritten by the community.

The focus is on usefulness, longevity, and collaboration. pawn-binary-storage does not aim to reinvent Pawn, but to keep it alive by providing developers with better tools for working with binary data in a language they already use.
