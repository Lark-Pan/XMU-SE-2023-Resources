#include <GL/glut.h>
#include <iostream>
#include<math.h>

#define PI 3.1415926535

/* ���������� */
GLfloat Vertices[8][3] = { {1,-1,1},{1,-1,-1},{-1,-1,-1},{-1,-1,1},{1,1,1},{1,1,-1},{-1,1,-1},{-1,1,1} }; //��������
GLint Faces[6][4] = { {0,3,7,4},{0,1,5,4},{1,2,6,5},{2,3,7,6},{4,5,6,7},{0,1,2,3} }; // �涥��������
GLfloat Colors[6][3] = { {1, 0, 0},{1, 1, 0} ,{0, 1, 0},{0, 0, 1},{1, 0, 1},{0, 1, 1} }; // ��ɫ

/* ������ת */
GLfloat beta = 0;
GLfloat delta = 1.0; // ��ת�ٶ�

/* ���̽��� */
bool enableMove = true; //�Ƿ���������ƶ�
GLfloat moveSpeed = 0.3;
GLfloat cameraPosX = 0.0f, cameraPosY = 0.0f, cameraPosZ = 10.0f;
GLfloat lookAtX = 0.0f, lookAtY = 0.0f, lookAtZ = -15.0f;

/* ��꽻�� */
GLfloat latestX = 0, latestY = 0;
GLint w = 1000, h = 1000;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);

	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST); //������Ȳ���

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, 1, 0.1, 60); // ѡ��͸���Ӿ���
	//glOrtho(10, -10, 10, -10, 0.1, 60);//ѡ�������Ӿ��壨���ǰ�����������С���䣩
	glMatrixMode(GL_MODELVIEW);

	latestX = w / 2;
	latestY = h / 2;
	glutWarpPointer(w / 2, h / 2);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(cameraPosX, cameraPosY, cameraPosZ,
		lookAtX, lookAtY, lookAtZ,
		0, 1, 0);//�����������

	glRotatef(beta, 1.0, -1.0, -1.0); //��ת

	for (int i = 0; i < 6; i++)//����������
	{
		glColor3fv(Colors[i]);
		glBegin(GL_POLYGON);
		for (int j = 0; j < 4; j++)
			glVertex3fv(Vertices[Faces[i][j]]);
		glEnd();
	}

	glutSwapBuffers();
}


void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void idlefunc()
{
	Sleep(3);
	//�ı䶯������
	beta += delta;
	if (beta > 360) beta -= 360;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	GLfloat move = enableMove ? moveSpeed : 0;
	switch (key) {
	case 27: exit(0); break;//esc�˳�
	case 's': 
		cameraPosZ += move; 
		lookAtZ += move;;//ע�⣬�������ͳ�������Ҫͬ�����ӻ����
		break;
	case 'w':
		cameraPosZ -= move;
		lookAtZ -= move; 
		break;
	case 'd': 
		cameraPosX += move; 
		lookAtX += move; 
		break;
	case 'a': 
		cameraPosX -= move; 
		lookAtX -= move; 
		break;
	case 'q': 
		cameraPosY += move; 
		lookAtY += move;
		break;
	case 'e':
		cameraPosY -= move; 
		lookAtY -= move; 
		break;
	case 'l': 
		enableMove = !enableMove; break; //��������ƶ�
	}
}

void mouse(int x, int y)
{
	if (enableMove)
	{
		lookAtX += (x - latestX) / 25;//�������ָ�������λ�ã��޸������������
		lookAtY += (latestY - y) / 25;
	}
	latestX = x;
	latestY = y;
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutPassiveMotionFunc(mouse);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idlefunc);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
