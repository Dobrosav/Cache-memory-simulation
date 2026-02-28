# Cache Memory Simulation

A simple cache memory simulator written in C++ that demonstrates basic cache operations including hit/miss handling and FIFO replacement policy.

## Overview

This project simulates a direct-mapped cache memory with the following features:
- **Tag-based addressing**: 3 hex digits for tag, 1 hex digit for offset
- **FIFO replacement policy**: First In, First Out when cache is full
- **HIT/MISS detection**: Tracks whether data is already in cache
- **Disk simulation**: Uses `hex.txt` file as backing storage

## Project Structure

| File | Description |
|------|-------------|
| `Main.cpp` | Main cache simulator with `CacheMem` class |
| `Generator.cpp` | Generates random test data for hex.txt |
| `hex.txt` | Simulated disk storage (format: `aaaa: dd`) |

## Building

```bash
g++ -o cache Main.cpp
g++ -o generator Generator.cpp
```

## Running

1. First, generate test data:
```bash
./generator
```

2. Run the cache simulator:
```bash
./cache
```

## Usage

The program presents a menu:
- **Option 1**: Read from cache - enter a 4-character hex address (e.g., `00AF`)
- **Option 2**: Exit

### Address Format
- First 3 characters: Tag
- Last 1 character: Offset (0-F)

### Example Session
```
1. Read from Cache
2. Exit
1
Enter address to read from
00AF
MISS
Searching for space to replace...
Replacement successful!
Reading from disk...
Disk read complete.
Data at address 00AF is XX
Cache tag contents:
v   tag  startAddress
1    00A      0
```

## Class: CacheMem

| Member | Type | Description |
|--------|------|-------------|
| `tags` | string[] | Tag array |
| `valid` | bool[] | Valid bit array |
| `startAddress` | int[] | Starting address in data array |
| `data` | string[] | Cache data storage |
| `count` | int | Number of cache lines |

### Methods
- `existsInCache()` - Check if address exists in cache (HIT)
- `insertIntoCache()` - Insert new address into cache
- `loadFromDisk()` - Load data from "disk"
- `readFromCache()` - Read data from cache
- `replace()` - FIFO replacement when cache is full
- `print()` - Print cache contents
- `printData()` - Print all cache data

## License

MIT
