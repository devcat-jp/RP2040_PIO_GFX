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
        uint32_t frame_time;        // 目標とする処理時間
        uint32_t start_time;        // 初期化時の時刻
        uint32_t end_time;          // 初期化時の時刻

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
        * @param   p_buffer : 転送メモリの初期設定
        ******************************************************************************/
        bool initDMA(uint16_t *p_buffer);


        /******************************************************************************
        * @fn      initDMA
        * @brief   DMA転送設定を行う
        * @param   p_buffer : 転送メモリの初期設定
        * @param   *p_func : 転送完了時に呼ばれるコールバック関数
        ******************************************************************************/
        bool initDMA(uint16_t *p_buffer, void (*p_func)());


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
    
    



        void updata(uint16_t *p_buffer);


        
    };


}

#endif