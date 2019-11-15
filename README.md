# directories

Write a program that will gather various information about a directory, specifically:
- List all the files in the directory
- Specify which files are directories (if any)
- Show the total size of all the regular files the directory
  - Note that you do not have to recursively go through any subdirectories to find their size for this part (unless you want to, but that is not a simple task)
- Have the program scan the current directory
- Possible enhancements:
  - Recursively list the files in any subdirectories, update the total to include the total size of subdirectories
  - Print out the size in a more readable format (like using KB, MB, GB for -byte prefixes)
  - Make it look more like $ ls -l
