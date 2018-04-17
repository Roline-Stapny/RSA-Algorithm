#include<windows.h>
#include<GL/glut.h>
#include<string.h>
#include<iostream>
#include<math.h>
#include<stdio.h>
#include<string>
#include<sstream>

using namespace std;

bool sendPacket=false;
int count=0;

int x=250,df=10;

//rsa functions
stringstream mystream;
long int p=11,q=13,n,z,e,d,temp[100],j,i;

int en[50],m[50],len;
string encyptedmsg;
string decryptedmsg;
std::string message;

void RSAlgo();


void init()
{
    glClearColor(1.0,0.921,0.803,0.5);
    glClear(GL_COLOR_BUFFER_BIT | GL_DOUBLE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,1000,0,1000);
    glFlush();
}




void displayDetails(std::string s, int x, int y)
{
    glColor3f(1.0f, 0.0f, 0.0f);//needs to be called before RasterPos
    glRasterPos2i(x, y);
    void * font = GLUT_BITMAP_TIMES_ROMAN_24;
    //GLUT_BITMAP_9_BY_15;

    //for (std::string::iterator i = s.begin(); i != s.end(); ++i)
     for(int i=0; i<s.length() ; i++)
    {
        char c = s[i];
        //this does nothing, color is fixed for Bitmaps when calling glRasterPos
        //glColor3f(1.0, 0.0, 1.0);
        glutBitmapCharacter(font, c);
    }

    glEnable(GL_TEXTURE_2D);


}

void drawHead(float x1, float y1,double radius)
{
    float x2,y2;
    float angle;

     glColor3f(1.0,0.64,0);

     glBegin(GL_TRIANGLE_FAN);
     glVertex2f(x1,y1);

     for (angle=1.0f;angle<361.0f;angle+=0.2)
    {
        x2 = x1+sin(angle)*radius;
        y2 = y1+cos(angle)*radius;
        glVertex2f(x2,y2);
    }

    glEnd();

    glFlush();

}

void displayHeadings()
{

    displayDetails("Enter Message",25,600);
    displayDetails("RSA ALGORITHM",300,960);
    displayDetails("Decrypted Message",850,600);
    displayDetails("---Help Alice to send secure message to bob",450,960);
}



void drawInitial()
{

     displayHeadings();
    //left screen
    //outer rect
 glColor3f(0.50,0.50,0.50);
      glBegin(GL_POLYGON);
          glVertex2f(200,600);
          glVertex2f(350,600);
          glVertex2f(350,450);
          glVertex2f(200,450);
      glEnd();
      //inner rect
      glColor3f(0.529,0.80,0.98);
      glBegin(GL_POLYGON);
          glVertex2f(220,580);
          glVertex2f(330,580);
          glVertex2f(330,470);
          glVertex2f(220,470);
      glEnd();
    //dots
      glColor3f(1,1,1);
      glPointSize(3);
      glBegin(GL_POINTS);
        glVertex2f(275,460);
         glVertex2f(265,460);
          glVertex2f(285,460);
      glEnd();
     //stand
      glColor3f(0.50,0.50,0.50);
      glBegin(GL_POLYGON);
         glVertex2f(170,430);
         glVertex2f(380,430);
         glVertex2f(380,400);
         glVertex2f(170,400);
      glEnd();

      //coonect stand and monitor
      glBegin(GL_POLYGON);
          glVertex2f(260,430);
          glVertex2f(290,430);
          glVertex2f(290,450);
          glVertex2f(260,450);
      glEnd();


    //right screen
     glColor3f(0.50,0.50,0.50);
      glBegin(GL_POLYGON);
          glVertex2f(650,600);
          glVertex2f(800,600);
          glVertex2f(800,450);
          glVertex2f(650,450);
      glEnd();

      glColor3f(0.529,0.80,0.98);
      glBegin(GL_POLYGON);
          glVertex2f(670,580);
          glVertex2f(780,580);
          glVertex2f(780,470);
          glVertex2f(670,470);
      glEnd();


       glColor3f(1,1,1);
      glPointSize(3);
      glBegin(GL_POINTS);
        glVertex2f(725,460);
         glVertex2f(715,460);
          glVertex2f(735,460);
      glEnd();


    glColor3f(0.50,0.50,0.50);
      glBegin(GL_POLYGON);
         glVertex2f(620,400);
         glVertex2f(830,400);
         glVertex2f(830,430);
         glVertex2f(620,430);
      glEnd();

       glBegin(GL_POLYGON);
          glVertex2f(710,430);
          glVertex2f(740,430);
          glVertex2f(740,450);
          glVertex2f(710,450);
      glEnd();

     //dotted line
      glPushAttrib(GL_ENABLE_BIT);
     glLineWidth(1);
     glLineStipple(2, 0xAAAA);  //# [1]   16 bit integer that determines vch fragment of line is drawn
     glEnable(GL_LINE_STIPPLE);

     glBegin(GL_LINES);
     glVertex2f(350,490);
     glVertex2f(650,490);
     glEnd();

      glPopAttrib();



   //drawing alice
    glColor3f(0.60,0.80,0.19);
   glBegin(GL_POLYGON);
      glVertex2f(250,790);
      glVertex2f(270,790);
      glVertex2f(310,680);
      glVertex2f(210,680);

   glEnd();
   drawHead(260,820,35);

   //drawing hands
   glLineWidth(2);
   glBegin(GL_LINES);
       glVertex2f(244,765);
       glVertex2f(225,765);
   glEnd();

  glBegin(GL_LINES);
       glVertex2f(276,765);
       glVertex2f(295,765);
  glEnd();

     //draw legs
     glBegin(GL_LINES);
          glVertex2f(240,680);
          glVertex2f(240,661);
     glEnd();

      glBegin(GL_LINES);
          glVertex2f(280,680);
          glVertex2f(280,661);
     glEnd();

     displayDetails("Alice",240,725);

     //draw eyes
     glColor3f(0,0,0);
     glPointSize(6);
     glBegin(GL_POINTS);
         glVertex2f(250,835);
         glVertex2f(270,835);

         glVertex2f(260,810);
     glEnd();

   //draw prison
   glColor3f(0,0,0);
    glBegin(GL_LINES);
      glVertex2f(180,655);
      glVertex2f(180,865);

      glVertex2f(190,655);
      glVertex2f(190,865);

      glVertex2f(200,655);
      glVertex2f(200,865);

      glVertex2f(210,655);
      glVertex2f(210,865);

      glVertex2f(220,655);
      glVertex2f(220,865);

      glVertex2f(230,655);
      glVertex2f(230,865);

      glVertex2f(240,655);
      glVertex2f(240,865);

      glVertex2f(250,655);
      glVertex2f(250,865);

      glVertex2f(260,655);
      glVertex2f(260,865);

      glVertex2f(270,655);
      glVertex2f(270,865);

      glVertex2f(280,655);
      glVertex2f(280,865);
      glVertex2f(290,655);
      glVertex2f(290,865);

      glVertex2f(300,655);
      glVertex2f(300,865);

      glVertex2f(310,655);
      glVertex2f(310,865);

      glVertex2f(320,655);
      glVertex2f(320,865);

      glVertex2f(330,655);
      glVertex2f(330,865);
    glEnd();


    //drawing bob
     glColor3f(0.60,0.80,0.19);
    glBegin(GL_POLYGON);
        glVertex2f(670,680);
        glVertex2f(760,680);
        glVertex2f(760,790);
        glVertex2f(670,790);

    glEnd();
    //bobs head
    drawHead(715,820,35);

     glLineWidth(2);
   glBegin(GL_LINES);
       glVertex2f(670,765);
       glVertex2f(651,765);
   glEnd();

  glBegin(GL_LINES);
       glVertex2f(760,765);
       glVertex2f(779,765);
  glEnd();

     //draw legs
     glBegin(GL_LINES);
          glVertex2f(700,680);
          glVertex2f(700,661);
     glEnd();

      glBegin(GL_LINES);
          glVertex2f(730,680);
          glVertex2f(730,661);
     glEnd();


      displayDetails("Bob",700,725);
     //draw eyes
      glColor3f(0,0,0);
     glPointSize(6);
     glBegin(GL_POINTS);
         glVertex2f(705,835);
         glVertex2f(725,835);

         glVertex2f(715,810);
     glEnd();
    glFlush();


}



void sendFunction()
{
    if(sendPacket && count<5)
      {
          displayDetails("Cypher text:",410,400);
          displayDetails(encyptedmsg,500,400);

          displayDetails("p = ",800,290);
          mystream.str(string());
          mystream.clear();
          mystream << p;
          displayDetails(mystream.str(),840,290);

          displayDetails("q = ",800,240);
          mystream.str(string());
          mystream.clear();
          mystream<<q;
          displayDetails(mystream.str(),840,240);



          displayDetails("phi = ",800,190);
           mystream.str(string());
          mystream.clear();
          mystream<<z;
          displayDetails(mystream.str(),840,190);


          displayDetails("public key = ",200,350);
           mystream.str(string());
          mystream.clear();
          mystream<<d;
          displayDetails(mystream.str(),300,350);

          //draw lock

          drawHead(175,350,20);
          glColor3f(0.75,0.75,0.75);
          glBegin(GL_POLYGON);
             glVertex2f(150,350);
             glVertex2f(200,350);
             glVertex2f(200,300);
             glVertex2f(150,300);
          glEnd();

          glColor3f(0,0,0);
          glPointSize(6);
          glBegin(GL_POINTS);
              glVertex2f(175,325);
          glEnd();

          displayDetails("private key = ",700,350);
           mystream.str(string());
          mystream.clear();
          mystream<<e;
          displayDetails(mystream.str(),800,350);

           //draw key
           glColor3f(0,0,0);
           glBegin(GL_POLYGON);
               glVertex2f(640,350);
               glVertex2f(690,350);
               glVertex2f(690,360);
               glVertex2f(640,360);
           glEnd();

           glLineWidth(6);
            glBegin(GL_LINES);
                glVertex2f(675,350);
                glVertex2f(675,340);
           glEnd();

            glBegin(GL_LINES);
                glVertex2f(685,350);
                glVertex2f(685,340);
           glEnd();

           glColor3f(0.7,0.6,0.8);
           glPushMatrix();
           glTranslatef(1.5f, 1.5f, 0.0f);
           glBegin(GL_POLYGON);
             glVertex2f(x,510);
             glVertex2f(x+50,510);
             glVertex2f(x+50,530);
             glVertex2f(x,530);
           glEnd();
           glPopMatrix();


           x=x+20;
           if(x>700)
           {
              x=250;
              count++;
           }
        //to give some delay
        int c, d;

          for (c = 1; c <= 32767; c++)
          for (d = 1; d <= 327; d++)
       //{}
        glutPostRedisplay();

      }
      else if(sendPacket==true && count ==5)
      {
           glColor3f(0.18, 0.30, 0.30);
          displayDetails(decryptedmsg,850,550);

          sendPacket=false;
      }


}

void output(int x, int y, char *string)
{
      int len, i;

           glRasterPos2f(x,y);
           len=(int) strlen(string);
           for (i = 0; i < len; i++)
			{
             glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
			}
}

void drawstring(int x, int y, char *string,void *font)
{
      int len, i;

           glRasterPos2f(x,y);
           len=(int) strlen(string);
           for (i = 0; i < len; i++)
			{
             glutBitmapCharacter(font,string[i]);
			}
}
void frontscreen(void)
{
    glColor3f(0.1,0.1,0.1);
	output(300,950,"NMAM INSTITUTE OF TECHNOLOGY");
	glColor3f(0.1,0.1,0.1);
	output(200,900,"DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
	glColor3f(1,0,1);
	output(200,700,"A Mini Project On:-");
	glColor3f(0.8,0,0.3);
	output(350,700,"\"Depicting RSA Algorithm using OpenGL\"");
	glColor3f(1,0,1);
	output(200,550,"Developed By :");
	glBegin(GL_LINES);
	glVertex2f(200,530);
	glVertex2f(290,530);
	glEnd();
	glColor3f(1,0,0);
	output(330,550,"Roline Stapny Saldanha and Amruthavarshini M R ");


	glColor3f(1,0,1);
	output(200,400,"Under the Guidence of :");
	glBegin(GL_LINES);
	glVertex2f(200,390);
	glVertex2f(390,390);
	glEnd();

	glColor3f(1,0,0);
	drawstring(400,400,"(M.Tech)",GLUT_BITMAP_HELVETICA_12);
	glColor3f(1,0,0);
	output(400,350,"Mr.Pawan Hegde,Dept. of CSE");

    glColor3f(0,0,0);
    drawstring(700,100," Press ENTER to go To next screen",GLUT_BITMAP_HELVETICA_18);

    glFlush();
	glutSwapBuffers();

}

 void Done()
 {

	glColor3f(0.89,0,0.133);
	 drawstring(400,600," CONGRATS!!!!!!!!!!!!! ",GLUT_BITMAP_TIMES_ROMAN_24);

	glColor3f(0,0.18,0.38);
	output(400,500,"YOU SAVED ALICE'S LIFE");
	 output(400,400,"* PRESS 1 TO EXIT ");
	glutSwapBuffers();
 }


void instructions()
{
  glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.11,0.266,0.29);
    output(350,900,"INSTRUCTIONS:");
	glBegin(GL_LINES);
	glVertex2f(350,890);
	glVertex2f(470,890);
	glEnd();
	glColor3f(0.8,0.33,0.0);
  output(100,700,"* ALICE IS KIDNAPPED AND SHE NEEDS TO INFORM HER FRIEND BOB ABOUT IT.");
  output(100,600,"* HELP ALICE TO SEND SECURE 'HELP' MESSAGE TO BOB USING RSA ALGORITHM");
  output(100,500,"* TYPE THE MESSAGE ON BEHALF OF ALICE");
  output(100,400,"* PRESS ENTER TO ENCRYPT AND TRANSMIT THE MESSAGE");
  output(100,300,"* BOB WILL HAVE THE KEY TO DECRYPT THE MESSAGE");
  output(100,200,"* USE  MOUSE RIGHT CLICK TO RESET, CHANGE THE KEY (using console), EXIT");
  output(100,100,"* PRESS 1 TO START");
   glutSwapBuffers();
}


void display()
{

   glClear(GL_COLOR_BUFFER_BIT |  GLUT_RGB );   // Clear the color buffer

   if(df==10)
   {

	frontscreen();
   }

    else if(df==2)
        instructions();
    else if(df==4)
    {
        drawInitial();
        sendFunction();
        glutSwapBuffers();
    }
	else if(df==5)
	{
		Done();
	}

}
void keyboardFunc(unsigned char key, int x, int y)
{
     if(df==10 && key==13)
     {
            df=2;
            glutPostRedisplay();
     }
     else if(df==2 && key=='1')
    {
       df=4;
       count=0;
        sendPacket=false;
        message="";
        encyptedmsg="";
        decryptedmsg="";
        glClear(GL_COLOR_BUFFER_BIT | GLUT_RGB);
        glutSwapBuffers();
        glClear(GL_COLOR_BUFFER_BIT | GLUT_RGB);
       key=' ';
	   glutPostRedisplay();
    }
     else if(df==5 && key=='1')
    {
         exit(0);
    }

    if(df==4)
    {


    if(count==0 )
    {
        drawInitial();
        if(key==13)
        {
            cout<<"sending";
            sendPacket=true;


            //calling rsa algorithm
            RSAlgo();




            char c;
            for(i=0;en[i]!=-1;i++)
            {
                c=(char)en[i];
                cout<<en[i]<<endl;
                encyptedmsg.push_back(c);
            }
            cout<<encyptedmsg;

            for(i=0;m[i]!=-1;i++)
            {
                c=(char)m[i];
                cout<<m[i]<<endl;
                decryptedmsg.push_back(c);
            }
            cout<<decryptedmsg;
            sendFunction();

        }

        message.push_back(key);
        glColor3f(0.18, 0.30, 0.30);
        glRasterPos2i(25, 550);
        void * font = GLUT_BITMAP_TIMES_ROMAN_24;
      for (std::string::iterator i = message.begin(); i != message.end(); ++i)
      {
            char c = *i;
            glutBitmapCharacter(font, c);
      }
    //glEnable(GL_TEXTURE_2D);
      glFlush();
     glutSwapBuffers();

      glClear(GL_COLOR_BUFFER_BIT | GL_RGB);
    }

    }


}



int prime(long int pr)
{
    int i;
    j=sqrt(pr);
    for(i=2;i<=j;i++)
    {
         if(pr%i==0)
         return 0;
    }
 return 1;

}



void menu(int value)
{
    if(value==1)
    {
        count=0;
        sendPacket=false;
        message="";
        encyptedmsg="";
        decryptedmsg="";
        glClear(GL_COLOR_BUFFER_BIT | GLUT_RGB);
        glutSwapBuffers();
        glClear(GL_COLOR_BUFFER_BIT | GLUT_RGB);
        glutPostRedisplay();
    }
    else if(value==2)
    {
        count=0;
        sendPacket=false;
        message="";
        encyptedmsg="";
        decryptedmsg="";
       glClear(GL_COLOR_BUFFER_BIT | GLUT_RGB);
        glutSwapBuffers();
        glClear(GL_COLOR_BUFFER_BIT | GLUT_RGB);


        printf("\n**********Changing keys**********");
        do
        {
             printf("\nenter 2 prime numbers ");
             scanf("%d%d",&p,&q);
        }
        while(!prime(p) || !prime(q));
        printf("\n**********Keys changed**********");
        glutPostRedisplay();


    }
    else if(value==3)
    {
        df=5;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(1000,1000);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutCreateWindow("RSA ALGORITHM");
    init();

    glutCreateMenu(menu);
    glutAddMenuEntry("Reset",1);

    glutAddMenuEntry("change the key ",2);
    glutAddMenuEntry("exit",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutKeyboardFunc(keyboardFunc);
    glutDisplayFunc(display);


    glutMainLoop();
    glFlush();


 return 0;

}


int prime(int a)
{
    int i;
    for(i=2; i<sqrt(a); i++)
    {
        if((a%i)==0)
            return 0;
    }
    return 1;
}
int gcd(int a, int b)
{
    int r=b%a;
    if(r==0)
        return a;
    else
    {
         b=a;
         a=r;

         gcd(a,b);
    }
}


void RSAlgo()
{
    n=p*q;
    z=(p-1)*(q-1);

    e=1;
    do
    {
        e++;
    }while(e<z && gcd(e,z)!=1 );   // e is the private key

    for(d=1; d<n; d++)             // d is the public key
    {
        if((e*d)%z==1)
            break;
    }

    len=message.length();

    for( i=0; i<len; i++ )
    {
        en[i]=1;
        for(j=0; j<e; j++)
        {
            en[i]=(en[i]*message[i])%n;
        }
    }
    en[i]=-1;
    for(i=0; i<len; i++)
    {
        m[i]=1;
        for(j=0; j<d; j++)
        {
            m[i]=(m[i]*en[i])%n;
        }
    }
    m[i]=-1;


}
