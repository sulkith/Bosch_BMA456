#ifndef __BOSCH_BMA456_DEFS_H__
#define __BOSCH_BMA456_DEFS_H__

/*!
 * \brief The I2C Address of the BMA
 *
 * see https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMA456-DS000.pdf for more details
 */
#define BMA_ADDRESS 0x19

//INTERRUPT CONFIG REGISTERS
/*!
 * \brief reserved Register, used for the stream write
 *
 * see https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMA456-DS000.pdf for more details
 */
#define BMA4_RESERVED_REG_5B_ADDR		UINT8_C(0x5B)
/*!
 * \brief reserved Register, used for the stream write
 *
 * see https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMA456-DS000.pdf for more details
 */
#define BMA4_RESERVED_REG_5C_ADDR		UINT8_C(0x5C)
/*!
 * \brief Register used for writing the config File and the Interrupt config
 *
 * see https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMA456-DS000.pdf for more details
 */
#define	BMA4_FEATURE_CONFIG_ADDR		UINT8_C(0x5E)
/*!
 * \brief sizeof the config file
 *
 * see https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMA456-DS000.pdf for more details
 */
#define	BMA4_CONFIG_STREAM_SIZE		UINT16_C(6144)

//STATUS
/*!
 * \brief Registeraddress of the internal error Register
 *
 * see https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMA456-DS000.pdf for more details
 */
#define	BMA4_INTERNAL_ERROR			UINT8_C(0x5F)
/*!
 * \brief Registeraddress of the internal status Register
 *
 * should be 0x01 if the interrupt Engine is running fine
 * see https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMA456-DS000.pdf for more details
 */
#define	BMA4_INTERNAL_STAT			UINT8_C(0x2A)
/*!
 * \brief Registeraddress of the Chip ID
 *
 * see https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMA456-DS000.pdf for more details
 */
#define	BMA4_CHIP_ID       			UINT8_C(0x00)

//POWER
/*!
 * \brief Registeraddress of the Power Conf Register
 *
 * see https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMA456-DS000.pdf for more details
 */
#define	BMA4_POWER_CONF_ADDR	UINT8_C(0x7C)
/*!
 * \brief Registeraddress of the Power Control Register
 *
 * see https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMA456-DS000.pdf for more details
 */
#define	BMA4_POWER_CTRL_ADDR	UINT8_C(0x7D)
/*!
 * \brief Registeraddress of the Init Control Register
 *
 * see https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMA456-DS000.pdf for more details
 */
#define	BMA4_INIT_CTRL_ADDR			UINT8_C(0x59)

//COMMAND
/*!
 * \brief Registeraddress of the Command Register
 *
 * see https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMA456-DS000.pdf for more details
 */
#define	BMA4_CMD_ADDR		UINT8_C(0X7E)

//ACCELEROMETER CONFIG
/*!
 * \brief Registeraddress of the Accelleration Config Register
 *
 * see https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMA456-DS000.pdf for more details
 */
#define	BMA4_ACCEL_CONFIG_ADDR		UINT8_C(0X40)
/*!
 * \brief Registeraddress of the Accelleration Range Register
 *
 * see https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMA456-DS000.pdf for more details
 */
#define	BMA4_ACCEL_RANGE_ADDR		UINT8_C(0X41)

//ACCELEROMETER DATA
/*!
 * \brief Registeraddress of the Accelleration in X direction
 *
 * see https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMA456-DS000.pdf for more details
 */
#define BMA4_X_AXIS 0x12
/*!
 * \brief Registeraddress of the Accelleration in Y direction
 *
 * see https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMA456-DS000.pdf for more details
 */
#define BMA4_Y_AXIS 0x14
/*!
 * \brief Registeraddress of the Accelleration in Z direction
 *
 * see https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMA456-DS000.pdf for more details
 */
#define BMA4_Z_AXIS 0x16

/*!
 * \brief Address of the Step Counter config position within the Interrupt config
 *
 * see https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMA456-DS000.pdf for more details
 */
#define BMA4_STEP_COUNTER 0x1E

#endif /*__BOSCH_BMA456_DEFS_H__*/
