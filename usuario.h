
#ifndef USUARIO_H_
#define USUARIO_H_

#ifdef __cplusplus
extern "C"{
#endif

typedef struct
{
	char * username;
	char * password;
}
Usuario;

int checkFileExistance();

int comprobarUserPass(Usuario u1);

void guardarUsuario(Usuario u);

int comprobarUsername(Usuario u);

void print(Usuario u);

#ifdef __cplusplus
}
#endif

#endif
