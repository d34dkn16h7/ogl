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
    physics - (pre-pre-pre alpha level) - Done!
    prefabs - (very basic) - Already done! Need a better reader
    geometry store - Done!
    gui - freshly started - canceled for now
    colliders -> (intersect) - Done!
*/
int main()
{
    Game *myGame = new Game();
    return myGame->Run();
}
