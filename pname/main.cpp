// Monkey Jump.cpp : Defines the entry point for the console application.


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<GL/glut.h>
#include<Windows.h>
#include<MMSystem.h>

int m1 = 150, m2 = 130, m3 = 155, m4 = 157, m5 = 165;//Monkey Initial Position
int mx1 = 130, my = 55, newx1 = 0, newx2 = 0, newy1 = 0, newy2 = 0;//Monkey Movements
int dmsg = 0, rst = 0, pause = 0, keybd = 0, menu = 0, gameoverflag = 0, start = 0;//Flags
int hmove1 = 0, hmove2 = 0, tmove1 = 0, tmove2 = 0;//Hurdle And Tree Move
float score = 0.0;

int x = 0;
char tmp[20];

bool playw = 0;

void keyboard1(unsigned char, int, int);//Used In Display1
void keyboard2(unsigned char, int, int);//Used In Display
void mouse(int, int, int, int);//Used In Display
void mouse1(int, int, int, int);//Used In Display1
void myinit();
void msg(char *);
void update(int);
void bitmap_output(int, int, char *, void *);
void display1();
void back_ground();
void tree1(int, int);
void tree();
void rtree1(int, int);
void rtree();
void grass1(int);
void grass();
void Monkey();
void hurdle();
void display();
void load();
void delay(int);
void restart();
void reset();

void myinit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 499, 0, 499);
	glFlush();
	glutSwapBuffers();
}

void msg(char *string)
{
	while (*string)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string++);
}

void update(int value)
{
	if (!gameoverflag && !pause)
	{
		hmove1 += 5;
		hmove2 += 5;
		tmove1 += 5;
		tmove2 += 5;

		if (hmove1 > 500) { hmove1 = -100; }
		if (hmove2 > 500) { hmove2 = -100; }
		if (tmove1 > 500) { tmove1 = -500; }
		if (tmove2 > 1000) { tmove2 = 0; }

		glFlush();
		glutSwapBuffers();
		glutPostRedisplay();
		glutTimerFunc(20, update, 0); //1st arg gives delay time

	}
}

void bitmap_output(int x, int y, char *string, void * font)
{
	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i<len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}
}

void display1(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.4, 1.0, 1.0);

	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(990, 0);
	glVertex2f(990, 990);
	glVertex2f(00, 990);
	glEnd();

	glColor3f(0, 1.0, 0);
	bitmap_output(150, 250, "NEXT-Click Right Mouse Button ", GLUT_BITMAP_TIMES_ROMAN_24);

	glColor3f(0, 1.0, 0);
	bitmap_output(150, 230, "Press S To Start The Game ", GLUT_BITMAP_TIMES_ROMAN_24);

	glColor3f(0, 1.0, 0);
	bitmap_output(150, 210, "Press Left Mouse Button To Make Jump ", GLUT_BITMAP_TIMES_ROMAN_24);

	fflush(stdin);
	glutMouseFunc(mouse1);
	glutKeyboardFunc(keyboard1);

	glEnd();
	glFlush();
	glutSwapBuffers();
}

void back_ground()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glColor3f(0.36, 0.20, 0.09);//Tree Left
	glBegin(GL_POLYGON);
	glVertex2f(120, 0);
	glVertex2f(130, 0);
	glVertex2f(130, 500);
	glVertex2f(120, 500);
	glEnd();

	glColor3f(0.36, 0.20, 0.09);//Tree Right
	glBegin(GL_POLYGON);
	glVertex2f(360, 0);
	glVertex2f(370, 0);
	glVertex2f(370, 500);
	glVertex2f(360, 500);
	glEnd();

	glColor3f(0.576471, 0.858824, 0.439216);//BG Left
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(120, 0);
	glVertex2f(120, 500);
	glVertex2f(0, 500);
	glEnd();

	glColor3f(0.576471, 0.858824, 0.439216);//BG Right
	glBegin(GL_POLYGON);
	glVertex2f(370, 0);
	glVertex2f(500, 0);
	glVertex2f(500, 500);
	glVertex2f(370, 500);
	glEnd();

	glColor3f(0.196078, 0.8, 0.6);//BG Middle
	glBegin(GL_POLYGON);
	glVertex2f(130, 0);
	glVertex2f(360, 0);
	glVertex2f(360, 500);
	glVertex2f(130, 500);
	glEnd();

	glutSwapBuffers();
}

void tree1(int t1, int t2)
{
	glColor3f(0.196078, 0.8, 0.196078);//Leaf2
	glBegin(GL_POLYGON);
	glVertex2f(t1 - 8, t2 + 15);
	glVertex2f(t1 + 12, t2 + 15);
	glVertex2f(t1 + 2, t2 + 25);
	glEnd();

	glColor3f(0.258824, 0.435294, 0.258824);//Leaf1
	glBegin(GL_POLYGON);
	glVertex2f(t1 - 8, t2 + 23);
	glVertex2f(t1 + 12, t2 + 23);
	glVertex2f(t1 + 2, t2 + 33);
	glEnd();

	glColor3f(0.36, 0.20, 0.09);//Trunk
	glBegin(GL_POLYGON);
	glVertex2f(t1, t2 + 15);
	glVertex2f(t1 + 4, t2 + 15);
	glVertex2f(t1 + 4, t2);
	glVertex2f(t1, t2);
	glEnd();

	glutSwapBuffers();
}

void tree()
{
	tree1(100, 0 - tmove1);tree1(48, 125 - tmove1);tree1(105, 327 - tmove1);tree1(8, 420 - tmove1);////Trees In Left Bg

	tree1(390, 0 - tmove1);tree1(460, 135 - tmove1);tree1(380, 327 - tmove1);tree1(490, 420 - tmove1);//Trees In Right Bg

	tree1(100, 600 - tmove2);tree1(30, 660 - tmove2);tree1(105, 827 - tmove2);tree1(50, 920 - tmove2);//Trees In Left Bg - Frame Above

	tree1(380, 827 - tmove2);tree1(450, 670 - tmove2);tree1(420, 550 - tmove2);tree1(490, 920 - tmove2);//Trees In Right Bg - Frame Above
}

void rtree1(int rt1, int rt2)
{
	glColor3f(0.36, 0.20, 0.09);//Round Tree Trunk
	glBegin(GL_POLYGON);
	glVertex2f(rt1 - 2, rt2);
	glVertex2f(rt1 + 2, rt2);
	glVertex2f(rt1 + 2, rt2 - 25);
	glVertex2f(rt1 - 2, rt2 - 25);
	glEnd();

	glColor3f(0.258824, 0.435294, 0.258824);//Round Tree
	glBegin(GL_POLYGON);
	for (int k = 0; k <= 36; k++)
	{
		glVertex2f(rt1 + 15 * cos(2 * 3.14*k / 36), rt2 + 15 * sin(2 * 3.14*k / 36));
	}
	glEnd();

	glColor3f(1.0, 1.0, 0.0);//Fruit1
	glBegin(GL_POLYGON);
	for (int k = 0; k <= 36; k++)
	{
		glVertex2f(rt1 + 2 * cos(2 * 3.14*k / 36), rt2 + 2 * sin(2 * 3.14*k / 36));
	}
	glEnd();

	glColor3f(1.0, 0.0, 0.0);//Fruit2
	glBegin(GL_POLYGON);
	for (int k = 0; k <= 36; k++)
	{
		glVertex2f((rt1 - 10) + 2 * cos(2 * 3.14*k / 36), rt2 + 2 * sin(2 * 3.14*k / 36));
	}
	glEnd();

	glColor3f(1.0, 0.0, 0.0);//Fruit3
	glBegin(GL_POLYGON);
	for (int k = 0; k <= 36; k++)
	{
		glVertex2f((rt1 + 5) + 2 * cos(2 * 3.14*k / 36), rt2 + 9 + 2 * sin(2 * 3.14*k / 36));
	}
	glEnd();

	glColor3f(1.0, 0.0, 0.0);//Fruit4
	glBegin(GL_POLYGON);
	for (int k = 0; k <= 36; k++)
	{
		glVertex2f((rt1 + 6) + 2 * cos(2 * 3.14*k / 36), rt2 - 8 + 2 * sin(2 * 3.14*k / 36));
	}
	glEnd();

	glutSwapBuffers();

}

void rtree()
{
	rtree1(18, 25 - tmove1);rtree1(90, 240 - tmove1);rtree1(25, 350 - tmove1);rtree1(105, 480 - tmove1);//Rtrees In Left Bg

	rtree1(470, 25 - tmove1);rtree1(400, 175 - tmove1);rtree1(480, 300 - tmove1);rtree1(400, 480 - tmove1);//Rtrees In Right Bg

	rtree1(25, 540 - tmove2);rtree1(90, 750 - tmove2);rtree1(25, 850 - tmove2);//Rtrees In Left Bg - Frame Above

	rtree1(480, 800 - tmove2);rtree1(400, 680 - tmove2);rtree1(420, 920 - tmove2);rtree1(480, 540 - tmove2);//Rtrees In Right Bg - Frame Above
}

void grass1(int g1)
{
	glColor3f(0.13, 0.37, 0.31);//Grass
	glBegin(GL_POLYGON);
	glVertex2f(g1, 0);
	glVertex2f(g1 - 3, 10);
	glVertex2f(g1 + 2, 2);
	glVertex2f(g1 + 3, 10);
	glVertex2f(g1 + 5, 2);
	glVertex2f(g1 + 9, 10);
	glVertex2f(g1 + 6, 0);
	glEnd();

	glutSwapBuffers();
}

void grass()
{
	grass1(0);grass1(10);grass1(20);grass1(30);grass1(40);grass1(50);grass1(60);grass1(70);grass1(80);grass1(90);grass1(100);grass1(110);grass1(120);//Grass In Left Bg

	grass1(365);grass1(375);grass1(385);grass1(395);grass1(405);grass1(415);grass1(425);grass1(435);grass1(445);grass1(455);grass1(465);grass1(475);grass1(485);grass1(495);//Grass In Right Bg
}

void Monkey()
{
	glColor3f(0.556863, 0.419608, 0.137255);//Upper Hand
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2f(m2, 55);
	glVertex2f(m1, 50);
	glEnd();

	glColor3f(0.556863, 0.419608, 0.137255);//Lower Hand
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2f(m2, 25);
	glVertex2f(m1, 30);
	glEnd();

	glColor3f(0.556863, 0.419608, 0.137255);//Tail
	glBegin(GL_POLYGON);
	glVertex2f(m3, 28);
	glVertex2f(m4, 30);
	glVertex2f(m5, 20);
	glEnd();

	glColor3f(0.623529, 0.623529, 0.372549);//Bottom Body
	glBegin(GL_POLYGON);
	for (int k = 0; k <= 36; k++)
	{
		glVertex2f(m1 + 7 * cos(2 * 3.14*k / 36), 30 + 5 * sin(2 * 3.14*k / 36));
	}
	glEnd();

	glColor3f(0.623529, 0.623529, 0.372549);//Body
	glBegin(GL_POLYGON);
	glVertex2f(m1, 70);
	glVertex2f(m1 - 7, 30);
	glVertex2f(m1 + 7, 30);
	glEnd();

	glColor3f(0.556863, 0.419608, 0.137255);//Left Ear
	glBegin(GL_POLYGON);
	for (int k = 0; k <= 36; k++)
	{
		glVertex2f((m1 - 5) + 3 * cos(2 * 3.14*k / 36), 68 + 3 * sin(2 * 3.14*k / 36));
	}
	glEnd();

	glColor3f(0.556863, 0.419608, 0.137255);//Right Ear
	glBegin(GL_POLYGON);
	for (int k = 0; k <= 36; k++)
	{
		glVertex2f((m1 + 5) + 3 * cos(2 * 3.14*k / 36), 68 + 3 * sin(2 * 3.14*k / 36));
	}
	glEnd();

	glColor3f(0.435294, 0.258824, 0.258824);//Head
	glBegin(GL_POLYGON);
	for (int k = 0; k <= 36; k++)
	{
		glVertex2f(m1 + 8 * cos(2 * 3.14*k / 36), 62 + 8 * sin(2 * 3.14*k / 36));
	}
	glEnd();
	glFlush();

	glColor3f(1.0, 1.0, 1.0);//Eyes
	glPointSize(3);
	glBegin(GL_POINTS);
	glVertex2f(m1 - 4, 64);
	glVertex2f(m1 + 4, 64);
	glEnd();

	glutSwapBuffers();
}

void hurdle()
{

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(130, 460 - hmove1);
	glVertex2f(140, 470 - hmove1);
	glVertex2f(130, 495 - hmove1);
	glVertex2f(140, 490 - hmove1);
	glVertex2f(130, 500 - hmove1);
	glEnd();

	newx1 = 130; newy1 = 460 - hmove1;

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(360, 320 - hmove2);
	glVertex2f(348, 320 - hmove2);
	glVertex2f(348, 325 - hmove2);
	glVertex2f(360, 325 - hmove2);
	glEnd();

	newx2 = 360; newy2 = 320 - hmove2;

	{
		if ((mx1 == newx1 - (newx1 % 5) && my == newy1 - (newy1 % 5)) || (mx1 == newx2 - (newx2 % 5) && my == newy2 - (newy2 % 5)))
		{
			gameoverflag = 1;
		}
	}

	glutSwapBuffers();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	fflush(stdin);
	glutKeyboardFunc(keyboard2);
	glutMouseFunc(mouse);
	back_ground();
	Monkey();
	tree();
	grass();
	rtree();
	hurdle();

	if (!gameoverflag)
	{
		score += 0.2;
	}

	int sc = score;//For Score Box
	glBegin(GL_POLYGON);
	glColor3f(0.329412, 0.329412, 0.329412);
	glVertex2f(5, 495);
	glVertex2f(85, 495);
	glVertex2f(85, 460);
	glVertex2f(5, 460);
	glEnd();
	glColor3f(1, 0, 0);
	glRasterPos2f(10, 480);
	//sprintf_s(tmp, "Score:%d", sc);
	msg(tmp);
	glColor3f(1, 0, 0);
	bitmap_output(10, 465, "Press P To pause", GLUT_BITMAP_TIMES_ROMAN_24);

	if (dmsg)
	{
		glBegin(GL_POLYGON);
		glColor3f(0.329412, 0.329412, 0.329412);
		glVertex2f(215, 255);
		glVertex2f(280, 255);
		glVertex2f(280, 235);
		glVertex2f(215, 235);
		glEnd();
		dmsg = 0;
		glColor3f(1, 0, 0);
		bitmap_output(220, 240, "Press S To Begin", GLUT_BITMAP_TIMES_ROMAN_24);

	}

	if (pause)
	{
		glBegin(GL_POLYGON);
		glColor3f(0.329412, 0.329412, 0.329412);
		glVertex2f(215, 255);
		glVertex2f(290, 255);
		glVertex2f(290, 235);
		glVertex2f(215, 235);
		glEnd();
		dmsg = 0;
		glColor3f(1, 0, 0);
		bitmap_output(220, 240, "Press R To Resume", GLUT_BITMAP_TIMES_ROMAN_24);
	}

	if (gameoverflag)
	{
		PlaySoundA(NULL, NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
		PlaySoundA("end.wav", NULL, SND_ASYNC | SND_FILENAME);
		glBegin(GL_POLYGON);
		glColor3f(0.329412, 0.329412, 0.329412);
		glVertex2f(195, 295);
		glVertex2f(305, 295);
		glVertex2f(305, 185);
		glVertex2f(195, 185);
		glEnd();
		glColor3f(1, 0, 0);
		bitmap_output(200, 280, "Game Over!!!", GLUT_BITMAP_TIMES_ROMAN_24);
		glColor3f(1, 0, 0);
		bitmap_output(200, 250, "Press R To Restart.", GLUT_BITMAP_TIMES_ROMAN_24);
		glColor3f(1, 0, 0);
		bitmap_output(200, 220, "Press M To Main Menu.", GLUT_BITMAP_TIMES_ROMAN_24);
		glColor3f(1, 0, 0);
		bitmap_output(200, 190, "Press E To Exit.", GLUT_BITMAP_TIMES_ROMAN_24);
		glFlush();
	}

	glFlush();
	glutSwapBuffers();
}

void load()
{
	glClearColor(0.80, 0.80, 0.80, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.576471, 0.858824, 0.439216);
	glRecti(175, 170, 325, 145);   //rect
	glColor3f(0.2, 0.1, 1);
	glRecti(180, 165, 194, 149);   //inner rect
	glColor3f(0.2, 0.6, 0.3);
	glRecti(197, 165, 211, 149);   //inner rect
	glColor3f(0.3, 0.5, 0.1);
	glRecti(214, 165, 228, 149);   //inner rect
	glColor3f(0.4, 0.5, 0.5);
	glRecti(231, 165, 245, 149);   //inner rect
	glColor3f(0.0, 0.0, 0.0);
	bitmap_output(175, 175, "Loading...", GLUT_BITMAP_TIMES_ROMAN_24);
	glFlush();
	glutSwapBuffers();
	delay(90);
	if (menu)
	{
		menu = 0;
		reset();
		dmsg = 0;
		display1();
	}
	else
	{
		display();
	}
	if (keybd)
	{
		keybd = 0;
		PlaySoundA("play.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
		glutDisplayFunc(display);
		glutTimerFunc(100, update, 0);
	}

	glFlush();
	glutSwapBuffers();
}

void delay(int dtime)
{
	float i1, j1, k1;

	for (i1 = 0;i1<dtime;i1 = i1 + .1)
		for (j1 = 0;j1<dtime;j1 = j1 + .1)
			for (k1 = 0;k1<dtime;k1 = k1 + .1);
}

void restart()
{
	reset();
	load();
}


void reset()
{
	gameoverflag = 0;
	score = 0;
	hmove1 = 0;hmove2 = 0;
	tmove1 = 0;tmove2 = 0;
	m1 = 150, m2 = 130, m3 = 155, m4 = 157, m5 = 165, mx1 = 130;
	start = 0;
	playw = 0;
	dmsg = 1;
	rst = 1;
	x = 0;
}

void mouse1(int button, int state, int x, int y)
{
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && !playw)
	{
		playw = 1;
		dmsg = 1;
		load();
	}
}

void mouse(int button, int state, int x, int y)
{
	if (!gameoverflag)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !gameoverflag)
		{

			if (m1 == 150)

			{

				m1 = 340, m2 = 360, m3 = 335, m4 = 333, m5 = 325, mx1 = 360;

			}
			else if (m1 == 340)

			{

				m1 = 150, m2 = 130, m3 = 155, m4 = 157, m5 = 165, mx1 = 130;

			}

			glutDisplayFunc(display);
			myinit();
			glutMainLoop();
		}

	}
}

void keyboard1(unsigned char key, int x, int y)
{
	if ((key == 's' || key == 'S') && (start == 0))
	{
		keybd = 1;
		start = 1;
		load();
	}
	glFlush();
}

void keyboard2(unsigned char key, int x, int y)
{
	if (playw == 1 || rst == 1)
	{
		if ((key == 's' || key == 'S') && (start == 0))
		{
			rst = 0;
			PlaySoundA("play.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
			glutDisplayFunc(display);
			glutTimerFunc(100, update, 0);
			start = 1;

		}
	}

	if (!gameoverflag)
	{
		if (key == 'p' || key == 'P')
		{
			pause = 1;
			display();
			PlaySoundA(NULL, NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
		}
		if ((key == 'r' || key == 'R') && pause)
		{
			pause = 0;
			PlaySoundA("play.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
			display();
			glutTimerFunc(0, update, 0);

		}
	}
	else
	{
		PlaySoundA(NULL, NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
		if (key == 'r' || key == 'R')
		{
			glFlush();
			restart();
		}
		if (key == 'e' || key == 'E')
		{
			exit(0);
		}
		if (key == 'm' || key == 'M')
		{
			menu = 1;
			load();
		}
	}

	glFlush();
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Monkey Jump!");
	myinit();
	glutDisplayFunc(display1);
	glutMainLoop();
	return 0;
}
