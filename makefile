ALL:
	cl src/main.cpp /EHsc C:/dev/SDL2/lib/x64/SDL2main.lib C:/dev/SDL2/lib/x64/SDL2.lib C:/dev/SDL2/lib/x64/SDL2_image.lib C:/dev/SDL2/lib/x64/SDL2_ttf.lib C:/dev/SDL2/lib/x64/SDL2_mixer.lib -IC:/dev/SDL2/include /Fo.\obj\Snake.obj /Febin/Snake.exe /link/SUBSYSTEM:CONSOLE 
CLEAN:
	del /Q bin\*
	del /Q obj\*