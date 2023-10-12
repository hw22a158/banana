#include "DrawPad.hpp"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int RandomColor()
{
    int r = random() % 256;
    int g = random() % 256;
    int b = random() % 256;
    return ((r << 16) | (g << 8) | b);
}

void DrawMain()
{
    // 乱数の初期化
    srandom((unsigned)time(NULL));
    
    // モデルの初期化
    const int kBallCount = 40;
    double x[kBallCount] = {};  // 初期値を書かなければすべて0で初期化
    double y[kBallCount] = {};  // 初期値を書かなければすべて0で初期化
    double vx[kBallCount];
    double vy[kBallCount];
    int colors[kBallCount];
    int r[kBallCount];
    for (int i = 0; i < kBallCount; i++) {
        double angle = ((random() % 201) / 100.0) * M_PI;
        double vsize = (random() % 10) + 1;
        vx[i] = cos(angle) * vsize;
        vy[i] = sin(angle) * vsize;
        colors[i] = RandomColor();
        r[i] = random() % 20 + 2;
    }

    // ループ処理
    while (true) {
        // 描画の処理
        StartBatch();
        Clear(kColorBlack);
        for (int i = 0; i < kBallCount; i++) {
            FillCircle(x[i], y[i], r[i], colors[i]);
        }
        EndBatch();

        // モデルの変更
        for (int i = 0; i < kBallCount; i++) {
            if (x[i] + vx[i] < -320 + r[i] || x[i] + vx[i] > 319 - r[i]) {
                vx[i] *= -1;
            }
            x[i] += vx[i];

            if (y[i] + vy[i] < -240 + r[i] || y[i] + vy[i] > 239 - r[i]) {
                vy[i] *= -1;
            }
            y[i] += vy[i];
        }

        // 一時休止
        Sleep(0.0167);
    }
}

