#include "ebentoak.h"

POSIZIOA mousePos;
SDL_Event event;

POSIZIOA getMousePos() { return mousePos;}

int getEvent(void) {
	int ret = 0;
	if(SDL_PollEvent(&event)) {
		/* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
		switch(event.type) {
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {
					case SDLK_LEFT:
						ret = TECLA_LEFT;
						break;
					case SDLK_RIGHT:
						ret = TECLA_RIGHT;
						break;
					case SDLK_DOWN:
						ret = TECLA_DOWN;	
						break;
					default:
						ret = event.key.keysym.sym;
						break;
				}
				break;
			case SDL_QUIT:
					ret = GERTAERA_IRTEN;
					break;
			case SDL_MOUSEBUTTONDOWN:
					switch ( event.button.button ){
						case SDL_BUTTON_LEFT:
							ret = MOUSE_KEY_LEFT;
							break;
						case SDL_BUTTON_RIGHT:
							ret = SAGU_BOTOIA_ESKUMA;
							break;
						default:
							ret = event.button.button;
							break;
					}
					break;
			case SDL_MOUSEMOTION:
					//ALDAGIA OROKOR BATEN EZARRIK ODUGU X ETA Y GERO FUNZTIO BATEKIN IRAKURTZEKO AZKEN EBENTUAREN POSIZIOA
					mousePos.x = (float)event.motion.x;
					mousePos.y = (float)event.motion.y;
					ret = SAGU_MUGIMENDUA;
					break;
			default:
				break;
		}
	}
	return ret;
}