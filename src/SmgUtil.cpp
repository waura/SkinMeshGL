#include "SkinMeshGL/SmgUtil.h"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

void RenderLine(int line_width, const SmgVertex* startPt, const SmgVertex* endPt)
{
	glLineWidth(line_width);
	glBegin(GL_LINES);
	glVertex3d(startPt->_d[0], startPt->_d[1], startPt->_d[2]);
	glVertex3d(endPt->_d[0], endPt->_d[1], endPt->_d[2]);
	glEnd();
}