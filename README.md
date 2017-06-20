# TeamProva Game Engine

# Todo

add description for the engine

## Priority
* Optimize rendering
* Sprite
    * Cache
* Sound class
    * Path
    * Play - maybe play through an audio class instead?
    * Pause
    * Pitch
    * Speed
    * Loop
    * Position
* UI
    * GUI class
        * scene pointer
        * focus management
        * draw method
    * Font class
    * Control
        * GUI pointer
        * Focus (click modifies this)
        * update method
        * draw method
    * Image
        * use sprite internally
    * Text
        * Font
        * Background
        * Alignment enum
    * Text Input
        * Extends Text
    * Button
        * Extends Text
        * Activates callback with controller A/Enter/Space/click, only if focused (click focuses first, so it always activates)
    * Input/Option List
        * DPad/WASD/Analog/up/down selects current input
    * Slider
        * Left/Right arrow, mouse
* Input class
    * Controller support
* SaveFile
    * Name
    * Save location?
* Render targets?
* Screen class
    * blend mode?

## Optional/Future functionality
* Console like Otter2D?
    * Autocomplete
    * Ability to pause the update loop
    * Ability to modify entities
        * Drag
        * Delete
        * Clone
    * Ability to save scene setups
        * https://stackoverflow.com/questions/1024648/retrieving-a-c-class-name-programmatically
    * Ability to display hitboxes
    * Get FPS
* Screen class
    * Ability to save the screen as a texture
    * Circles
* Model class
    * Mesh
    * Textures
    * UV Maps
* Quaternions for rotation