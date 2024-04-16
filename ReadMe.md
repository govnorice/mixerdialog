# Example using:
****
- Increase volume (0.1 - 1.0)
```bash
mixerdialog increase 0.1
```
- Decrease volume (0.1 - 1.0)
```bash
mixerdialog decrease 0.1
```

## Wayland tailing WM warning
****
GTK3 cannot make window float on Wayland using GDK_WINDOW_TYPE_HINT_DIALOG!

**Use floating rules for your wayland WM!**

### Example hypland:

hyprland.conf
```hyprland.conf
windowrule = float, ^(mixerdialog)$
```
