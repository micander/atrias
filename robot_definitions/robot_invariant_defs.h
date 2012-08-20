#ifndef ROBOT_INVARIANT_DEFS_H
#define ROBOT_INVARIANT_DEFS_H

typedef enum {
	medulla_state_idle     = 0,
	medulla_state_init     = 1,
	medulla_state_run      = 2,
	medulla_state_stop     = 3,
	medulla_state_halt     = 4,
	medulla_state_error    = 5,
	medulla_state_reset    = 6,
	medulla_state_watchdog = 7
} medulla_state_t;

// EtherCAT IDs
#define MEDULLA_VENDOR_ID                                                  0x60F
#define MEDULLA_LEG_PRODUCT_CODE                                      0x00000001
#define MEDULLA_HIP_PRODUCT_CODE                                      0x00000002
#define MEDULLA_BOOM_PRODUCT_CODE                                     0x00000003
#define MEDULLA_TEST_PRODUCT_CODE                                     0x00000004
#define MEDULLA_ASSIGN_ACTIVATE_WORD                                      0x0300


// Medulla IDs
#define MEDULLA_ID_PREFIX_MASK                                              0x30
#define MEDULLA_LEG_ID_PREFIX                                               0x00
#define MEDULLA_HIP_ID_PREFIX                                               0x10
#define MEDULLA_BOOM_ID_PREFIX                                              0x20
#define MEDULLA_TEST_ID_PREFIX                                              0x30

#define MEDULLA_AMPLIFIER_DEBUG                                             0x00
#define MEDULLA_LEFT_LEG_A_ID                       (MEDULLA_LEG_ID_PREFIX  + 1)
#define MEDULLA_LEFT_LEG_B_ID                       (MEDULLA_LEG_ID_PREFIX  + 2)
#define MEDULLA_LEFT_HIP_ID                         (MEDULLA_HIP_ID_PREFIX  + 0)
#define MEDULLA_RIGHT_LEG_A_ID                      (MEDULLA_LEG_ID_PREFIX  + 3)
#define MEDULLA_RIGHT_LEG_B_ID                      (MEDULLA_LEG_ID_PREFIX  + 4)
#define MEDULLA_RIGHT_HIP_ID                        (MEDULLA_HIP_ID_PREFIX  + 1)
#define MEDULLA_BOOM_ID                             (MEDULLA_BOOM_ID_PREFIX + 0)

// Limit switch masks for medullas
#define MEDULLA_LLEG_ASIDE_LSW_MASK                    0b00111111
#define MEDULLA_LLEG_BSIDE_LSW_MASK                    0b00011111

// Medulla errors
typedef enum {
	medulla_error_estop         = 1<<0,
	medulla_error_limit_switch  = 1<<1,
	medulla_error_thermistor    = 1<<2,
	medulla_error_motor_voltage = 1<<3,
	medulla_error_logic_voltage = 1<<4,
	medulla_error_encoder       = 1<<5,
	medulla_error_halt          = 1<<6,
	medulla_error_amplifier     = 1<<7
} medulla_error_t;

// Safety cut off values

// Danger region for motor power
#define MOTOR_VOTLAGE_DANGER_MAX                                            3000
#define MOTOR_VOLTAGE_DANGER_MIN                                            1500

// Low voltage cut off for logic power
#define LOGIC_VOLTAGE_MIN                                                   2950

/** @brief Maximum allowable thermistor value
  * This is a minimum ADC value, but it
  * relates to the maximum temp.
  */
#define THERMISTOR_MAX_VAL                                                   300

// Loop period for main RT operations
#define CONTROLLER_LOOP_PERIOD_NS                                      1000000LL
/** @brief The offset between the DC and our code loop.
  */
#define CONTROLLER_LOOP_OFFSET_NS                                       100000LL

//Loop period for the GUI
#define GUI_LOOP_PERIOD_NS                                            20000000LL

#define LEG_A_CALIB_LOC                                       1.3089969389957472
#define LEG_B_CALIB_LOC                                       1.8325957145940461

/** @brief The maximum commanded amplifier value.
  * This is the maximum value sent to the
  * Medullas for the amplifier command.
  */
#define MTR_MAX_COUNT                                                      19900

// ... and the maximum torque (for scaling)
#define MTR_MAX_TORQUE                                                     120.0
#define MTR_HIP_MAX_TORQUE                                                  60.0

// Here are the main motor torque limits. These are not used for scaling, just as limits.
#define MAX_MTR_TRQ_CMD                                                    120.0
#define MIN_MTR_TRQ_CMD                                                   -120.0
#define MAX_HIP_MTR_TRQ_CMD                                                 60.0
#define MIN_HIP_MTR_TRQ_CMD                                                -60.0

// Limits the maximum adjustment that may be applied to the leg position when the spring deflections
// are zeroed during initialization (in radians).
#define MAX_LEG_POS_ADJUSTMENT                                               0.2

/** @brief The voltage at which the xMega's ADCs max out.
  * This is used for scaling the ADC values.
  */
#define MEDULLA_ADC_MAX_VOLTS                                               2.72

/** @brief The amount of time RT Ops should wait for the Medullas to enter idle after a reset.
  */
#define MEDULLA_RESET_TIME_MS                                                  5

/** @brief This is the number of radians represented by one tick of the motor's internal incremental encoder.
  * Used for scaling.
  */
#define INC_ENC_RAD_PER_TICK                              0.00044879895051282761

/** @brief This is the rate at which the Medulla's timers run. Used for timestamp usage for velocity calculation.
  */
#define MEDULLA_TIMER_FREQ                                            32000000.0

#endif // ROBOT_INVARIANT_DEFS_H