# TTE
A terminal text editor, designed for people who want gedit/notepad from the CLI!!

Very much WIP, hope to fix that

Idea is to use ncurses to draw the terminal screen, a 2D linked list buffer to store the text while it is being edited (this might go horribly in larger files...)
and a file read operation to initalize the buffer

also hope to implement a "string buffer" to reduce the amount of linked list searching
