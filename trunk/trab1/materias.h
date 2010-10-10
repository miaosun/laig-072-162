#define GrassTexture 5
#define wood_texture  6
#define stone_texture 7
#define janela_texture 8
#define torre_base_texture  9
#define plataform_texture 10
#define roof_texture 11
#define heliporto_texture  12
#define cauda_texture 13
#define base_texture 14
#define holo_base_texture  15
#define folha_texture 16

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

//declaracoes para material da cauda do helicoptero
float mat3_shininess[] = {128.0}; 
float mat3_specular[] = {0.6, 0.7, 0.8, 0.8};	/* specular reflection. */
float mat3_diffuse[] =  {0.6, 0.7, 0.8, 0.8};	/* diffuse reflection. */
float mat3_ambient[] =  {0.6, 0.7, 0.8, 0.8};	/* ambient reflection. */

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

