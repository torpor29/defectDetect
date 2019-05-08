#ifndef _BVMAINCORE_H
#define _BVMAINCORE_H

#ifdef BVMAINCORE_EXPORTS
#define BVMAINCORE_API __declspec(dllexport)
#else
#define BVMAINCORE_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define BV_SUCCESS							(0)
#define BV_ERROR_INVALID_PARAMETERS			(-1)
#define BV_ERROR_UNSUPPORTED				(-2)
#define BV_ERROR_EXCEPTION					(-3)
#define BV_ERROR_BUSY						(-4)
#define BV_ERROR_CREATEFAILED				(-5)
#define BV_ERROR_OPENFAILED					(-6)
#define BV_ERROR_TIMEOUT					(-7)
#define BV_ERROR_BUFFNOTENOUGH				(-8)
#define BV_ERROR_LACKOFRESOURCE				(-9)

#define pr_debug printf("%s %d failed\n", __FILE__, __LINE__);

BVMAINCORE_API int Roseek_MainCore_Init();
BVMAINCORE_API int Roseek_MainCore_UnInit();
BVMAINCORE_API int Roseek_MainCore_SetLogLevel(UINT32 Level);
BVMAINCORE_API int Roseek_MainCore_Start();
BVMAINCORE_API int Roseek_MainCore_Stop();

//EEPROM

BVMAINCORE_API int Roseek_EEPROM_Write(UINT32 Offset, void *pBuff, UINT32 DataSize);
BVMAINCORE_API int Roseek_EEPROM_Read(UINT32 Offset, void *pBuff, UINT32 DataSize);


//WatchDog

enum 
{
	BV_WATCHDOG_MODE_CLOSE,
	BV_WATCHDOG_MODE_OPEN,
	BV_WATCHDOG_MODE_MAX
};

#define BV_WATCHDOG_TIMER_MAX_IN_SEC		(60)

BVMAINCORE_API int Roseek_WatchDog_SetMode(UINT32 Mode);
BVMAINCORE_API int Roseek_WatchDog_GetMode(UINT32 *pMode);
BVMAINCORE_API int Roseek_WatchDog_SetTimer(UINT32 Time_sec);
BVMAINCORE_API int Roseek_WatchDog_GetTimer(UINT32 *pTime_sec);
BVMAINCORE_API int Roseek_WatchDog_Kick();

//System

enum
{
	BV_RESET_MODE_WARM,
	BV_RESET_MODE_COLD,
	BV_RESET_MODE_MAX
};

enum
{
	BV_SERIAL_PORT_232,
	BV_SERIAL_PORT_485,
	BV_SERIAL_PORT_MAX
};


#define BV_MAX_MODULES_NUM			30
#define BV_MAX_MODULE_INFO_SIZE		256

BVMAINCORE_API int Roseek_System_Reset(UINT32 Mode);
BVMAINCORE_API int Roseek_System_GetSerialPortName(UINT32 ID, char *pNameBuff, UINT32 BuffSize);
BVMAINCORE_API int Roseek_System_GetTemprature(float *pTemprature);
BVMAINCORE_API int Roseek_System_GetUniqueNums(UINT8 *pNumsBuff, UINT32 BuffSize);
BVMAINCORE_API int Roseek_System_GetDevModel(char *pModelBuff, UINT32 BuffSize);
BVMAINCORE_API int Roseek_System_GetDevSN(char *pSNBuff, UINT32 BuffSize);
BVMAINCORE_API int Roseek_System_GetHWMixVersion(char *pVerBuff, UINT32 BuffSize);
BVMAINCORE_API int Roseek_System_GetFWMixVersion(char *pVerBuff, UINT32 BuffSize);
BVMAINCORE_API int Roseek_System_RegisterModule(const char *pModuleInfo);
BVMAINCORE_API int Roseek_System_ReadDevInfo(char *pInfoBuff, UINT32 BuffSize);
BVMAINCORE_API int Roseek_System_Private(void *pIn, UINT32 InSize, void *pOut, UINT32 *pInOutSize);
BVMAINCORE_API int Roseek_System_UpdateFPGA(const char *pFilePath, UINT32 *pProgress);
BVMAINCORE_API int Roseek_System_UpdateMCU(const char *pFilePath, UINT32 *pProgress);
BVMAINCORE_API int Roseek_System_StoreRunParams();
BVMAINCORE_API int Roseek_System_ApplyRunParams();
BVMAINCORE_API int Roseek_System_RestoreRunParams();
BVMAINCORE_API int Roseek_System_SetUserAccount(const char *pUsername, const char *pPassword);
BVMAINCORE_API int Roseek_System_GetUserAccount(char *pUsername, UINT32 NameBuffSize, char *pPassword, UINT32 WordBuffSize);

//IO

enum
{
	DO_0,
	DO_1,
	DO_2,
	DO_3,
	DO_4,
	DO_5,
	DO_6,
	DO_7,
	DO_MAX
};

enum
{
	DI_0,
	DI_1,
	DI_2,
	DI_3,
	DI_4,
	DI_5,
	DI_6,
	DI_7,
	DI_MAX
};

enum
{
	DI_MODE_NORMAL,
	DI_MODE_TRIG_DELAY,
	DI_MODE_COUNTER,
	DI_MODE_MAX
};

enum
{
	DI_COUNT_CHANGE,
	DI_COUNT_FALLING,
	DI_COUNT_RISING,
	DI_COUNT_MAX
};

enum
{
	DI_EVENT_FALLING,
	DI_EVENT_RISING,
	DI_EVENT_CHANGE,
	DI_EVENT_MAX
};

enum
{
	DI_EVENTMASK_INVALID,
	DI_EVENTMASK_VALID,
	DI_EVENTMASK_MAX
};

BVMAINCORE_API int Roseek_DO_SetPort(UINT8 State);
BVMAINCORE_API int Roseek_DO_GetPort(UINT8 *pState);
BVMAINCORE_API int Roseek_DI_SetMode(UINT8 ID, UINT8 Mode);
BVMAINCORE_API int Roseek_DI_GetMode(UINT8 ID, UINT8 *pMode);
BVMAINCORE_API int Roseek_DI_SetEventCountMode(UINT8 ID, UINT8 Enable, UINT8 Mode);
BVMAINCORE_API int Roseek_DI_GetEventCountMode(UINT8 ID, UINT8 *pEnable, UINT8 *pMode);
BVMAINCORE_API int Roseek_DI_GetEventCount(UINT32 *pCount);
BVMAINCORE_API int Roseek_DI_ClearEventCount(void);
BVMAINCORE_API int Roseek_DI_SetTrigDelayTime(UINT8 ID, UINT32 TimeInUS);
BVMAINCORE_API int Roseek_DI_GetTrigDelayTime(UINT8 ID, UINT32 *pTimeInUS);
BVMAINCORE_API int Roseek_DI_GetPort(UINT8 *pState);
BVMAINCORE_API int Roseek_DI_SetEventMode(UINT8 ID, UINT8 Mode);
BVMAINCORE_API int Roseek_DI_GetEventMode(UINT8 ID, UINT8 *pMode);
BVMAINCORE_API int Roseek_DI_SetEventMask(UINT8 IntValid);
BVMAINCORE_API int Roseek_DI_GetEventMask(UINT8 *pIntValid);
BVMAINCORE_API int Roseek_DI_SetFilter(UINT8 ID, UINT32 TimeInUS);
BVMAINCORE_API int Roseek_DI_GetFilter(UINT8 ID, UINT32 *pTimeInUS);


typedef int(*FUNC_DIEVENTCB)(UINT32 IntSrc);
BVMAINCORE_API int Roseek_DI_RegisterEventCallBack(FUNC_DIEVENTCB Func);

//Led Driver

enum
{
	LED_DRIVER_1,
	LED_DRIVER_2,
	LED_DRIVER_3,
	LED_DRIVER_4,
	LED_DRIVER_MAX
};


enum
{
	BV_LEDSTATUS_INDEX_0 = 1,
	BV_LEDSTATUS_INDEX_1,
	BV_LEDSTATUS_INDEX_MAX
};

enum LED_CONFIG 
{ 
	BV_LEDDRIVER_MODE_USER,
	BV_LEDDRIVER_MODE_SYNC_HIGHLEVEL,
	BV_LEDDRIVER_MODE_SYNC_LOWLEVEL,
	RESERVED1,
	RESERVED2,
	BV_LEDDRIVER_MODE_TRIG,
	BV_LEDDRIVER_MODE_MAX
};

enum
{
	BV_LEDMASK_INVALID,
	BV_LEDMASK_VALID,
	BV_LEDMASK_MAX
};

enum LEDSTATUS
{
	BV_LEDSTATUS_CLOSED,
	BV_LEDSTATUS_RED,
	BV_LEDSTATUS_GREEN,
	BV_LEDSTATUS_RED_GREEN,
	BV_LEDSTATUS_RED_BLINK,
	BV_LEDSTATUS_GREEN_BLINK,
	BV_LEDSTATUS_RG_BINK,
	BV_LEDSTATUS_MAX
};


#define BV_LED_MAX_DRV_PULSE_WIDTH_IN_US		(1000000L)
#define BV_LED_MAX_DRV_CURRENT_IN_MA			(1550)

BVMAINCORE_API int Roseek_LEDDriver_SetPulseWidth(UINT8 ID, UINT32 WidthInUS);
BVMAINCORE_API int Roseek_LEDDriver_GetPulseWidth(UINT8 ID, UINT32 *pWidthInUS);
BVMAINCORE_API int Roseek_LEDDriver_SetCurrent(UINT8 ID, UINT16 DrvCurrent_mA);
BVMAINCORE_API int Roseek_LEDDriver_GetCurrent(UINT8 ID, UINT16 *pDrvCurrent_mA);
BVMAINCORE_API int Roseek_LEDDriver_SetMode(UINT8 ID, UINT8 Mode);
BVMAINCORE_API int Roseek_LEDDriver_GetMode(UINT8 ID, UINT8 *pMode);
BVMAINCORE_API int Roseek_LEDDriver_SetState(UINT8 ID, UINT8 State);
BVMAINCORE_API int Roseek_LEDDriver_GetState(UINT8 ID, UINT8 *pState);
BVMAINCORE_API int Roseek_LEDDriver_SetMask(UINT8 ID, UINT8 Mask);
BVMAINCORE_API int Roseek_LEDDriver_GetMask(UINT8 ID, UINT8 *pMask);
BVMAINCORE_API int Roseek_LED_SetState(UINT8 ID, UINT8 Status);

BVMAINCORE_API int Roseek_POE_GetPowerState(UINT8 *pStatus);

#ifdef __cplusplus
};
#endif

#endif
