#pragma once

#include <px4_platform_common/module.h>
#include <px4_platform_common/module_params.h>
#include <px4_platform_common/px4_work_queue/ScheduledWorkItem.hpp>

#include <uORB/Subscription.hpp>
#include <uORB/topics/parameter_update.h>
#include <uORB/topics/manual_control_setpoint.h>
#include <uORB/topics/vehicle_command.h>
#include <uORB/uORB.h>
#include <drivers/drv_pwm_output.h>

class ThrowServo :
	public ModuleBase<ThrowServo>,
	public ModuleParams,
	public px4::ScheduledWorkItem
{
public:

	ThrowServo();
	~ThrowServo() override = default;

	// ModuleBase 接口
	static int task_spawn(int argc, char *argv[]);
	static int custom_command(int argc, char *argv[]);
	static int print_usage(const char *reason = nullptr);
    	static ThrowServo *instantiate(int argc, char *argv[]);

	bool init();

private:

	// WorkQueue 入口函数
	void Run() override;

	// 参数更新在这里处理
	void parameters_updated();

	bool _default_pwm_applied=false, _pending_cmd=false;
	// int channel , pwm;

	uORB::Subscription _param_update_sub{ORB_ID(parameter_update)};
	uORB::Subscription _manual_ctrl_sub{ORB_ID(manual_control_setpoint)};
	uORB::Subscription _vehicle_cmd_sub;

    DEFINE_PARAMETERS(
        (ParamInt<px4::params::THROW_SERVO_EN>)   _param_throw_servo_en,
        (ParamInt<px4::params::THROW_SERVO_CH1>)  _param_throw_servo_ch1,
        (ParamInt<px4::params::THROW_SERVO_CH2>)  _param_throw_servo_ch2,
        (ParamInt<px4::params::THROW_SERVO_CH3>)  _param_throw_servo_ch3,
        (ParamFloat<px4::params::THROW_SERVO_PWM1>) _param_throw_servo_pwm1,
        (ParamFloat<px4::params::THROW_SERVO_PWM2>) _param_throw_servo_pwm2,
        (ParamFloat<px4::params::THROW_SERVO_PWM3>) _param_throw_servo_pwm3
    )

	int32_t _enable_servo{0};
	int32_t _servo_ch[3]{-1,-1,-1};
	float   _servo_pwm[3]{900.0f,900.0f,900.0f};
};
