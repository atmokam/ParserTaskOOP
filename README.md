## OOP parser task

To run: 
1) with file, `./prog -filename <path>`
2) without file, `./prog`

[] - optionals indicated
```
add -name <shape> -pos <position> -w <width> -h <height> [-lcolor <hex color> -fcolor <hex color>]

remove -id <id>

change -id <id> <any operands to be changed>

save -path <path> -filename <name>

display

display -id <id>

list
```
```
TODO: add LoadCommand, figure out what it does
      add trim method for trailing whitespaces in file input lines
```
