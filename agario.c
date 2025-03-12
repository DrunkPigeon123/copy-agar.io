#include "raylib.h"
#include "math.h"

#define ScreenHeight 800
#define ScreenWidht 600
#define maxGummies 50
#define playerSpeed 0.04f

bool Eat(Vector2 playerPos, Vector2 gummie,int* playerSize)
{
    if(fabs(playerPos.x-gummie.x)<*playerSize && fabs(playerPos.y-gummie.y)<*playerSize){return true;}
    return false;
}

void camera(Vector2 playerPos, Vector2 gummie,Vector2* cplayerPos,Vector2* cgummie)
{
 cplayerPos->x = ScreenWidht/2; 
 cplayerPos->y = ScreenHeight/2;
 cgummie->x =  gummie.x - playerPos.x  + ScreenWidht/2;
 cgummie->y = gummie.y - playerPos.y   + ScreenHeight/2;
}

void projection(Vector2* playerPos, Vector2 gummies[],int* playerSize)
{
    Vector2 cplayerPos;
    Vector2 cgummie;
    for(int i=0;i<maxGummies;i++)
    {
        if(IsKeyDown(KEY_W)){playerPos->y -= playerSpeed;}
        if(IsKeyDown(KEY_S)){playerPos->y += playerSpeed;}
        if(IsKeyDown(KEY_A)){playerPos->x -= playerSpeed;}
        if(IsKeyDown(KEY_D)){playerPos->x += playerSpeed;}
        camera(*playerPos,gummies[i],&cplayerPos,&cgummie);
        DrawCircle(cgummie.x,cgummie.y,10,RED);
        if(Eat(*playerPos,gummies[i],playerSize)){gummies[i].x=GetRandomValue(0,3000);gummies[i].y=GetRandomValue(0,1000);*playerSize+=2;}
        
    }
    DrawCircle(cplayerPos.x,cplayerPos.y,*playerSize,BLUE);
    
}

int main()
{
    InitWindow(ScreenWidht,ScreenHeight,"Diep.io");
    SetTargetFPS(60);
    Vector2 playerPos = {ScreenWidht/2,ScreenHeight/2};
    Vector2 gummies[maxGummies] = {0};
    int playerSize = 30;
    for(int i=0;i<maxGummies;i++)
    {
        gummies[i].x= GetRandomValue(0,ScreenWidht);
        gummies[i].y= GetRandomValue(0,ScreenHeight);
    }
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        projection(&playerPos,gummies,&playerSize);
        EndDrawing();
    }
    return 0;
}