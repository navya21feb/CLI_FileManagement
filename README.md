# File Management CLI
A powerful and feature-rich Command Line Interface (CLI) file management system designed for automating and simplifying file handling tasks in a terminal environment. This project allows users to perform common file operations like creating, deleting, renaming, and viewing files, as well as advanced features like managing file metadata, counting words, and maintaining a history of executed commands.  

## Features:
Basic File Operations:  
-Create: Create new files with a check to prevent overwriting existing files.  
-Delete: Remove files from the system.  
-Rename: Rename files with a single command.  
-Move: Move files to a different directory.  
-Copy: Duplicate files to a specified location.  

Advanced Operations:  
-Search Files: Search for files using filters (e.g., by extension or name pattern).  
-View Metadata: Display metadata such as file size, permissions, and modification time.  
-Show Creation Date: View the creation date of files.  
-Count Words: Count the number of words in a file's content.  
-View Content: Display the content of a file in the terminal.  

Command History:  
-Logs all executed commands to a history file (command_history.txt) for future reference.  

Error Handling:  
-Prevents overwriting files by checking if a file already exists.  
-Provides descriptive error messages for invalid or failed operations.  

## Technologies Used:
-Programming Language: C  
-Environment: Linux-based terminal (compatible with Ubuntu and other Unix-like systems)  
-Libraries:  
<stdio.h>: Standard I/O operations  
<stdlib.h>: Memory allocation and process control  
<string.h>: String handling  
<sys/stat.h>: File metadata operations  
<time.h>: Date and time manipulation  
