#include "raylib.h"
#include <time.h>

int main()
{
    const int windowHeight = 720;
    const int windowWidth = 1280;
    
    InitWindow(windowWidth, windowHeight, "Testing cat");
    
    Texture2D player_texture = LoadTexture("cat_walkv2.png");
    
    int frameWidth = player_texture.width;
    int frameHeight = player_texture.height;
    int currentFrame = 0;
    int framescounter = 0;
    int framespeed = 8;
    int jump=0;
    
    
    bool sgravity = true;
    
    
    
    Rectangle grass = {-100, windowHeight/2+30, 6000, 90};
    Rectangle destRec = {windowWidth/2, windowHeight/2, frameWidth/4*2, frameHeight*2};
    Rectangle frameRec = {0,0, frameWidth/4, frameHeight};
    
    Vector2 player = {0, 0};
    
    float tmp = player.y;
    float velocity = 10.0f;
    
    Camera2D camera;
    camera.target = player;
    camera.offset = (Vector2) {0,0};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    
    clock_t end = clock() + jump * CLOCKS_PER_SEC/1000.0;
    
    SetTargetFPS(60);
    
    
    while(!WindowShouldClose())
    {
     //vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
     //There is jump
        if(IsKeyPressed(KEY_SPACE))
        {
           if(jump > 0)
		   //nothing
		   else
            jump = 10;
			
            sgravity = false;//disabling gravity for jump time
            velocity = 5;
        }
        if(jump)
        {
           velocity+=jump/5;
           camera.offset.y+=velocity;
           player.y+=velocity; 
           jump--;
        }
        else
            sgravity=true;//if jump end gravity start

        //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        
        if(IsKeyDown(KEY_RIGHT))
        {
           
            if(frameRec.width<0)
                frameRec.width*=-1;
         
            camera.offset.x-=3.0;
            player.x-=3.0;
            framescounter++;
        }
        
        if(IsKeyDown(KEY_LEFT))
        {
          
            if(frameRec.width>0)
                frameRec.width*=-1;
           
            camera.offset.x+=3.0;
            player.x+=3.0;
            framescounter++;
        }
        
        if(IsKeyDown(KEY_UP))
        {
            camera.offset.y+=3.0;
            player.y+=3.0;
            framescounter++;
        }
        
        if(IsKeyDown(KEY_DOWN))
        {
           if(player.y <= -120 + frameHeight*2)
           {
                player.y = -120 + frameHeight*2;
                camera.offset.y = -120 + frameHeight*2;
           }
           else
           {
                camera.offset.y-=3.0;
                player.y-=3.0; 
           }  
            framescounter++;
        }
        
        //gravity
        if(sgravity)
        if(!CheckCollisionPointRec((Vector2){windowWidth/2 + frameWidth/4 - player.x, windowHeight/2 + frameHeight - player.y},grass))
        {
            camera.offset.y-=5.0;
            player.y-=5.0;
        }
   
        if(tmp<player.y)
            tmp = player.y;
        
        //animation
        if(framescounter>=(60/framespeed))
        {
            framescounter = 0;
            currentFrame++;
            
            if(currentFrame > 3) currentFrame = 0;
            
            frameRec.x = (float)currentFrame*(float)player_texture.width/4;
        }
        
        camera.target = player;
        
        BeginDrawing();
            ClearBackground(RAYWHITE);
            
                BeginMode2D(camera);
                
                //buildings
                DrawRectangle(60,(float) windowHeight/2-350, 100, 400, Fade(GREEN, 0.5f));
                DrawRectangle(1000,(float) windowHeight/2-300, 100, 350, Fade(BLUE, 0.3));
               
               //some trash
              //  DrawText(FormatText("Frames = %d,width = %d, height = %d,time = %.2f", framescounter,frameWidth/4,frameHeight, GetFrameTime()*1000),0,30,10,BLUE );
              //  DrawText(FormatText("Player.y = %2.2f camera.offset.y = %2.2f ", tmp, camera.offset.y),0,50,15,RED);
               
                //ground
                DrawRectangleRec(grass, GREEN);
                
                //player
                DrawTexturePro(player_texture, frameRec, destRec, player, 0, WHITE );
                
               
                EndMode2D();
        
            DrawFPS(0,0);
        EndDrawing();
        
    }
    
    UnloadTexture(player_texture);
    CloseWindow();
    
    
    return 0;
}
float max(float x)
{
    
    
}