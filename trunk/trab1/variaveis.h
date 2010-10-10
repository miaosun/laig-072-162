
const int TRUE  = 1;
const int FALSE = 0;

//texturas
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
#define wall_texture 17
#define hangar_texture 18

//declaracoes das camaras
int camera_select;
int camara3_x, camara3_y, camara3_z, camara3_ox, camara3_oy, camara3_oz;

// declaracoes de luz
#define LIGHT0_ID 100
#define LIGHT1_ID 101
#define LIGHT2_ID 102
#define LIGHT3_ID 103
#define LIGHT4_ID 104
int light0_enabled;
int light1_enabled;
int light2_enabled;
int light3_enabled;
int light4_enabled;

//declaracoes para holofotes
float holofote_ambient[] =   {0.0, 0.0, 0.0, 1.0}; // sem componente ambiente
float holofote_diffuse[] =   {6.0, 6.0, 6.0, 1.0};
float holofote_specular[] =  {6.0, 6.0, 6.0, 1.0};
float holofote_kc = 0.0;
float holofote_kl = 0.1;
float holofote_kq = 0.0;
float ang=30.0;


// declaraces para a fonte de luz LIGHT0;
float light0_position[]  = {0.0, 3.0, 4.0, 1.0}; // nao necessaria...
float light0_ambient[] =   {0.0, 0.0, 0.0, 1.0}; // sem componente ambiente
float light0_diffuse[] =   {6.0, 6.0, 6.0, 1.0};
float light0_specular[] =  {6.0, 6.0, 6.0, 1.0};
float light0_kc = 0.0;
float light0_kl = 0.0;
float light0_kq = 0.0;
float light0_direction[] = {0.0, -1.0, -1.0, 1.0};
double light0x = 450.0;
double light0y = 150.0;
double light0z = 150.0;
double symb_light0_radius = 0.2;


int symb_light0_slices = 8;
int symb_light0_stacks = 8;

// fonte (global) de luz ambiente 
float light_ambient[] = {0.6, 0.6, 0.6, 1.0}; /* Set the background ambient lighting. */// era 0.6 nos primeiros 3

double poste_r = 3.0/2.0;
double poste_altura = 47.0;
double baseInf_r = 13.0/2.0;
double baseSup_r = 7.0/2.0;
double base_altura = 7.0;



// declarações para animacao
unsigned int mili_secs = 10;
double obj_rotate, move_x, move_y, move_z, delta_rotate, delta_rot_2, delta_r, angle, y_axis, x_axis, z_axis, heli_rot;
#define RADIUS_SPEED  0.4  // unidades de comprimento por segundo
#define ANGULAR_SPEED 0.5  // rotacoes por segundo
int heli_anim, anim_1;
bool sobe, esquerda, tras, aterra;
#define HELI_ID 150 
#define ANIM_ID 151

//variaveis para o chao
double dimx1 = 150.0;
double dimx2 = 300.0;
double dimx3 = 450.0;
double dimy  =-300.0;

//variaveis para o heliporto
double heliporto_x1 = 45.0/2.0;
double heliporto_x2 = heliporto_x1+105.0;
double heliporto_y1 = -75.0/2.0;
double heliporto_y2 = heliporto_y1-75.0;

//variaveis para helicoptero
double base1_r = 3.0/2.0;
double base2_r = 2.0/2.0;
double base1_lth = 24.0;
double base2_lth = 7.0;
int nslices = 23;
int nstacks = 10;

double cauda_r1 = 5.0;
double cauda_r2 = 3.0;
double cauda_length = 30;

double alpha = 15.0;
double belta = 25.0;
double distancia = -13;

double corpo_r = 12.0;

double folha_temp = 6.0;

double torre_r = 25.0/2.0;
double torre_altura = 95.0;
double plataforma_r = 90.0/2.0;
double plataforma_altura = 7.0;

const char *TITULO_JANELA = { "LAIG_T2_G06 - Gaspar & Miao" };
// dimensoes e localizacao da janela
#define DIMX 800
#define DIMY 700
#define INITIALPOS_X 200
#define INITIALPOS_Y 200

float xy_aspect;

// matriz de transf. geometrica utilizada pelo botao esferico
float view_rotate[16] = { 1,0,0,0,
                          0,1,0,0,
                          0,0,1,0,
                          0,0,0,1 };

// vector de posicao utilizado pelo botao de afastamento
float obj_pos[] = { 0.0, 0.0, 0.0 };

// declaraces para os tres eixos (cilindros)
double axis_radius_begin =  0.2;
double axis_radius_end   =  0.0;
double axis_lenght       = 16.0;
int axis_nslices = 8;
int axis_nstacks = 1;

// variaveis para a janela
int main_window;
GLUI  *glui2;


RGBpixmap pixmap;
