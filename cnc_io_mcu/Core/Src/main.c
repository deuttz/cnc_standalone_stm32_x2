/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "ILI9341.h"
#include "keyboard.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI2_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

#if TEST_TFT_AT_STARTUP
void test_RGB()
{
    ILI9341_fill(Red);
    HAL_Delay(600);
    ILI9341_fill(Green);
    HAL_Delay(600);
    ILI9341_fill(Blue);
    HAL_Delay(600);
    ILI9341_fill(Black);
}


void test_colours()
{
    ILI9341_draw_rectangle(0, 0, 319, 23, YES, SQUARE, Grey, Grey);
    ILI9341_draw_rectangle(0, 23, 319, 47, YES, SQUARE, White, White);
    ILI9341_draw_rectangle(0, 47, 319, 71, YES, SQUARE, Cyan, Cyan);
    ILI9341_draw_rectangle(0, 71, 319, 95, YES, SQUARE, Light_Blue, Light_Blue);
    ILI9341_draw_rectangle(0, 95, 319, 119, YES, SQUARE, Blue, Blue);
    ILI9341_draw_rectangle(0, 119, 319, 143, YES, SQUARE, Green, Green);
    ILI9341_draw_rectangle(0, 143, 319, 167, YES, SQUARE, Yellow, Yellow);
    ILI9341_draw_rectangle(0, 167, 319, 191, YES, SQUARE, Magenta, Magenta);
    ILI9341_draw_rectangle(0, 191, 319, 215, YES, SQUARE, Red, Red);
    ILI9341_draw_rectangle(0, 215, 319, 239, YES, SQUARE, Black, Black);
    HAL_Delay(2600);
    ILI9341_fill(Black);
}


void test_2D_graphics()
{
    signed int i = 0;

    ILI9341_fill(Black);

    for(i = 0; i <= 320; i += 10)
    {
        ILI9341_draw_v_line(i, 0, 240, White);
    }
    for(i = 0; i <= 240; i += 10)
    {
        ILI9341_draw_h_line(0, 320, i, White);
    }

    HAL_Delay(3000);

    ILI9341_fill(Black);
    for(i = 0; i < 240; i += 5)
    {
        ILI9341_draw_line(0, 0, 319, i, Light_Blue);
    }

    for(i = 239; i > -1; i -= 5)
    {
        ILI9341_draw_line(319, 240, 0, i, Blue);
    }

    HAL_Delay(3000);

    ILI9341_fill(Black);

    ILI9341_draw_rectangle(9, 19, 309, 199, NO, ROUND, Magenta, Black);
    ILI9341_draw_rectangle(19, 29, 299, 189, YES, SQUARE, Cyan, Black);

    HAL_Delay(4000);

    ILI9341_fill(Black);

    ILI9341_draw_circle(159, 119, 80, NO, Red);
    ILI9341_draw_circle(159, 119, 40, YES, Yellow);


    HAL_Delay(3000);

    ILI9341_fill(Black);

    ILI9341_draw_triangle(10, 200, 309, 200, 149, 19, NO, Green);
    HAL_Delay(400);
    ILI9341_draw_triangle(10, 200, 309, 200, 149, 19, YES, Grey);

    HAL_Delay(3000);

    ILI9341_fill(Black);
}


void draw_flag()
{
    ILI9341_draw_rectangle(20, 20, 299, 219, YES, SQUARE, Green, Green);
    ILI9341_draw_circle(160, 120, 60, YES, Red);
    HAL_Delay(6000);
    ILI9341_fill(Black);
}


void print_test_data()
{
    unsigned char s = 0;
    signed char c = -9;

    signed int i = -9;

    float f = -9.9;


    ILI9341_print_str(16, 10, 1, Red, Black, "MicroArena");
    ILI9341_print_str(16, 30, 2, Green, Black, "MicroArena");
    ILI9341_print_str(16, 60, 3, Blue, Black, "MicroArena");
    ILI9341_print_str(16, 90, 1, White, Black, "https://www.facebook.com/MicroArena");

    for(s = 0; s < 250; s++)
    {
        ILI9341_print_c(22, 150, 1, Red, Black, c);
        ILI9341_print_i(22, 175, 2, Green, Black, i);
        ILI9341_print_f(22, 210, 3, Blue, Black, f, 1);

        c++;
        i++;
        f += 0.1;

        HAL_Delay(45);
    }
    ILI9341_fill(Black);
}
#endif

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI2_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

    ILI9341_init();
    ILI9341_set_rotation(LANDSCAPE_1);

#if TEST_TFT_AT_STARTUP
    ILI9341_fill(White);
    test_RGB();
    print_test_data();
    test_colours();
    test_2D_graphics();
    draw_flag();
#endif

    int c = 0;
    ILI9341_fill(Black);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1)
    {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
        c += 12345;
        //ILI9341_printf_tft("deadbeef %d", White, Black, c);
        int ret = Keyboard_get_key();
        if (ret != -1) {
            //ILI9341_printf_tft("key pressed %X", White, Black, ret);
            switch(ret) {
                case KEY_0:
                    ILI9341_printf_tft2("key 0\t %X", White, Black, ret);
                    break;
                case KEY_1:
                    ILI9341_printf_tft2("key 1\n\t %X", White, Black, ret);
                    break;
                case KEY_2:
                    ILI9341_printf_tft2("key 2 %X", White, Black, ret);
                    break;
                case KEY_3:
                    ILI9341_printf_tft2("key 3 %X", White, Black, ret);
                    break;
                case KEY_4:
                    ILI9341_printf_tft2("key 4 %X", White, Black, ret);
                    break;
                case KEY_5:
                    ILI9341_printf_tft2_xy(30, 110, "key 5 %X", White, Black, ret);
                    break;
                case KEY_6:
                    ILI9341_printf_tft2_xy(160, 60, "key 6 %X", White, Black, ret);
                    break;
                case KEY_7:
                    ILI9341_printf_tft2_xy(10, 180, "key 7 %X", White, Black, ret);
                    break;
                case KEY_8:
                    ILI9341_printf_tft("key 8 %X", White, Black, ret);
                    break;
                case KEY_9:
                    ILI9341_printf_tft("key 9 %X", White, Black, ret);
                    break;
                case KEY_A:
                    ILI9341_printf_tft("key A %X", White, Black, ret);
                    break;
                case KEY_B:
                    ILI9341_printf_tft("key B %X", White, Black, ret);
                    break;
                case KEY_C:
                    ILI9341_printf_tft("key C %X", White, Black, ret);
                    break;
                case KEY_D:
                    ILI9341_printf_tft("key D %X", White, Black, ret);
                    break;
                case KEY_STAR:
                    ILI9341_printf_tft("key * %X", White, Black, ret);
                    break;
                case KEY_DIES:
                    ILI9341_printf_tft("key # %X", White, Black, ret);
                    break;
            }
        } else {
            //ILI9341_printf_tft("deadbeef %d", White, Black, c);
        }
        HAL_Delay(100);
        HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_HARD_INPUT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_HalfDuplex_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, D0_Pin|D1_Pin|D2_Pin|D3_Pin
                          |D4_Pin|D5_Pin|D6_Pin|D7_Pin
                          |ROW0_Pin|ROW1_Pin|ROW2_Pin|ROW3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, RD_Pin|WR_Pin|RS_Pin|CS_Pin
                          |RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : D0_Pin D1_Pin D2_Pin D3_Pin
                           D4_Pin D5_Pin D6_Pin D7_Pin */
  GPIO_InitStruct.Pin = D0_Pin|D1_Pin|D2_Pin|D3_Pin
                          |D4_Pin|D5_Pin|D6_Pin|D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : COL3_Pin COL2_Pin COL1_Pin COL0_Pin */
  GPIO_InitStruct.Pin = COL3_Pin|COL2_Pin|COL1_Pin|COL0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : ROW0_Pin ROW1_Pin ROW2_Pin ROW3_Pin */
  GPIO_InitStruct.Pin = ROW0_Pin|ROW1_Pin|ROW2_Pin|ROW3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : RD_Pin WR_Pin RS_Pin CS_Pin
                           RST_Pin */
  GPIO_InitStruct.Pin = RD_Pin|WR_Pin|RS_Pin|CS_Pin
                          |RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
