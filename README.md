# Planck MTGAP layout

This is a variant [MTGAP](https://mathematicalmulticore.wordpress.com/) layout
for the Planck 4x12 ortho keyboard, restructured as a 2x(3x5+2) split layout.
That is, each hand has 3x5 keys for the fingers and two for the thumbs.

The layout has 4 layers, controlled by `MO(1)` and `MO(2)` keys, which when held
switch to layers 1 and 2, respectively, and layer 3 when both are held.

![Rendering of keymap layers](https://github.com/instinctive/qmk-planck/blob/main/doc/instinctive.png?raw=true)

## Building

    $ cd /path/to/qmk_firmware/keyboards/planck/keymaps
    $ git clone <this repository> instinctive
    $ cd /path/to/qmk_firmware/.build
    $ qmk config user.keyboard=planck/rev6_drop
    $ qmk config user.keymap=instinctive
    $ qmk compile
    $ qmk flash planck_rev6_drop_instinctive.bin

## Credits

The one-shot modifiers are taken directly from [users/callum](
https://github.com/qmk/qmk_firmware/tree/999008f0eb8204f2d6d99113ae45aad2337dcf28/users/callum).
