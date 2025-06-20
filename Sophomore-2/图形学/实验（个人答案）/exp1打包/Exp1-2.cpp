#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#include <GL/freeglut.h>
#endif

//������ת�Ƕ�
static GLfloat spin = 0.0;

// ����Բ��λ�úͰ뾶
float centerX = 0.0f;
float centerY = 0.0f;
float radius = 0.5f;
// �������ڽ���Բ�εĶ�������
const int numVertices = 1000;

// ����ͼ������Ļ�е�ƫ����
float offsetX = 0.3f;
float offsetY = 0.3f;

void display(void)
{
    // �����ɫ������
    glClear(GL_COLOR_BUFFER_BIT);

    // �ı�ͼ������Ļ�е�λ��
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glTranslatef(offsetX, offsetY, 0.0f);

    // ��ʼ���ƶ����������Բ��
    
    for (int j = 1; j <= 8; j++) {
        glBegin(GL_POLYGON);
        for (int i = (numVertices / 8) * (j-1); i < (numVertices / 8) * j; ++i) {
            // ���㵱ǰ����ĽǶ�
            float angle = spin + 2.0f * 3.1415926f * static_cast<float>(i) / static_cast<float>(numVertices);
            // ���㵱ǰ����� x �� y ����
            float x = centerX + radius * cosf(angle);
            float y = centerY + radius * sinf(angle);

            // ָ���������ɫ
           
            glColor3f(0.125f * static_cast<float>(j) , 1.0f - 0.125f * static_cast<float>(j) , 1.0f/ static_cast<float>(j));

            // ָ����ǰ���������
            glVertex2f(x, y);
        }
        glVertex2f(centerX, centerY);
        glEnd();
        
    }
   
    // ˢ�� OpenGL ������
    glutSwapBuffers();
 
}

void spinDisplay(void) {
    spin = spin + 2.0;
    if (spin > 360.0)
        spin = spin - 360.0;
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
                glutIdleFunc(spinDisplay);
            break;
        case GLUT_MIDDLE_BUTTON:
            if (state == GLUT_DOWN)
                glutIdleFunc(NULL);
            break;
        default:
            break;
    }
}

void init()
{
    // ���������ɫΪ��ɫ
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // ����ͶӰ����
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // ��������ͶӰ����ΧΪ -1 �� 1
    glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
}

int main(int argc, char** argv)
{
    // ��ʼ�� GLUT
    glutInit(&argc, argv);
    // ������ʾģʽΪ������� RGB ��ɫģʽ
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    // ���ô��ڴ�С
    glutInitWindowSize(500, 500);
    // ���ô���λ��
    glutInitWindowPosition(0, 0);
    // �������ڣ����ڱ���Ϊ "simple"
    glutCreateWindow("simple");

   
    init();

    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    
    glutMainLoop();

    return 0;
}