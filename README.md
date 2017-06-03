# TeamProva Game Engine

# Todo

add description for the engine

## Priority
* Optimize rendering
* Sprite
    * Cache
* Collider class
* Camera class
    * Vector2 camera follow
        * Update with the update method of an entity to follow an entity
    * float cameraGrip
        * When equal to 1 it will be following 1:1 with the follow position
        * lower values cause the camera to have a smooth delay
* Sound class
    * Path
    * Play - maybe play through an audio class instead?
    * Pause
    * Pitch
    * Speed
    * Loop
    * Position
* UI
    * Font class
    * Button
    * Text
* Controller support
* Shader class
    * Set VAO?

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
    * Lines
    * Rects
    * Circles
    * Fill
* Model class
    * Mesh
    * Textures
    * UV Maps
* Camera
    * 3D options
* Quaternions for rotation