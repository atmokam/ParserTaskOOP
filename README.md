## OOP parser task

To run: 
1) with file, `./prog -filename <path>`
2) without file, `./prog`

[] - optionals indicated
```
add -name <shape> -pos <position> -w <width> -h <height> [-lcolor <hex color> -fcolor <hex color> -lstyle <style> -lwidth <width>]

add -slide

next      // goes to next slide

prev      // goes to previous slide

remove -id <id>

remove -slide

change -id <id> <any operands to be changed>

save -path <path> -filename <name>

display [-id <id>]

list

load -path <path>
```
```
Don't know whether I should put View (a data object used to track the current slide and maintain a pointer to it) inside Data?

Also should it have the display commands? I think those are redundant.

```
