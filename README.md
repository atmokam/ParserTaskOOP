## OOP parser task

I've added things in the new commit and it's still unfinished, so please check out this commit for the working version of the project. Thank you.
https://github.com/atmokam/ParserTaskOOP/commit/a52e5b9da49ad2bf861eabaa111f5761d73caaca

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

exit
```
