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
 * 地面を描く
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
	//モデルを変形
#ifdef WIN32
	FrameMoveByTime(g_pModel, timeGetTime()/1000);
#elif LINUX
	FrameMoveByTime(g_pModel, gettimeofday_sec());
#endif
	glutPostRedisplay();
}

/*
 * 画面表示
 */
void display(void)
{
  static double r;
  static GLfloat lightpos[] = { 3.0, 4.0, 5.0, 1.0 }; /* 光源の位置 */

  /* 画面クリア */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* モデルビュー変換行列の初期化 */
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  /* 光源の位置を設定 */
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

  /* 視点の移動（物体の方を奥に移す）*/
  gluLookAt(30.0, 30.0, 30.0,
	  0.0, 0.0, 0.0,
	  0.0, 1.0, 0.0);
  glRotated(r, 0.0, 1.0, 0.0);
  /* 地面 */
  myGround(-1.8);

  //Xファイルからよみこんだモデルを表示
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
  /* ウィンドウ全体をビューポートにする */
  glViewport(0, 0, w, h);

  /* 透視変換行列の指定 */
  glMatrixMode(GL_PROJECTION);

  /* 透視変換行列の初期化 */
  glLoadIdentity();
  gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);

  /* モデルビュー変換行列の指定 */
  glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y)
{
  switch (button) {
  case GLUT_LEFT_BUTTON:
    glutIdleFunc(idle); //アニメーション開始
    //初期時間を設定
#ifdef WIN32
    SetStartTime(g_pModel, timeGetTime()/1000);
#elif LINUX
    SetStartTime(g_pModel, gettimeofday_sec());
#endif //WIN32
    break;
  case GLUT_MIDDLE_BUTTON:
    glutIdleFunc(0); //アニメーション停止
    break;
  case GLUT_RIGHT_BUTTON:
    if(state == GLUT_DOWN){
      FrameMoveOneStep(g_pModel);
      glutPostRedisplay(); //コマ送り
    }
    break;
  default:
    break;
  }
}

void keyboard(unsigned char key, int x, int y)
{
  /* ESC か q をタイプしたら終了 */
  if (key == '\033' || key == 'q') {
    exit(0);
  }
}

void init(void)
{
  /* 初期設定 */
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glCullFace(GL_BACK); //背面のポリゴンを消去

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
