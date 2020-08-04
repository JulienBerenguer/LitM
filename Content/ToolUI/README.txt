ToolUI for easy use of keyboard, gamepad and mouse for menu UI.

How to use :
- In Project Settings -> Engine -> User Interface -> Focus, set Render Focus Rule to Never to don't show default focus outline,
- Assign "ToolUIGamemode" to your map,
- Create your widget in map blueprint,
- Use "EnableToolUI" function from "ToolUI_FunctionLibrary" to assign widget reference and it's root canvas panel (must be a variable !),
- Navigation between buttons now works (button must be sorted on widget canvas !).

Example map and example widget available.

Controls :
- Mouse : 
> Mouse movement for navigation
> Left click for validation
- Keyboard :
> Arrows for navigation
> Enter or Space bar for navigation
- Gamepad :
> Left pad or arrows for navigation
> A button for validation