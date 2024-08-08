#include <citro2d.h>

#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

int main(int argc, char* argv[]) {
    // Init various things
	romfsInit();
    gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
    // Don't do that
	// consoleInit(GFX_BOTTOM, NULL);
    
    // Create a C3D render target
    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
    
    // Load the bird
	C2D_SpriteSheet sheet = C2D_SpriteSheetLoad("romfs:/gfx/Bird-128.t3x");	
	C2D_Image bird = C2D_SpriteSheetGetImage(sheet, 0);
    
    while (aptMainLoop()) {
        hidScanInput();

		// Respond to user input
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu
        
        // Render the scene
        C2D_TargetClear(top, C2D_Color32(0x00, 0x00, 0x00, 0xff));
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_SceneBegin(top);
        
        // Draw the Bird
        C2D_DrawImageAt(bird, 136, 56, 0, NULL, 1, 1);
        
        
        C3D_FrameEnd(0);
        
        // Render the scene
        C2D_TargetClear(bottom, C2D_Color32(0x00, 0x00, 0x00, 0xff));
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_SceneBegin(bottom);
        
        // Draw the Bird
        C2D_DrawImageAt(bird, 96, 60, 0, NULL, 1, 1);
        
        
        C3D_FrameEnd(0);
    };
    
    // Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}