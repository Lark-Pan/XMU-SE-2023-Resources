import random

def monte_carlo_product():
    product = 1.0
    for _ in range(25):
        # ���ѡ341~365������
        x = random.randint(341, 365)  
        product *= x
    return product / (365**25)

# ��β���ȡƽ�����������ȣ�
N = 10000
total = 0
for _ in range(N):
    total += monte_carlo_product()
result = total / N
print(f"���ؿ�����ƽ����{result:.4g}")
