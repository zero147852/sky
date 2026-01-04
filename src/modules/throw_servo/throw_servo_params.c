/**
 * @file throw_servo_params.c
 * Parameters for multicopter attitude controller.
 *
 * @author no name <anton@px4.io>
 */

/**
 * Enable throw servo
 *
 * Enable throw servo
 *
 * @value 0 OFF
 * @value 1 ON
 * @boolean
 * @group THROW_SERVO
 */
PARAM_DEFINE_INT32(THROW_SERVO_EN, 0);

/**
 * Default throw servo channel 1~6
 *
 * Default throw servo channel 1~6
 *
 * @value 0 channel1
 * @value 1 channel2
 * @value 2 channel3
 * @value 3 channel4
 * @value 4 channel5
 * @value 5 channel6
 * @value 6 channel7
 * @value 7 channel8
 * @value -1 OFF
 * @group THROW_SERVO
 */
PARAM_DEFINE_INT32(THROW_SERVO_CH1, -1);

/**
 * Default throw servo channel 1~8
 *
 * Default throw servo channel 1~8
 *
 * @value 0 channel1
 * @value 1 channel2
 * @value 2 channel3
 * @value 3 channel4
 * @value 4 channel5
 * @value 5 channel6
 * @value 6 channel7
 * @value 7 channel8
 * @value -1 OFF
 * @group THROW_SERVO
 */
PARAM_DEFINE_INT32(THROW_SERVO_CH2, -1);

/**
 * Default throw servo channel 1~8
 *
 * Default throw servo channel 1~8
 *
 * @value 0 channel1
 * @value 1 channel2
 * @value 2 channel3
 * @value 3 channel4
 * @value 4 channel5
 * @value 5 channel6
 * @value 6 channel7
 * @value 7 channel8
 * @value -1 OFF
 * @group THROW_SERVO
 */
PARAM_DEFINE_INT32(THROW_SERVO_CH3, -1);

/**
 * Default throw servo PWM1
 *
 * Default throw servo PWM1
 *
 * @min 500.00000
 * @max 2500.00000
 * @group THROW_SERVO
 */
PARAM_DEFINE_FLOAT(THROW_SERVO_PWM1, 900.0f);

/**
 * Default throw servo PWM2
 *
 * Default throw servo PWM2
 *
 * @min 500.00000
 * @max 2500.00000
 * @group THROW_SERVO
 */
PARAM_DEFINE_FLOAT(THROW_SERVO_PWM2, 900.0f);

/**
 * Default throw servo PWM3
 *
 * Default throw servo PWM3
 *
 * @min 500.00000
 * @max 2500.00000
 * @group THROW_SERVO
 */
PARAM_DEFINE_FLOAT(THROW_SERVO_PWM3, 900.0f);



