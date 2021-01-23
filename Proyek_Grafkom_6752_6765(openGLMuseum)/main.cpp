#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

#include <windows.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glut.h"
#include <vector>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <stdlib.h>

/* Windows globals, defines, and prototypes */
CHAR szAppName[]="Proyek Grafkom - Military Museum";
HWND  ghWnd;
HDC   ghDC;
HGLRC ghRC;

#define SWAPBUFFERS SwapBuffers(ghDC)
#define WIDTH           1000
#define HEIGHT          768

using namespace std;

struct Objek{
	vector< vector<float> > vektor;
	vector< vector<float> > vektorNormal;
	vector< vector<int> > faces;
};

vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;
    while (getline (ss, item, delim)) {
        result.push_back (item);
    }
    return result;
}

vector<string> splitstring (string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;
    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }
    res.push_back (s.substr (pos_start));
    return res;
}

float a = 0;
float b = 0;
float c = 0;
float ctrpropeller = 0;
float vr1rot, vr2rot, vr3rot, vr4rot, vr5rot, vr6rot, propeller;
float posx,posy,posz, posxasli, posx2, posy2, posz2, posxasli2;
float liftA = 0;
float liftB = 70;

double yangle, xzangle;

bool onheli = false;
bool blift = false;
bool flagz= false;
bool lamp1 = true;
bool lamp2 = true;
bool lamp3 = true;
bool lamp4 = true;
bool lamp5 = true;
bool lamp6 = true;
bool lamp7 = true;


int vr = 0;
int vrsenjata = 0;
int flaglift = 0;
int w, h;
int flag;

char ch='1';

unsigned char texturedata[20][512*512*3];

GLuint wall, floortex, ceiltex, sword, green, picture, tank, pesawat,
       kapal, besi, heli, nakel, cor, mir, cen, blue, grey, helicopter, misil, mirage;
GLuint vr1, vr2, vr3, vr4, vr5, vr6;

GLfloat posisiBenda[19][3] = { {186.2,30,220},{130,-30,265},
                                {130,102,157},{130,70,140},
                                {11,50,100},{35,50,389},{188,70,520},
                                {75,80,120},{130,80,195},
                                {42,0,320},
                                {50,0,520},
                                {130,48,75},{-88,50,280},
                                {30,155,520},{115,155,180},{-75,145,120},
                                //pintu 1 & 2
                                {30,5,-1}, {30,155,-1},{-75,210,130}
                            };

GLfloat angle, eyex, eyey, eyez, lookatx, lookaty, lookatz;
GLfloat eyex1, eyey1, eyez1;
GLfloat red[]   = { 1,0,0,1 };
GLfloat white[] = { 1,1,1,1 };
GLfloat lampx,lampy,lampz;
GLfloat pos2[] = { 200,250,-10, 1 };
GLfloat pos3[] = { 0,320,50, 1 };
GLfloat pos4[] = { 300,320,50, 1 };
GLfloat pos5[] = { 300,380,280, 1 };
GLfloat pos6[] = { 0,380,0, 1 };
GLfloat pos7[] = { -100,380,600, 1 };
GLfloat pos8[] = { 300,380,600, 1 };

Objek object[20];

struct POINT3D { double x,y,z;};
struct TRIANGLE { int p1,p2,p3; };

POINT p;
POINT pos;

LONG WINAPI MainWndProc (HWND, UINT, WPARAM, LPARAM);
BOOL bSetupPixelFormat(HDC);

/* OpenGL globals, defines, and prototypes */
GLfloat latitude, longitude, latinc, longinc;
GLdouble radius;

#define GLOBE    1
#define CYLINDER 2
#define CONE     3

void DrawScene();
void doorPosition();
void lightPosition();
void SetupScene();
void loadObj(string filename, int index);
void UpdateScene();
void genlist();
void lift(float b);
void drawObjek();
void resize( int width, int height );
void MouseMove(HWND h);
void Up();
void Down();
void loadObj2(char *fname, int index);

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG        msg;
    WNDCLASS   wndclass;

    /* Register the frame class */
    wndclass.style         = 0;
    wndclass.lpfnWndProc   = (WNDPROC)MainWndProc;
    wndclass.cbClsExtra    = 0;
    wndclass.cbWndExtra    = 0;
    wndclass.hInstance     = hInstance;
    wndclass.hIcon         = LoadIcon (hInstance, szAppName);
    wndclass.hCursor       = LoadCursor (NULL,IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wndclass.lpszMenuName  = szAppName;
    wndclass.lpszClassName = szAppName;

    if (!RegisterClass (&wndclass) )
        return FALSE;

    /* Create the frame */
    ghWnd = CreateWindow (szAppName,
             "Proyek Grafkom - Military Museum",
         WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
             CW_USEDEFAULT,
             CW_USEDEFAULT,
             WIDTH,
             HEIGHT,
             NULL,
             NULL,
             hInstance,
             NULL);

    /* make sure window was created */
    if (!ghWnd)
        return FALSE;

    /* show and update main window */
    ShowWindow (ghWnd, nCmdShow);

    UpdateWindow (ghWnd);
    string namaobj[19] = {"object/tanggaatas.obj","object/tanggabawah.obj",
                        "object/misil.obj","object/kotak.obj",
                        "object/pigura.obj","object/pigura.obj","object/pigura.obj",
                        "object/fence.obj","object/fence.obj",
                        "object/diorama.obj",
                        "object/diorama.obj",
                        "object/tank.obj","object/pigura.obj",
                        "object/corsair.obj","object/dassault.obj","object/helicopter.obj",
                        "object/pintu.obj","object/pintu.obj","object/baling.obj"
                     };
    for(int i = 0; i < 19; i++)
    {
        loadObj(namaobj[i],i);
    }
    //menginisialisasi verteks objek ke dalam list
    genlist();
    loadObj2("object/heli.obj",0);
    loadObj2("object/grumman.obj",1);
    loadObj2("object/tilotor.obj",2);
    loadObj2("object/cruiser.obj",3);
    loadObj2("object/battleship.obj",4);
    loadObj2("object/sub.obj",5);

    //menginisialisai posisi pintu sehingga bisa otomatis
    doorPosition();
    lightPosition();
    /* animation loop */
    while (1) {
        /*
         *  Process all pending messages
         */

        while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) == TRUE)
        {
            if (GetMessage(&msg, NULL, 0, 0) )
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            } else {
                return TRUE;
            }
        }
        DrawScene();
    }

}

/* main window procedure */
RECT rect, wrect;
POINT oldpos;

LONG WINAPI MainWndProc (
    HWND    hWnd,
    UINT    uMsg,
    WPARAM  wParam,
    LPARAM  lParam)
{
    LONG    lRet = 1;
    PAINTSTRUCT    ps;

    switch (uMsg) {

    case WM_CREATE:
        ghDC = GetDC(hWnd);
        if (!bSetupPixelFormat(ghDC))
            PostQuitMessage (0);
        ghRC = wglCreateContext(ghDC);
        wglMakeCurrent(ghDC, ghRC);
		GetWindowRect(hWnd, &wrect);
		SetupScene();
        break;

    case WM_PAINT:
        BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;

     case WM_CLOSE:
        if (ghRC)
            wglDeleteContext(ghRC);
        if (ghDC)
            ReleaseDC(hWnd, ghDC);
        ghRC = 0;
        ghDC = 0;

        DestroyWindow (hWnd);
        break;

    case WM_DESTROY:
        if (ghRC)
            wglDeleteContext(ghRC);
        if (ghDC)
            ReleaseDC(hWnd, ghDC);

        PostQuitMessage (0);
        break;

    case WM_SIZE:
        GetClientRect(hWnd, &rect);
        resize(rect.right, rect.bottom);
        GetWindowRect(hWnd, &wrect);
        break;

    case WM_KEYDOWN:
        switch (wParam) {
        case VK_ESCAPE:
			exit(0);
            break;
        case VK_UP:
			Up();
            break;
        case VK_RIGHT:
            if(vr == 0){
                vr = 1;
            }else if(vr == 1){
                vr = 2;
            }else{
                vr = 0;
            }
            break;
        case VK_LEFT:
        if(vrsenjata ==0)vrsenjata=1;
        else if( vrsenjata==1) vrsenjata=2;
        else vrsenjata=0;
        break;
        case UINT('W'):
			Up();
            break;
        case UINT('S'):
			Down();
            break;
        case UINT('L'):
			blift = true;
            break;
        case UINT('V'):
            if(!onheli) onheli = true;
            else onheli = false;
            break;
        case UINT('1'):
            if(!lamp1) lamp1 = true;
            else lamp1 = false;
            break;
        case UINT('2'):
            if(!lamp2) lamp2 = true;
            else lamp2 = false;
            break;
        case UINT('3'):
            if(!lamp3) lamp3 = true;
            else lamp3 = false;
            break;
        case UINT('4'):
            if(!lamp4) lamp4 = true;
            else lamp4 = false;
            break;
        case UINT('5'):
            if(!lamp5) lamp5 = true;
            else lamp5 = false;
            break;
        case UINT('6'):
            if(!lamp6) lamp6 = true;
            else lamp6 = false;
            break;
        case UINT('7'):
            if(!lamp7) lamp7 = true;
            else lamp7 = false;
            break;
        }

	case WM_MOUSEMOVE:
		MouseMove(hWnd);
		break;

    default:
        lRet = DefWindowProc (hWnd, uMsg, wParam, lParam);
        break;
    }

    return lRet;
}

BOOL bSetupPixelFormat(HDC hdc)
{
    PIXELFORMATDESCRIPTOR pfd, *ppfd;
    int pixelformat;

    ppfd = &pfd;

    ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR);
    ppfd->nVersion = 1;
    ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
                        PFD_DOUBLEBUFFER;
    ppfd->dwLayerMask = PFD_MAIN_PLANE;
    ppfd->iPixelType = PFD_TYPE_COLORINDEX;
    ppfd->cColorBits = 8;
    ppfd->cDepthBits = 16;
    ppfd->cAccumBits = 0;
    ppfd->cStencilBits = 0;

    pixelformat = ChoosePixelFormat(hdc, ppfd);

    if ( (pixelformat = ChoosePixelFormat(hdc, ppfd)) == 0 )
    {
        MessageBox(NULL, "ChoosePixelFormat failed", "Error", MB_OK);
        return FALSE;
    }

    if (SetPixelFormat(hdc, pixelformat, ppfd) == FALSE)
    {
        MessageBox(NULL, "SetPixelFormat failed", "Error", MB_OK);
        return FALSE;
    }

    return TRUE;
}

void resize( int width, int height )
{
    GLfloat aspect;

    glViewport( 0, 0, width, height );
    aspect = (GLfloat) width / height;
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 5.0, aspect, 3.0, 70.0 );
    glMatrixMode( GL_MODELVIEW );
}

//________________________BAGIAN TEKSTUR DAN OBJEK____________________________________

void loadObj(string filename, int index){
    ifstream inFile;
    string line;
    inFile.open(filename.c_str());
    if (!inFile) {
        cout << "Unable to open file";
    }else{
        while (getline(inFile, line)) {
            char kataPertama = line[0];
            if(kataPertama == 'f'){
                line = line.substr(2);
                vector<string> splitted = split(line, ' ');
                vector<string> pisahPertama = splitstring(splitted[0], "//");
                vector<string> pisahKedua = splitstring(splitted[1], "//");
                vector<string> pisahKetiga = splitstring(splitted[2], "//");
                vector<int> face;
                int temp1, temp2, temp3;
                stringstream(pisahPertama[0]) >> temp1;
                stringstream(pisahPertama[1]) >> temp2;
                face.push_back(temp1);
                face.push_back(temp2);

                stringstream(pisahKedua[0]) >> temp1;
                stringstream(pisahKedua[1]) >> temp2;
                face.push_back(temp1);
                face.push_back(temp2);

                stringstream(pisahKetiga[0]) >> temp1;
                stringstream(pisahKetiga[1]) >> temp2;
                face.push_back(temp1);
                face.push_back(temp2);
                object[index].faces.push_back(face);
                face.clear();
                // f 33//44 44//55 66//77
            }
            else{
                char kataKedua = line[1];
                if(kataKedua == 'n'){
                    line = line.substr(3);
                    vector<float> normal;
                    vector<string> splitted = split(line, ' ');
                    float temp1, temp2, temp3;
                    stringstream(splitted[0]) >> temp1;
                    stringstream(splitted[1]) >> temp2;
                    stringstream(splitted[2]) >> temp3;
                    normal.push_back(temp1);
                    normal.push_back(temp2);
                    normal.push_back(temp3);
                    object[index].vektorNormal.push_back(normal);
                    normal.clear();
                }else if(line.substr(0,2) == "v "){
                    line = line.substr(2);
                    vector<float> vertex;
                    vector<string> splitted = split(line, ' ');
                    float temp1, temp2, temp3;
                    stringstream(splitted[0]) >> temp1;
                    stringstream(splitted[1]) >> temp2;
                    stringstream(splitted[2]) >> temp3;
                    vertex.push_back(temp1);
                    vertex.push_back(temp2);
                    vertex.push_back(temp3);
                    object[index].vektor.push_back(vertex);
                    vertex.clear();
                }
            }
        }
        inFile.close();
    }
}

void drawObjek(){
    float h1=0, h2=0, h3=1, w1=0, w2=1, w3=1;
    for(int k = 0;k < 16; k++){
        glPushMatrix();
        glTranslatef(posisiBenda[k][0], posisiBenda[k][1], posisiBenda[k][2]);
        if(k==0){
            glShadeModel(GL_FLAT);
            glBindTexture(GL_TEXTURE_2D, floortex);
            glScalef(20,20,20);
            glRotatef(-90,0,1,0);
        }
        else if(k==1){
            glShadeModel(GL_FLAT);
            glBindTexture(GL_TEXTURE_2D, floortex);
            glScalef(20,20,20);
            glRotatef(-180,0,1,0);
        }
        else if(k==2){
            glShadeModel(GL_FLAT);
            glBindTexture(GL_TEXTURE_2D, sword);
            glScalef(5,6,5);
            glRotatef(-90,1,0,0);
        }
        else if(k==3){
            glShadeModel(GL_FLAT);
            glBindTexture(GL_TEXTURE_2D, wall);
            glScalef(10,3,10);
        }
        else if(k==4){
            glShadeModel(GL_FLAT);
            glBindTexture(GL_TEXTURE_2D, picture);
            glTranslatef(a,b,c);
            glScalef(5,10,15);
            glRotatef(270,0,1,0);
        }
        else if(k==5){
            glShadeModel(GL_FLAT);
            glBindTexture(GL_TEXTURE_2D, picture);
            glTranslatef(a,b,c);
            glScalef(8,8,5);
            glRotatef(360,0,1,0);
        }
        else if(k==6){
            glShadeModel(GL_FLAT);
            glBindTexture(GL_TEXTURE_2D, picture);
            glTranslatef(a,b,c);
            glScalef(5,15,25);
            glRotatef(90,0,1,0);
        }
        else if(k==7){
            glShadeModel(GL_FLAT);
            glBindTexture(GL_TEXTURE_2D, besi);
            glTranslatef(a,b,c);
            glScalef(5,10,16);
        }
        else if(k==8){
            glShadeModel(GL_FLAT);
            glBindTexture(GL_TEXTURE_2D, besi);
            glTranslatef(a,b,c);
            glScalef(8,10,5);
            glRotatef(90,0,1,0);
        }
        else if(k==9){
            glShadeModel(GL_FLAT);
            glBindTexture(GL_TEXTURE_2D, picture);
            glTranslatef(a,b,c);
            glScalef(17,50,17);
        }
        else if(k==10){
            glShadeModel(GL_FLAT);
            glBindTexture(GL_TEXTURE_2D, picture);
            glTranslatef(a,b,c);
            glScalef(17,50,17);
        }
        else if(k==11){
            glShadeModel(GL_3D_COLOR_TEXTURE);
            glBindTexture(GL_TEXTURE_2D, green);
            glTranslatef(a,b,c);
            glScalef(5,8,5);
        }
        else if(k==12){
            glShadeModel(GL_FLAT);
            glBindTexture(GL_TEXTURE_2D, picture);
            glTranslatef(a,b,c);
            glScalef(5,20,25);
            glRotatef(270,0,1,0);
        }
        else if(k==13){
            glShadeModel(GL_FLAT);
            glBindTexture(GL_TEXTURE_2D, blue);
            glTranslatef(a,b,c);
            glScalef(75,65,75);
            glRotatef(-180,0,1,0);
        }
        else if(k==14){
            glShadeModel(GL_FLAT);
            glBindTexture(GL_TEXTURE_2D, mirage);
            glTranslatef(a,b,c);
            glScalef(60,65,105);
            glRotatef(-90,0,1,0);
        }
        else if(k==15){
            glShadeModel(GL_FLAT);
            glBindTexture(GL_TEXTURE_2D, grey);
            glTranslatef(a,b,c);
            glScalef(20,35,20);
            glRotatef(90,0,1,0);
        }
        for(int i = 0;i < object[k].faces.size();i++){
            glBegin(GL_TRIANGLES);
            glNormal3f(
                object[k].vektorNormal[object[k].faces[i].at(1) - 1].at(0),
                object[k].vektorNormal[object[k].faces[i].at(1) - 1].at(1),
                object[k].vektorNormal[object[k].faces[i].at(1) - 1].at(2)
            );
            glTexCoord2f(w1, h1);
            glVertex3f(
                object[k].vektor[object[k].faces[i].at(0) - 1].at(0),
                object[k].vektor[object[k].faces[i].at(0) - 1].at(1),
                object[k].vektor[object[k].faces[i].at(0) - 1].at(2)
            );

            glNormal3f(
                object[k].vektorNormal[object[k].faces[i].at(3) - 1].at(0),
                object[k].vektorNormal[object[k].faces[i].at(3) - 1].at(1),
                object[k].vektorNormal[object[k].faces[i].at(3) - 1].at(2)
            );
            glTexCoord2f(w2, h2);
            glVertex3f(
                object[k].vektor[object[k].faces[i].at(2) - 1].at(0),
                object[k].vektor[object[k].faces[i].at(2) - 1].at(1),
                object[k].vektor[object[k].faces[i].at(2) - 1].at(2)
            );

            glNormal3f(
                object[k].vektorNormal[object[k].faces[i].at(5) - 1].at(0),
                object[k].vektorNormal[object[k].faces[i].at(5) - 1].at(1),
                object[k].vektorNormal[object[k].faces[i].at(5) - 1].at(2)
            );
            glTexCoord2f(w3, h3);
            glVertex3f(
                object[k].vektor[object[k].faces[i].at(4) - 1].at(0),
                object[k].vektor[object[k].faces[i].at(4) - 1].at(1),
                object[k].vektor[object[k].faces[i].at(4) - 1].at(2)
            );
            glEnd();
        }
        glPopMatrix();
    }
}

void LoadBMP(char *fname, unsigned char *buf, int& w, int& h)
{
	HANDLE handle;
	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER infoheader;
	unsigned long read;
	unsigned long palettelength;
	RGBQUAD palette[256];
	int width, height;
	unsigned long bitmaplength;

	handle=CreateFile(fname, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
	if (handle==INVALID_HANDLE_VALUE) exit(1);

	ReadFile(handle, &fileheader, sizeof(fileheader), &read, 0);
	ReadFile(handle, &infoheader, sizeof(infoheader), &read, 0);

	palettelength = infoheader.biClrUsed;
	ReadFile(handle, palette, palettelength, &read, 0);
	if (read!=palettelength) exit(1);

	width = infoheader.biWidth;
	height = infoheader.biHeight;
	bitmaplength = infoheader.biSizeImage;
	if (bitmaplength==0)
		bitmaplength = width*height*infoheader.biBitCount / 8;

	ReadFile(handle, buf, bitmaplength, &read, 0);
	if (read!=bitmaplength) exit(1);

	CloseHandle(handle);

	for(unsigned long i=0;i<bitmaplength;i+=3)
		{
		unsigned char tmp;
		tmp=buf[i];
		buf[i]=buf[i+2];
		buf[i+2]=tmp;
		}

	w=width; h=height;
}

void LoadTexture(char *fn, unsigned char *buf, GLuint& id)
{
	GLuint tex1;
	glEnable(GL_TEXTURE_2D);

	LoadBMP(fn, buf, w, h);
	glGenTextures(1, &tex1);
	id = tex1;
	glBindTexture(GL_TEXTURE_2D, id);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, buf);
}

void SetupTexture()
{
	LoadTexture("texture/wall.bmp", texturedata[0], wall);
	LoadTexture("texture/ceil2.bmp", texturedata[1], ceiltex);
	LoadTexture("texture/floor2.bmp", texturedata[2], floortex);
	LoadTexture("texture/glass.bmp", texturedata[3], sword);
	LoadTexture("texture/green.bmp", texturedata[4], green);
	LoadTexture("texture/brick4.bmp", texturedata[5], picture);
	LoadTexture("texture/tank.bmp", texturedata[6], tank);
	LoadTexture("texture/pesawat.bmp", texturedata[7], pesawat);
	LoadTexture("texture/kapal.bmp", texturedata[8], kapal);
	LoadTexture("texture/besi.bmp", texturedata[9], besi);
	LoadTexture("texture/heli2.bmp", texturedata[10], heli);
	LoadTexture("texture/Nama.bmp", texturedata[11], nakel);
	LoadTexture("texture/corsair.bmp", texturedata[12], cor);
	LoadTexture("texture/mirage.bmp", texturedata[13], mir);
	LoadTexture("texture/cen.bmp", texturedata[14], cen);
	LoadTexture("texture/blue.bmp", texturedata[15], blue);
	LoadTexture("texture/grey.bmp", texturedata[16], grey);
	LoadTexture("texture/bell.bmp", texturedata[17], helicopter);
	LoadTexture("texture/misil.bmp", texturedata[18], misil);
	LoadTexture("texture/ggreen.bmp", texturedata[19], mirage);
}


//____________________________BAGIAN SCENE________________________________________________________________

void SetupScene()
{
	SetupTexture();

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);

	angle=0.0;
	yangle=0;
	xzangle=0;
	eyex=25;
	eyey=25;
	eyez=-30;

	lookatx=1000000.0*cos(xzangle*3.14/180.0);
	lookaty=1000000.0*sin(yangle*3.14/180.0);
	lookatz=1000000.0*sin(xzangle*3.14/180.0);

	flag=0;
	SetCursorPos(	wrect.left+(wrect.right-wrect.left)/2,
					wrect.top+(wrect.bottom-wrect.top)/2);
	flag=1;
}

//verteks kubus
POINT3D vertex[139] = {
    //lorong utama ---0
	{  0,  0,  0},{70,  0,  0},{70,140,  0},{  0,140,  0},
	{  0,  0, 200},{70,  0, 200},{70,140, 200},{  0,140, 200},
	//lorong 2 ---8
	{ -100,  0, 200},{-100,140, 200},{-100,140, 650},{-100,0,650},
	{  200,  0, 200},{200,  140, 200},{200,0, 650},{ 200,140, 650},
	//kusen kamar1 1 ---16
	{10,0,0},{10,140,0},{10,140,-2},{10,0,-2},{0,0,-2},{0,140,-2},
	//kusen kamar1 2 ---22
	{50,0,0},{50,140,0},{70,0,-2},{70,140,-2},{50,0,-2},{50,140,-2},
	//kusen kamar1 3 ---28
	{10,60,0},{50,60,0},{10,60,-2},{50,60,-2},
	//kamar1 ---32
	{  0,  liftA,  -70},{70,  liftA,  -70},{70,liftB,  -70},{  0,liftB,  -70},
	{  0,  liftA,-2},{70,  liftA, -2},{70,liftB, -2},{  0,liftB, -2},
	//dinding ruang bawah lorong 2 ---40
	{70,70,200},{200,70,200},{160,70,200},{160,140,200},
	//dinding ruang atas lorong 2 ---44
	{70,70,0},{200,70,0},{70,140,0},{200,140,0},
	//collide tangga1 ---48
	{130,0,270},{165,40,270},{165,40,230},{130,0,230},{200,40,230},{200,40,270},
	{135,0,270},{165,38,270},{165,32,230},{135,0,230},
	//collide tangga2 ---58
	{170,73,190},{170,40,230},{200,40,230},{200,73,190},
	//collide tank+ sidewinder ---62
	{120,70,35},{120,70,150},{120,140,150},{120,140,35},
	{145,70,35},{145,140,35},{145,70,150},{145,140,150},
	//collide pesawat2 ---70
	{-150,280,420},{-150,140,420},{100,140,420},{100,280,420},{100,280,650},
	{100,140,650},{0,0,-50},
	//collide heli ---77
	{18,0,297},{18,0,341},{18,50,341},{18,50,297},
	{66,50,341},{66,50,297},{66,0,297},{66,0,341},
	//sekat tengah--85
	{-35,0,400},{135,0,400},{-35,140,400},{135,140,400},
	{-35,0,420},{135,0,420},{-35,140,420},{135,140,420},
	//collide vr kapal ---93
	{10,0,487},{10,0,540},{10,50,540},{10,50,487},
	{58,50,540},{58,50,487},{58,0,487},{58,0,540},
	//Collide lantai atas ---101
	{-150,280,0},{-150,140,0},{-150,140,650},{-150,280,650},
	{200,280,0},{200,140,0},{200,140,650},{200,280,650},
//	//collide lift atas ---109
	{0,140,-70},{70,140,-70},{70,209.9,-70},{0,209.9,-70},
	{0,140,-2},{70,140,-2},{70,209.9,-2},{0,209.9,-2},
//	//collide kusen lantai atas ---117
	{-150,210,0},{10,210,0},{50,210,0},{200,210,0},{10,140,0},{50,140,0},

//	//colide pesawat1 ---123
	{200,140,130},{20,140,130},{20,140,300},{200,140,300},{200,280,130},
	{20,280,130},{20,280,300},{200,280,300},
//	//collide heli ---131
	{-45,140,0},{-45,280,0},{-45,140,200},{-45,280,200},{-150,140,200},{-150,280,200},
	//collide tambahan --- 137
	{0,140,0},{0,140,650}
};

TRIANGLE triangle[154] = {
    //lorong utama
	{5,1,2},{2,6,5},
	//{1,0,2},{3,2,0},
	{4,7,3},{3,0,4},
	{7,6,2},{2,3,7},
	{4,0,1},{1,5,4},
	//===============8
	//lorong 2
	{13,9,10},{10,15,13},
	{12,13,14},{14,15,13},
	{10,11,14},{10,15,14},
	{9,10,11},{9,8,11},
	{7,4,8},{7,9,8},
	{12,8,11},{11,14,12},
	{11,4,12},{14,12,11},
	{7,13,10},{10,13,15},
	//===============12
	//kusen kamar 1 (kiri)
	{0,3,16},{16,17,3},
	{18,19,16},{17,18,16},
	{21,20,18},{18,19,21},
	//================6
	//kusen kamar 2 (kanan)
    {23,22,1},{23,2,1},
	{27,22,26},{23,27,22},
	{27,26,24},{27,25,24},
	//================6
	//kusen kamar 3 (atas)
    {17,29,28},{17,23,29},
    {28,31,30},{28,29,31},
    {18,31,30},{18,27,31},
    //================6
    {16,19,26},{16,22,26},
    //================2
    {37,33,34},{34,38,37},
	{33,32,34},{35,34,32},
	{36,39,35},{35,32,36},
	{39,38,34},{34,35,39},
	{36,32,33},{33,37,36},
	//================10
	//dinding ruang bawah lorong 2
	{40,5,12},{40,41,12},{6,40,42},{6,43,42},
	//================4
	//dinding ruang atas lorong 2
	{46,44,45},{46,47,45},
	{47,45,41},{47,13,41},
	{46,6,13},{46,47,13},
	{44,40,41},{44,45,41},
	//================8
	//collide tangga1
	{50,51,48},{50,49,48},
	{50,49,53},{50,52,53},
	{52,53,55},{54,53,55},
	{56,50,51},{56,57,51},
	//================8
	//colide tangga2
	{58,59,60},{58,61,60},
	//collide piala
	{65,62,63},{65,64,63},
	{67,66,62},{67,65,62},
	{66,67,69},{69,68,66},
	{69,68,63},{69,64,63},
	{69,67,65},{69,64,65},
	//================10
	//collide pesawat1
	{127,123,124},{127,128,124},
	{128,124,125},{128,129,125},
	{130,129,125},{130,126,125},
	//=================6
	//collide heli
	{77,80,78},{80,79,78},
	{82,80,83},{83,77,80},
	{82,81,83},{83,84,81},
	{81,79,80},{81,82,80},
	{84,79,78},{84,81,79},
	//=================8
	//colide sekat tengah
	{88,86,85},{88,87,85},
	{87,85,89},{87,92,89},
	{88,86,90},{88,91,90},
	{91,92,89},{91,90,89},
	//=================8
	//collide machine
	{93,94,95},{96,94,95},
	{97,95,94},{97,100,94},
	{97,98,99},{99,100,97},
	{98,96,93},{98,99,93},
	{97,98,96},{97,95,96},
	//=================10
	//collide lantai atas
    {101,102,103},{103,104,101},
    {104,103,107},{104,108,107},
    {105,106,107},{105,108,107},
    {101,105,108},{101,108,104},
    {137,102,103},{137,138,103},
//    {106,102,103},{106,107,103},
//	//==================12
//	//collide kusen lantai atas
	{101,117,120},{101,105,120},
	{117,102,121},{117,118,121},
	{119,120,106},{119,122,106},
////	//===================6
//	//collide lift atas
	{109,113,114},{109,110,114},
	{116,115,111},{116,112,111},
	{112,109,113},{112,116,113},
	{111,110,114},{111,115,114},
	{112,111,110},{112,109,110},
//	//===================6
//	//collide pesawat2
	{73,70,71},{73,72,71},{74,75,72},{74,73,72},
//	//collide heli
	{134,133,131},{134,132,131},{136,134,133},{136,135,133}
};

void DrawWall()
{
	GLfloat c[11];

	//nganu lampu

	glLightfv(GL_LIGHT1, GL_POSITION, pos2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
	if(lamp1) glEnable(GL_LIGHT1);
	else glDisable(GL_LIGHT1);

	glLightfv(GL_LIGHT2, GL_POSITION, pos3);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, white);
	if(lamp2) glEnable(GL_LIGHT2);
	else glDisable(GL_LIGHT2);

	glLightfv(GL_LIGHT3, GL_POSITION, pos4);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, white);
	if(lamp3) glEnable(GL_LIGHT3);
	else glDisable(GL_LIGHT3);

	glLightfv(GL_LIGHT4, GL_POSITION, pos5);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, white);
	if(lamp4) glEnable(GL_LIGHT4);
	else glDisable(GL_LIGHT4);

	glLightfv(GL_LIGHT5, GL_POSITION, pos6);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, white);
	if(lamp5) glEnable(GL_LIGHT5);
	else glDisable(GL_LIGHT5);

	glLightfv(GL_LIGHT6, GL_POSITION, pos7);
	glLightfv(GL_LIGHT6, GL_DIFFUSE, white);
	if(lamp6) glEnable(GL_LIGHT6);
	else glDisable(GL_LIGHT6);

	glLightfv(GL_LIGHT7, GL_POSITION, pos8);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, white);
	if(lamp7) glEnable(GL_LIGHT7);
	else glDisable(GL_LIGHT7);

    //45
	c[0] = c[1] = c[2] = c[3] = c[4]= c[5]= c[6]= c[7]= c[8]= c[9]= c[10] = 1;

	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);

	//lorong utama
    //hadap atas
	glBindTexture(GL_TEXTURE_2D, floortex);
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f( 0,10); glVertex3f( 0,0,200);
	glTexCoord2f(10,10); glVertex3f(70,0,200);
	glTexCoord2f(10, 0); glVertex3f(70,0,  0);
	glTexCoord2f( 0, 0); glVertex3f( 0,0,  0);
	glEnd();

	//hadap kiri  --ke atas ke kiri
	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(1,0,0);
	glTexCoord2f(0,0); glVertex3f(0,  0,  0);
	glTexCoord2f(4,0); glVertex3f(0,140,  0);
	glTexCoord2f(4,4); glVertex3f(0,140,200);
	glTexCoord2f(0,4); glVertex3f(0,  0,200);
	glEnd();

	//hadap kanan --ke atas ke kanan
	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0,4); glVertex3f( 70, 0,200);
	glTexCoord2f(4,4); glVertex3f( 70,70,200);
	glTexCoord2f(4,0); glVertex3f( 70,70,  0);
	glTexCoord2f(0,0); glVertex3f( 70, 0,  0);
	glEnd();

	//hadap bawah --ke atas trus kiri
	glBindTexture(GL_TEXTURE_2D, ceiltex);
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0,0); glVertex3f( 0,140,  0);
	glTexCoord2f(4,0); glVertex3f(70,140,  0);
	glTexCoord2f(4,4); glVertex3f(70,140,200);
	glTexCoord2f(0,4); glVertex3f( 0,140,200);
	glEnd();

	//lorong 2
    glBindTexture(GL_TEXTURE_2D, floortex);
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0,4); glVertex3f(-100,0,200);
	glTexCoord2f(4,4); glVertex3f(-100,0,650);
	glTexCoord2f(4,0); glVertex3f( 200,0,650);
	glTexCoord2f(0,0); glVertex3f( 200,0,200);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, ceiltex);
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0,0); glVertex3f(-100,140,200);
	glTexCoord2f(4,0); glVertex3f( 200,140,200);
	glTexCoord2f(4,4); glVertex3f( 200,140,650);
	glTexCoord2f(0,4); glVertex3f(-100,140,650);
	glEnd();

    glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(1,0,0);
	glTexCoord2f(0,0); glVertex3f(-100,  0,200);
	glTexCoord2f(4,0); glVertex3f(-100,140,200);
	glTexCoord2f(4,4); glVertex3f(-100,140,650);
	glTexCoord2f(0,4); glVertex3f(-100,  0,650);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0,0); glVertex3f(-100,  0,650);
	glTexCoord2f(4,0); glVertex3f(-100,140,650);
	glTexCoord2f(4,4); glVertex3f( 200,140,650);
	glTexCoord2f(0,4); glVertex3f( 200,  0,650);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0,0); glVertex3f(200,  0,650);
	glTexCoord2f(4,0); glVertex3f(200,140,650);
	glTexCoord2f(4,4); glVertex3f(200,140,200);
	glTexCoord2f(0,4); glVertex3f(200,  0,200);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(1,0,0);
	glTexCoord2f(0,0); glVertex3f(200, 0,200);
	glTexCoord2f(4,0); glVertex3f(200,70,200);
	glTexCoord2f(4,4); glVertex3f( 70,70,200);
	glTexCoord2f(0,4); glVertex3f( 70, 0,200);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(1,0,0);
	glTexCoord2f(0,0); glVertex3f(   0,  0,200);
	glTexCoord2f(4,0); glVertex3f(   0,140,200);
	glTexCoord2f(4,4); glVertex3f(-100,140,200);
	glTexCoord2f(0,4); glVertex3f(-100,  0,200);
	glEnd();

	//kusen kamar 1
    glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(0,0,1);
	glTexCoord2f(0,0); glVertex3f( 0,  0,0);
	glTexCoord2f(4,0); glVertex3f(10,  0,0);
	glTexCoord2f(4,4); glVertex3f(10,140,0);
	glTexCoord2f(0,4); glVertex3f( 0,140,0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(1,0,0);
	glTexCoord2f(0,0); glVertex3f(10,  0,-2);
	glTexCoord2f(4,0); glVertex3f(10,210,-2);
	glTexCoord2f(4,4); glVertex3f(10,210, 0);
	glTexCoord2f(0,4); glVertex3f(10,  0, 0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(1,0,0);
	glTexCoord2f(0,0); glVertex3f(10,  0,-2);
	glTexCoord2f(4,0); glVertex3f( 0,  0,-2);
	glTexCoord2f(4,4); glVertex3f( 0,210,-2);
	glTexCoord2f(0,4); glVertex3f(10,210,-2);
	glEnd();

	//kusen kamar 2
	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(0,0,1);
	glTexCoord2f(0,0); glVertex3f(50,  0,0);
	glTexCoord2f(4,0); glVertex3f(70,  0,0);
	glTexCoord2f(4,4); glVertex3f(70,140,0);
	glTexCoord2f(0,4); glVertex3f(50,140,0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(1,0,0);
	glTexCoord2f(0,0); glVertex3f(50,  0, 0);
	glTexCoord2f(4,0); glVertex3f(50,210, 0);
	glTexCoord2f(4,4); glVertex3f(50,210,-2);
	glTexCoord2f(0,4); glVertex3f(50,  0,-2);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(0,0,1);
	glTexCoord2f(0,0); glVertex3f(70,  0,-2);
	glTexCoord2f(4,0); glVertex3f(50,  0,-2);
	glTexCoord2f(4,4); glVertex3f(50,210,-2);
	glTexCoord2f(0,4); glVertex3f(70,210,-2);
	glEnd();

	//kusen kamar 3
    glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(0,0,1);
	glTexCoord2f(0,0); glVertex3f(10, 60,0);
	glTexCoord2f(4,0); glVertex3f(50, 60,0);
	glTexCoord2f(4,4); glVertex3f(50,140,0);
	glTexCoord2f(0,4); glVertex3f(10,140,0);
	glEnd();

    glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0,0); glVertex3f(50,60, 0);
	glTexCoord2f(4,0); glVertex3f(10,60, 0);
	glTexCoord2f(4,4); glVertex3f(10,60,-2);
	glTexCoord2f(0,4); glVertex3f(50,60,-2);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(1,0,0);
	glTexCoord2f(0,0); glVertex3f(50, 60,-2);
	glTexCoord2f(4,0); glVertex3f(10, 60,-2);
	glTexCoord2f(4,4); glVertex3f(10,140,-2);
	glTexCoord2f(0,4); glVertex3f(50,140,-2);
	glEnd();

	//lantai antar kusen
	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0,1); glVertex3f(10,0, 0);
	glTexCoord2f(1,1); glVertex3f(50,0, 0);
	glTexCoord2f(1,0); glVertex3f(50,0,-2);
	glTexCoord2f(0,0); glVertex3f(10,0,-2);
	glEnd();

	//kamar1
    glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(0,0,1);
	glTexCoord2f(0,0); glVertex3f( 0, 0,-70);
	glTexCoord2f(4,0); glVertex3f(70, 0,-70);
	glTexCoord2f(4,4); glVertex3f(70,210,-70);
	glTexCoord2f(0,4); glVertex3f( 0,210,-70);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, floortex);
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0,4); glVertex3f( 0,liftA, -2);
	glTexCoord2f(4,4); glVertex3f(70,liftA, -2);
	glTexCoord2f(4,0); glVertex3f(70,liftA,-70);
	glTexCoord2f(0,0); glVertex3f( 0,liftA,-70);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(1,0,0);
	glTexCoord2f(0,0); glVertex3f(0,  0,-70);
	glTexCoord2f(4,0); glVertex3f(0,210,-70);
	glTexCoord2f(4,4); glVertex3f(0,210, -2);
	glTexCoord2f(0,4); glVertex3f(0,  0, -2);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0,4); glVertex3f(70,  0, -2);
	glTexCoord2f(4,4); glVertex3f(70,210, -2);
	glTexCoord2f(4,0); glVertex3f(70,210,-70);
	glTexCoord2f(0,0); glVertex3f(70,  0,-70);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, ceiltex);
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0,0); glVertex3f( 0,liftB,-70);
	glTexCoord2f(4,0); glVertex3f(70,liftB,-70);
	glTexCoord2f(4,4); glVertex3f(70,liftB, -2);
	glTexCoord2f(0,4); glVertex3f( 0,liftB, -2);
	glEnd();

	//ruang atas
	glBindTexture(GL_TEXTURE_2D, floortex);
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0, 10); glVertex3f( 70,70,200);
	glTexCoord2f(10,10); glVertex3f(200,70,200);
	glTexCoord2f(10, 0); glVertex3f(200,70,  0);
	glTexCoord2f( 0, 0); glVertex3f( 70,70,  0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, ceiltex);
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0,0); glVertex3f( 70,140,  0);
	glTexCoord2f(4,0); glVertex3f(200,140,  0);
	glTexCoord2f(4,4); glVertex3f(200,140,200);
	glTexCoord2f(0,4); glVertex3f( 70,140,200);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, cen);
	glBegin(GL_QUADS);
	glNormal3f(0,0,1);
	glTexCoord2f(0,0); glVertex3f( 70, 70,0);
	glTexCoord2f(1,0); glVertex3f(200, 70,0);
	glTexCoord2f(1,1); glVertex3f(200,140,0);
	glTexCoord2f(0,1); glVertex3f( 70,140,0);
	glEnd();

    glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0,4); glVertex3f(200, 70,200);
	glTexCoord2f(4,4); glVertex3f(200,140,200);
	glTexCoord2f(4,0); glVertex3f(200,140,  0);
	glTexCoord2f(0,0); glVertex3f(200, 70,  0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, misil);
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0,1); glVertex3f(199.9, 70,170);
	glTexCoord2f(1,1); glVertex3f(199.9,140,170);
	glTexCoord2f(1,0); glVertex3f(199.9,140,100);
	glTexCoord2f(0,0); glVertex3f(199.9, 70,100);
	glEnd();

	//gambar pigura
	glBindTexture(GL_TEXTURE_2D, tank);
	glBegin(GL_QUADS);
	glNormal3f(1,0,0);
	glTexCoord2f(0,0); glVertex3f(0.1,46, 74);
	glTexCoord2f(1,0); glVertex3f(0.1,82, 74);
	glTexCoord2f(1,1); glVertex3f(0.1,82,128);
	glTexCoord2f(0,1); glVertex3f(0.1,46,128);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, pesawat);
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0,0); glVertex3f(20,46,399.1);
	glTexCoord2f(1,0); glVertex3f(20,75,399.1);
	glTexCoord2f(1,1); glVertex3f(50,75,399.1);
	glTexCoord2f(0,1); glVertex3f(50,46,399.1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, kapal);
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0,0); glVertex3f(199.1, 68,555);
	glTexCoord2f(1,0); glVertex3f(199.1,112,555);
	glTexCoord2f(1,1); glVertex3f(199.1,112,480);
	glTexCoord2f(0,1); glVertex3f(199.1, 68,480);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, heli);
	glBegin(GL_QUADS);
	glNormal3f(1,0,0);
	glTexCoord2f(0,0); glVertex3f(-99.1, 47,247);
	glTexCoord2f(1,0); glVertex3f(-99.1,112,247);
	glTexCoord2f(1,1); glVertex3f(-99.1,112,324);
	glTexCoord2f(0,1); glVertex3f(-99.1, 47,324);
	glEnd();

	// sekat tengah
    glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0,0); glVertex3f(-35,  0,400);
	glTexCoord2f(1,0); glVertex3f(-35,140,400);
	glTexCoord2f(1,1); glVertex3f(135,140,400);
	glTexCoord2f(0,1); glVertex3f(135,  0,400);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(1,0,0);
	glTexCoord2f(0,0); glVertex3f(135,  0,400);
	glTexCoord2f(1,0); glVertex3f(135,140,400);
	glTexCoord2f(1,1); glVertex3f(135,140,420);
	glTexCoord2f(0,1); glVertex3f(135,  0,420);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(1,0,0);
	glTexCoord2f(0,0); glVertex3f(-35,0,420);
	glTexCoord2f(1,0); glVertex3f(-35,140,420);
	glTexCoord2f(1,1); glVertex3f(-35,140,400);
	glTexCoord2f(0,1); glVertex3f(-35,0,400);
	glEnd();

    glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(0,0,1);
	glTexCoord2f(0,0); glVertex3f(-35,  0,420);
	glTexCoord2f(4,0); glVertex3f(135,  0,420);
	glTexCoord2f(4,4); glVertex3f(135,140,420);
	glTexCoord2f(0,4); glVertex3f(-35,140,420);
	glEnd();

	//kusen antara lift dan lantai 2
    glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0,0); glVertex3f(50,209.9, 0);
	glTexCoord2f(4,0); glVertex3f(10,209.9, 0);
	glTexCoord2f(4,4); glVertex3f(10,209.9,-2);
	glTexCoord2f(0,4); glVertex3f(50,209.9,-2);
	glEnd();

	//lantai 2
	//hadap atas
    glBindTexture(GL_TEXTURE_2D, floortex);
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0, 4); glVertex3f(-150,140,650);
	glTexCoord2f(4, 4); glVertex3f( 200,140,650);
	glTexCoord2f(4, 0); glVertex3f( 200,140, -2);
	glTexCoord2f(0, 0); glVertex3f(-150,140, -2);
	glEnd();

	//hadap depan
	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(0,0,1);
	glTexCoord2f(0,0); glVertex3f(-150,209.9,0);
	glTexCoord2f(4,0); glVertex3f( 200,209.9,0);
	glTexCoord2f(4,4); glVertex3f( 200,  280,0);
	glTexCoord2f(0,4); glVertex3f(-150,  280,0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(0,0,1);
	glTexCoord2f(0, 0); glVertex3f(-150,140,0);
	glTexCoord2f(4, 0); glVertex3f(  10,140,0);
	glTexCoord2f(4, 4); glVertex3f(  10,210,0);
	glTexCoord2f(0, 4); glVertex3f(-150,210,0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(0,0,1);
	glTexCoord2f(0, 0); glVertex3f( 50,140,0);
	glTexCoord2f(4, 0); glVertex3f(200,140,0);
	glTexCoord2f(4, 4); glVertex3f(200,210,0);
	glTexCoord2f(0, 4); glVertex3f( 50,210,0);
	glEnd();

	//hadap kiri
	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(1,0,0);
	glTexCoord2f(0,0); glVertex3f(-150,140, -2);
	glTexCoord2f(4,0); glVertex3f(-150,280, -2);
	glTexCoord2f(4,4); glVertex3f(-150,280,650);
	glTexCoord2f(0,4); glVertex3f(-150,140,650);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, helicopter);
	glBegin(GL_QUADS);
	glNormal3f(1,0,0);
	glTexCoord2f(0,0); glVertex3f(-149.9,140, -2);
	glTexCoord2f(1,0); glVertex3f(-149.9,280, -2);
	glTexCoord2f(1,1); glVertex3f(-149.9,280,200);
	glTexCoord2f(0,1); glVertex3f(-149.9,140,200);
	glEnd();

	//hadap kanan
	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0,4); glVertex3f(200,140,650);
	glTexCoord2f(4,4); glVertex3f(200,280,650);
	glTexCoord2f(4,0); glVertex3f(200,280, -2);
	glTexCoord2f(0,0); glVertex3f(200,140, -2);
	glEnd();

	//hadap belakang
	glBindTexture(GL_TEXTURE_2D, cor);
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0,0); glVertex3f(-150,140,650);
	glTexCoord2f(1,0); glVertex3f(-150,280,650);
	glTexCoord2f(1,1); glVertex3f( 200,280,650);
	glTexCoord2f(0,1); glVertex3f( 200,140,650);
	glEnd();

	//hadap bawah
    glBindTexture(GL_TEXTURE_2D, ceiltex);
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0,0); glVertex3f(-150,280, -2);
	glTexCoord2f(4,0); glVertex3f( 200,280, -2);
	glTexCoord2f(4,4); glVertex3f( 200,280,650);
	glTexCoord2f(0,4); glVertex3f(-150,280,650);
	glEnd();

	//sekat tengah lantai 2
	//hadap belakang
	glBindTexture(GL_TEXTURE_2D, mir);
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0,0); glVertex3f( 20,140,290);
	glTexCoord2f(1,0); glVertex3f( 20,280,290);
	glTexCoord2f(1,1); glVertex3f(200,280,290);
	glTexCoord2f(0,1); glVertex3f(200,140,290);
	glEnd();

	//hadap kanan
	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(1,0,0);
	glTexCoord2f(0,0); glVertex3f(20,140,300);
	glTexCoord2f(1,0); glVertex3f(20,280,300);
	glTexCoord2f(1,1); glVertex3f(20,280,290);
	glTexCoord2f(0,1); glVertex3f(20,140,290);
	glEnd();

	//hadap depan
    glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glNormal3f(0,0,1);
	glTexCoord2f(0,0); glVertex3f( 20,140,300);
	glTexCoord2f(4,0); glVertex3f(200,140,300);
	glTexCoord2f(4,4); glVertex3f(200,280,300);
	glTexCoord2f(0,4); glVertex3f( 20,280,300);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, nakel);
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0,1); glVertex3f(69,20,-20);
	glTexCoord2f(1,1); glVertex3f(69,50,-20);
	glTexCoord2f(1,0); glVertex3f(69,50,-50);
	glTexCoord2f(0,0); glVertex3f(69,20,-50);
	glEnd();
}

void lift(float b)
{
    liftA += b;
    eyey += b;
    liftB += b;
}

void genlist(){
    vr1=glGenLists(1);
    vr2=glGenLists(2);
    vr3=glGenLists(3);
    vr4 = glGenLists(4);
    vr5= glGenLists(5);
    vr6 =glGenLists(6);
}

void loadObj2(char *fname, int index)
{
    FILE *fp;
    int read;
    GLfloat x, y, z;
    char ch;

    fp=fopen(fname,"r");
    if (!fp)
    {
        printf("can't open file %s\n", fname);
        exit(1);
    }
    glPointSize(2.0);
    glColor3f(0,0,0);
    if(index == 0){
        glNewList(vr1, GL_COMPILE);
        {
            glPushMatrix();
            glBegin(GL_POINTS);
            while(!(feof(fp)))
            {
                read=fscanf(fp,"%c %f %f %f",&ch,&x,&y,&z);
                if(read==4&&ch=='v')
                {
                    glVertex3f(x,y,z);
                }
            }
            glEnd();
        }
        glPopMatrix();
        glEndList();
    }else if(index == 1)
    {
        glNewList(vr2, GL_COMPILE);
        {
            glPushMatrix();
            glBegin(GL_POINTS);
            while(!(feof(fp)))
            {
                read=fscanf(fp,"%c %f %f %f",&ch,&x,&y,&z);
                if(read==4&&ch=='v')
                {
                    glVertex3f(x,y,z);
                }
            }
            glEnd();
        }
        glPopMatrix();
        glEndList();
    }else if(index ==2){
        glNewList(vr3, GL_COMPILE);
        {
            glPushMatrix();
            glBegin(GL_POINTS);
            while(!(feof(fp)))
            {
                read=fscanf(fp,"%c %f %f %f",&ch,&x,&y,&z);
                if(read==4&&ch=='v')
                {
                    glVertex3f(x,y,z);
                }
            }
            glEnd();
        }
        glPopMatrix();
        glEndList();
    }else if(index ==3){
        glNewList(vr4, GL_COMPILE);
        {
            glPushMatrix();
            glBegin(GL_POINTS);
            while(!(feof(fp)))
            {
                read=fscanf(fp,"%c %f %f %f",&ch,&x,&y,&z);
                if(read==4&&ch=='v')
                {
                    glVertex3f(x,y,z);
                }
            }
            glEnd();
        }
        glPopMatrix();
        glEndList();
    }else if(index ==4){
        glNewList(vr5, GL_COMPILE);
        {
            glPushMatrix();
            glBegin(GL_POINTS);
            while(!(feof(fp)))
            {
                read=fscanf(fp,"%c %f %f %f",&ch,&x,&y,&z);
                if(read==4&&ch=='v')
                {
                    glVertex3f(x,y,z);
                }
            }
            glEnd();
        }
        glPopMatrix();
        glEndList();
    }else if(index ==5){
        glNewList(vr6, GL_COMPILE);
        {
            glPushMatrix();
            glBegin(GL_POINTS);
            while(!(feof(fp)))
            {
                read=fscanf(fp,"%c %f %f %f",&ch,&x,&y,&z);
                if(read==4&&ch=='v')
                {
                    glVertex3f(x,y,z);
                }
            }
            glEnd();
        }
        glPopMatrix();
        glEndList();
    }
    fclose(fp);
}

void rotatesvr1()
{
    glPushMatrix();
    glTranslatef(44,20,318);
    glColor3f(0,0,0);
    glScalef(14,14,14);
    glRotatef(vr1rot,0,1,0);
    glCallList(vr1);
    glPopMatrix();
    vr1rot=vr1rot-0.6;
    if(vr1rot>360)vr1rot=vr1rot-360;
}

void rotatesvr2()
{
    glPushMatrix();
    glTranslatef(40,55,318);
    glColor3f(0,0,0);
    glScalef(12,12,12);
    glRotatef(vr2rot,0,1,0);
    glCallList(vr2);
    glPopMatrix();
    vr2rot=vr2rot-0.6;
    if(vr2rot>360)vr2rot=vr2rot-360;
}

void rotatesvr3()
{
    glPushMatrix();
    glTranslatef(40,55,318);
    glColor3f(0,0,0);
    glScalef(10,12,10);
    glRotatef(vr3rot,0,1,0);
    glCallList(vr3);
    glPopMatrix();
    vr3rot=vr3rot-0.6;
    if(vr3rot>360)vr3rot=vr3rot-360;
}

void rotatesvr4()
{
    glPushMatrix();
    glTranslatef(50,50,520);
    glColor3f(0,0,0);
    glScalef(18,15,15);
    glRotatef(vr4rot,0,1,0);
    glCallList(vr4);
    glPopMatrix();

    vr4rot=vr4rot-0.6;
    if(vr4rot<0)vr4rot=vr4rot+360;
}

void rotatesvr5()
{
    glPushMatrix();
    glTranslatef(50,50,520);
    glColor3f(0,0,0);
    glScalef(15,20,30);
    glRotatef(vr5rot,0,1,0);
    glCallList(vr5);
    glPopMatrix();

    vr5rot=vr5rot-0.6;
    if(vr5rot<0)vr5rot=vr5rot+360;
}

void rotatesvr6()
{
    glPushMatrix();
    glTranslatef(50,60,520);
    glColor3f(0,0,0);
    glScalef(10,12,10);
    glRotatef(vr6rot,0,1,0);
    glCallList(vr6);
    glPopMatrix();

    vr6rot=vr6rot-0.6;
    if(vr6rot<0)vr6rot=vr6rot+360;
}

void rotatespropeller(float a){
    glPushMatrix();
    glTranslatef(posisiBenda[18][0], posisiBenda[18][1], posisiBenda[18][2]);
    glScalef(10,10,10);
    glRotatef(propeller, 0, 1.0f, 0);
    float h1=0, h2=0, h3=1, w1=0, w2=1, w3=1;
    for(int i = 0;i < object[18].faces.size();i++){
        glBegin(GL_POLYGON);
        glNormal3f(
            object[18].vektorNormal[object[18].faces[i].at(1) - 1].at(0),
            object[18].vektorNormal[object[18].faces[i].at(1) - 1].at(1),
            object[18].vektorNormal[object[18].faces[i].at(1) - 1].at(2)
        );
        glTexCoord2f(w1, h1);
        glVertex3f(
            object[18].vektor[object[18].faces[i].at(0) - 1].at(0),
            object[18].vektor[object[18].faces[i].at(0) - 1].at(1),
            object[18].vektor[object[18].faces[i].at(0) - 1].at(2)
        );

        glNormal3f(
            object[18].vektorNormal[object[18].faces[i].at(3) - 1].at(0),
            object[18].vektorNormal[object[18].faces[i].at(3) - 1].at(1),
            object[18].vektorNormal[object[18].faces[i].at(3) - 1].at(2)
        );
        glTexCoord2f(w2, h2);
        glVertex3f(
            object[18].vektor[object[18].faces[i].at(2) - 1].at(0),
            object[18].vektor[object[18].faces[i].at(2) - 1].at(1),
            object[18].vektor[object[18].faces[i].at(2) - 1].at(2)
        );

        glNormal3f(
            object[18].vektorNormal[object[18].faces[i].at(5) - 1].at(0),
            object[18].vektorNormal[object[18].faces[i].at(5) - 1].at(1),
            object[18].vektorNormal[object[18].faces[i].at(5) - 1].at(2)
        );
        glTexCoord2f(w3, h3);
        glVertex3f(
            object[18].vektor[object[18].faces[i].at(4) - 1].at(0),
            object[18].vektor[object[18].faces[i].at(4) - 1].at(1),
            object[18].vektor[object[18].faces[i].at(4) - 1].at(2)
        );
        glEnd();
    }
    glPopMatrix();

    propeller=propeller+a;
    if(propeller>360)propeller=propeller-360;
}

void doorPosition(){
    posx = posisiBenda[16][0];
    posxasli = posisiBenda[16][0];
    posy = posisiBenda[16][1];
    posz = posisiBenda[16][2];

    posx2 = posisiBenda[17][0];
    posxasli2 = posisiBenda[17][0];
    posy2 = posisiBenda[17][1];
    posz2 = posisiBenda[17][2];
}

void slidingdoor(){
    glPushMatrix();
    glTranslatef(posx, posy, posz);
    glBindTexture(GL_TEXTURE_2D, besi);
    glScalef(20,25,2);
    glRotatef(90, 0, 1, 0);
    float h1=0, h2=0, h3=1, w1=0, w2=1, w3=1;
    for(int i = 0;i < object[16].faces.size();i++){
        glBegin(GL_POLYGON);
        glNormal3f(
            object[16].vektorNormal[object[16].faces[i].at(1) - 1].at(0),
            object[16].vektorNormal[object[16].faces[i].at(1) - 1].at(1),
            object[16].vektorNormal[object[16].faces[i].at(1) - 1].at(2)
        );
        glTexCoord2f(w1, h1);
        glVertex3f(
            object[16].vektor[object[16].faces[i].at(0) - 1].at(0),
            object[16].vektor[object[16].faces[i].at(0) - 1].at(1),
            object[16].vektor[object[16].faces[i].at(0) - 1].at(2)
        );

        glNormal3f(
            object[16].vektorNormal[object[16].faces[i].at(3) - 1].at(0),
            object[16].vektorNormal[object[16].faces[i].at(3) - 1].at(1),
            object[16].vektorNormal[object[16].faces[i].at(3) - 1].at(2)
        );
        glTexCoord2f(w2, h2);
        glVertex3f(
            object[16].vektor[object[16].faces[i].at(2) - 1].at(0),
            object[16].vektor[object[16].faces[i].at(2) - 1].at(1),
            object[16].vektor[object[16].faces[i].at(2) - 1].at(2)
        );

        glNormal3f(
            object[16].vektorNormal[object[16].faces[i].at(5) - 1].at(0),
            object[16].vektorNormal[object[16].faces[i].at(5) - 1].at(1),
            object[16].vektorNormal[object[16].faces[i].at(5) - 1].at(2)
        );
        glTexCoord2f(w3, h3);
        glVertex3f(
            object[16].vektor[object[16].faces[i].at(4) - 1].at(0),
            object[16].vektor[object[16].faces[i].at(4) - 1].at(1),
            object[16].vektor[object[16].faces[i].at(4) - 1].at(2)
        );
        glEnd();
    }
    glPopMatrix();
     if(flagz){
        posx-=1;
       if(posx<=-9) posx = -9;
     }else{
        posx+=1;
        if(posx>=posxasli) posx = posxasli;
     }
}

void slidingdoor2(){
    glPushMatrix();
    glTranslatef(posx2, posy2, posz2);
    glBindTexture(GL_TEXTURE_2D, besi);
    glScalef(20,25,2);
    glRotatef(90, 0, 1, 0);
    float h1=0, h2=0, h3=1, w1=0, w2=1, w3=1;
    for(int i = 0;i < object[17].faces.size();i++){
        glBegin(GL_POLYGON);
        glNormal3f(
            object[17].vektorNormal[object[17].faces[i].at(1) - 1].at(0),
            object[17].vektorNormal[object[17].faces[i].at(1) - 1].at(1),
            object[17].vektorNormal[object[17].faces[i].at(1) - 1].at(2)
        );
        glTexCoord2f(w1, h1);
        glVertex3f(
            object[17].vektor[object[17].faces[i].at(0) - 1].at(0),
            object[17].vektor[object[17].faces[i].at(0) - 1].at(1),
            object[17].vektor[object[17].faces[i].at(0) - 1].at(2)
        );

        glNormal3f(
            object[17].vektorNormal[object[17].faces[i].at(3) - 1].at(0),
            object[17].vektorNormal[object[17].faces[i].at(3) - 1].at(1),
            object[17].vektorNormal[object[17].faces[i].at(3) - 1].at(2)
        );
        glTexCoord2f(w2, h2);
        glVertex3f(
            object[17].vektor[object[17].faces[i].at(2) - 1].at(0),
            object[17].vektor[object[17].faces[i].at(2) - 1].at(1),
            object[17].vektor[object[17].faces[i].at(2) - 1].at(2)
        );

        glNormal3f(
            object[17].vektorNormal[object[17].faces[i].at(5) - 1].at(0),
            object[17].vektorNormal[object[17].faces[i].at(5) - 1].at(1),
            object[17].vektorNormal[object[17].faces[i].at(5) - 1].at(2)
        );
        glTexCoord2f(w3, h3);
        glVertex3f(
            object[17].vektor[object[17].faces[i].at(4) - 1].at(0),
            object[17].vektor[object[17].faces[i].at(4) - 1].at(1),
            object[17].vektor[object[17].faces[i].at(4) - 1].at(2)
        );
        glEnd();
    }
    glPopMatrix();
     if(flagz){
        posx2-=1;
       if(posx2<=-9) posx2 = -9;
     }else{
        posx2+=1;
        if(posx2>=posxasli2) posx2 = posxasli2;
     }
}

void DrawObject()
{
	glLoadIdentity();
	DrawWall();
    drawObjek();
}

void DrawScene()
{
	double dx, dy;

	glClearColor(0.0f,0.4f,0.6f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	dy = (wrect.top+(wrect.bottom-wrect.top)/2)-pos.y;
	dx = (wrect.left+(wrect.right-wrect.left)/2)-pos.x;

	yangle+=(dy/5.0);
	xzangle-=(dx/5.0);

	if (yangle>60.0) yangle=60.0;
	if (yangle<-60.0) yangle=-60.0;

	if (yangle>360.0) yangle-=360.0;
	if (yangle<-360.0) yangle+=-360.0;

	lookatx=eyex+1000000.0*cos(xzangle*3.14/180.0);
	lookaty=eyey+1000000.0*sin(yangle*3.14/180.0);
	lookatz=eyez+1000000.0*sin(xzangle*3.14/180.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1,1,-1,1,1,10000);
	gluLookAt(eyex,eyey,eyez, lookatx,lookaty,lookatz, 0,1,0);

	flag=0;
	SetCursorPos(	wrect.left+(wrect.right-wrect.left)/2,
					wrect.top+(wrect.bottom-wrect.top)/2);
	flag=1;

	glMatrixMode(GL_MODELVIEW);
	DrawObject();
	if(vr == 0){
        rotatesvr1();
	}else if(vr == 1){
        rotatesvr2();
	}else{
        rotatesvr3();
	}

	if(vrsenjata==0){
        rotatesvr4();
	}else if(vrsenjata==1){
        rotatesvr5();
	}else{
        rotatesvr6();
	}
    slidingdoor();
    slidingdoor2();
    if(onheli){
        ctrpropeller += 0.1;
        if(ctrpropeller >= 50) ctrpropeller = 50;
    }else{
        ctrpropeller -= 0.1;
        if(ctrpropeller <= 0) ctrpropeller = 0;
    }
    rotatespropeller(ctrpropeller);
    GLfloat pos1[] = { lampx,lampy,lampz, 1 };
    glLightfv(GL_LIGHT0, GL_POSITION, pos1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glEnable(GL_LIGHT0);
    if(blift == true){
        if(flaglift == 0){
           lift(1);
            if(liftA >= 139.9){
                blift= false;
                flaglift=1;
            }
        }else {
            lift(-1);
            if(liftA <= 0){
                blift= false;
                flaglift = 0;
            }
        }
    }
	SwapBuffers(ghDC);
}

void MouseMove(HWND h)
{
	if (!flag) return;

	GetCursorPos(&pos);
}

double Dot(POINT3D a, POINT3D b)
{
	return a.x*b.x+a.y*b.y+a.z*b.z;
}

void Normalize(POINT3D &v)
{
	double le = sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
	v.x/=le;
	v.y/=le;
	v.z/=le;
}

int collide(double tx, double ty, double tz)
{
	double angle1, angle2, angle3;
	POINT3D v1, v2;
	int i;

	for (i=0; i < 154; i++)
		{
		v1.x = vertex[triangle[i].p1].x-tx;
		v1.y = vertex[triangle[i].p1].y-ty;
		v1.z = vertex[triangle[i].p1].z-tz;

		//{5,1,2}
		v2.x = vertex[triangle[i].p2].x-tx;
		v2.y = vertex[triangle[i].p2].y-ty;
		v2.z = vertex[triangle[i].p2].z-tz;

		Normalize(v1); Normalize(v2);
		angle1 = acos( Dot(v1,v2) );

		v1.x = vertex[triangle[i].p2].x-tx;
		v1.y = vertex[triangle[i].p2].y-ty;
		v1.z = vertex[triangle[i].p2].z-tz;

		v2.x = vertex[triangle[i].p3].x-tx;
		v2.y = vertex[triangle[i].p3].y-ty;
		v2.z = vertex[triangle[i].p3].z-tz;

		Normalize(v1); Normalize(v2);
		angle2 = acos( Dot(v1,v2) );

		v1.x = vertex[triangle[i].p3].x-tx;
		v1.y = vertex[triangle[i].p3].y-ty;
		v1.z = vertex[triangle[i].p3].z-tz;

		v2.x = vertex[triangle[i].p1].x-tx;
		v2.y = vertex[triangle[i].p1].y-ty;
		v2.z = vertex[triangle[i].p1].z-tz;

		Normalize(v1); Normalize(v2);
		angle3 = acos( Dot(v1,v2) );

		if ((angle1+angle2+angle3) > (350.0*3.14/180.0))
			return 1;
		}
	return 0;
}

void lightPosition()
{
    lampx = eyex;
    lampy = eyey;
    lampz = eyez;
}

void Up()
{
    lampx = eyex;
    lampy = eyey;
    lampz = eyez;

    if(!blift){
	double tx,ty,tz;

	tx=eyex+5.0*cos(xzangle*3.14/180.0);
	tz=eyez+5.0*sin(xzangle*3.14/180.0);
	ty=eyey+5.0*sin(yangle*3.14/180.0);

	if (!collide(tx,ty,tz))
		{
		eyex = tx;
		eyey = ty;
		eyez = tz;
		}

		if(tz<=25 && tz>= -25){
            flagz = true;
		}else{
            flagz = false;
		}
    }
}

void Down()
{
    lampx = eyex;
    lampy = eyey;
    lampz = eyez;
    if(!blift){
    double tx,ty,tz;

	tx=eyex-5.0*cos(xzangle*3.14/180.0);
	tz=eyez-5.0*sin(xzangle*3.14/180.0);
	ty=eyey-5.0*sin(yangle*3.14/180.0);

	if (!collide(tx,ty,tz))
		{
		eyex = tx;
		eyey = ty;
		eyez = tz;
		}

		if(tz<=25 && tz>= -25){
            flagz = true;
		}else{
            flagz = false;
		}
    }
}
