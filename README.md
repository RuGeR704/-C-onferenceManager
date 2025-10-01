# (C)onference Manager
A C-based system for managing conference scheduling, developed as part of a university exam at the University of Salerno (UNISA).
The project allows organizers to add, edit, and remove events (workshops, keynotes, and discussion panels) and to display an agenda sorted by date and time.

The software leverages Abstract Data Types (ADTs) to keep events organized and manage event queues, and it provides a simple command-line interface for user interaction.

# 📖 Description
The Conference Event Manager is a C-based system designed to support the organization of academic and professional conferences.
Developed as part of a university exam based on Data Structures, the project provides a practical solution for handling event scheduling in a structured way.

The program allows organizers to:

- Add, edit, and remove events such as workshops, keynotes, and discussion panels.

- Display the full conference agenda, sorted by date and time.

- Leverage Abstract Data Types (ADTs) to maintain events in an ordered structure and manage queues of sessions waiting to be assigned to rooms.

- Interact via a command-line interface (CLI) that ensures ease of use and direct control over the schedule.

- This project highlights the use of fundamental data structures and algorithms in C to solve a real-world problem in event management.

# ⚙️ How to use
The program is really simple to use. Follow these steps
1. Clone the repository on your PC
```
git clone https://github.com/your-username/conference-event-manager.git
cd conference-event-manager
```
2. Build the program use the "makefile". Use the command `make` in the bash. If it doesn't work you have to compile every file in the repo with "gcc"
   In the command line type:
   ``` gcc -c data.c
   gcc -c orario.c
   gcc -c evento.c
   gcc -c codaEventi.c
   gcc -c agenda.c
   gcc -c utils.c
   gcc -c main.c
   gcc data.o orario.o evento.o codaEventi.o agenda.o utils.o main.o -o main.exe
   main.exe 
   ```
   (if you want to delete the .o files type in the bash `"del *.o"`)
3. You can run the program and use it :D


