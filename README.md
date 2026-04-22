# 📁 File Analyzer & Text Processing Tool (C)

## 📌 Overview

This project is a command-line utility written in C that:

* Traverses directories recursively
* Analyzes files (words, characters, lines)
* Executes text-based operations from an input file
* Generates a visual directory graph
* Produces statistical plots

---

## ✨ Features

### 📂 Directory Analysis

* Recursive directory traversal
* Skips already processed files
* Generates a graph (`graph.dot` → `graph.png`)

### 🔍 Text Processing Commands

Commands are read from an input file:

* `search <word> in <file>`
* `count <word> in <file>`
* `replace <word> with <newword> in <file>`
* `delete <word> in <file>`
* `append <word> to <file>`
* `rename <file> to <newname>`
* `deletefile <file>`
* `top <n> <file>`

---

## 📊 Output Files

| File        | Description                    |
| ----------- | ------------------------------ |
| `words.txt` | Word count per file            |
| `chars.txt` | Character count per file       |
| `lines.txt` | Line count per file            |
| `graph.dot` | Graph representation           |
| `graph.png` | Visualized directory structure |
| `words.png` | bargraph no of words vs files  |
| `chars.png` | bargraph no of chars vs files  |
| `lines.png` | bargraph no of lines vs files  |
---

## 🛠️ Requirements

* GCC Compiler
* Graphviz (`dot`)
* Gnuplot

### Install (Ubuntu/Debian)

```bash
sudo apt install graphviz gnuplot
```

---

## ⚙️ Build (Using Makefile)

```bash
make
```

---

## 🚀 Run

```bash
./a.out input.txt
```

---

## 🧹 Clean Build Files

```bash
make clean
```

---

## 📝 Input File Format

* **First line** → directory path
* **Next lines** → commands

### Example:

```id="m4n5o6"
/home/user/data
search hello in file1.txt
count test in file2.txt
replace old with new in file3.txt
delete temp in file4.txt
append data to file5.txt
rename file1.txt to newfile.txt
deletefile file6.txt
top 5 file7.txt
```

---

## ⚙️ How It Works

1. Reads directory path from input file
2. Executes commands sequentially
3. Traverses directory recursively
4. Generates:

   * File statistics
   * Graph visualization
   * Plots using gnuplot

---

## ⚠️ Notes

* `processedfiles.txt` is automatically created by the Makefile during build
* Input files must have correct permissions
* Graphviz must be installed for graph generation

---

## 📷 Output

* 📊 Graph image → `graph.png`
* 📈 Plots generated using gnuplot

---

## 🚀 Future Improvements

* Better error handling
* Support for large files
* Parallel processing
* GUI interface

---

## 👨‍💻 Author
 Yasvitaw k
---
