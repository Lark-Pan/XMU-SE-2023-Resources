#include <GL/glut.h>
#include <GL/GL.h>
#include <cmath>
#include <ctime>

#define PI 3.1415926535
#define LINE_NUM 40 //����γ�ߵ�����
#define N 100 // ����Բ�Ķ�����

/* ������� */
GLfloat theta = 0, fai = 0;
GLfloat radius = 2;

/* ������ת */
GLfloat beta = 0;
GLfloat delta = 1.0; // ��ת�ٶ�

/* ���̽��� */
bool enableMove = true; //�Ƿ���������ƶ�
GLfloat moveSpeed = 0.1;
GLfloat cameraPosX = 0.0f, cameraPosY = 0.0f, cameraPosZ = 5.0f;
GLfloat lookAtX = 0.0f, lookAtY = 0.0f, lookAtZ = -10.0f;

/* ��꽻�� */
GLfloat latestX = 0, latestY = 0, latestZ = 0;
GLint w = 1000, h = 1000;

GLfloat aspectRatio = 1.0;// ���洰�ڵĿ�߱�

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);

	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST); //������Ȳ���

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, 1, 0.1, 60); // ѡ��͸���Ӿ���
	glMatrixMode(GL_MODELVIEW);

	latestX = w / 2;
	latestY = h / 2;
	glutWarpPointer(w / 2, h / 2);
}

GLfloat* getRandomColor()
{
	srand((unsigned)time(NULL));

	GLfloat* colors = new GLfloat[3];

	colors[0] = (double)rand() / (RAND_MAX);
	colors[1] = (double)rand() / (RAND_MAX);
	colors[2] = (double)rand() / (RAND_MAX);

	return colors;
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(cameraPosX, cameraPosY, cameraPosZ,
		lookAtX, lookAtY, lookAtZ,
		0, 1, 0); // �����������ת

	glRotatef(beta, 1.0, -1.0, -1.0); //��ת

	if (aspectRatio < 1.0) 
		glScalef(aspectRatio, aspectRatio, aspectRatio); //����

	GLfloat x, y, z;
	//�����߿�����
	for (int i = 0; i <= LINE_NUM; i++)
	{
		glColor3fv(getRandomColor());//�����ɫ

		// ���ƾ���
		theta = 2 * PI * i / LINE_NUM;//����i���÷����theta
		glBegin(GL_LINE_STRIP);
		for (int j = 0; j <= N; j++)//���Ƶ�ǰ�����theta�ľ���
		{
			fai = PI * j / N;							//���ϸ��¼��������϶��������
			x = radius * sin(fai) * cos(theta);//������Ĳ������̼���
			y = radius * sin(fai) * sin(theta);//������뾶������fai�ͷ����theta���㶥�������
			z = radius * cos(fai);
			glVertex3f(x, y, z);
		}
		glEnd();
		// ����γ��
		fai = PI * i / LINE_NUM;//����i���ü���fai
		glBegin(GL_LINE_STRIP);
		for (int j = 0; j <= N; j++)//���Ƶ�ǰ����fai��γ��
		{
			theta = 2 * PI * j / N;					//���ϸ��·���������϶��������
			x = radius * sin(fai) * cos(theta);
			y = radius * sin(fai) * sin(theta);
			z = radius * cos(fai);
			glVertex3f(x, y, z);
		}
		glEnd();
	}
	
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);//�޸��ӿڿ��
	aspectRatio = (GLfloat)w / (GLfloat)h;

	// ����ͶӰ����
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80.0, aspectRatio, 1.0, 60.0);//���ݴ��ڿ�߱ȵ����Ӿ���Ŀ�߱�
	glMatrixMode(GL_MODELVIEW);
}

void idlefunc()
{
	//�ı䶯������
	beta += delta;
	if (beta > 360) beta -= 360;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)//ʵ�������������task2��ͬ
{
	GLfloat move = enableMove ? moveSpeed : 0;
	switch (key) {
	case 27: exit(0); break;
	case 's': cameraPosZ += move; lookAtZ += move; break;
	case 'w': cameraPosZ -= move; lookAtZ -= move; break;
	case 'd': cameraPosX += move; lookAtX += move; break;
	case 'a': cameraPosX -= move; lookAtX -= move; break;
	case 'q': cameraPosY += move; lookAtY += move; break;
	case 'e': cameraPosY -= move; lookAtY -= move; break;
	case 'l': enableMove = !enableMove; break; //��������ƶ�
	}
}

void mouse(int x, int y)
{
	if (enableMove)
	{
		lookAtX += (x - latestX) / 25;
		lookAtY += (latestY - y) / 25;
	}
	latestX = x;
	latestY = y;
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(w, h);
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
