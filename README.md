## OOP PowerPoint project

To run: 
1) with file, `./PowerPointProject -path <path>`
2) without file, `./PowerPointProject`

[  ] - optionals indicated

## Add
#### Shape:
```
add -name <shape> -pos <position> -w <width> -h <height> [-text <text> -lcolor <hex color> -fcolor <hex color> -lstyle <style> -lwidth <width>]
```
Line is an exception: 
```
 add -name line -pos <x, y>
```
#### Slide:
```
add -slide
```

## Remove
#### Shape:
```
remove -id <id>
```
#### Slide:
```
remove -slide
```
## Change attribute or geometry of item
```
change -id <id> <any operands to be changed>
```

## Slide navigation
```
next      
```
```
prev      
```
## Save
```
save -path <path> -filename <name>
```
## Load
```
load -path <path>
```
## Display to console
```
display [-id <id>]
```
## Draw to image
```
draw -path <path>
```
## List item IDs
```
list
```
## Undo/Redo
```
undo
```

```
redo
```

## Exit
```
exit [-force]
```
