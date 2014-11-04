#ifndef __WIIMOTE_DLL_IMP
#define __WIIMOTE_DLL_IMP

#define WM_TWO          0
#define WM_ONE          1
#define WM_B            2
#define WM_A            3
#define WM_MINUS        4
#define WM_HOME         7
#define WM_LEFT         8
#define WM_RIGHT        9
#define WM_DOWN         10
#define WM_UP           11
#define WM_PLUS         12
#define WM_UNKNOWN      14
#define WM_ALL          15

#define WM_NUNCHUCK_Z   16
#define WM_NUNCHUCK_C   17
#define WM_NUNCHUCK_ALL 18

#define WM_CLASSIC_UP           0
#define WM_CLASSIC_LEFT         1
#define WM_CLASSIC_ZR           2
#define WM_CLASSIC_X            3
#define WM_CLASSIC_A            4
#define WM_CLASSIC_Y            5
#define WM_CLASSIC_B            6
#define WM_CLASSIC_ZL           7
#define WM_CLASSIC_R            9
#define WM_CLASSIC_PLUS         10
#define WM_CLASSIC_HOME         11
#define WM_CLASSIC_MINUS        12
#define WM_CLASSIC_L            13
#define WM_CLASSIC_DOWN         20
#define WM_CLASSIC_RIGHT        21
#define WM_CLASSIC_ALL          19

#define WM_GH3_STRUM_UP         0
#define WM_GH3_YELLOW           3
#define WM_GH3_GREEN            4
#define WM_GH3_BLUE             5
#define WM_GH3_RED              6
#define WM_GH3_ORANGE           7
#define WH_GH3_PLUS             10
#define WM_GH3_MINUS            12
#define WM_GH3_STRUM_DOWN       14
#define WM_GH3_ALL              19

typedef double (__cdecl*dfunc0)();
typedef double (__cdecl*dfunc1)(double);
typedef double (__cdecl*dfunc2)(double,double);
typedef double (__cdecl*dfunc3)(double,double,double);
typedef double (__cdecl*dfunc4)(double,double,double,double);
typedef double (__cdecl*dfunc5)(double,double,double,double,double);

HINSTANCE wiidll = LoadLibrary("SuperWiimote.dll");

#define SM_EXPORT __declspec(dllimport) extern

#ifdef __cplusplus
extern "C" {
#endif

SM_EXPORT double InitWiimotes(double max_wiimotes);
SM_EXPORT double UseMotionSensing(double wiimotes, double use_motion_sensing);
SM_EXPORT double UseIRCamera(double wiimotes, double use_ir_camera);

SM_EXPORT double Destroy();
SM_EXPORT double UpdateWiimotes();
SM_EXPORT double LookForWiiomtes();
SM_EXPORT double GetNumWiimotes();

SM_EXPORT double GetWiimoteKey(double wiimote, double key);
SM_EXPORT double GetWiimoteKeyPressed(double wiimote, double key);
SM_EXPORT double GetWiimoteKeyReleased(double wiimote, double key);

SM_EXPORT double RumbleWiimote(double wiimote, double rumble_on);
SM_EXPORT double GetWiimoteBattery(double wiimote);

SM_EXPORT double GetAccelX(double wiimote);
SM_EXPORT double GetAccelY(double wiimote);
SM_EXPORT double GetAccelZ(double wiimote);

SM_EXPORT double GetOrientRoll(double wiimote);
SM_EXPORT double GetOrientPitch(double wiimote);
SM_EXPORT double GetOrientYaw(double wiimote);

SM_EXPORT double GetGForceX(double wiiomte);
SM_EXPORT double GetGForceY(double wiiomte);
SM_EXPORT double GetGForceZ(double wiiomte);

SM_EXPORT double TurnOnLED(double wiimote, double led);
SM_EXPORT double TurnOffLED(double wiimote, double led);
SM_EXPORT double SetWiimoteLED(double wiimote, double led1, double led2, double led3, double led4);
SM_EXPORT double GetLEDStatus(double wiimote, double led);

SM_EXPORT double GetExpansion(double wiimote);

SM_EXPORT double GetClassicControllerKey(double wiimote, double key);
SM_EXPORT double GetClassicControllerKeyPressed(double wiimote, double key);
SM_EXPORT double GetClassicControllerKeyReleased(double wiimote, double key);

SM_EXPORT double GetClassicLPos(double wiimote);
SM_EXPORT double GetClassicRPos(double wiimote);
SM_EXPORT double GetClassicLJoyXPos(double wiimote);
SM_EXPORT double GetClassicLJoyYPos(double wiimote);
SM_EXPORT double GetClassicRJoyXPos(double wiimote);
SM_EXPORT double GetClassicRJoyYPos(double wiimote);

SM_EXPORT double GetGH3ControllerKey(double wiimote, double key);
SM_EXPORT double GetGH3ControllerKeyPressed(double wiimote, double key);
SM_EXPORT double GetGH3ControllerKeyReleased(double wiimote, double key);

SM_EXPORT double GetGH3WhammyBarPos(double wiimote);

SM_EXPORT double GetIRDist(double wiimote);
SM_EXPORT double GetZDist(double wiimote);
SM_EXPORT double GetDotVisible(double wiimote, double dot);
SM_EXPORT double GetDotX(double wiimote, double dot);
SM_EXPORT double GetDotY(double wiimote, double dot);
SM_EXPORT double GetIRX(double wiimote, double dot);
SM_EXPORT double GetIRY(double wiimote, double dot);

SM_EXPORT double GetNunchukControllerKey(double wiimote, double key);
SM_EXPORT double GetNunchukControllerKeyPressed(double wiimote, double key);
SM_EXPORT double GetNunchukControllerKeyReleased(double wiimote, double key);

SM_EXPORT double GetNunchukOrientRoll(double wiimote);
SM_EXPORT double GetNunchukOrientPitch(double wiimote);
SM_EXPORT double GetNunchukOrientYaw(double wiimote);
SM_EXPORT double GetNunchukGForceX(double wiimote);
SM_EXPORT double GetNunchukGForceY(double wiimote);
SM_EXPORT double GetNunchukGForceZ(double wiimote);

SM_EXPORT double GetBalanceBoardTR(double wiimote);
SM_EXPORT double GetBalanceBoardTL(double wiimote);
SM_EXPORT double GetBalanceBoardBR(double wiimote);
SM_EXPORT double GetBalanceBoardBL(double wiimote);

#ifdef __cplusplus
}
#endif

#endif
