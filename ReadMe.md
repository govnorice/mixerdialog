![screenshot.png](screenshot.png)

https://github.com/govnorice/mixerdialog/assets/80642969/83154b88-1a92-456e-8f0e-4b9f0841006c

A simple application to control system volume with fancy visualisation.

# Usage:
Application controls system volume by giving arguments to it through command execution.
****
Possible arguments are:
- Increase volume (0.1 - 1.0)
```bash
mixerdialog increase 0.1
```
- Decrease volume (0.1 - 1.0)
```bash
mixerdialog decrease 0.1
```

## For Wayland tiling compositors users
****
In Wayland, programs can't forcefully change windows' attributes. In this program, GDK_WINDOW_TYPE_HINT_DIALOG is used, but it doesn't give any effect further.

**To fix this, use rules or any other way to disable stacking to your tiled layout for current compositor!**

### Example of setting a special rule with Hyprland:

~/config/hypr/hyprland.conf
```hyprland.conf
windowrule = float, ^(mixerdialog)$
```
