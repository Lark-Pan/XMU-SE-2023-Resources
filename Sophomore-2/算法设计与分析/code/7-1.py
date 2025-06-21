import random

def generate_unique_random(n, m):
    result = []
    # ���� 1 �� n �����ּ���
    numbers = set(range(1, n + 1))  
    for _ in range(m):
        # ���ѡһ�����Ƴ�����֤���ظ�
        num = random.sample(numbers, 1)[0]  
        numbers.remove(num)  
        result.append(num)
    return result

# ����n=10��m=5
n = 10
m = 5
print(generate_unique_random(n, m))
