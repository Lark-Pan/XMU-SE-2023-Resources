#pragma once

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <iostream>
using namespace std;
#define PI 3.1415927

extern Eigen::Matrix4f mModelView;
extern Eigen::Matrix4f mProjection;
extern Eigen::Matrix4f mViewPort;


void Test()
{
	//�����÷�
	Eigen::Matrix4f m;
	m.setZero();
	m(0, 0) = 1;
	m(3, 3) = 1;
	m(1, 1) = 2.3;   m(1, 2) = 0.99;
	m(2, 1) = 1.1;   m(2, 2) = 0;
	cout << "Matrix:" << endl;
	cout << m << endl;

	//�����÷�
	Eigen::Vector4f v;
	v[0] = 1.0;
	v[1] = 2.0;
	v[2] = 3.0;
	v[3] = 1.0;
	//v[4] = 1.0;
	v.normalize();//��һ��

	//���������������˵Ľ��
	cout << "result:" << endl;
	cout << m * v << endl;
}

vector<Eigen::Vector3f> VertexTransform(vector<Eigen::Vector3f> vertices)
{
	vector<Eigen::Vector3f> rlt(vertices.size());
	Eigen::Vector4f v;

	Eigen::Matrix4f M = mViewPort * mProjection * mModelView;

	for (int i = 0; i < vertices.size(); ++i)
	{
		v[3] = 1.0;
		v.head<3>() = vertices[i];

		v = M * v;
		rlt[i][0] = v[0] / v[3];
		rlt[i][1] = v[1] / v[3];
		rlt[i][2] = v[2] / v[3];
	}
	return rlt;
}

Eigen::Matrix4f myLookAt(float ex, float ey, float ez, float atx, float aty, float atz, float upx, float upy, float upz)
{
	Eigen::Matrix4f m;
	m.setZero();

	//��������հ״���ɴ˺���
	
	Eigen::Vector3f eye(ex, ey, ez);
	Eigen::Vector3f target(atx, aty, atz);
	Eigen::Vector3f up(upx, upy, upz);

	Eigen::Vector3f z_axis = (eye - target).normalized();
	Eigen::Vector3f x_axis = up.cross(z_axis).normalized();
	Eigen::Vector3f y_axis = z_axis.cross(x_axis).normalized();

	Eigen::Matrix4f rotation;
	rotation << x_axis(0), x_axis(1), x_axis(2), 0,
		y_axis(0), y_axis(1), y_axis(2), 0,
		z_axis(0), z_axis(1), z_axis(2), 0,
		0, 0, 0, 1;

	Eigen::Matrix4f translation;
	translation << 1, 0, 0, -ex,
		0, 1, 0, -ey,
		0, 0, 1, -ez,
		0, 0, 0, 1;

	m = rotation * translation;
	//m.setIdentity();//���Ӧ��ȥ��

	//��������հ״���ɴ˺���

	mModelView *= m;
	return m;
}

Eigen::Matrix4f myRotateX(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();

	float costheta = cos(theta);
	float sintheta = sin(theta);
	m(0, 0) = 1;
	m(3, 3) = 1;
	m(1, 1) = costheta;   
	m(1, 2) = -sintheta;
	m(2, 1) = sintheta;  
	m(2, 2) = costheta;

	mModelView *= m;
	return m;
}

Eigen::Matrix4f myRotateY(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();

	float costheta = cos(theta);
	float sintheta = sin(theta);
	m(1, 1) = 1;
	m(3, 3) = 1;
	m(0, 0) = costheta;
	m(0, 2) = sintheta;
	m(2, 0) = -sintheta;
	m(2, 2) = costheta;

	mModelView *= m;
	return m;
}

Eigen::Matrix4f myRotateZ(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();

	float costheta = cos(theta);
	float sintheta = sin(theta);
	m(2, 2) = 1;
	m(3, 3) = 1;
	m(0, 0) = costheta;
	m(0, 1) = -sintheta;
	m(1, 0) = sintheta;
	m(1, 1) = costheta;

	mModelView *= m;
	return m;
}


Eigen::Matrix4f myTranslate(float x, float y, float z)
{
	Eigen::Matrix4f m;
	m.setZero();


	m(0, 0) = 1;
	m(1, 1) = 1;
	m(2, 2) = 1;
	m(3, 3) = 1;

	m(0, 3) = x;
	m(1, 3) = y;
	m(2, 3) = z;


	mModelView *= m;
	return m;
}

Eigen::Matrix4f myRotate(float angle, float x, float y, float z)
{
	float theta = angle / 180.0 * PI;

	Eigen::Matrix4f m;

	

	//���Ƚ��й�һ������
	Eigen::Vector3f normal;
	normal[0] = x;
	normal[1] = y;
	normal[2] = z;
	normal.normalize();

	//��������ת����
	m.setZero();
	m(0, 0) = cos(theta) + (1 - cos(theta)) * normal[0] * normal[0];
	m(0, 1) = (1 - cos(theta)) * normal[0] * normal[1] - normal[2] * sin(theta);
	m(0, 2) = (1 - cos(theta)) * normal[0] * normal[2] + normal[1] * sin(theta);
	m(1, 0) = (1 - cos(theta)) * normal[0] * normal[1] + normal[2] * sin(theta);
	m(1, 1) = cos(theta) + (1 - cos(theta)) * normal[1] * normal[1];
	m(1, 2) = (1 - cos(theta)) * normal[1] * normal[2] - normal[0] * sin(theta);
	m(2, 0) = (1 - cos(theta)) * normal[0] * normal[2] - normal[1] * sin(theta);
	m(2, 1) = (1 - cos(theta)) * normal[1] * normal[2] + normal[0] * sin(theta);
	m(2, 2) = cos(theta) + (1 - cos(theta)) * normal[2] * normal[2];
	m(3, 3) = 1;


	

	mModelView *= m;

	return m;
}

Eigen::Matrix4f myFrustum(float l, float r, float b, float t, float n, float f)
{
	Eigen::Matrix4f m;
	m.setZero();

	//��������հ״���ɴ˺���

	m(0, 0) = 2 * n / (r - l);
	m(0, 2) = (r + l) / (r - l);
	m(1, 1) = 2 * n / (t - b);
	m(1, 2) = (t + b) / (t - b);
	m(2, 2) = -(f + n) / (f - n);
	m(2, 3) = -2 * f * n / (f - n);
	m(3, 2) = -1;
	
	//m.setIdentity();//���Ӧ��ȥ��

	//��������հ״���ɴ˺���

	mProjection *= m;
	return m;
}

Eigen::Matrix4f myOrtho(float l, float r, float b, float t, float n, float f)
{
	Eigen::Matrix4f m;
	m.setZero();

	//��������հ״���ɴ˺���
	
	m(0, 0) = 2 / (r - l);
	m(0, 3) = -(r + l) / (r - l);
	m(1, 1) = 2 / (t - b);
	m(1, 3) = -(t + b) / (t - b);
	m(2, 2) = -2 / (f - n);
	m(2, 3) = -(f + n) / (f - n);
	m(3, 3) = 1;

	//m.setIdentity();//���Ӧ��ȥ��


	//��������հ״���ɴ˺���

	mProjection *= m;

	return m;
}

Eigen::Matrix4f myViewPort(float x, float y, float w, float h)
{
	Eigen::Matrix4f m;
	m.setZero();

	//��������հ״���ɴ˺���

	m(0, 0) = w / 2.0f;
	m(0, 3) = w / 2.0f + x;
	m(1, 1) = -h / 2.0f;
	m(1, 3) = h / 2.0f + 500 - h - y;
	m(2, 2) = 1.0;
	m(3, 3) = 1.0;

	//������δ���Ӧ��ɾ��
	/*
	m(0, 0) = 125;
	m(1, 1) = 125.0;
	m(0, 3) = 125.0;
	m(1, 3) = 125.0;
	m(2, 2) = 1.0;
	m(3, 3) = 1.0;
	*/
	//������δ���Ӧ��ɾ��

	//��������հ״���ɴ˺���

	mViewPort = m;

	return m;
}

Eigen::Matrix4f myPerspective(float fovy, float aspect, float zNear, float zFar)
{
	Eigen::Matrix4f m;
	m.setZero();
	const float pi = 3.1415926535897932384626433832795;

	//��������հ״���ɴ˺���
	float tanHalfFovy = 1.0 / tan(fovy * pi / 360.0);
	m(0, 0) = tanHalfFovy / aspect;
	m(1, 1) = tanHalfFovy;
	m(2, 2) = -(zFar + zNear) / (zFar - zNear);
	m(2, 3) = -1.0;
	m(3, 2) = -(2.0 * zFar * zNear) / (zFar - zNear);

	//m.setIdentity();//���Ӧ��ȥ��

	//��������հ״���ɴ˺���

	mProjection *= m;
	return m;
}