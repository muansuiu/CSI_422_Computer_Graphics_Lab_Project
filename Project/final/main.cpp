#include<windows.h>
#include<stdlib.h>
#include<gl/glut.h>
#include<time.h>
#include<stdio.h>
#include<math.h>

#define BLOCKSPEED 0.009
#define PI 3.1416

int SCREENH=500,SCREENW=800;
//object struct
typedef struct mountain
{
	float block_x,block_y;
	bool state;
	int no_height;
}mountain;

typedef struct Cloud
{
	float block_x,block_y;
	bool state;
}Cloud;

float bspd=BLOCKSPEED;
bool pause=false,lflag = true,wflag = true,gameEndStatus=false,instflag=false,abtflag=false,start=false;
float bird_move=0.0;
float score=100;
char score_Str[20],slevel[20];
int level=1,buildColor;
mountain b;
Cloud s;

//used functions
void keyPressed(unsigned char,int,int);
void mouse(int button, int state, int x, int y);
void printString(float x,float y,float z,void *font,char *string);//what does this do??
void Buildingmountain();
void CloudBlock();
void init();
void gameEnd();
void drawBg();
void welcome();
void drawMountain();
void drawCloud();
bool cloudHit();
bool mountainhit();
void printScore();
void display();
void drawBird();
void birdDown();
void birdUp();

void Buildingmountain()
{
	b.block_x=50.0;
	srand(time(0));
	b.no_height = rand()%3+4;
	buildColor = rand()%3;
	b.block_y=b.no_height*10 +15;   // generate block y cordinate depending on no of floors
	b.state=true;
	s.state=false;
}
void CloudBlock()
{
	s.block_x=40.0;
	srand(time(0));
	s.block_y=(rand()%250)+30;   //randomly generate block y cordinate
	s.state=true;
	b.state=false;
}




void Circle(float x1,float y1,float radius)
{
	float x2,y2;
	float angle;
	glBegin(GL_POINTS);

	for (angle=1.0f;angle<360.0f;angle++)
	{
		x2 = x1+sin(angle)*radius;
		y2 = y1+cos(angle)*radius;
		glVertex2f(x2,y2);
	}
	glEnd();

}

void draw_head(float radius_x, float radius_y)
{
	int i=0;
	float angle = 0.0;

	glBegin(GL_POLYGON);

		for(i = 0; i < 100; i++)
		{
			angle = 2 * PI * i / 100;
			glVertex2f (cos(angle) * radius_x, sin(angle) * radius_y);
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

	//head

	glTranslatef(17.75,48.0,0);
    glColor3f(0.79, 1.81, 0.10);
	draw_head(2.25,2.25);
	glTranslatef(1.0,0.5,0);
    glColor3f(0, 0, 0);
	draw_head(.5,.5);


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

void gameEnd()
{
	gameEndStatus = true;
	glColor3f(0.3,0.56,0.84);
	glBegin(GL_POLYGON);
	glVertex3f(0.0,0.0,0.0);
	glColor3f(0.24,0.17,0.12);
	glVertex3f(100.0,0.0,0.0);
	glColor3f(0.196,0.196,0.8);
	glVertex3f(100.0,100.0,0.0);
	glVertex3f(0.0,100.0,0.0);
	glEnd();
	glPushMatrix();
	glScalef(0.8,0.8,0);
	glPopMatrix();


	glColor3f(0.24,0.17,0.12);  // disp box
	glRectf(20.0,30.0,70.0,60.0);
	glColor3f(0.45,0.63,0.76);
	glRectf(21.0,31.0,69.0,59.0);




	glColor3f(0.196,0.196,0.8);   //restart button
	glRectf(40,5,60,10);
	glColor3f(0.8,0.8,0.8);
	glRectf(40.5,5.5,59.5,9.5);
	glColor3f(0.137,0.137,0.556);

	drawString(43,6,0,GLUT_BITMAP_TIMES_ROMAN_24,"RESTART");
	drawString(41,51,0,GLUT_BITMAP_TIMES_ROMAN_24,"GAME OVER!!!");
	drawString(23,41,0,GLUT_BITMAP_HELVETICA_18,"DISTANCE :");
	drawString(40,41,0,GLUT_BITMAP_TIMES_ROMAN_24,score_Str);
		printf("\n");
	printf("\n");
	drawString(23,36,0,GLUT_BITMAP_HELVETICA_18,"LEVEL         :");
	drawString(40,36,0,GLUT_BITMAP_TIMES_ROMAN_24,slevel);

	//glutPostRedisplay();

}

void drawBg()
{
	glPushMatrix();

	glColor3f(0.0,0.0,0.00);		// green floor

	glBegin(GL_POLYGON);
	glVertex3f(0.0,9.0,0.0);
	glVertex3f(100.0,9.0,0.0);
	glColor3f(0.0,0.3,0.03);
	glVertex3f(100.0,10.0,0.0);
	glVertex3f(0.0,10.0,0.0);
	glVertex3f(0.0,9.0,0.0);
	glEnd();

	glColor3f(0.474,0.298,0.074);  // brown ground
	glBegin(GL_POLYGON);
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(100.0,0.0,0.0);
	glColor3f(0.3,0.1,0.03);
	glVertex3f(100.0,9.0,0.0);
	glVertex3f(0.0,9.0,0.0);
	glEnd();

	glColor3f(0.5,0.6,0.79);
	glBegin(GL_POLYGON);				//ceiling
	glVertex3f(0.0,100.0,0.0);
	glVertex3f(100.0,100.0,0.0);
	glColor3f(0.6,0.7,0.89);
	glVertex3f(100.0,80.0,0.0);
	glVertex3f(0.0,80.0,0.0);
	glEnd();

	glColor3f(0.5,0.6,0.79);// sky blue
	glBegin(GL_POLYGON);   //background screen
	glVertex3f(0.0,90.0,5.0);
	glVertex3f(100.0,90.0,5.0);
	glColor3f(0.7,0.8,0.99);//sky
	glVertex3f(100.0,10.0,5.0);
	glVertex3f(0.0,10.0,5.0);
	glEnd();

	glPopMatrix();
}

void welcome()
{


    glColor3f(0.1f, 0.0f, 0.0f);

	glBegin(GL_POLYGON);
	glVertex3f(0.0,0.0,0.0);
	glColor3f(0.1f, 0.0f, 0.0f);
	glVertex3f(100.0,0.0,0.0);
	glColor3f(0.196,0.196,0.8);
	glVertex3f(100.0,100.0,0.0);
	glVertex3f(0.0,100.0,0.0);

	glEnd();



    glPushMatrix();

	glColor3f(0.1f, 0.0f, 0.0f);//Brown
	drawString(10.5,92,0,GLUT_BITMAP_TIMES_ROMAN_24,"WELCOME TO OUR COMPUTER GRAPHICS LAB PROJECT");
	    drawBird();

	glPopMatrix();


	glColor3f(0.137,0.137,0.556);

	glColor3f(0.8,0.8,0.8);

	glRectf(40,40,60,45);

	glColor3f(0.137,0.137,0.556);
	drawString(47,42,0,GLUT_BITMAP_TIMES_ROMAN_24,"PLAY");


    glColor3f(1.0,0.0,0.0);

    drawString(20,20,0,GLUT_BITMAP_TIMES_ROMAN_24,"FUN MEMBER : PRODIP@@ ,MUBIN@,SAFA@,SIJAN@");


}

void drawMountain()
{
	glPushMatrix();						// 3D part
	if(buildColor==0)
		glColor3f(0.0,50.0,0.0);
	else if (buildColor ==1)
		glColor3f(0.23,0.48,0.34);
	else
		glColor3f(1.0,1.0,1.0);

	glTranslatef(b.block_x,b.no_height*10.0+10,0.0);

    glBegin(GL_TRIANGLES);

      glVertex2f(5.0f, -b.no_height*10.0f);
      glVertex2f(20.0f, -b.no_height*10.0f);
      glVertex2f(10.5f,0.0f);
      glEnd();

	glPopMatrix();


}

void drawCloud()
{
	glColor3f(0.74,0.83,0.90);
	glTranslatef(s.block_x,s.block_y,0.0);
	glutSolidSphere(5,100,10);
	glTranslatef(6,-3.0,0.0);
	glutSolidSphere(5,100,10);
	glTranslatef(0,6.0,0.0);
	glutSolidSphere(5,100,10);
	glTranslatef(6,-3.0,0.0);
	glutSolidSphere(5,100,10);

}

bool cloudHit()
{
	if(s.block_x < 15 && s.block_x> -5)
		if(bird_move-4+50 >s.block_y-4 && bird_move-3+50 < s.block_y+4)
			return true;

	if(s.block_x < 12 && s.block_x> -4)
		if(bird_move-3+50 >s.block_y-5 && bird_move-3+50 < s.block_y+5)
			return true;

	if(s.block_x < 10 && s.block_x> -1)
		if(bird_move-3+50 >s.block_y-6 && bird_move-3+50 < s.block_y-2)
			return true;


	return false;
}


bool mountainhit()
{
	if (((int)b.block_x<=8 &&(int)b.block_x>=-7 && ((int)bird_move+50)-b.block_y<=3))
		return true;
	else if (((int)b.block_x<=10 &&(int)b.block_x>=-5 && ((int)bird_move+50)-b.block_y<=0))
		return true;
	else if(((int)b.block_x<=6 &&(int)b.block_x>=-3 && ((int)bird_move+47)-b.block_y<=0))
		return true;
	else if(((int)b.block_x<=4 &&(int)b.block_x>=-4 && ((int)bird_move+47)-b.block_y<=3))
		return true;
	else
		return false;
}

bool boundHit()
{
	if(bird_move+50>=100||bird_move+50 <=18)
		return true;
	else
		return false;
}

void printScore()
{
	glColor3f(0.1f, 0.1f, 0.1f);//score

	sprintf(slevel, "%d", (int)level );
	drawString(58,93,0,GLUT_BITMAP_TIMES_ROMAN_10,"Level");
	drawString(58,95,0,GLUT_BITMAP_TIMES_ROMAN_24,slevel);
    score+=0.05;

	drawString(38,93,0,GLUT_BITMAP_TIMES_ROMAN_10,"Distance");
	sprintf(score_Str, "%d cm",(int)score );
	drawString(38,95,0,GLUT_BITMAP_TIMES_ROMAN_24, score_Str);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//GameOver Checking
	if(gameEndStatus == true)
	{
		gameEnd();
	}
	else if(wflag==true)//Welcome Screen
	{
		welcome();
	}

	else if( pause == true)
	{
		drawBg();
		glPushMatrix();
		glScalef(0.8,0.8,0);
		drawBird();
		glPopMatrix();
		glPushMatrix();
		glColor3f(0.196,0.196,0.8);
		glRectf(35.0,40.0,65.0,60.0);
		glColor3f(0.8,0.8,0.8);
		glRectf(36.0,41.0,64.0,59.0);
		glPopMatrix();
		glColor3f(0.137,0.137,0.556);

		glutPostRedisplay();

	}
	else if((b.state == true && mountainhit() == true)|| boundHit()== true)
	{
		gameEndStatus = true;
		gameEnd();
	}
	else if(s.state == true && cloudHit() == true)
	{

		gameEndStatus = true;
		gameEnd();
	}
	else
	{

		if((int)score%50==0 && lflag==true)// l-level
		{
			lflag=false;
			level++;
			bspd+=0.002;
		}
		else if((int)score%50!=0 && lflag==false)
		{
			lflag=true;
		}

		glPushMatrix();
		drawBg();


		glPushMatrix();
		glTranslatef(0.0,bird_move,0.0);
		drawBird();
		glPopMatrix();


		if( (b.state == true && b.block_x < -10) || (s.state == true && s.block_x < -10))            //for new building //building has gone outside the screen- state=true
		{
			srand(time(NULL));
			int random = rand()%2;//for random building or cloud
			if( random == 0)
			{
				Buildingmountain();
			}
			else
			{
				CloudBlock();
			}
		}

		else if(b.state == true)
		{

            b.block_x-=bspd;
		}
		else if( s.state == true)
		{

            s.block_x-=bspd;

		}
		if(b.state == true)
		{
			glTranslatef(b.block_x,0.0,0.0);
			drawMountain();
		}
		else if( s.state == true)
		{
			glTranslatef(s.block_x,0.0,0.0);
			drawCloud();
		}
		glPopMatrix();

		printScore();
	}
	glFlush();
	glutSwapBuffers();
}


void birdUp()
{
	if(start == false)
		glutPostRedisplay();
	else if(pause == false)
	{

		bird_move+=0.05;
		glutPostRedisplay();
	}
}


void birdDown()
{
	if(start == false)
		glutPostRedisplay();
	else if(pause == false )
	{
		bird_move-=0.05;
		glutPostRedisplay();
	}
}



void mouse(int button, int state, int x, int y)
{
	int mx=x*100/SCREENW,my=(SCREENH-y)*100/SCREENH;


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
				if(gameEndStatus)
				{
					wflag = true;
					gameEndStatus = false;
					bird_move = 0;
					start = false;
					init();
					bspd = BLOCKSPEED;//restarting the game
					score=1;
					level=1;
					glutPostRedisplay();
				}

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
				glutIdleFunc(birdUp);

			else if (state == GLUT_UP )
				glutIdleFunc(birdDown);
		}

	}
}
void keyPressed(unsigned char key,int x, int y) // int x and y are mouse pos at time of press
{
	if(key == 'p' || key == 'P')
	{
		if(pause == true)
			pause = false;
		else
			pause = true;
	}
	glutPostRedisplay();
}
void myReshape(int w, int h)
{
	SCREENH=h,SCREENW=w;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 100.0, 0.0, 100.0,	-5.0 , 10.0);
	glMatrixMode(GL_MODELVIEW);
}

void init()
{
	srand(time(0));
	int random = rand()%2;
	if( random == 0)
	{
		Buildingmountain();
	}
	else
	{
		CloudBlock();
	}
}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (SCREENW,SCREENH);
	glutInitWindowPosition (50,50);
	glutCreateWindow ("Bird On The Move");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(myReshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyPressed);
	glutMainLoop();
	return 0;
}

