#include "throw_servo.hpp"

#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/log.h>
#include <px4_platform_common/px4_work_queue/ScheduledWorkItem.hpp>
#include <drivers/drv_pwm_output.h>
#include <uORB/topics/vehicle_command.h>

ThrowServo::ThrowServo() :
    ModuleParams(nullptr),
    px4::ScheduledWorkItem(MODULE_NAME, px4::wq_configurations::nav_and_controllers),
    _vehicle_cmd_sub{ORB_ID(vehicle_command)}  // 在初始化列表中初始化
{
    // 构造函数体中不再调用 subscribe()
}


bool ThrowServo::init()
{
    // 读取初始参数
    parameters_updated();
    return true;
}

void ThrowServo::parameters_updated()
{
    _enable_servo = _param_throw_servo_en.get();
    _servo_ch[0]  = _param_throw_servo_ch1.get();
    _servo_ch[1]  = _param_throw_servo_ch2.get();
    _servo_ch[2]  = _param_throw_servo_ch3.get();
    _servo_pwm[0] = _param_throw_servo_pwm1.get();
    _servo_pwm[1] = _param_throw_servo_pwm2.get();
    _servo_pwm[2] = _param_throw_servo_pwm3.get();
}

void ThrowServo::Run()
{
    printf("hello \r\n");

    // 参数更新检测
    bool updated = false;
    _param_update_sub.update(&updated);
    if (updated) {
        parameters_updated();
    }

    if (_enable_servo == 1) {

        // 默认 PWM 设置
        if (!_default_pwm_applied) {
            for (int i = 0; i < 3; i++) {
                int ch  = _servo_ch[i];
                int pwm = (int)_servo_pwm[i];

                if (ch >= 0 && ch <= 8 && pwm >= 500 && pwm <= 2500) {
                    up_pwm_servo_set(ch, pwm);
                }
            }

            PX4_INFO("ThrowServo: default PWM applied");
        }

        // 检查 MAV_CMD 更新
        bool cmd_updated = false;
        _vehicle_cmd_sub.update(&cmd_updated);
        if (cmd_updated) {
            vehicle_command_s cmd{};
            _vehicle_cmd_sub.copy(&cmd);

            if (cmd.command == 111) {
                _default_pwm_applied = true;
                int channel = (int)cmd.param1;
                int pwm     = (int)cmd.param2;
                // float delay = cmd.param3;

                // if (delay > 0.0f) {
                //     px4_usleep((uint32_t)(delay * 1e6f));
                // }

                if (channel >= 0 && channel <= 7 &&
                    pwm >= 500 && pwm <= 2500)
                {
                    up_pwm_servo_set(channel, pwm);
                    // PX4_INFO("ThrowServo: CMD111 CH%d = %d (delay=%.2f)", channel, pwm, (double)delay);
                }
            }
        }

        // 延迟
        ScheduleDelayed(1000);
    }
}


ThrowServo *ThrowServo::instantiate(int argc, char *argv[])
{
    return new ThrowServo();
}


int ThrowServo::task_spawn(int argc, char **argv)
{
    ThrowServo *instance = new ThrowServo();
    if (!instance) {
        PX4_ERR("alloc failed");
        return -1;
    }
    instance->ScheduleNow();
    return 0;
}

int ThrowServo::custom_command(int argc, char *argv[])
{
    return print_usage("Unrecognized command");
}

int ThrowServo::print_usage(const char *reason)
{
    if (reason) {
        PX4_WARN("%s", reason);
    }

    PX4_INFO("Usage: throw_servo {start|stop|status}");
    return 0;
}

extern "C" __EXPORT int throw_servo_main(int argc, char *argv[])
{
    return ThrowServo::main(argc, argv);
}



