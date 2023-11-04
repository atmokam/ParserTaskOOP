## OOP parser task

To run: 
1) with file, `./prog -filename <path>`
2) without file, `./prog`

[] - optionals indicated
```
add -name <shape> -pos <position> -w <width> -h <height> [-lcolor <hex color> -fcolor <hex color>]

add -slide

next

prev

remove -id <id>

remove -slide

change -id <id> <any operands to be changed>

save -path <path> -filename <name>

display [-id <id>]

list

load -path <path>
```

