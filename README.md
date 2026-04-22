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

* `search <word> in <file_path>`
* `count <word> in <file_path>`
* `replace <word> with <newword> in <file_path>`
* `delete <word> in <file_path>`
* `append <word> to <file_path>`
* `rename <file_path> to <newfile_path>`
* `deletefile <file_path>`
* `top <n> <file_path>`

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
search hello in /home/user/data/file1.txt
count test in /home/user/data/file2.txt
replace old with new in /home/user/data/file3.txt
delete temp in /home/user/data/file4.txt
append data to /home/user/data/file5.txt
rename /home/user/data/file1.txt to /home/user/data/newfile.txt
deletefile /home/user/data/file6.txt
top 5 /home/user/data/file7.txt
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
* 📈 bargraphs generated using gnuplot

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
