## OOP PowerPoint project

To run: 
1) with file, `./PowerPointProject -path <path>`
2) without file, `./PowerPointProject`

[  ] - optionals indicated

## Add
#### Shape

Available shapes : trapezoid, line, rectangle, ellipse, triangle

```
add -name <shape> -pos <(x, y)> -w <width> -h <height> 
[-text <text> -lcolor <hex color> -fcolor <hex color> -lstyle <style> -lwidth <width>]
```
**Line's signature is an exception:*
```
 add -name line -pos <(x, y) (x, y)> [...]
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
