# 01-Primus-1K: The Kaleidoscope

An ultra-compact, hand-optimized 1KB Intro written in pure C and Win32/OpenGL fixed pipeline. This is the **Primus (First) stone** laid in my journey of mastering low-level tech and chasing a childhood dream.

It renders **28 independently animating, color-shifting, and dual-axis rotating quads** directly onto the screen via a brutal raw DC blasting technique (`GetDC(NULL)`), packed into **EXACTLY 1,024 bytes** after being processed by Crinkler.

---

## 🛠️ Technical Implementation & Size Optimization

To fit the executable into a strict 1,024-byte limit without breaking the PE file format, every single line of code and compiler behavior was meticulously audited:

### 1. IAT (Import Address Table) Strip-down
* Removed `glScalef` from the pipeline entirely. Vertex scaling operations are calculated directly inside `glVertex2f` inline mathematical formulas, saving crucial bytes in the import table.
* Replaced standard double-precision `sin`/`cos` with their single-precision float counterparts `sinf`/`cosf` to align mathematical operations and registers efficiently.

### 2. CRT & Security Overhead Elimination
* Compiled with `/NODEFAULTLIB` to strip the Microsoft C Runtime entirely.
* Disabled C++ RTTI (`/GR-`) and security buffer cookies (`/GS-`), forcing the MSVC compiler to emit nothing but raw, deterministic x86 assembly instructions.

### 3. Bit-Level Micro-Tuning
* Leveraged standard `float` loop counters (`for (float i = 1.0f; ...)`) instead of traditional `int` iterators. This eliminates type-casting instructions completely at the machine-code level.
* Micro-tuned global animation constants and inserted strategic mathematical parameters to perfectly fit into Crinkler's Huffman-style compression budget while maintaining a smooth frame pace via `Sleep(22)`.

---

## 💻 How to Run

> ⚠️ **Warning for Single Monitor:** Because this intro utilizes a raw Windows Desktop DC (`GetDC(NULL)`), it is highly recommended to run this in a single-monitor environment for the optimal visual effect.

1. Navigate to the `bin/` directory.
2. Run `primus_1k.exe`.
3. Sit back and enjoy the 1KB mathematical neon storm.
4. Press `ESC` to gracefully exit back to the desktop (safely handled via `GetAsyncKeyState`).

---

## 🔨 Build Specifications

This project is a CRT-free, size-optimized 1KB Intro. Due to variations in local environment paths and individual toolchain setups, a generic build script is not provided to keep the repository unpolluted.

Follow the standard Demoscene compilation pipeline below to reproduce the exact 1,024-byte binary.

### Prerequisites
1. **MSVC Compiler (`cl.exe`)**: Run inside the **`x86 Native Tools Command Prompt for VS 2022`** to ensure a 32-bit target object file is emitted. (Do NOT use the x64 cross-tools terminal).
2. **Crinkler Linker (Strict x86 Version)**: You **MUST** use the 32-bit version of Crinkler (`crinkler.exe`). Do NOT use the 64-bit alternative (`crinkler_x64.exe`), as architectural pointer mismatches during extreme CRT-free linking can cause immediate unresolved symbol failures.

### Step-by-Step Compilation

#### Step 1: Compile into a raw, CRT-free object file
Execute the following command in your VS terminal to emit pure x86 machine instructions without runtime overhead:

```cmd
cl /c /O1 /Os /GS- /GR- src/main.c
```
#### Step 2: Link and compress via Crinkler
Pass the emitted 32-bit `main.obj` to Crinkler. Ensure the system dependencies are explicitly linked, and the entry point is set to our custom `love` function:

```cmd
crinkler.exe main.obj /ENTRY:love /SUBSYSTEM:WINDOWS /COMPAT /OUT:bin/primus_1k.exe user32.lib gdi32.lib opengl32.lib kernel32.lib
```

#### Step 3: Housekeeping (Optional)
Remove the intermediate cache artifact to keep your working directory clean:

```cmd
del main.obj
```

## 📜 Project Metadata & Archival
- **Release Target**: Windows (x86)
- **Author**: halsingland
- **Archival**: You will find `file_id.diz` in the root directory of this repository. This file contains the project's historical BBS-style metadata and personal notes. Please preserve it if you mirror or redistribute this project.
