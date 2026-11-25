//repositorio de git= https://github.com/lopez1409/TP3_Info_BMI

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>
#include <time.h>

char *extraer_dato_json(char c,char *cadena_json,char *elem_Copiar);
char *responder(char *text,char *usuario);

struct memory {
  char *response;
  size_t size;
};

static size_t cb(char *data, size_t size, size_t nmemb, void *clientp){
  size_t realsize = size * nmemb;
  struct memory *mem = clientp;

  char *ptr = realloc(mem->response, mem->size + realsize + 1);
  if(!ptr)
    return 0;  /* out of memory */

  mem->response = ptr;
  memcpy(&(mem->response[mem->size]), data, realsize);
  mem->size += realsize;
  mem->response[mem->size] = 0;

  return realsize;
}

int main(void){	
	char api_url[128]={0};
	char api_response[256]={0};
	char api_borrar[128]={0};
	CURLcode res;
	//time_t time;	//para posterior modificacion en el registro
	
	FILE *argv=fopen(".args.txt","r");
	if(argv==NULL){
		printf("-- ERROR -- No se pudo acceder al archivo args");
		return -1;
	}
	char TOKEN[64]={0};
	fgets(TOKEN,64,argv);
	
	fclose(argv);
	
	snprintf(
		api_url,
		sizeof(api_url),
		"https://api.telegram.org/bot%s/getUpdates",
		TOKEN
	);
	
	while(1){
	CURL *curl = curl_easy_init();
	struct memory chunk = {0};
	
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, api_url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

		res = curl_easy_perform(curl);
		if (res != 0){
			printf("Error Codigo: %d\n", res);
			return -1;
		}
		else{
			printf("%s\n", chunk.response);
			char* update_id=extraer_dato_json(',',chunk.response,"\"update_id\":");
			char* id=extraer_dato_json(',',chunk.response,"\"id\":");
			char* text=extraer_dato_json('\"',chunk.response,"\"text\":\"");
			char* nombre_user=extraer_dato_json('\"',chunk.response,"\"last_name\":\"");
			char* date=extraer_dato_json(',',chunk.response,"\"date\":");
			if(update_id!=NULL){
				printf("\nupdate_id: %s\nid: %s\ntext: %s\nlast_name: %s\n",update_id,id,text,nombre_user);
				int update_id_entero=strtol(update_id,NULL,10)+1;
				
				snprintf(
					api_borrar,
					sizeof(api_borrar),
					"https://api.telegram.org/bot%s/getUpdates?offset=%d",
					TOKEN,
					update_id_entero
				);
				
				printf("\n%s\n",api_borrar);
				curl_easy_reset(curl);
				curl_easy_setopt(curl, CURLOPT_URL, api_borrar);
				curl_easy_perform(curl);
				
				char *respuesta=responder(text,nombre_user);
				
				snprintf(
					api_response,
					sizeof(api_response),
					"https://api.telegram.org/bot%s/sendmessage?chat_id=%s&text=%s",
					TOKEN,
					id,
					respuesta				
				);
				
				free(respuesta);
				
				
				curl_easy_reset(curl);
				curl_easy_setopt(curl, CURLOPT_URL, api_response);
				curl_easy_perform(curl);
				
				//guardado de datos
				//time = (time_t)strtoll(date, NULL, 10);//para modificacion de fecha en el registro
				argv=fopen("registro.txt","a");
				if(argv==NULL)
					printf("-- ERROR -- No se puede escribir en el archivo de registro");
				fprintf(argv,"Fecha: %s/Nombre: %s/Mensaje: %s\n\n",date,nombre_user,text);
				fclose(argv);
			}
			free(update_id);
			free(id);
			free(text);
			free(nombre_user);
			free(date);
		}
		
		
		free(chunk.response);
		curl_easy_cleanup(curl);
	}
	sleep(2);
	}
}

char *extraer_dato_json(char c,char *cadena_json,char *elem_Copiar){
	int tam=1;
	int a=strlen(elem_Copiar);
	int b=a;
	char *p=strstr(cadena_json,elem_Copiar);
	if(p==NULL)
		return NULL;
	else{
		while(*(p+a)!=c){
			tam++;
			a++;
		}
		char *q=malloc(sizeof(char)*tam);
		strncpy(q,p+b,(size_t)(tam-1));
		q[tam-1]='\0';
		return q;
	}
}
	
char *responder(char *text,char *usuario){
	char *respuesta=malloc(sizeof(char)*128);
	if(strcmp(text,"HOLA")==0||strcmp(text,"Hola")==0||strcmp(text,"hola")==0){
		snprintf(
			respuesta,
			sizeof(char)*128,
			"Hola%%20%s%%21%%2C%%20como%%20andas%%3F",
			usuario
		);
	}
	else if(strcmp(text,"Chau")==0||strcmp(text,"CHAU")==0||strcmp(text,"chau")==0){
		snprintf(
			respuesta,
			sizeof(char)*128,
			"Hasta%%20luego%%20%s%%2C%%20que%%20te%%20vaya%%20bien",
			usuario
		);
	}else{
		snprintf(
			respuesta,
			sizeof(char)*128,
			"No%%20se%%20como%%20responder%%20a%%20tu%%20peticion"
		);
	}
	return respuesta;
}
