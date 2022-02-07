/*
 *  ======== ti_drivers_config.c ========
 *  Configured TI-Drivers module definitions
 *
 *  DO NOT EDIT - This file is generated for the CC1312R1F3RGZ
 *  by the SysConfig tool.
 */

#include <stddef.h>
#include <stdint.h>

#ifndef DeviceFamily_CC13X2
#define DeviceFamily_CC13X2
#endif

#include <ti/devices/DeviceFamily.h>

#include "ti_drivers_config.h"

/*
 *  =============================== ADC ===============================
 */

#include <ti/drivers/ADC.h>
#include <ti/drivers/adc/ADCCC26XX.h>

#define CONFIG_ADC_COUNT 2

/*
 *  ======== adcCC26xxObjects ========
 */
ADCCC26XX_Object adcCC26xxObjects[CONFIG_ADC_COUNT];

/*
 *  ======== adcCC26xxHWAttrs ========
 */
const ADCCC26XX_HWAttrs adcCC26xxHWAttrs[CONFIG_ADC_COUNT] = {
    /* CONFIG_ADC_0 */
    {
        .adcDIO              = IOID_24,
        .adcCompBInput       = ADC_COMPB_IN_AUXIO6,
        .refSource           = ADCCC26XX_FIXED_REFERENCE,
        .samplingDuration    = ADCCC26XX_SAMPLING_DURATION_2P7_US,
        .inputScalingEnabled = true,
        .refVoltage          = 3300000,
        .triggerSource       = ADCCC26XX_TRIGGER_MANUAL,
        .returnAdjustedVal   = false
    },
    /* CONFIG_ADC_1 */
    {
        .adcDIO              = IOID_25,
        .adcCompBInput       = ADC_COMPB_IN_AUXIO5,
        .refSource           = ADCCC26XX_FIXED_REFERENCE,
        .samplingDuration    = ADCCC26XX_SAMPLING_DURATION_2P7_US,
        .inputScalingEnabled = true,
        .refVoltage          = 3300000,
        .triggerSource       = ADCCC26XX_TRIGGER_MANUAL,
        .returnAdjustedVal   = false
    },
};

/*
 *  ======== ADC_config ========
 */
const ADC_Config ADC_config[CONFIG_ADC_COUNT] = {
    /* CONFIG_ADC_0 */
    {
        .fxnTablePtr = &ADCCC26XX_fxnTable,
        .object = &adcCC26xxObjects[CONFIG_ADC_0],
        .hwAttrs = &adcCC26xxHWAttrs[CONFIG_ADC_0]
    },
    /* CONFIG_ADC_1 */
    {
        .fxnTablePtr = &ADCCC26XX_fxnTable,
        .object = &adcCC26xxObjects[CONFIG_ADC_1],
        .hwAttrs = &adcCC26xxHWAttrs[CONFIG_ADC_1]
    },
};

const uint_least8_t CONFIG_ADC_0_CONST = CONFIG_ADC_0;
const uint_least8_t CONFIG_ADC_1_CONST = CONFIG_ADC_1;
const uint_least8_t ADC_count = CONFIG_ADC_COUNT;

/*
 *  =============================== DMA ===============================
 */

#include <ti/drivers/dma/UDMACC26XX.h>
#include <ti/devices/cc13x2_cc26x2/driverlib/udma.h>
#include <ti/devices/cc13x2_cc26x2/inc/hw_memmap.h>

UDMACC26XX_Object udmaCC26XXObject;

const UDMACC26XX_HWAttrs udmaCC26XXHWAttrs = {
    .baseAddr        = UDMA0_BASE,
    .powerMngrId     = PowerCC26XX_PERIPH_UDMA,
    .intNum          = INT_DMA_ERR,
    .intPriority     = (~0)
};

const UDMACC26XX_Config UDMACC26XX_config[1] = {
    {
        .object         = &udmaCC26XXObject,
        .hwAttrs        = &udmaCC26XXHWAttrs,
    },
};

/*
 *  =============================== I2C ===============================
 */

#include <ti/drivers/I2C.h>
#include <ti/drivers/i2c/I2CCC26XX.h>
#include <ti/drivers/power/PowerCC26XX.h>

#define CONFIG_I2C_COUNT 1

/*
 *  ======== i2cCC26xxObjects ========
 */
I2CCC26XX_Object i2cCC26xxObjects[CONFIG_I2C_COUNT];

/*
 *  ======== i2cCC26xxHWAttrs ========
 */
const I2CCC26XX_HWAttrsV1 i2cCC26xxHWAttrs[CONFIG_I2C_COUNT] = {
    /* CONFIG_I2C_0 */
    {
        .baseAddr    = I2C0_BASE,
        .powerMngrId = PowerCC26XX_PERIPH_I2C0,
        .intNum      = INT_I2C_IRQ,
        .intPriority = (~0),
        .swiPriority = 0,
        .sclPin      = IOID_3,
        .sdaPin      = IOID_4
    },
};

/*
 *  ======== I2C_config ========
 */
const I2C_Config I2C_config[CONFIG_I2C_COUNT] = {
    /* CONFIG_I2C_0 */
    {
        .object      = &i2cCC26xxObjects[CONFIG_I2C_0],
        .hwAttrs     = &i2cCC26xxHWAttrs[CONFIG_I2C_0]
    },
};

const uint_least8_t CONFIG_I2C_0_CONST = CONFIG_I2C_0;
const uint_least8_t I2C_count = CONFIG_I2C_COUNT;

/*
 *  =============================== NVS ===============================
 */

#include <ti/drivers/NVS.h>
#include <ti/drivers/nvs/NVSCC26XX.h>

/*
 *  NVSCC26XX Internal NVS flash region definitions
 *
 * Place uninitialized char arrays at addresses
 * corresponding to the 'regionBase' addresses defined in
 * the configured NVS regions. These arrays are used as
 * place holders so that the linker will not place other
 * content there.
 *
 * For GCC targets, the char arrays are each placed into
 * the shared ".nvs" section. The user must add content to
 * their GCC linker command file to place the .nvs section
 * at the lowest 'regionBase' address specified in their NVS
 * regions.
 */

#if defined(__TI_COMPILER_VERSION__) || defined(__clang__)

static char flashBuf0[0x2000] __attribute__ ((retain, noinit, location(0x0)));

#elif defined(__IAR_SYSTEMS_ICC__)

__no_init static char flashBuf0[0x2000] @ 0x0;

#elif defined(__GNUC__)

__attribute__ ((section (".nvs")))
static char flashBuf0[0x2000];

#endif

NVSCC26XX_Object nvsCC26XXObjects[1];

static const NVSCC26XX_HWAttrs nvsCC26XXHWAttrs[1] = {
    /* CONFIG_NVS_0 */
    {
        .regionBase = (void *) flashBuf0,
        .regionSize = 0x2000
    },
};

#define CONFIG_NVS_COUNT 1

const NVS_Config NVS_config[CONFIG_NVS_COUNT] = {
    /* CONFIG_NVS_0 */
    {
        .fxnTablePtr = &NVSCC26XX_fxnTable,
        .object = &nvsCC26XXObjects[0],
        .hwAttrs = &nvsCC26XXHWAttrs[0],
    },
};

const uint_least8_t CONFIG_NVS_0_CONST = CONFIG_NVS_0;
const uint_least8_t NVS_count = CONFIG_NVS_COUNT;

/*
 *  =============================== PIN ===============================
 */
#include <ti/drivers/PIN.h>
#include <ti/drivers/pin/PINCC26XX.h>

#define CONFIG_PIN_COUNT 6

const PIN_Config BoardGpioInitTable[CONFIG_PIN_COUNT + 1] = {
    /* Parent Signal: CONFIG_ADC_0 ADC Pin, (DIO24) */
    CONFIG_PIN_0 | PIN_INPUT_EN | PIN_NOPULL | PIN_IRQ_DIS,
    /* Parent Signal: CONFIG_ADC_1 ADC Pin, (DIO25) */
    CONFIG_PIN_1 | PIN_INPUT_EN | PIN_NOPULL | PIN_IRQ_DIS,
    /* Parent Signal: CONFIG_I2C_0 SDA, (DIO4) */
    CONFIG_PIN_4 | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_DIS,
    /* Parent Signal: CONFIG_I2C_0 SCL, (DIO3) */
    CONFIG_PIN_5 | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_DIS,
    /* Parent Signal: CONFIG_UART2_0 TX, (DIO17) */
    CONFIG_PIN_2 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MED,
    /* Parent Signal: CONFIG_UART2_0 RX, (DIO16) */
    CONFIG_PIN_3 | PIN_INPUT_EN | PIN_PULLDOWN | PIN_IRQ_DIS,

    PIN_TERMINATE
};

const PINCC26XX_HWAttrs PINCC26XX_hwAttrs = {
    .intPriority = (~0),
    .swiPriority = 0
};

/*
 *  =============================== Power ===============================
 */
#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerCC26X2.h>
#include "ti_drivers_config.h"

extern void PowerCC26XX_standbyPolicy(void);
extern bool PowerCC26XX_calibrate(unsigned int);

const PowerCC26X2_Config PowerCC26X2_config = {
    .enablePolicy             = true,
    .policyInitFxn            = NULL,
    .policyFxn                = PowerCC26XX_standbyPolicy,
    .calibrateFxn             = PowerCC26XX_calibrate,
    .calibrateRCOSC_LF        = true,
    .calibrateRCOSC_HF        = true,
    .enableTCXOFxn            = NULL
};


/*
 *  =============================== RF Driver ===============================
 */
#include <ti/drivers/rf/RF.h>

/*
 * Platform-specific driver configuration
 */
const RFCC26XX_HWAttrsV2 RFCC26XX_hwAttrs = {
    .hwiPriority        = (~0),
    .swiPriority        = (uint8_t)0,
    .xoscHfAlwaysNeeded = true,
    .globalCallback     = NULL,
    .globalEventMask    = 0
};


/*
 *  =============================== TRNG ===============================
 */

#include <ti/drivers/TRNG.h>
#include <ti/drivers/trng/TRNGCC26XX.h>

#define CONFIG_TRNG_COUNT 1

TRNGCC26XX_Object trngCC26XXObjects[CONFIG_TRNG_COUNT];

/*
 *  ======== trngCC26XXHWAttrs ========
 */
static const TRNGCC26XX_HWAttrs trngCC26XXHWAttrs[CONFIG_TRNG_COUNT] = {
    {
        .intPriority = (~0),
        .swiPriority = 0,
        .samplesPerCycle = 240000
    },
};

const TRNG_Config TRNG_config[CONFIG_TRNG_COUNT] = {
    {   /* CONFIG_TRNG_0 */
        .object         = &trngCC26XXObjects[CONFIG_TRNG_0],
        .hwAttrs        = &trngCC26XXHWAttrs[CONFIG_TRNG_0]
    },
};

const uint_least8_t CONFIG_TRNG_0_CONST = CONFIG_TRNG_0;
const uint_least8_t TRNG_count = CONFIG_TRNG_COUNT;

/*
 *  =============================== UART2 ===============================
 */

#include <ti/drivers/UART2.h>
#include <ti/drivers/uart2/UART2CC26X2.h>
#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerCC26X2.h>
#include <ti/devices/cc13x2_cc26x2/inc/hw_memmap.h>
#include <ti/devices/cc13x2_cc26x2/inc/hw_ints.h>

#define CONFIG_UART2_COUNT 1

UART2CC26X2_Object uart2CC26X2Objects[CONFIG_UART2_COUNT];

static unsigned char uart2RxRingBuffer0[32];
static unsigned char uart2TxRingBuffer0[32];

static const UART2CC26X2_HWAttrs uart2CC26X2HWAttrs[CONFIG_UART2_COUNT] = {
  {
    .baseAddr           = UART0_BASE,
    .intNum             = INT_UART0_COMB,
    .intPriority        = (~0),
    .rxPin              = IOID_16,
    .txPin              = IOID_17,
    .ctsPin             = PIN_UNASSIGNED,
    .rtsPin             = PIN_UNASSIGNED,
    .flowControl        = UART2_FLOWCTRL_NONE,
    .rxBufPtr           = uart2RxRingBuffer0,
    .rxBufSize          = sizeof(uart2RxRingBuffer0),
    .txBufPtr           = uart2TxRingBuffer0,
    .txBufSize          = sizeof(uart2TxRingBuffer0),
    .rxChannelMask      = 1 << UDMA_CHAN_UART0_RX,
    .txChannelMask      = 1 << UDMA_CHAN_UART0_TX,
    .txIntFifoThr       = UART2CC26X2_FIFO_THRESHOLD_1_8,
    .rxIntFifoThr       = UART2CC26X2_FIFO_THRESHOLD_4_8
  },
};

const UART2_Config UART2_config[CONFIG_UART2_COUNT] = {
    {   /* CONFIG_UART2_0 */
        .object      = &uart2CC26X2Objects[CONFIG_UART2_0],
        .hwAttrs     = &uart2CC26X2HWAttrs[CONFIG_UART2_0]
    },
};

const uint_least8_t CONFIG_UART2_0_CONST = CONFIG_UART2_0;
const uint_least8_t UART2_count = CONFIG_UART2_COUNT;

/*
 *  =============================== Watchdog ===============================
 */

#include <ti/drivers/Watchdog.h>
#include <ti/drivers/watchdog/WatchdogCC26XX.h>
#include <ti/devices/cc13x2_cc26x2/inc/hw_memmap.h>

#define CONFIG_WATCHDOG_COUNT 1


WatchdogCC26XX_Object watchdogCC26XXObjects[CONFIG_WATCHDOG_COUNT];

const WatchdogCC26XX_HWAttrs watchdogCC26XXHWAttrs[CONFIG_WATCHDOG_COUNT] = {
    /* CONFIG_WATCHDOG_0: period = 1000 */
    {
        .baseAddr    = WDT_BASE,
        .reloadValue = 1000
    },
};

const Watchdog_Config Watchdog_config[CONFIG_WATCHDOG_COUNT] = {
    /* CONFIG_WATCHDOG_0 */
    {
        .fxnTablePtr = &WatchdogCC26XX_fxnTable,
        .object      = &watchdogCC26XXObjects[CONFIG_WATCHDOG_0],
        .hwAttrs     = &watchdogCC26XXHWAttrs[CONFIG_WATCHDOG_0]
    }
};

const uint_least8_t CONFIG_WATCHDOG_0_CONST = CONFIG_WATCHDOG_0;
const uint_least8_t Watchdog_count = CONFIG_WATCHDOG_COUNT;

#include <ti/drivers/Board.h>

/*
 *  ======== Board_initHook ========
 *  Perform any board-specific initialization needed at startup.  This
 *  function is declared weak to allow applications to override it if needed.
 */
void __attribute__((weak)) Board_initHook(void)
{
}

/*
 *  ======== Board_init ========
 *  Perform any initialization needed before using any board APIs
 */
void Board_init(void)
{
    /* ==== /ti/drivers/Power initialization ==== */
    Power_init();

    /* ==== /ti/drivers/PIN initialization ==== */
    if (PIN_init(BoardGpioInitTable) != PIN_SUCCESS) {
        /* Error with PIN_init */
        while (1);
    }
    /* ==== /ti/devices/CCFGTemplate initialization ==== */

    /* ==== /ti/drivers/RF initialization ==== */

    Board_initHook();
}

