#include <GL/freeglut.h>
#include <iostream>
#include <cmath>

// ���������ε���������
struct Point {
    float x;
    float y;
};

// ����������е�
Point midpoint(const Point& p1, const Point& p2) {
    return { (p1.x + p2.x) / 2, (p1.y + p2.y) / 2 };
}

// �ݹ���� Sierpinski �ε�
void drawSierpinski(Point a, Point b, Point c, int depth) {
    if (depth == 0) {
        // ����������
        glBegin(GL_TRIANGLES);
        glVertex2f(a.x, a.y);
        glVertex2f(b.x, b.y);
        glVertex2f(c.x, c.y);
        glEnd();
    }
    else {
        // �����е�
        Point ab = midpoint(a, b);
        Point bc = midpoint(b, c);
        Point ca = midpoint(c, a);

        // �ݹ����������������
        drawSierpinski(a, ab, ca, depth - 1);
        drawSierpinski(ab, b, bc, depth - 1);
        drawSierpinski(ca, bc, c, depth - 1);
    }
}

// ȫ�ֱ������ڿ��ƶ���
float rotationAngle = 0.0f;
float scaleFactor = 1.0f;
float colorOffset = 0.0f;
const float colorChangeSpeed = 0.01f;
const float rotationSpeed = 0.5f;
const float scaleSpeed = 0.001f;
const float scaleRange = 0.2f;

// ��ʾ�ص�����
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // ������ɫ
    float r = std::sin(colorOffset);
    float g = std::sin(colorOffset + 2.0f);
    float b = std::sin(colorOffset + 4.0f);
    glColor3f(r, g, b);

    // ���ñ任����
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
    glScalef(scaleFactor, scaleFactor, 1.0f);

    // �����ʼ�����εĶ���
    Point a = { -0.8f, -0.8f };
    Point baseB = { 0.8f, -0.8f };
    Point c = { 0.0f, 0.8f };

    // �ݹ����
    int depth = 5;

    // ���� Sierpinski �ε�
    drawSierpinski(a, baseB, c, depth);

    glutSwapBuffers();
}

// ��ʱ���ص����������ڸ��¶���״̬
void timer(int value) {
    // ������ɫƫ��
    colorOffset += colorChangeSpeed;

    // ������ת�Ƕ�
    rotationAngle += rotationSpeed;
    if (rotationAngle >= 360.0f) {
        rotationAngle -= 360.0f;
    }

    // ������������
    scaleFactor = 1.0f + scaleRange * std::sin(glutGet(GLUT_ELAPSED_TIME) * scaleSpeed);

    // ��Ǵ�����Ҫ�ػ�
    glutPostRedisplay();

    // �ٴ����ö�ʱ��
    glutTimerFunc(16, timer, 0);
}

// ��ʼ�� OpenGL ����
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

// ������
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Animated Sierpinski Gasket");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}