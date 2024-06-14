#ifndef RP2040_PIO_GFX_H
#define RP2040_PIO_GFX_H

#include <hardware/pio.h>
#include <hardware/dma.h>


//
namespace RP2040_PIO_GFX {

    class Gfx {
    private:
        bool isInit;                // 液晶の初期化実施フラグ
        int dma_chan;               // 取得したDMAチャンネル
        uint16_t width;             // 指定された画面幅
        uint16_t height;            // 指定された画面高さ
        uint32_t screen_size;       //
        uint32_t frame_time;        // 目標とする処理時間
        uint32_t start_time;        // 初期化時の時刻
        uint32_t end_time;          // 初期化時の時刻

        bool is_transparent_font;   
        uint16_t font_color;        // 文字描画の配色
        uint16_t font_back_color;   // 文字描画の背景色

        uint16_t *p_buffer;         //

        /******************************************************************************
        * @fn      digitalWrite_with_sleep
        * @brief   信号切り替え時の前後で指定時間待機する
        * @param   pin : ピン番号
        * @param   mode : HIGH or LOW
        * @param   ms : 待ち時間
        ******************************************************************************/
        void digitalWrite_with_sleep(uint8_t pin, bool mode, int16_t ms=20);


    public:
        /******************************************************************************
        * @fn      Gfx
        * @brief   コンストラクタ
        ******************************************************************************/
        Gfx();

        /******************************************************************************
        * @fn      Color
        * @brief   色定義
        ******************************************************************************/
        enum Color
        {
            RED = 0xF800,
            BLUE = 0x001F,
            GREEN = 0x07E0,
            WHITE = 0xFFFF,
            BLACK = 0x0000,
        };

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
        ******************************************************************************/
        void initILI9341(uint8_t pin_clk,
                        uint8_t pin_mosi,
                        uint8_t pin_dc,
                        uint8_t pin_rst,
                        uint8_t pin_cs,
                        uint16_t start_col,
                        uint16_t start_row,
                        uint16_t col_size,
                        uint16_t row_size,
                        uint8_t rot_mode
                        );


        /******************************************************************************
        * @fn      initDMA
        * @brief   DMA転送設定を行う
        ******************************************************************************/
        bool initDMA();


        /******************************************************************************
        * @fn      initDMA
        * @brief   DMA転送設定を行う
        * @param   p_buffer : 転送メモリの初期設定
        ******************************************************************************/
        bool initDMA(void (*p_func)());


        /******************************************************************************
        * @fn      initWaitTime
        * @brief   周期処理用のタイマー設定
        * @param   wait_time : 待ち時間
        ******************************************************************************/
        void initWaitTime(uint16_t wait_time);

        /******************************************************************************
        * @fn      waitFrame
        * @brief   ウエイト処理
        ******************************************************************************/
        bool waitFrame();


        /******************************************************************************
        * @fn      is_completed_transfer
        * @brief   DMAによる画像メモリ転送が完了しているか確認する
        ******************************************************************************/
        bool is_completed_transfer();
    

        void updata();
        void clear(uint16_t color);


        /******************************************************************************
        * @fn      setFontColor
        * @brief   文字の色設定
        * @param   font_color : 文字の色
        * @param   font_back_color : 文字の背景色
        ******************************************************************************/
        void setFontColor(uint16_t font_color);
        void setFontColor(uint16_t font_color, uint16_t font_back_color);


        /******************************************************************************
        * @fn      writeFont8
        * @brief   8x8の文字をメモリに書き込む
        * @param   c_cur : 表示開始位置（col）
        * @param   r_cur : 示開始位置（row）
        * @param   *str : 表示文字列
        ******************************************************************************/
        void writeFont8(uint16_t c_cur, uint16_t r_cur, const char *str);


        /******************************************************************************
        * @fn      drawLine
        * @brief   直線描画
        * @param   p1_x : 始点 x
        * @param   p1_y : 始点 y
        * @param   p2_x : 終点 x
        * @param   p2_x : 終点y
        * @param   color : 色
        ******************************************************************************/
        void drawLine(uint16_t p1_x, uint16_t p1_y, uint16_t p2_x, uint16_t p2_y, uint16_t color);


        /******************************************************************************
        * @fn      drawdrawCircleLine
        * @brief   円描画
        * @param   cx : 始点 x
        * @param   cy : 始点 y
        * @param   radius : 終点 x
        * @param   color : 色
        ******************************************************************************/
        void drawCircle(uint16_t cx, uint16_t cy, uint16_t radius, uint16_t color);


        /******************************************************************************
        * @fn      getImageBuffer
        * @brief   クラス内で確保している配列のアドレスを返す
        ******************************************************************************/
        uint16_t *getImageBuffer(){return this->p_buffer;}



        
    };


}

#endif