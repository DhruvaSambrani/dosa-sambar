# Dosa Sambar

The Markdown based, git synced, TUI checklist app with vim keybindings

# How to eat

- `j`: up
- `up arrow`: up
- `k`: down
- `down arrow`: down
- `x`: toggle selection
- `d`: delete active selection
- `i`: add item
- `w`: write file
- `g`: git commit
- `q`: quit

# How to cook

1. Install g++. `sudo apt install g++`
2. Install ncurses. `sudo apt-get install libncurses5-dev libncursesw5-dev`
3. Clone repo
4. Run `g++ dosas.cpp -l ncurses -o dosas`
5. Copy `dosas` to a folder in your `PATH`
6. `dosas` requires a file called `test.md`. Custom filenames as a parameter will be added.

# Best served with

- [GitJournal](https://gitjournal.io/) for mobile, both notes and checklists
- [bat](https://github.com/sharkdp/bat) to display notes
- Your favorite text editor
- A private git repo

# Demo

<video src="dosas_demo.mp4" width=400px height=300px></video>

