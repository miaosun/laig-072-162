#include "variaveis.h"

// declaracoes para as paredes
float mat1_shininess[] = {128.0};
float mat1_specular[] = {0.3, 0.3, 0.3, 1.0};	/* specular reflection. */
float mat1_diffuse[] =  {0.7, 0.7, 0.7, 1.0};	/* diffuse reflection. */
float mat1_ambient[] =  {0.7, 0.7, 0.7, 1.0};	/* ambient reflection. */


//declaracoes para material da semi-esfera da torre
float mat2_shininess[] = {128.0}; 
float mat2_specular[] = {0.0, 0.1, 1.0, 0.5};	/* specular reflection. */
float mat2_diffuse[] =  {0.0, 0.1, 0.8, 0.5};	/* diffuse reflection. */
float mat2_ambient[] =  {0.0, 0.1, 1.0, 0.5};	/* ambient reflection. */

//declaracoes para material da lampada
float mat3_shininess[] = {32.0}; 
float mat3_specular[] = {0.7, 0.7, 0.7, 1.0};	/* specular reflection. */
float mat3_diffuse[] =  {0.7, 0.7, 0.7, 1.0};	/* diffuse reflection. */
float mat3_ambient[] =  {0.7, 0.7, 0.7, 1.0};	/* ambient reflection. */

//declaracoes para material de parede do hospital
float mat4_shininess[] = {128.0}; 
float mat4_specular[] = {0.6, 0.6, 0.6, 1.0};	/* specular reflection. */
float mat4_diffuse[] =  {0.4, 0.4, 0.4, 1.0};	/* diffuse reflection. */
float mat4_ambient[] =  {0.5, 0.5, 0.5, 1.0};	/* ambient reflection. */

void material1()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat1_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat1_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat1_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat1_ambient);
}

void material2()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat2_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat2_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat2_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat2_ambient);
}

void material3()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat3_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat3_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat3_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat3_ambient);
}

void texturas()
{
	// Texturas a utilizar (ver classe RGBpixmap)
	pixmap.readBMPFile("feup.bmp");
	pixmap.setTexture(1);

	pixmap.readBMPFile("tile.bmp");
	pixmap.setTexture(2);

	pixmap.readBMPFile("clamp.bmp");
	pixmap.setTexture(3);

	pixmap.readBMPFile("mandril.bmp");
	pixmap.setTexture(4);

	pixmap.readBMPFile("GrassTexture.bmp");
	pixmap.setTexture(5);

	pixmap.readBMPFile("wood_texture.bmp");
	pixmap.setTexture(6);

	pixmap.readBMPFile("stone_texture.bmp");
	pixmap.setTexture(7);

	pixmap.readBMPFile("janela_texture.bmp");
	pixmap.setTexture(8);

	pixmap.readBMPFile("torre_base_texture.bmp");
	pixmap.setTexture(9);

	pixmap.readBMPFile("plataform_texture.bmp");
	pixmap.setTexture(10);
	
	pixmap.readBMPFile("roof_texture.bmp");
	pixmap.setTexture(11);

	pixmap.readBMPFile("heliporto_texture.bmp");
	pixmap.setTexture(12);

	pixmap.readBMPFile("cauda_texture.bmp");
	pixmap.setTexture(13);

	pixmap.readBMPFile("base_texture.bmp");
	pixmap.setTexture(14);

	pixmap.readBMPFile("holo_base_texture.bmp");
	pixmap.setTexture(15);

	pixmap.readBMPFile("folha_texture.bmp");
	pixmap.setTexture(16);

	pixmap.readBMPFile("wall_texture.bmp");
	pixmap.setTexture(17);

	pixmap.readBMPFile("floor_texture.bmp");
	pixmap.setTexture(18);
}