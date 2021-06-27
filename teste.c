#include <stdio.h>
#include <stdlib.h>

/*Testando a integração com o mpv.*/
int main(){

	int opcao=-1;


	do{

	printf("1 - Tocar Musica Atual\n");
	printf("2 - Proxima Musica\n");
	printf("0 - Sair\n");
	scanf("%d", &opcao);	
		switch(opcao){
	
			case 1:
				//mpv 2pac.mp3 --no-audio-display --no-resume-playback --no-terminal --input-ipc-server=/tmp/mpvsocket &
				// para pausar: echo '{ "command": ["set_property", "pause", true] }' | socat - /tmp/mpvsocket
				//para voltar o play: echo '{ "command": ["set_property", "pause", false] }' | socat - /tmp/mpvsocket
				//matar processo: pkill mpv
				system("mpv 2pac.mp3 --no-audio-display --no-resume-playback --no-terminal &");
				break;
			case 2:
				system("pkill mpv");
				system("echo tocando proxima");
				break;

		}
	}while(opcao != 0);
	return(0);

}
