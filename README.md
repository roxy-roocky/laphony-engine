# LaphonyEngine
The Laphony engine is a 2D game engine coded in C++, which use the library SDL2.

---------
 
# TODO
## BasicPhysic
- [x] Collider (box)
- [x] Static bodies
- [x] Dynamics bodies
- [x] Make bodies virtual pure (must override identifier string method for others can know what type of object is)
- [x] Physic engine
- [x] Raycast

## Events
- [x] Named controls
- [x] Keyboard events
- [x] Joystick support
    - [x] Buttons
    - [x] Hats
    - [x] Axis
- [x] Auto detect joystick system
- [x] Mouse position getter
- [x] Mouse button control
- [ ] Rumble gamepad
- [ ] Controls map system with save file

## Frames
- [x] Update engine
- [x] Pause system for `Updatable` objects
- [x] Update engine in other thread

## Graphics
- [x] Put pivot in Image
- [x] Class for wrap `SDL_Surface` and `SDL_Texture` structures
- [x] Class represents an simple image
- [x] Frames Animation
- [x] Animator
- [x] Graphic engine which wrap `SDL_Window` and `SDL_Renderer` structures
- [ ] TTF text support 

## Sound
- [ ] Named sounds and musics
- [ ] Sound engine (DJ system)
- [ ] Actions - Musics sync

## Game
- [ ] Storage objects system
- [ ] Sprite
- [ ] Tileset system
- [ ] Map

## Engine UI
- [ ] Base UI system
- [ ] Tileset editor
- [ ] Map editor
- [ ] Object creator


