/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-12-12      Wayne        First version
*
******************************************************************************/
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <drv_gpio.h>
#define LED_R   NU_GET_PININDEX(NU_PB, 13)
void uart_api_init(void);
static rt_device_t serial;

int main(void *parameter)
{
//    char ch;
    rt_pin_mode(LED_R, PIN_MODE_OUTPUT);
    uart_api_init();
    uint8_t ch=0x00;
    while (1)
    {;
        rt_device_open(serial, RT_DEVICE_FLAG_INT_RX);
        rt_device_write(serial, 0, &ch, 1);
        rt_device_close(serial);
        rt_pin_write(LED_R, PIN_LOW);
        rt_thread_mdelay(100);
    }
}
void uart_api_init(void)
{
                                                               /* �����豸��� */
        struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;  /* ��ʼ�����ò��� */

        /* step1�����Ҵ����豸 */
        serial = rt_device_find("uart1");

        /* step2���޸Ĵ������ò��� */
        config.baud_rate = 115200;               //�޸Ĳ�����Ϊ 1000000
        config.data_bits = DATA_BITS_8;           //����λ 8
        config.stop_bits = STOP_BITS_1;           //ֹͣλ 1
        config.bufsz     = 128;                   //�޸Ļ����� buff size Ϊ 128
        config.parity    = PARITY_NONE;           //����żУ��λ

        /* step3�����ƴ����豸��ͨ�����ƽӿڴ�����������֣�����Ʋ��� */
        rt_device_control(serial, RT_DEVICE_CTRL_CONFIG, &config);


}
