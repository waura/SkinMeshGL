#define LINUX 1
#ifdef WIN32
	#include "Windows.h"
#elif LINUX
        #include <time.h>
        #include <sys/time.h>

double gettimeofday_sec()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + (double)tv.tv_usec*1e-6;
}
#endif //WIN32

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

#include <stdlib.h>
#include "SkinMeshGL/XFileLoad.h"

SmgModel* g_pModel=NULL;

/*
 * $BCOLL$rIA$/(B
 */
void myGround(double height)
{
  static GLfloat ground[][4] = {
    { 0.6, 0.6, 0.6, 1.0 },
    { 0.3, 0.3, 0.3, 1.0 }
  };

  int i, j;

  glBegin(GL_QUADS);
  glNormal3d(0.0, 1.0, 0.0);
  for (j = -5; j <= 5; ++j) {
    for (i = -5; i < 5; ++i) {
      glMaterialfv(GL_FRONT, GL_DIFFUSE, ground[(i + j) & 1]);
      glVertex3d((GLdouble)i, height, (GLdouble)j);
      glVertex3d((GLdouble)i, height, (GLdouble)(j + 1));
      glVertex3d((GLdouble)(i + 1), height, (GLdouble)(j + 1));
      glVertex3d((GLdouble)(i + 1), height, (GLdouble)j);
    }
  }
  glEnd();
}

void idle(void)
{
	//$B%b%G%k$rJQ7A(B
#ifdef WIN32
	FrameMoveByTime(g_pModel, timeGetTime()/1000);
#elif LINUX
	FrameMoveByTime(g_pModel, gettimeofday_sec());
#endif
	glutPostRedisplay();
}

/*
 * $B2hLLI=<((B
 */
void display(void)
{
  static double r;
  static GLfloat lightpos[] = { 3.0, 4.0, 5.0, 1.0 }; /* $B8w8;$N0LCV(B */

  /* $B2hLL%/%j%"(B */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* $B%b%G%k%S%e!<JQ499TNs$N=i4|2=(B */
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  /* $B8w8;$N0LCV$r@_Dj(B */
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

  /* $B;kE@$N0\F0!JJ*BN$NJ}$r1|$K0\$9!K(B*/
  gluLookAt(30.0, 30.0, 30.0,
	  0.0, 0.0, 0.0,
	  0.0, 1.0, 0.0);
  glRotated(r, 0.0, 1.0, 0.0);
  /* $BCOLL(B */
  myGround(-1.8);

  //X$B%U%!%$%k$+$i$h$_$3$s$@%b%G%k$rI=<((B
  RenderSmgModelGL(g_pModel, DRAW_POLY);

  //glFlush();
  glutSwapBuffers();

  r += 1.0;
  if(r > 360.0){
	  r=0.0;
  }
}

void resize(int w, int h)
{
  /* $B%&%#%s%I%&A4BN$r%S%e!<%]!<%H$K$9$k(B */
  glViewport(0, 0, w, h);

  /* $BF);kJQ499TNs$N;XDj(B */
  glMatrixMode(GL_PROJECTION);

  /* $BF);kJQ499TNs$N=i4|2=(B */
  glLoadIdentity();
  gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);

  /* $B%b%G%k%S%e!<JQ499TNs$N;XDj(B */
  glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y)
{
  switch (button) {
  case GLUT_LEFT_BUTTON:
    glutIdleFunc(idle); //$B%"%K%a!<%7%g%s3+;O(B
    //$B=i4|;~4V$r@_Dj(B
#ifdef WIN32
    SetStartTime(g_pModel, timeGetTime()/1000);
#elif LINUX
    SetStartTime(g_pModel, gettimeofday_sec());
#endif //WIN32
    break;
  case GLUT_MIDDLE_BUTTON:
    glutIdleFunc(0); //$B%"%K%a!<%7%g%sDd;_(B
    break;
  case GLUT_RIGHT_BUTTON:
    if(state == GLUT_DOWN){
      FrameMoveOneStep(g_pModel);
      glutPostRedisplay(); //$B%3%^Aw$j(B
    }
    break;
  default:
    break;
  }
}

void keyboard(unsigned char key, int x, int y)
{
  /* ESC $B$+(B q $B$r%?%$%W$7$?$i=*N;(B */
  if (key == '\033' || key == 'q') {
    exit(0);
  }
}

void init(void)
{
  /* $B=i4|@_Dj(B */
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glCullFace(GL_BACK); //$BGXLL$N%]%j%4%s$r>C5n(B

  ////XLex-test
  //XFILE_TOKENS* pTokens = XLexFmtTxt("model\\model3.x");
  //DumpTokens(pTokens);
  //ReleaseTokens(&pTokens);

  //g_pModel = XFileLoad("model/model2.x");
  //g_pModel = XFileLoad("model/model3.x");
  //g_pModel = XFileLoad("model\\robo.x");
  //g_pModel = XFileLoad("model\\tiny.x");
  //g_pModel = XFileLoad("model\\4-1.x");
  g_pModel = XFileLoad("model/4-1-2.x");
  //g_pModel = XFileLoad("model\\4-4.x");
  //g_pModel = XFileLoad("model/Robot_Action.x");
  //g_pModel = XFileLoad("model\\Robot_Action2.x");
  //g_pModel = XFileLoad("model\\Robot_Action3.x");
  //g_pModel = XFileLoad("model\\Robot_Action4.x");
  //g_pModel = XFileLoad("model/cube-move.x");
  //g_pModel = XFileLoad("model\\cube-rot.x");
  //g_pModel = XFileLoad("model\\cube-rot2.x");
  //g_pModel = XFileLoad("model\\cube-scale.x");
  //g_pModel = XFileLoad("model\\tset-FrameAnim.x");
  //g_pModel = XFileLoad("model\\tset-FrameAnim2.x");
  //g_pModel = XFileLoad("model\\robo_scene.x");
  if(g_pModel == NULL){
    exit(1);
  }
  //DumpSmgModel(g_pModel);
  DumpSmgFrameHierarchy(g_pModel->pRootFrame, 0);
  GenSmgModelTexture(g_pModel);
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMouseFunc(mouse);
  glutKeyboardFunc(keyboard);
  init();
  glutMainLoop();
  ReleaseSmgModel(&g_pModel);
  return 0;
}
