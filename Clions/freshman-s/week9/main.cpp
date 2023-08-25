#include "stdio.h"
#include "stdlib.h"

// int��ʽ�洢���洢2^31-1���ڵ㣬�����Ҫ�洢����ڵ㣬����ʹ��long long
// ��c��ĳ�_bool����ֱ����int
inline int fa(int x) { return x / 2; }

bool find(int *arr, int x, int n)
{
    for (int i = 1; i <= n; ++i)
    {
        if (arr[i] == x)
            return true;
    }
    return false;
}

void buildtree(int N, int *treecount)// ʹ�����ñ���Ϊcpp����c++��֧��vla
{
    // �ֶ��ݹ�
    int idx = 1;
    int sum = 0;
    int *arr = (int *) malloc((N + 1) * sizeof(int));
    int *n = (int *) malloc((1 << N) * sizeof(int));
    int *m = (int *) malloc((1 << N) * sizeof(int));
    int *i = (int *) malloc((1 << N) * sizeof(int));
    for (int j = 1; j <= (1 << N); ++j)
        i[j] = 0;
    arr[1] = 1;
    n[1] = 1;
    m[1] = 2;

    bool flag = true;
    while (idx > 0)
    {
        if (flag == false)
            goto lable;
        if (m[idx] == N + 1)
        {
            ++sum;
            for (int i = 1; i <= N; ++i)
                printf("%d ", arr[i]);
            printf("\n");
            --idx;
            flag = false;
            continue;
        }
        if (flag)
            i[idx] = n[idx] + 1;
        for (i[idx]; i[idx] <= n[idx] * 2 + 1; ++i[idx])// ���ұߵ�һ���ڵ㿪ʼ�����ӽڵ�Ϊֹ�����ӽڵ�����Ľڵ�ĸ��ڵ�һ������arr�У�������
        {
            if (find(arr, fa(i[idx]), m[idx] - 1))
            {
                arr[m[idx]] = i[idx];
                ++idx;
                flag = true;
                n[idx] = i[idx - 1];
                m[idx] = m[idx - 1] + 1;
                i[idx - 1]++;
                break;
            }
        lable:
        }
        if (i[idx] == n[idx] * 2 + 2)
        {
            --idx;
            flag = false;
        }
    }

    free(arr);
    free(n);
    free(m);
    free(i);
    *treecount = sum;
    return;
}

int main()
{
    int tree_count;
    int N;
    scanf("%d", &N);
    buildtree(N, &tree_count);
    printf("tree_count is %d when N is %d", tree_count, N);
    return 0;
}