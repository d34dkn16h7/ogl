#include "game.h"

/*
Global Lists:
    Renderer -> drawList (geo)
    Geometry -> pointer to main data (geo)
    Collider -> colliders (colliders with gmo owners)
    Map      -> data (gmo)
*/
/*
To Do:
    physics
    prefabs
    geometry store
    gui
    colliders -> (intersect)
*/

int main()
{
    Game *myGame = new Game();
    return myGame->Run();
}
