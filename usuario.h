
#ifndef USUARIO_H_
#define USUARIO_H_

typedef struct
{
	char * username;
	char * password;
}
Usuario;

void guardarUsuario(Usuario u);

int comprobarUsername(Usuario u);

void print(Usuario u);

#endif
