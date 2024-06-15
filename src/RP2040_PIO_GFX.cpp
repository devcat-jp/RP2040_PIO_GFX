
#include <RP2040_PIO_GFX.h>
#include <FontData8x8.h>
#include "Arduino.h"
#include "pio.h"

#define PIO_ID pio0
#define PIO_TX_SM 0


namespace RP2040_PIO_GFX {

    /******************************************************************************
    * @fn      Gfx
    * @brief   コンストラクタ
    ******************************************************************************/
    Gfx::Gfx(){
        this->isInit = false;
        this->width = 0;
        this->height = 0;

        this->is_transparent_font = false;
        this->font_color = 0xFFFF;
        this->font_back_color = 0x0000;
    }


    /******************************************************************************
    * @fn      initILI9341
    * @brief   ILI9341の初期化処理
    * @param   TFT_CLK : クロックピン番号
    * @param   pin_mosi : MOSIピン番号
    * @param   pin_dc : DCピン番号
    * @param   pin_rst : リセットピン番号
    * @param   pin_cs : CSピン番号
    * @param   col_size : COLサイズ
    * @param   row_size : ROWサイズ
    * @param   rot_mode : 画面の向き
    ******************************************************************************/
    void Gfx::initILI9341(uint8_t pin_clk,
                        uint8_t pin_mosi,
                        uint8_t pin_dc,
                        uint8_t pin_rst,
                        uint8_t pin_cs,
                        uint16_t start_col,
                        uint16_t start_row,
                        uint16_t col_size,
                        uint16_t row_size,
                        uint8_t rot_mode){
        // PIOにプログラム転送
        uint8_t addr = pio_add_program(PIO_ID, &spi_tx_program);
        // PIO初期化
        spi_tx_init(
            PIO_ID,
            PIO_TX_SM,  // ステートマシン（0～3）
            addr,       // プログラム位置
            pin_mosi,
            pin_clk,
            1.0);

        // ピン設定
        pinMode(pin_dc, OUTPUT);
        pinMode(pin_rst, OUTPUT);
        pinMode(pin_cs, OUTPUT);

        // CS設定、常時使用が前提
        digitalWrite(pin_cs, LOW);

        // ILI9341の初期化処理
        digitalWrite_with_sleep(pin_rst, LOW);      // HARDWARE Reset
        digitalWrite_with_sleep(pin_rst, HIGH);
        digitalWrite_with_sleep(pin_dc, LOW);
        pio_putc(PIO_ID, PIO_TX_SM, 0x01);          // SOFTWARE RESET
        pio_putc(PIO_ID, PIO_TX_SM, 0x13);          // Normal Display Mode ON
        pio_putc(PIO_ID, PIO_TX_SM, 0x36);          // Memory Access Control
        digitalWrite_with_sleep(pin_dc, HIGH);      // Data mode
        if(rot_mode == 0)
            pio_putc(PIO_ID, PIO_TX_SM, 0x48);      // 縦画面, 左上から描画
        else if(rot_mode == 1)
            pio_putc(PIO_ID, PIO_TX_SM, 0x8c);      // 縦画面, 右下から描画
        else if(rot_mode == 2)
            pio_putc(PIO_ID, PIO_TX_SM, 0x28);      // 横画面, 左上から描画
        else
            pio_putc(PIO_ID, PIO_TX_SM, 0xe8);      // 横画面, 右下から描画
        digitalWrite_with_sleep(pin_dc, LOW);       // Command mode
        pio_putc(PIO_ID, PIO_TX_SM, 0x3a);          // COLMOD: Pixel Format Set
        digitalWrite_with_sleep(pin_dc, HIGH);      // Data mode
        pio_putc(PIO_ID, PIO_TX_SM, 0x55);          // 16Bits / 1Pixcel
        digitalWrite_with_sleep(pin_dc, LOW);       // Command mode
        pio_putc(PIO_ID, PIO_TX_SM, 0x11);          // Sleep Out
        delay(150);
        pio_putc(PIO_ID, PIO_TX_SM, 0x29);          // Display ON
        // COL方向の描画範囲
        digitalWrite_with_sleep(pin_dc, LOW);       // Command mode
        pio_putc(PIO_ID, PIO_TX_SM, 0x2a);
        digitalWrite_with_sleep(pin_dc, HIGH);      // Data mode
        if(rot_mode == 0 || rot_mode == 1){
            pio_putc(PIO_ID, PIO_TX_SM, 0x00);
            pio_putc(PIO_ID, PIO_TX_SM, 0x00);
            pio_putc(PIO_ID, PIO_TX_SM, 0x00);
            pio_putc(PIO_ID, PIO_TX_SM, 0xef);
        } else {
            pio_putc(PIO_ID, PIO_TX_SM, 0x00);
            pio_putc(PIO_ID, PIO_TX_SM, 0x00);
            pio_putc(PIO_ID, PIO_TX_SM, 0x01);
            pio_putc(PIO_ID, PIO_TX_SM, 0x3f);
        }
        // ROW方向の描画範囲
        digitalWrite_with_sleep(pin_dc, LOW);       // Command mode
        pio_putc(PIO_ID, PIO_TX_SM, 0x2b);
        digitalWrite_with_sleep(pin_dc, HIGH);      // Data mode
        if(rot_mode == 0 || rot_mode == 1){
            pio_putc(PIO_ID, PIO_TX_SM, 0x00);
            pio_putc(PIO_ID, PIO_TX_SM, 0x00);
            pio_putc(PIO_ID, PIO_TX_SM, 0x01);
            pio_putc(PIO_ID, PIO_TX_SM, 0x3f);
        } else {
            pio_putc(PIO_ID, PIO_TX_SM, 0x00);
            pio_putc(PIO_ID, PIO_TX_SM, 0x00);
            pio_putc(PIO_ID, PIO_TX_SM, 0x00);
            pio_putc(PIO_ID, PIO_TX_SM, 0xef);
        }

        // 画面を黒で塗りつぶす
        digitalWrite_with_sleep(pin_dc, LOW);       // Command mode
        pio_putc(PIO_ID, PIO_TX_SM, 0x2c);          // Memory Write
        digitalWrite_with_sleep(pin_dc, HIGH);      // Data mode
        for(int i = 0; i < 320*240*2; i++)
            pio_putc(PIO_ID, PIO_TX_SM, 0x00);

        // 描画範囲設定
        digitalWrite_with_sleep(pin_dc, LOW);       // Command mode
        pio_putc(PIO_ID, PIO_TX_SM, 0x2a);
        digitalWrite_with_sleep(pin_dc, HIGH);      // Data mode
        pio_putc(PIO_ID, PIO_TX_SM, (start_col) >> 8);
        pio_putc(PIO_ID, PIO_TX_SM, (start_col) & 0xFF);
        pio_putc(PIO_ID, PIO_TX_SM, (start_col + col_size - 1) >> 8);
        pio_putc(PIO_ID, PIO_TX_SM, (start_col + col_size - 1) & 0xFF);
        //
        digitalWrite_with_sleep(pin_dc, LOW);       // Command mode
        pio_putc(PIO_ID, PIO_TX_SM, 0x2b);
        digitalWrite_with_sleep(pin_dc, HIGH);      // Data mode
        pio_putc(PIO_ID, PIO_TX_SM, (start_row) >> 8);
        pio_putc(PIO_ID, PIO_TX_SM, (start_row) & 0xFF);
        pio_putc(PIO_ID, PIO_TX_SM, (start_row + row_size - 1) >> 8);
        pio_putc(PIO_ID, PIO_TX_SM, (start_row + row_size - 1) & 0xFF);

        // 描画データ転送モード
        digitalWrite_with_sleep(pin_dc, LOW);       // Command mode
        pio_putc(PIO_ID, PIO_TX_SM, 0x2c);          // Memory Write
        digitalWrite_with_sleep(pin_dc, HIGH);      // Data mode

        // プログラム削除
        pio_remove_program(PIO_ID, &spi_tx_program, addr);
        delay(10);

        // PIOにプログラム転送
        addr = pio_add_program(PIO_ID, &spi_tx_16bit_program);
        // PIO初期化
        spi_tx_init(
            PIO_ID,
            PIO_TX_SM,  // ステートマシン（0～3）
            addr,       // プログラム位置
            pin_mosi,
            pin_clk,
            1.0);

        // 画面サイズ記録
        this->width = col_size;
        this->height = row_size;
        this->screen_size = col_size * row_size;

        // メモリ確保
        this->top_buffer = new uint16_t[this->width*this->height];
        this->write_buffer = this->top_buffer;

        // 初期化フラグを有効化
        this->isInit = true;
    }


    /******************************************************************************
    * @fn      initDoubleBuffer
    * @brief   ダブルバッファを生成する
    ******************************************************************************/
    bool Gfx::initDoubleBuffer(){
        if(!this->isInit) return false;
        // メモリ確保
        this->back_buffer = new uint16_t[this->width*this->height];
        this->write_buffer = this->back_buffer;
        return true;
    }


     /******************************************************************************
    * @fn      initDMA
    * @brief   DMA転送設定を行う
    * @param   top_buffer : 転送メモリの初期設定
    ******************************************************************************/
    bool Gfx::initDMA(){
        if(!this->isInit) return false;

        // DMA設定
        dma_chan = dma_claim_unused_channel(true);                          // 未使用のDMAチャンネルを取得
        dma_channel_config c = dma_channel_get_default_config(dma_chan);
        channel_config_set_transfer_data_size(&c, DMA_SIZE_16);             // Nbit単位で転送
        channel_config_set_read_increment(&c, true);                        // データ元の自動インクリメントを有効
        channel_config_set_dreq(&c, DREQ_PIO0_TX0);                         // TX FIFOが空になったらDMA実行
        dma_channel_configure(
            dma_chan,
            &c,
            &pio0_hw->txf[PIO_TX_SM],                                       // PIOのTX FIFO
            this->top_buffer,                                                 // 
            this->width*this->height,                                       // 繰り返し回数
            true                                                            // 開始フラグ
        );
        dma_channel_set_irq0_enabled(dma_chan, true);                       // IRQ0の割り込みを有効化

        return true;
    }


    /******************************************************************************
    * @fn      initDMA
    * @brief   DMA転送設定を行う
    * @param   top_buffer : 転送メモリの初期設定
    * @param   *p_func : 転送完了時に呼ばれるコールバック関数
    ******************************************************************************/
    bool Gfx::initDMA(void (*p_func)()){
        if(!this->isInit) return false;

        // DMA設定
        dma_chan = dma_claim_unused_channel(true);  // 未使用のDMAチャンネルを取得
        dma_channel_config c = dma_channel_get_default_config(dma_chan);
        channel_config_set_transfer_data_size(&c, DMA_SIZE_16);     // N bit単位で転送
        channel_config_set_read_increment(&c, true);                // データ元の自動インクリメントを有効
        channel_config_set_dreq(&c, DREQ_PIO0_TX0);                 // TX FIFOが空になったらDMA実行
        dma_channel_configure(
            dma_chan,
            &c,
            &pio0_hw->txf[PIO_TX_SM],                               // PIOのTX FIFO
            this->top_buffer,                                         // 
            this->width*this->height,                               // 繰り返し回数
            true                                                    // 開始フラグ
        );
        dma_channel_set_irq0_enabled(dma_chan, true);               // IRQ0の割り込みを有効化
        irq_set_exclusive_handler(DMA_IRQ_0, p_func);               // IRQハンドラーを設定
        irq_set_enabled(DMA_IRQ_0, true);

        return true;
    }


    /******************************************************************************
    * @fn      initWaitTime
    * @brief   周期処理用のタイマー設定
    * @param   wait_time : 待ち時間
    ******************************************************************************/
    void Gfx::initWaitTime(uint16_t wait_time){
        this->frame_time = wait_time;                           // 1秒を指定したFPSで割る
        this->start_time = micros();                            // 基準時刻記録
    }


    /******************************************************************************
    * @fn      waitFrame
    * @brief   ウエイト処理
    ******************************************************************************/
    bool Gfx::waitFrame(){
        this->end_time = micros();
        // 超過しているか？
        if(this->end_time - this->start_time > this->frame_time){
            // 時刻を更新して異常応答
            this->start_time = micros();
            return false;
        } else {
            // 指定時間まで待つ
            delayMicroseconds(this->frame_time - (this->end_time - this->start_time));
            this->start_time = micros();
            return true;
        }
    }


    /******************************************************************************
    * @fn      updata
    * @brief   DMA転送を指示する
    ******************************************************************************/
    void Gfx::updata(){
        dma_hw->ints0 = 1u << dma_chan;                         // 割り込み要求をクリア
        dma_channel_set_read_addr(dma_chan, this->top_buffer, true);
    }

    /******************************************************************************
    * @fn      swap
    * @brief   ライブラリ内部で確保しているバッファを入れ替える
    ******************************************************************************/
    void Gfx::swap() {
        // 描画メモリ交換
        this->back_buffer = this->top_buffer;
        this->top_buffer = this->write_buffer;
        this->write_buffer = this->back_buffer;
        this->updata();
    }


    /******************************************************************************
    * @fn      clear
    * @brief   現在操作中のバッファをクリアする
    ******************************************************************************/
    void Gfx::clear(uint16_t color){
        for(int i = 0; i < this->screen_size; i++) this->write_buffer[i] = color;
    }


    /******************************************************************************
    * @fn      isCompletedTransfer
    * @brief   DMAによる画像メモリ転送が完了しているか確認する
    ******************************************************************************/
    bool Gfx::isCompletedTransfer(){
        if(dma_hw->ints0 == 1) return true;
        else return false;
    }


    /******************************************************************************
    * @fn      digitalWrite_with_sleep
    * @brief   信号切り替え時の前後で指定時間待機する
    * @param   pin : ピン番号
    * @param   mode   : HIGH or LOW
    * @param   ms   : 待ち時間
    ******************************************************************************/
    void Gfx::digitalWrite_with_sleep(uint8_t pin, bool mode, int16_t ms) {
        delay(ms);
        digitalWrite(pin, mode);
        delay(ms);
    }

    /******************************************************************************
    * @fn      setFontColor
    * @brief   文字の色設定
    * @param   font_color : 文字の色
    * @param   font_back_color : 文字の背景色
    ******************************************************************************/
    void Gfx::setFontColor(uint16_t font_color){
        this->font_color = font_color;
        this->is_transparent_font = true;
    }
    void Gfx::setFontColor(uint16_t font_color, uint16_t font_back_color){
        this->font_color = font_color;
        this->font_back_color = font_back_color;
        this->is_transparent_font = false;
    }


     /******************************************************************************
    * @fn      writeFont8
    * @brief   8x8の文字をメモリに書き込む
    * @param   c_cur : 表示開始位置（col）
    * @param   r_cur : 示開始位置（row）
    * @param   *str : 表示文字列
    * @param   *write_buffer : 書き込み先のメモリ
    ******************************************************************************/
    void Gfx::writeFont8(uint16_t c_cur, uint16_t r_cur, const char *str){
        uint8_t _font_size = 8;
        uint16_t _pos = 0;
        uint16_t _loop = 0;
        uint16_t _newline = 0;

        // 入力文字分繰り返す
        while(str[_loop] != '\0'){
            _pos = (str[_loop] - 0x20) * _font_size;       // スペース(0x20) から配列用意
            // 文字データを書き込む
            for(int row = 0; row < _font_size; row++){
                for(int col = 0; col < _font_size; col++){
                    if( (pgm_read_byte(&(FontData8[_pos + row])) >> (_font_size - col - 1)) & 0b1 == 0b1)
                        this->write_buffer[_loop*_font_size + (c_cur*_font_size) + (r_cur*_font_size*this->width) + (col+(row*this->width)) + _newline] = this->font_color;
                    else if(!this->is_transparent_font)
                        this->write_buffer[_loop*_font_size + (c_cur*_font_size) + (r_cur*_font_size*this->width) + (col+(row*this->width)) + _newline] = this->font_back_color;
                    // 改行判断
                    if(((_loop*_font_size) + (c_cur*_font_size) - _newline) >= this->width){
                        c_cur = 0;                                                      // 端に移動
                        _newline += (_font_size*this->width) - _loop*_font_size;        // 1行分補正
                    }
                }
            }
            _loop++;
        }
    }

    /******************************************************************************
    * @fn      drawLine
    * @brief   直線描画
    * @param   p1_x : 始点 x
    * @param   p1_y : 始点 y
    * @param   p2_x : 終点 x
    * @param   p2_x : 終点y
    ******************************************************************************/
    void Gfx::drawLine(uint16_t p1_x, uint16_t p1_y, uint16_t p2_x, uint16_t p2_y, uint16_t color){
        uint16_t dx = abs(p2_x - p1_x);
        uint16_t dy = abs(p2_y - p1_y);
        uint16_t sx = (p1_x < p2_x) ? 1 : -1;
        uint16_t sy = (p1_y < p2_y) ? 1 : -1;
        int err = dx - dy;

        while (1){
            this->write_buffer[p1_x + (p1_y * this->width)] = color;

            if (p1_x == p2_x && p2_y == p1_y) {
                break;
            }

            int16_t e2 = 2 * err;
            if (e2 > -dy) {
                err -= dy;
                p1_x += sx;
            }
            if (e2 < dx) {
                err += dx;
                p1_y += sy;
            }
        }
    }


    /******************************************************************************
    * @fn      drawdrawCircleLine
    * @brief   円描画
    * @param   cx : 始点 x
    * @param   cy : 始点 y
    * @param   radius : 終点 x
    * @param   color : 色
    ******************************************************************************/
    void Gfx::drawCircle(uint16_t cx, uint16_t cy, uint16_t radius, uint16_t color) {
        // 簡易確認
        if(cx + (cy * this->width) - radius - (radius * this->width) < 0 ||
           cx + (cy * this->width) + radius + (radius * this->width) > this->width + (this->height * this->width)) return;

        // 円の内側判定のものを埋める
        for (int y = cy - radius; y < cy + radius; y++){
            for (int x = cx - radius; x < cx + radius; x++){
                // 判定用
                int lx = (x - cx) * (x - cx);
                int ly = (y - cy) * (y - cy);
                int lr = radius * radius;
                if (lx + ly < lr){
                    this->write_buffer[x + (y * this->width)] = color;
                }
            }
        }
        // 外周を少し膨らませる
        for(int x = cx - (radius/10); x < cx + (radius/10); x++) {
            this->write_buffer[x + ((cy + radius) * this->width)] = color;
            this->write_buffer[x + ((cy - radius) * this->width)] = color;
        }
        for(int y = cy - (radius/10); y < cy + (radius/10); y++) {
            this->write_buffer[cx + radius + (y * this->width)] = color;
            this->write_buffer[cx - radius + (y * this->width)] = color;
        }
    }

    /******************************************************************************
    * @fn      drawPixel
    * @brief   1点描画する
    * @param   px : x
    * @param   py : y
    * @param   color : 色
    ******************************************************************************/
    void Gfx::drawPixel(uint16_t px, uint16_t py, uint16_t color){
        if(px + (py * this->width) > this->width + (this->height * this->width)) return;
        this->write_buffer[px + (py * this->width)] = color;
    }



}
