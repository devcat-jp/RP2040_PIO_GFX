#include <Arduino.h>
#include <RP2040_PIO_GFX.h>

// ピンアサイン
#define TFT_MOSI 19
#define TFT_CLK 18
#define TFT_DC 22
#define TFT_RST 26
#define TFT_CS 27
// 解像度
#define WIDTH 240
#define HEIGHT 240
// 描画クラス
RP2040_PIO_GFX::Gfx gfx;


void setup() {
  // LCD初期化
  gfx.initILI9341(
    TFT_CLK,
    TFT_MOSI,
    TFT_DC,
    TFT_RST,
    TFT_CS,
    40,
    0,
    WIDTH,
    HEIGHT,
    2,
    1.0);

  // ダブルバッファ用のメモリ生成
  // メモリサイズはLCD初期化の際の画面サイズと同じ
  gfx.initDoubleBuffer();

  // DMAによる画像メモリ転送を有効化
  gfx.initDMA();

  // LED点灯
  pinMode(25, OUTPUT);
  digitalWrite(25, HIGH);
}


unsigned long ts = 0, te = 0;
char _buf[12];

void loop() {
  // DMA転送が完了したら処理実行
  if(gfx.isCompletedTransfer()){
    // 描画指示
    gfx.swap();

    // 全画面クリア
    gfx.clear(gfx.BLACK);

    // 図形描画
    for(int i = 0; i < 33; i++){
      gfx.drawCircle(random(240), random(240), random(20), gfx.RED);
      gfx.drawCircle(random(240), random(240), random(20), gfx.BLUE);
      gfx.drawCircle(random(240), random(240), random(20), gfx.GREEN);
    }

    // 時間計測、および文字出力
    te = micros();
    unsigned long _time = te - ts;
    unsigned long _fps = 1'000'000 / _time;
    snprintf(_buf, 12, "%d", _time);
    gfx.writeFont8(0, 0, "TIME:");
    gfx.writeFont8(5, 0, _buf);
    snprintf(_buf, 12, "%d", _fps);
    gfx.writeFont8(0, 1, "FPS :");
    gfx.writeFont8(5, 1, _buf);
    ts = micros();
  }
}