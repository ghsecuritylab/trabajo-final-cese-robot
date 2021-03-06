/*
 * create2.cpp
 *
 *  Created on: Sep 21, 2019
 *      Author: alexis
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "create2.h"

namespace irobot {

create2::create2(UART_HandleTypeDef* _uart, GPIO_TypeDef* _brcPort,
		uint16_t _brcPin) :
		uart(_uart), brcPort(_brcPort), brcPin(_brcPin) {
}

create2::~create2() {
}

void create2::start() {
	uint8_t txByte = 128;
	HAL_UART_Transmit(uart, &txByte, 1, 500);
}

void create2::stop() {
	uint8_t txByte = 173;
	HAL_UART_Transmit(uart, &txByte, 1, 500);
}

void create2::reset() {
	uint8_t txByte = 7;
	HAL_UART_Transmit(uart, &txByte, 1, 500);
}

void create2::goSafeMode() {
	uint8_t txByte = 131;
	HAL_UART_Transmit(uart, &txByte, 1, 500);
}

void create2::goFullMode() {
	uint8_t txByte = 132;
	HAL_UART_Transmit(uart, &txByte, 1, 500);
}

void create2::clean() {
	uint8_t txByte = 135;
	HAL_UART_Transmit(uart, &txByte, 1, 500);
}

void create2::drive(int16_t velocity, int16_t radius) {
	velocity = clamp(velocity, -500, 500);
	radius = clamp(radius, -2000, 2000);
	uint8_t txData[5];
	txData[0] = 137;
	txData[1] = velocity >> 8;
	txData[2] = velocity;
	txData[3] = radius >> 8;
	txData[4] = radius;
	HAL_UART_Transmit(uart, txData, 5, 500);
}

void create2::driveVelocity(int16_t rightVel, int16_t leftVel) {
	rightVel = clamp(rightVel, -500, 500);
	leftVel = clamp(leftVel, -500, 500);
	uint8_t txData[5];
	txData[0] = 145;
	txData[1] = rightVel >> 8;
	txData[2] = rightVel;
	txData[3] = leftVel >> 8;
	txData[4] = leftVel;
	HAL_UART_Transmit(uart, txData, 5, 500);
}

void create2::drivePWM(int16_t rightPWM, int16_t leftPWM) {
	rightPWM = clamp(rightPWM, -255, 255);
	leftPWM = clamp(leftPWM, -255, 255);
	uint8_t txData[5];
	txData[0] = 146;
	txData[1] = rightPWM >> 8;
	txData[2] = rightPWM;
	txData[3] = leftPWM >> 8;
	txData[4] = leftPWM;
	HAL_UART_Transmit(uart, txData, 5, 500);
}

} /* namespace irobot */

#ifdef __cplusplus
}
#endif
