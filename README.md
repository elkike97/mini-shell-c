# mini-shell-c

A minimal Unix-like shell written in C.  
Supports foreground/background processes, custom variables, and a few built-in commands.

---

## Features
- Run external commands (`ls -l`, `cat file.txt`, etc.)
- Foreground & background jobs (`sleep 10 &`)
- Built-ins:
  - `quit` → exit shell
  - `set VAR=value` → define variable
  - `set` → list all variables
  - `bgprocesses` → list background jobs
- Basic `PATH` support via `set PATH=/dir`

---

## Installation
```bash
git clone https://github.com/your-username/shellex.git
cd shellex
make
