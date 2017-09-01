#include <SDL.h>
#include <stdio.h>
#include <SDL_rwops.h>
#include <stdbool.h>

const char lol[]="MADE BY ROOT xd";

int main( int argc, char* args[] )
{
bool isvalid=false;
	SDL_RWops* sourcetex=SDL_RWFromFile("GROUND.TEX","r");
	SDL_RWops* destbmp=SDL_RWFromFile("GROUND.BMP","w");
	if (SDL_RWsize(sourcetex) > 1056) {
		isvalid=true; //if true convert the file!
	}
	if (isvalid == true) {
		SDL_RWseek(sourcetex,20,RW_SEEK_SET);
		unsigned short width=SDL_ReadLE16(sourcetex);
		SDL_RWseek(sourcetex,24,RW_SEEK_SET);
		unsigned short height=SDL_ReadLE16(sourcetex);
		//BMP stuff
		SDL_WriteU8(destbmp,66); //b
		SDL_WriteU8(destbmp,77); //hehe bm xd lol
		SDL_WriteLE32(destbmp,14 + 40 + (4*256) + (width*height)); //size
		SDL_WriteLE32(destbmp,0); //idk
		SDL_WriteLE32(destbmp,14 + 40 + (4*256)); //offset from beginning to pixel data
		SDL_WriteLE32(destbmp,40); //header size (wat)
		SDL_WriteLE32(destbmp,width);
		SDL_WriteLE32(destbmp,height);
		SDL_WriteLE16(destbmp,1); //color planes
		SDL_WriteLE16(destbmp,8); //bits per pixel
		SDL_WriteLE32(destbmp,0); //compression type (lol)
		SDL_WriteLE32(destbmp,width*height);
		SDL_WriteLE32(destbmp,1); //x pixels per meter? what the fuck?
		SDL_WriteLE32(destbmp,1); //y too..what is this for?!
		SDL_WriteLE32(destbmp,255); //number of colors
		SDL_WriteLE32(destbmp,255); //number of important colors?
		SDL_RWseek(sourcetex,32,RW_SEEK_SET);
		//read palette
		unsigned short r,g,b,a;
		unsigned long i;
		i=0;
		while (i < 256) {
			r=SDL_ReadU8(sourcetex);
			g=SDL_ReadU8(sourcetex);
			b=SDL_ReadU8(sourcetex);
			a=SDL_ReadU8(sourcetex);
			SDL_WriteU8(destbmp,b);
			SDL_WriteU8(destbmp,g);
			SDL_WriteU8(destbmp,r);
			SDL_WriteU8(destbmp,a);
			i++;
		}
//now for the pixels themselves! in other words WRITE WHATS IN THE TEX FILE TO THE BMP! :D (bmp reads the data backwards though so the texture will be flipped)
		i=0;
		while (i < (width*height)) {
			SDL_WriteU8(destbmp,SDL_ReadU8(sourcetex));
			i++;
		}
	} //end of isvalid (this is only incase you don't have GROUND.TEX in the folder for..some reason!

	SDL_RWclose(sourcetex);
	SDL_RWclose(destbmp);
return 0;
}