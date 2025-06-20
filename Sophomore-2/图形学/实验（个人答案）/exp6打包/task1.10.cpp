#include <Eigen/Core>
#include "ppm.hpp"
#include "camera.hpp"
#include "raytracer.hpp"
#include "scene.hpp" 
#include <iostream>
#include <string>
#include <vector>
#include <utility> // ���� std::pair
#include <cmath>   // ���� std::abs
#include <cstdio>  // ���� sprintf
#include <cstdlib> // ���� rand, srand
#include <ctime>   // ���� srand ��ʱ��

using namespace std;
using namespace Eigen;

// �������� [0, 1] ��Χ�ڵ�������������������������˶�ģ��/����Ӱ��
float random_float_01() {
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

int main()
{
	srand(static_cast<unsigned int>(time(nullptr))); // ��ʼ�����������

	int width = 640;  
	int height = 480; 
	Camera cam;

	// ��̬���壨sp1 �� sp2 �Ƕ�̬����ģ�
	Sphere sp3_static(Vector3f(-2.0, 0, -2), 0.5);
	Sphere sp4_static(Vector3f(1.0, -0.2, -1.0), 0.3);
	Sphere sp5_static(Vector3f(3.0, 0, -2.2), 0.4);


	// ���ʶ���
	Material mtl_sp1, mtl_sp2_ground, mtl_sp3, mtl_sp4, mtl_sp5, mtl_sp6;

	// sp1 �Ĳ��ʣ��м��ɫ���壩
	mtl_sp1.SetKa(Vector3f(0.5, 0.5, 0.5));
	mtl_sp1.SetKd(Vector3f(0.8, 0.6, 0.0));
	mtl_sp1.SetKs(Vector3f(0.7, 0.8, 0.8));
	mtl_sp1.SetTransparent(false);
	mtl_sp1.SetReflective(true);
	mtl_sp1.SetShiness(50);

	// sp2 �Ĳ��ʣ��������壩
	mtl_sp2_ground.SetKa(Vector3f(0.5, 0.5, 0.5)); // �ɼ�����
	mtl_sp2_ground.SetKd(Vector3f(0.2, 0.4, 0.1)); // ����ɫ/��ɫ
	mtl_sp2_ground.SetKs(Vector3f(0.1, 0.1, 0.1));
	mtl_sp2_ground.SetTransparent(false);
	mtl_sp2_ground.SetReflective(false);
	mtl_sp2_ground.SetShiness(10);

	// sp3 �Ĳ��ʣ���ɫС��
	mtl_sp3.SetKa(Vector3f(0.5, 0.5, 0.5));
	mtl_sp3.SetKd(Vector3f(0.0, 0.3, 0.6));
	mtl_sp3.SetKs(Vector3f(0.0, 0.0, 0.0));
	mtl_sp3.SetTransparent(false);
	mtl_sp3.SetReflective(false);
	mtl_sp3.SetShiness(10);

	// sp4 �Ĳ��ʣ��Ҳ��ɫ���� - ͸����
	mtl_sp4.SetKa(Vector3f(0.1, 0.1, 0.1));
	mtl_sp4.SetKd(Vector3f(0.0, 0.0, 0.0));
	mtl_sp4.SetKs(Vector3f(0.0, 0.0, 0.0));
	mtl_sp4.SetTransparent(true);
	mtl_sp4.SetReflective(false);
	mtl_sp4.SetRefraction(1.33);
	mtl_sp4.SetShiness(200);

	// sp5 �Ĳ��ʣ��Ҳ��ɫ���壩
	mtl_sp5.SetKa(Vector3f(0.5, 0.5, 0.5));
	mtl_sp5.SetKd(Vector3f(0.75, 0.56, 0.0));
	mtl_sp5.SetKs(Vector3f(0.75, 0.56, 0.0));
	mtl_sp5.SetTransparent(false);
	mtl_sp5.SetReflective(false);
	// mtl_sp5.SetRefraction(1.33); 
	mtl_sp5.SetShiness(100);



	// �������������
	int total_frames = 120; // ��֡��
	float fps = 24.0f; // ֡��
	float time_per_frame = 1.0f / fps; // ÿ֡��ʱ��

	// sp1�������������壩�Ĳ���
	Vector3f sp1_initial_static_pos(0, 0.5, -2); // ��ʼλ��
	float sp1_radius = 1.0f;
	Vector3f sp1_current_pos = sp1_initial_static_pos;
	sp1_current_pos.y() = 5.0f; // �Ӹ���λ�ÿ�ʼ����
	Vector3f sp1_velocity(0, 0, 0); // ��ʼ�ٶ�Ϊ 0
	float gravity_y = -9.8f;       // �������ٶ�
	float restitution = 0.75f;     // ����ϵ����0 �� 1��

	// sp2���������壩�Ĳ���
	Vector3f sp2_ground_center(0, -10000.5, -2);
	float sp2_ground_radius = 10000.0f;
	float ground_contact_y = sp2_ground_center.y() + sp2_ground_radius; // ���� y ����

	// ��ʼ��֡��Ⱦ
	for (int frame = 0; frame < total_frames; ++frame)
	{
		cout << "��Ⱦ֡ " << frame << "/" << total_frames << "..." << endl;

		// ���� sp1 ������״̬
		sp1_velocity.y() += gravity_y * time_per_frame;
		sp1_current_pos += sp1_velocity * time_per_frame;

		// �����������ײ
		if ((sp1_current_pos.y() - sp1_radius) < ground_contact_y)
		{
			sp1_current_pos.y() = ground_contact_y + sp1_radius; // ����λ��ʹ��Ӵ�����
			sp1_velocity.y() *= -restitution;                    // ���򲢼����ٶȣ�������

			// ����ٶȺ�С���Ҽ������أ���ֹͣ����
			if (std::abs(sp1_velocity.y()) < 0.1f && (sp1_current_pos.y() - sp1_radius - ground_contact_y) < 0.01f) {
				sp1_velocity.y() = 0;
			}
		}

		// ������ǰ֡�ĳ���
		Scene world_this_frame;
		Sphere sp1_dynamic(sp1_current_pos, sp1_radius);
		Sphere sp2_ground_dynamic(sp2_ground_center, sp2_ground_radius);

		world_this_frame.Insert(make_pair(sp1_dynamic, mtl_sp1));
		world_this_frame.Insert(make_pair(sp2_ground_dynamic, mtl_sp2_ground));
		world_this_frame.Insert(make_pair(sp3_static, mtl_sp3));
		world_this_frame.Insert(make_pair(sp4_static, mtl_sp4));
		world_this_frame.Insert(make_pair(sp5_static, mtl_sp5));
		

		// ��Ⱦͼ��
		PPM outrlt(width, height);
		for (int j = height - 1; j >= 0; --j)
		{
			for (int i = 0; i < width; ++i)
			{
				float u = float(i) / float(width);
				float v = float(j) / float(height);
				Ray ray = cam.GenerateRay(u, v);
				Vector3f color = RayColor(ray, world_this_frame, 0); // ��ʼ�ݹ����Ϊ 0

				outrlt.SetPixel(j, i,
					int(255.99 * color[0]), int(255.99 * color[1]), int(255.99 * color[2]));
			}
		}
		char filename_buffer[100];
		sprintf_s(filename_buffer, "frame_%04d.ppm", frame); // ����֡�ļ���
		outrlt.Write2File(filename_buffer); // ����ͼ���ļ�
	}
	cout << "��Ⱦ���" << endl;
	return 0;
}
