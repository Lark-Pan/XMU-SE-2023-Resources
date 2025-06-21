import random

def estimate_set_size(X, trials=1000):
    total_k = 0
    n_estimates = []
    for _ in range(trials):
        seen = set()
        k = 0
        while True:
            elem = random.choice(list(X))
            if elem in seen:
                total_k += (k + 1)  # �״��ظ��� k+1 ��
                break
            seen.add(elem)
            k += 1
    avg_k = total_k / trials
    return (2 / 3.1415927) * avg_k ** 2  # �� ���� 3.1416

# ���ԣ����� X �Ǻ� n ��Ԫ�صļ���
X = set(range(1000))  # ʵ���� X ��δ֪���ϣ�����ģ��
print(estimate_set_size(X))
