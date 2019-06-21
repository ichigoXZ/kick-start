// small input
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

void getPoints(int (*points)[2], int V1, int H1, int A, int B, int C, int D, 
        int E, int F, int M, int N) {
    points[0][0] = V1;
    points[0][1] = H1;
    for (int i = 1; i < N; i++) {
        points[i][0] = (A * points[i - 1][0] + B * points[i - 1][1] + C ) % M;
        points[i][1] = (D * points[i - 1][0] + E * points[i - 1][1] + F) % M;
    }
}

int getCircles(int (*points)[2], int N, int M) {
    int nums[M+1][M+1];
    memset(nums, 0, sizeof(nums));
    for (int i = 0; i < N; i++)
        nums[points[i][0]][points[i][1]] = 1;
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= M; j++)
            nums[i][j] += (nums[i-1][j] + nums[i][j-1] - nums[i-1][j-1]);
    }
    int unable = 0; 
    for (int i = 0; i < N; i++)
        for (int j = i; j < N; j++) {
            if (points[i][0] == points[j][0] || points[i][1] == points[j][1])
                continue;
            int maxV = points[i][0] > points[j][0] ? points[i][0] : points[j][0];
            int minV = points[i][0] < points[j][0] ? points[i][0] : points[j][0];
            int maxH = points[i][1] > points[j][1] ? points[i][1] : points[j][1];
            int minH = points[i][1] < points[j][1] ? points[i][1] : points[j][1];
            if (maxV - minV == 1 || maxH - minH == 1)
                continue;
            unable += (nums[maxV-1][maxH-1] - nums[maxV-1][minH] - nums[minV][maxH-1] + nums[minV][minH]);
        }
    return max(N * (N - 1) * (N - 2) / 6, 1) - unable;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int V1, H1, N, M;
        int A, B, C, D, E , F;
        cin >> N >> V1 >> H1 
            >> A >> B >> C >> D >> E >> F >> M;
        int points[N][2];
        getPoints(points, V1, H1, A, B, C, D, E, F, M, N);
        printf("Case #%d: %d\n", i + 1, getCircles(points, N, M));
    }
}