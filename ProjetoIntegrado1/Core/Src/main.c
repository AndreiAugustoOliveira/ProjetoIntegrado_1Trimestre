/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2026 STMicroelectronics.
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
#include <stdlib.h>
#include <stdio.h>
#include "ST7735\st7735.h"
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
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
int Stage = 0;
GPIO_PinState botao_UP, botao_LEFT, botao_RIGHT, botao_DOWN;
int nums[4] = {1, 0, 0 , 0};
int senha = 0, i = 0, senha_input = 0;
int Tentativas = 0;
int students = 0;
int TotalSaidas = 0;
bool Confirm = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  ST7735_Init();

  //ST7735_Test();
  int Presentes = 0;
  ST7735_FillScreen(WHITE);
  ST7735_WriteString(5, 10, "Clique o botao", Font_7x10,BLACK,WHITE);
  ST7735_WriteString(5, 25, "superior para", Font_7x10,BLACK,WHITE);
  ST7735_WriteString(5, 40, "gerar a senha", Font_7x10,BLACK,WHITE);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  botao_UP = HAL_GPIO_ReadPin(Button_UP_GPIO_Port, Button_UP_Pin);
	  botao_LEFT = HAL_GPIO_ReadPin(Button_LEFT_GPIO_Port, Button_LEFT_Pin);
	  botao_RIGHT = HAL_GPIO_ReadPin(Button_RIGHT_GPIO_Port, Button_RIGHT_Pin);
	  botao_DOWN = HAL_GPIO_ReadPin(Button_DOWN_GPIO_Port, Button_DOWN_Pin);

	  if(Stage == 0)
		  Authentication();
	  else if(Stage == 1)
	  {
		  ClassLimit();
	  }
	  else if (Stage == 2)
		  Presentes = ControlePresenca();
	  else if (Stage == 3)
		  RoomControl();
	  else if(Stage == 4)
		  EoDReport();


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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
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
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ST7735_DC_Pin|ST7735_RES_Pin|Led_4_Pin|Led_3_Pin
                          |Led_2_Pin|Led_1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : ST7735_CS_Pin */
  GPIO_InitStruct.Pin = ST7735_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ST7735_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ST7735_DC_Pin ST7735_RES_Pin Led_4_Pin Led_3_Pin
                           Led_2_Pin Led_1_Pin */
  GPIO_InitStruct.Pin = ST7735_DC_Pin|ST7735_RES_Pin|Led_4_Pin|Led_3_Pin
                          |Led_2_Pin|Led_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : Button_LEFT_Pin Button_DOWN_Pin Button_RIGHT_Pin Button_UP_Pin */
  GPIO_InitStruct.Pin = Button_LEFT_Pin|Button_DOWN_Pin|Button_RIGHT_Pin|Button_UP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
int PasswordGenerator()
{
	int seed = HAL_GetTick();
	int senha = rand() % 10000;
	ST7735_FillScreen(WHITE);
	ST7735_WriteString(20, 35, "Gerando a senha!", Font_7x10,BLACK,WHITE);
	HAL_Delay(1000);
	ST7735_FillScreen(WHITE);
	//char input_str[6];
	//sprintf(input_str, "%d", 0);
	//ST7735_WriteString(40, 5, input_str, Font_11x18,BLACK,WHITE);
	return senha;
}

void Authentication()
{


	if(botao_UP == 0 && senha == 0)
	{
		senha = PasswordGenerator();
		senha_input = nums[0] * 1000 + nums[1] * 100 + nums[2] * 10 + nums[3];
		LengthAdjuster(senha_input);
		ST7735_WriteString(10, 50, "^", Font_11x18, 0x001F, WHITE);
		ST7735_WriteString(21, 50, "^^^", Font_11x18, BLACK, WHITE);
		ST7735_WriteString(65, 35, "*", Font_11x18, BLACK, WHITE);
	}
	else if(botao_UP == 0 && senha != 0 && i != 4)
	{
		if(nums[i] == 9)
			nums[i] = 0;
		else
			nums[i]++;
		senha_input = nums[0] * 1000 + nums[1] * 100 + nums[2] * 10 + nums[3];
		LengthAdjuster(senha_input);
		HAL_Delay(300);
	}
	else if(botao_UP == 0 && i == 4)
	{
		if(senha == senha_input)
		{
			HAL_GPIO_WritePin(Led_4_GPIO_Port, Led_4_Pin, 1);
			HAL_Delay(300);
			HAL_GPIO_WritePin(Led_4_GPIO_Port, Led_4_Pin, 0);
			Stage++;
			ST7735_FillScreen(WHITE);
			return;
		}
		else
		{
			Tentativas++;
			if(Tentativas == 3)
			{
				ST7735_FillScreen(WHITE);
				ST7735_WriteString(5, 10, "Tentativas de senha", Font_7x10,BLACK,WHITE);
				ST7735_WriteString(5, 25, "excedido", Font_7x10,BLACK,WHITE);
				ST7735_WriteString(5, 40, "Dispositivo bloqueado", Font_7x10,BLACK,WHITE);
				ST7735_WriteString(5, 55, "por 20s", Font_7x10,BLACK,WHITE);
				HAL_Delay(20000);
				ST7735_FillScreen(WHITE);
				//senha_input = nums[0] * 1000 + nums[1] * 100 + nums[2] * 10 + nums[3];
				LengthAdjuster(senha_input);
				Tentativas = 0;
			}
			else
			{
				ST7735_FillScreen(WHITE);
				ST7735_WriteString(25, 40, "Senha incorreta", Font_7x10,BLACK,WHITE);
				HAL_Delay(4000);
				ST7735_FillScreen(WHITE);
				//senha_input = nums[0] * 1000 + nums[1] * 100 + nums[2] * 10 + nums[3];
				LengthAdjuster(senha_input);
			}
		}
	}

	if(botao_LEFT == 0 && i != 0 && senha != 0)
	{
		i--;
		switch(i)
		{
			case 0:
				ST7735_WriteString(10, 50, "^", Font_11x18, 0x001F, WHITE);
				ST7735_WriteString(21, 50, "^^^", Font_11x18, BLACK, WHITE);
				ST7735_WriteString(65, 35, "*", Font_11x18, BLACK, WHITE);
				break;
			case 1:
				ST7735_WriteString(10, 50, "^", Font_11x18, BLACK, WHITE);
				ST7735_WriteString(21, 50, "^", Font_11x18, 0x001F, WHITE);
				ST7735_WriteString(32, 50, "^^", Font_11x18, BLACK, WHITE);
				ST7735_WriteString(65, 35, "*", Font_11x18, BLACK, WHITE);
				break;
			case 2:
				ST7735_WriteString(10, 50, "^^", Font_11x18, BLACK, WHITE);
				ST7735_WriteString(32, 50, "^", Font_11x18, 0x001F, WHITE);
				ST7735_WriteString(43, 50, "^", Font_11x18, BLACK, WHITE);
				ST7735_WriteString(65, 35, "*", Font_11x18, BLACK, WHITE);
				break;
			case 3:
				ST7735_WriteString(10, 50, "^^^", Font_11x18, BLACK, WHITE);
				ST7735_WriteString(43, 50, "^", Font_11x18, 0x001F, WHITE);
				ST7735_WriteString(65, 35, "*", Font_11x18, BLACK, WHITE);
				break;
			case 4:
				ST7735_WriteString(10, 50, "^^^^", Font_11x18, BLACK, WHITE);
				ST7735_WriteString(65, 35, "*", Font_11x18, 0x001F, WHITE);
				break;
		}
		HAL_Delay(200);
	}

	if(botao_RIGHT == 0 && i != 4 && senha != 0)
	{
		i++;
		switch(i)
		{
		case 0:
			ST7735_WriteString(10, 50, "^", Font_11x18, 0x001F, WHITE);
			ST7735_WriteString(21, 50, "^^^", Font_11x18, BLACK, WHITE);
			ST7735_WriteString(65, 35, "*", Font_11x18, BLACK, WHITE);
			break;
		case 1:
			ST7735_WriteString(10, 50, "^", Font_11x18, BLACK, WHITE);
			ST7735_WriteString(21, 50, "^", Font_11x18, 0x001F, WHITE);
			ST7735_WriteString(32, 50, "^^", Font_11x18, BLACK, WHITE);
			ST7735_WriteString(65, 35, "*", Font_11x18, BLACK, WHITE);
			break;
		case 2:
			ST7735_WriteString(10, 50, "^^", Font_11x18, BLACK, WHITE);
			ST7735_WriteString(32, 50, "^", Font_11x18, 0x001F, WHITE);
			ST7735_WriteString(43, 50, "^", Font_11x18, BLACK, WHITE);
			ST7735_WriteString(65, 35, "*", Font_11x18, BLACK, WHITE);
			break;
		case 3:
			ST7735_WriteString(10, 50, "^^^", Font_11x18, BLACK, WHITE);
			ST7735_WriteString(43, 50, "^", Font_11x18, 0x001F, WHITE);
			ST7735_WriteString(65, 35, "*", Font_11x18, BLACK, WHITE);
			break;
		case 4:
			ST7735_WriteString(10, 50, "^^^^", Font_11x18, BLACK, WHITE);
			ST7735_WriteString(65, 35, "*", Font_11x18, 0x001F, WHITE);
			break;
		}
		HAL_Delay(400);
	}

	if(botao_DOWN == 0 && senha != 0 && i != 4)
	{
		if(nums[i] == 0)
			nums[i] = 9;
		else
			nums[i]--;
		senha_input = nums[0] * 1000 + nums[1] * 100 + nums[2] * 10 + nums[3];
		LengthAdjuster(senha_input);
		HAL_Delay(400);
	}
}

void ClassLimit()
{
	char input_str[2];

	if(botao_RIGHT == 0 && Confirm == 0)
	{
		//Texto de confirmação
		Confirm = 1;
	}
	else if(botao_RIGHT == 0 && Confirm == 1)
	{
		//Confirmação para usuário
		//Delay para possibilitar leitura
		HAL_GPIO_WritePin(Led_4_GPIO_Port, Led_4_Pin, 1);
		HAL_Delay(300);
		HAL_GPIO_WritePin(Led_4_GPIO_Port, Led_4_Pin, 0);
		Stage++;
		return;
	}

	if(botao_UP == 0)
	{
		Confirm = 0;
		students++;
		HAL_Delay(200);
		sprintf(input_str, "%d", students);
		ST7735_WriteString(40, 5, input_str, Font_11x18,BLACK,WHITE);

	}

	if(botao_DOWN == 0)
	{
		Confirm = 0;
		students--;
		HAL_Delay(200);
		sprintf(input_str, "%d", students);
		ST7735_WriteString(40, 5, input_str, Font_11x18,BLACK,WHITE);
	}

	if(botao_LEFT == 0)
		Confirm = 0;
}

int ControlePresenca()
{
	bool presenca[students];
	bool confirm = 0;
	int id = 0, presentes = 0;

	while(1)
	{
		if(botao_UP == 0)
		{
			presenca[id] = 1;	//input manual, já que nao tem o sistema de reconhecimento facial.
			HAL_Delay(200);
		}

		if(botao_RIGHT == 0 && confirm == 0)
		{
			//Texto de confirmação
			confirm = 1;
		}
		else if (botao_RIGHT == 0 && confirm == 1)
		{
			HAL_GPIO_WritePin(Led_4_GPIO_Port, Led_4_Pin, 1);
			HAL_Delay(300);
			HAL_GPIO_WritePin(Led_4_GPIO_Port, Led_4_Pin, 0);
			Stage++;
			for(int j = 0; j < students; j ++)
			{
				if(presenca[j] == 1)
					presentes++;
			}
			return presentes;
		}

	}
}

void RoomControl()
{
	int OutOfRoom = 0;
	while(1)
	{
		botao_UP = HAL_GPIO_ReadPin(Button_UP_GPIO_Port, Button_UP_Pin);
		botao_LEFT = HAL_GPIO_ReadPin(Button_LEFT_GPIO_Port, Button_LEFT_Pin);
		botao_RIGHT = HAL_GPIO_ReadPin(Button_RIGHT_GPIO_Port, Button_RIGHT_Pin);
		botao_DOWN = HAL_GPIO_ReadPin(Button_DOWN_GPIO_Port, Button_DOWN_Pin);

		if(botao_UP == 0 && OutOfRoom != 3)
		{
			OutOfRoom++;
			TotalSaidas++;
		}
		else if(botao_UP == 0 && OutOfRoom == 3)
		{
			ST7735_FillScreen(WHITE);
			ST7735_WriteString(5, 10, "Limite de alunos", Font_7x10,BLACK,WHITE);
			ST7735_WriteString(5, 25, "fora de sala excedido", Font_7x10,BLACK,WHITE);
			ST7735_FillScreen(WHITE);
		}

		if(botao_DOWN == 0 && OutOfRoom != 0)
		{
			OutOfRoom--;
		}
		else if(botao_DOWN == 0 && OutOfRoom == 0)
		{
			ST7735_FillScreen(WHITE);
			ST7735_WriteString(5, 10, "Nao ha nenhum aluno", Font_7x10,BLACK,WHITE);
			ST7735_WriteString(5, 25, "fora da sala", Font_7x10,BLACK,WHITE);
			ST7735_FillScreen(WHITE);
		}

		if(botao_LEFT == 0 & botao_RIGHT == 0)
		{
			//Mensagem de turno encerrado;
			Stage++;
			return;
		}
	}
}

void EoDReport()
{
	Stage++;
}

void LengthAdjuster(int senha_input)
{
	char input_str[6];
	if(senha_input >= 1000)
	{
		ST7735_WriteString(5, 10, "Senha:", Font_11x18,BLACK,WHITE);
		sprintf(input_str, "%d", senha_input);
		ST7735_WriteString(10, 30, input_str, Font_11x18,BLACK,WHITE);
	}
	else if(senha_input >= 100)
	{
		ST7735_WriteString(5, 10, "Senha:", Font_11x18,BLACK,WHITE);
		sprintf(input_str, "%d", senha_input);
		ST7735_WriteString(10, 30, "0", Font_11x18,BLACK,WHITE);
		ST7735_WriteString(21, 30, input_str, Font_11x18,BLACK,WHITE);
	}
	else if(senha_input >= 10)
	{
		ST7735_WriteString(5, 10, "Senha:", Font_11x18,BLACK,WHITE);
		sprintf(input_str, "%d", senha_input);
		ST7735_WriteString(10, 30, "00", Font_11x18,BLACK,WHITE);
		ST7735_WriteString(32, 30, input_str, Font_11x18,BLACK,WHITE);
	}
	else
	{
		ST7735_WriteString(5, 10, "Senha:", Font_11x18,BLACK,WHITE);
		sprintf(input_str, "%d", senha_input);
		ST7735_WriteString(10, 30, "000", Font_11x18,BLACK,WHITE);
		ST7735_WriteString(43, 30, input_str, Font_11x18,BLACK,WHITE);
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
