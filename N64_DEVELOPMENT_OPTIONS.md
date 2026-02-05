# N64 Game Development - Tech Stack Options

**Status: SETUP COMPLETE**

Your environment is configured with:
- **libdragon** (preview branch) - N64 SDK
- **tiny3d** - High-performance 3D library
- **Toolchain** - GCC 14.2.0 for MIPS R4300

## Quick Start
```batch
build_game.bat    # Build your game
clean.bat         # Clean build artifacts
setup.bat         # Re-run setup if needed
```

---

This document outlines modern options for building Nintendo 64 homebrew games in 2026.

---

## Quick Recommendation

**For most developers: Go with Libdragon + Tiny3D**

It's the most actively maintained, has the best tooling, excellent documentation, and a thriving community.

---

## Option 1: Libdragon (C/C++) ⭐ RECOMMENDED

**Repository:** [DragonMinded/libdragon](https://github.com/DragonMinded/libdragon)

### Overview
The most popular open-source N64 SDK. Actively maintained with modern tooling and a large community.

### Pros
- **Modern GCC 14** with full C11 support
- **Docker-based setup** - Get started in minutes
- **64-bit capable** - Uses full R4300 CPU capabilities (unlike original SDK)
- **OpenGL 1.1 port** with N64-specific extensions
- **Excellent debugging** - Assertions, printf debugging via USB/emulator
- **Fast boot** - Open-source IPL3 boots ROMs 5x faster
- **Active community** - N64brew Discord, game jams, regular updates
- **Great documentation** at [libdragon.dev](https://libdragon.dev/)

### Cons
- Requires modern emulator (Ares) for accurate testing
- Learning curve if coming from original N64 SDK

### 3D Graphics Options

| Library | Description | Best For |
|---------|-------------|----------|
| **OpenGL 1.1** | Built into libdragon | Familiar API, easier porting |
| **Tiny3D** | High-performance native 3D | Maximum performance, N64-specific |
| **rdpq** | Low-level RDP access | 2D games, custom rendering |

### Build Requirements
- Docker (easiest)
- Or: Linux/WSL with GCC cross-compiler

---

## Option 2: Libdragon + Tiny3D (Best for 3D Games)

**Repositories:**
- [DragonMinded/libdragon](https://github.com/DragonMinded/libdragon)
- [HailToDodongo/tiny3d](https://github.com/HailToDodongo/tiny3d)

### Overview
Tiny3D is a high-performance 3D library built specifically for the N64, designed to work with libdragon.

### Pros
- **Custom RSP microcode** written from scratch (no proprietary code)
- **GLTF import** - Use Blender for 3D modeling
- **Skeletal animation** with skinning support
- **Direct RDPQ interop** - Mix 2D and 3D easily
- **High performance** - Optimized for N64 hardware

### Cons
- Requires libdragon preview branch
- Smaller community than core libdragon

---

## Option 3: Rust Development (nust64 + libdragon)

**Repositories:**
- [rust-n64/nust64](https://github.com/rust-n64/nust64)
- [rust-n64/n64-project-template](https://github.com/rust-n64/n64-project-template)

### Overview
For Rust developers who want memory safety on the N64.

### Pros
- **Memory safety** - Rust's guarantees
- **Modern tooling** - Cargo integration
- **Uses libdragon's IPL3** - No need to source bootcode
- **Good starting template** available

### Cons
- Smaller community
- Less documentation than C options
- Some N64-specific patterns don't map well to Rust
- Last major update: mid-2024

---

## Option 4: Modern SDK (n64sdkmod)

**Repository:** [CrashOveride95/n64sdkmod](https://github.com/CrashOveride95/n64sdkmod)

### Overview
Modernized version of the original Nintendo libultra SDK.

### Pros
- **Familiar to N64 veterans** - Same API as original games
- **Lots of documentation** - Original Nintendo docs apply
- **Battle-tested** - The API that made classic N64 games

### Cons
- **Linux only** (Debian-based)
- Legal gray area (based on leaked SDK)
- 32-bit ABI limitations
- Less active development than libdragon

---

## Option 5: n64chain (Minimal Toolchain)

**Repository:** [tj90241/n64chain](https://github.com/tj90241/n64chain)

### Overview
Minimal GCC toolchain with no proprietary dependencies.

### Pros
- **Lightweight** - Just the compiler
- **No proprietary code** - Completely clean
- **Educational** - Great for learning N64 internals

### Cons
- No high-level libraries included
- You build everything from scratch
- Not recommended for game development

---

## Comparison Matrix

| Feature | Libdragon | Libdragon+Tiny3D | Rust | Modern SDK |
|---------|-----------|------------------|------|------------|
| **Language** | C/C++ | C/C++ | Rust | C |
| **3D Support** | OpenGL 1.1 | Native optimized | Limited | libultra |
| **Setup Ease** | ⭐⭐⭐⭐⭐ | ⭐⭐⭐⭐ | ⭐⭐⭐ | ⭐⭐ |
| **Documentation** | ⭐⭐⭐⭐⭐ | ⭐⭐⭐⭐ | ⭐⭐⭐ | ⭐⭐⭐⭐ |
| **Community** | ⭐⭐⭐⭐⭐ | ⭐⭐⭐⭐ | ⭐⭐ | ⭐⭐⭐ |
| **Performance** | ⭐⭐⭐⭐ | ⭐⭐⭐⭐⭐ | ⭐⭐⭐ | ⭐⭐⭐⭐ |
| **Legal Status** | ✅ Clean | ✅ Clean | ✅ Clean | ⚠️ Gray area |
| **Windows Support** | ✅ Docker/WSL | ✅ Docker/WSL | ✅ | ❌ Linux only |

---

## Recommended Emulator

**Ares** - The only emulator that accurately emulates N64 hardware for homebrew development.

Other emulators (Project64, Mupen64Plus) focus on compatibility with commercial games and may not work correctly with modern homebrew.

---

## My Recommendation

### For a New N64 Game Project:

```
Libdragon (preview branch) + Tiny3D + Docker
```

**Why?**
1. **Easiest setup** - Docker container works on Windows/Mac/Linux
2. **Best 3D pipeline** - Tiny3D with GLTF/Blender workflow
3. **Active community** - Get help on N64brew Discord
4. **Modern tooling** - GCC 14, proper debugging
5. **Legally clean** - No proprietary Nintendo code
6. **Future-proof** - Most active development

---

## Resources

- [n64.dev](https://n64.dev/) - Curated list of N64 development resources
- [libdragon.dev](https://libdragon.dev/) - Official libdragon documentation
- [N64brew Discord](https://discord.gg/WqFgNWf) - Active community
- [N64brew Wiki](https://n64brew.dev/wiki/) - Community wiki

---

## Next Steps

Once you've chosen a stack, I can clone the necessary repositories and set up the development environment for you.

**Let me know which option you'd like to proceed with!**
