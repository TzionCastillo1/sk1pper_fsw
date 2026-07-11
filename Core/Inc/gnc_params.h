#ifndef GNC_PARAMS
#define GNC_PARAMS

typedef struct gnc_params_t {
    float roll_pid_kp;
    float roll_pid_ki;
    float roll_pid_kd;
    float pitch_pid_kp;
    float pitch_pid_ki;
    float pitch_pid_kd;
    float yaw_pid_kp;
    float yaw_pid_ki;
    float yaw_pid_kd;
    float motor_max_throttle;
} gnc_params_t;

#endif //GNC_PARAMS