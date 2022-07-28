#include<windows.h>
#include<stdlib.h>
#include<gl/glut.h>
#include<time.h>
#include<stdio.h>
#include<math.h>

#define BLOCKSPEED 0.009
#define BOOSTER_MAX 50
#define PI 3.1416

int screen_height=600,screen_width=800;

bool pause=false,lflag = true,wflag = true,gameEndStatus=false,instflag=false,abtflag=false,start=false;
float bird_move=0.0;
int level=1,buildColor;


void mouse(int button, int state, int x, int y);
void printString(float x,float y,float z,void *font,char *string);//what does this do??
void drawBird();
void drawBg();
void welcome();
void display();
void moveBirdU();
void moveBirdD();


void circle(float radius_x, float radius_y)
{
	int i=0;
	float angle = 0.0;

	glBegin(GL_POLYGON);

		for(i = 0; i < 100; i++)
		{
			angle = 2 * PI * i / 100;
			glVertex2f (cos(angle) * radius_x, sin(angle) * radius_y);
			//glVertex2f (cos(angle) * radius_x+5, sin(angle) * radius_y);
		}

	glEnd();
}

void drawBird()
{
    //wing

    glColor3f(0.29,.33,0.13);
	glBegin(GL_POLYGON);

	glVertex2d(9,50);
	glVertex2d(10.5,53);
	glVertex2d(12,50);
	glVertex2d(13.5,54);
	glEnd();

    //body
    glColor3f(0.24,0.33,0.41);
	glBegin(GL_POLYGON);
	glVertex2d(5.0,48);
	glVertex2d(7.5,49);
	glVertex2d(9.0,50);
	glVertex2d(10.5,51);
	glVertex2d(12.0,51);
    glVertex2d(13.5,50);
    glVertex2d(15.0,49);

    glVertex2d(16.0,48);

    glVertex2d(15.0,47);
    glVertex2d(13.5,46);
    glVertex2d(11.0,45);
    glVertex2d(9.5,44);
    glVertex2d(8.0,45);
    glVertex2d(7.0,46);
    glVertex2d(6.0,47);
    glVertex2d(5.0,48);
	glEnd();

	//face

	glTranslatef(17.75,48.0,0);
    glColor3f(0.79, 1.81, 0.10);
	circle(2.25,2.25);
	glTranslatef(1.0,0.5,0);
    glColor3f(0, 0, 0);
	circle(.5,.5);


	//beak
	glBegin(GL_POLYGON);
    glColor3f(0.2,0.2,0.2);
    glVertex2d(1,1);
    glVertex2d(2.5,0);
    glVertex2d(1,-1);
    glEnd();


}


void drawString(float x,float y,float z,void *font,char *string)
{
	char *c;
	glRasterPos3f(x, y,z);

	for (c=string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}


void drawBg()
{
	glPushMatrix();


	glColor3f(0.45,0.6,0.89);
	glBegin(GL_POLYGON);
	glVertex3f(0.0,90.0,5.0);
	glVertex3f(100.0,90.0,5.0);
	glColor3f(0.7,0.,0.99);
	glVertex3f(100.0,10.0,5.0);
	glVertex3f(0.0,10.0,5.0);
	glEnd();

	glPopMatrix();
}

void welcome()
{
	glColor3f(0.3,0.56,0.84);
	glBegin(GL_POLYGON);
	glVertex3f(0.0,0.0,0.0);
	glColor3f(0.137,0.137,0.556);
	glVertex3f(100.0,0.0,0.0);
	glColor3f(0.196,0.196,0.8);
	glVertex3f(100.0,100.0,0.0);
	glVertex3f(0.0,100.0,0.0);
	glEnd();


	glColor3f(0.196,0.196,0.8);
	glRectf(39.5,39.5,60.5,45.5);

	glColor3f(0.8,0.8,0.8);
	glRectf(40,40,60,45);
	glColor3f(0.137,0.137,0.556);
	drawString(47,42,0,GLUT_BITMAP_TIMES_ROMAN_24,"PLAY");


	glPushMatrix();
	glColor3f(0.8,0.8,0.8);
	drawString(10.5,92,0,GLUT_BITMAP_TIMES_ROMAN_24,"WELCOME TO OUR COMPUTER GRAPHICS LAB PROJECT");
	glPopMatrix();
	glColor3f(0.137,0.137,0.556);

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(wflag==true)
	{
		welcome();
	}
	else if (instflag == true)
	{
		glColor3f(0.3,0.56,0.84);
		glBegin(GL_POLYGON);
		glVertex3f(0.0,0.0,0.0);
		glColor3f(0.137,0.137,0.556);
		glVertex3f(100.0,0.0,0.0);
		glColor3f(0.196,0.196,0.8);
		glVertex3f(100.0,100.0,0.0);
		glVertex3f(0.0,100.0,0.0);
		glEnd();
		glPushMatrix();
		glScalef(0.8,0.8,0);
		drawBird();
		glPopMatrix();
		glColor3f(0.137,0.137,0.556);
		glRectf(20.0,20.0,80.0,80.0);
		glColor3f(0.8,0.8,0.8);
		glRectf(21.0,21.0,79.0,79.0);


		glutPostRedisplay();

	}


	else
	{

		glPushMatrix();
		drawBg();


		glPushMatrix();
		glTranslatef(0.0,bird_move,0.0);
		drawBird();
		glPopMatrix();

	}

	glFlush();
	glutSwapBuffers();
}


void moveBirdU()      // jet moving up
{
	if(start == false)
		glutPostRedisplay();
	else if(pause == false)
	{
		//alti_ang-=0.15;

		bird_move+=0.05;
		glutPostRedisplay();
	}
}


void moveBirdD()          // jet moving down
{
	if(start == false)
		glutPostRedisplay();
	else if(pause == false )
	{
		//alti_ang+=0.15;
		bird_move-=0.05;
		glutPostRedisplay();
	}
}



void mouse(int button, int state, int x, int y)            // takes input from mouse
{
	int mx=x*100/screen_width,my=(screen_height-y)*100/screen_height;

	if(instflag || abtflag || gameEndStatus)
	{
		if(mx>40 && mx<60)
		{
			if(my>5 && my<10)
			{
				wflag = true;
				if(instflag)
					instflag = false;
				else if (abtflag)
					abtflag = false;

			}
		}
	}
	if(wflag == true)
	{
		if(mx>40 && mx<60)
		{
			if(my>40 && my<45)
			{
				start = true;
				wflag=false;
			}
			else if(my>30 && my<35)
			{
				instflag = true;
				wflag = false;
			}
			else if(my>20 && my<25)
			{
				abtflag = true;
				wflag = false;
			}
			else if(my>10 && my<15)
			{
				exit(0);
			}

		}
	}
	else
	{

		if(button == GLUT_LEFT_BUTTON)
		{
			if (state == GLUT_DOWN )
				glutIdleFunc(moveBirdU);

			else if (state == GLUT_UP )
				glutIdleFunc(moveBirdD);
		}

	}
}

void myReshape(int w, int h)
{
	screen_height=h,screen_width=w;
	printf("width = %d\theight= %d",w,h);
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 100.0, 0.0, 100.0,	-5.0 , 10.0);
	glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (screen_width,screen_height);
	glutInitWindowPosition (50,50);
	glutCreateWindow ("Airplane Simulation Game");
	glutDisplayFunc(display);
	glutReshapeFunc(myReshape);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}
