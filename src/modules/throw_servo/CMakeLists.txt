px4_add_module(
    MODULE modules__throw_servo
    MAIN throw_servo
    STACK_MAIN 2048
    SRCS
        throw_servo.cpp
        throw_servo.hpp
    DEPENDS
        uORB
        drivers__pwm_out
)

