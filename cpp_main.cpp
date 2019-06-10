/*
 * cpp_main.cpp
 *
 *  Created on: 2019¦~6¤ë10¤é
 *      Author: Little_guang
 */
#include "ros.h"
#include "main.h"
#include "stm32f1xx_hal.h"
#include "std_msgs/String.h"
#include "cpp_main.h"
#include <stdio.h>

ros::NodeHandle nh;
std_msgs::String msg;
std_msgs::String num_msg;
//char version[] = "version: 0.3";

void callback(const std_msgs::String& msg);

ros::Publisher num("version", &num_msg);
ros::Subscriber<std_msgs::String> listener("chatter", &callback);

void callback(const std_msgs::String& msg){
	num_msg.data = msg.data;
	num.publish(&num_msg);
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->flush();
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->reset_rbuf();
}


void Setup(void){

	nh.initNode();
	nh.advertise(num);
    nh.subscribe(listener);

}

void Loop(void){

    //HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);
    HAL_Delay(500);
	nh.spinOnce();

}



