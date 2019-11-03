#pragma once

/* Version 1.0 */

/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* LIBRARY INFO
 *
 * AutoItX v3 32bit port for MINGW
 * AutoIt website: autoitscript.com
 * Autor: michal037 - github.com/michal037
 */

/* HOW TO USE -- README
 *
 * Store AutoItX3.dll with your executable program.
 * Link libautoit3mingw.dll.a library to your project.
 * Use autoit3.h header in your programs.
 * Initialize library at begin of your program -> AU3_Init();
 * Optional uninitialize (function added by me) -> AU3_Exit();
 * Use this library as original without changes.
 */

#ifndef AUTOIT3_MINGW_H
#define AUTOIT3_MINGW_H 1

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

/* "Default" value for _some_ int parameters (largest negative number) */
#define AU3_INTDEFAULT (-2147483647)

/*
 * nBufSize
 * When used for specifying the size of a resulting string buffer this is the number of CHARACTERS
 * in that buffer, including the null terminator.  For example:
 *
 * WCHAR szBuffer[10];
 * AU3_ClipGet(szBuffer, 10);
 *
 * The resulting string will be truncated at 9 characters with the the terminating null in the 10th.
 */

////////////////////////////////////////////////////////////////////////////////
// Exported functions                                                         //
////////////////////////////////////////////////////////////////////////////////

/* Use this function when you want to use this library */
void WINAPI AU3_Init(void);

/* Use this function when you want to uninitialize library (optional)
 * Automatically at the end of the program */
void AU3_Exit(void);

/* Function pointer declarations */
typedef int (*_AU3_error)(void);

typedef int WINAPI (*_AU3_AutoItSetOption)(LPCWSTR szOption, int nValue);

typedef void WINAPI (*_AU3_ClipGet)(LPWSTR szClip, int nBufSize);
typedef void WINAPI (*_AU3_ClipPut)(LPCWSTR szClip);
/* DEFAULTS _AU3_ControlClick: int nX = AU3_INTDEFAULT, int nY = AU3_INTDEFAULT */
typedef int WINAPI (*_AU3_ControlClick)(LPCWSTR szTitle, LPCWSTR szText, LPCWSTR szControl, LPCWSTR szButton, int nNumClicks, int nX, int nY);
/* DEFAULTS _AU3_ControlClickByHandle: int nX = AU3_INTDEFAULT, int nY = AU3_INTDEFAULT */
typedef int WINAPI (*_AU3_ControlClickByHandle)(HWND hWnd, HWND hCtrl, LPCWSTR szButton, int nNumClicks, int nX, int nY);
typedef void WINAPI (*_AU3_ControlCommand)(LPCWSTR szTitle, LPCWSTR szText, LPCWSTR szControl, LPCWSTR szCommand, LPCWSTR szExtra, LPWSTR szResult, int nBufSize);
typedef void WINAPI (*_AU3_ControlCommandByHandle)(HWND hWnd, HWND hCtrl, LPCWSTR szCommand, LPCWSTR szExtra, LPWSTR szResult, int nBufSize);
typedef void WINAPI (*_AU3_ControlListView)(LPCWSTR szTitle, LPCWSTR szText, LPCWSTR szControl, LPCWSTR szCommand, LPCWSTR szExtra1, LPCWSTR szExtra2, LPWSTR szResult, int nBufSize);
typedef void WINAPI (*_AU3_ControlListViewByHandle)(HWND hWnd, HWND hCtrl, LPCWSTR szCommand, LPCWSTR szExtra1, LPCWSTR szExtra2, LPWSTR szResult, int nBufSize);
typedef int WINAPI (*_AU3_ControlDisable)(LPCWSTR szTitle, LPCWSTR szText, LPCWSTR szControl);
typedef int WINAPI (*_AU3_ControlDisableByHandle)(HWND hWnd, HWND hCtrl);
typedef int WINAPI (*_AU3_ControlEnable)(LPCWSTR szTitle, LPCWSTR szText, LPCWSTR szControl);
typedef int WINAPI (*_AU3_ControlEnableByHandle)(HWND hWnd, HWND hCtrl);
typedef int WINAPI (*_AU3_ControlFocus)(LPCWSTR szTitle, LPCWSTR szText, LPCWSTR szControl);
typedef int WINAPI (*_AU3_ControlFocusByHandle)(HWND hWnd, HWND hCtrl);
typedef void WINAPI (*_AU3_ControlGetFocus)(LPCWSTR szTitle, LPCWSTR szText, LPWSTR szControlWithFocus, int nBufSize);
typedef void WINAPI (*_AU3_ControlGetFocusByHandle)(HWND hWnd, LPWSTR szControlWithFocus, int nBufSize);
typedef HWND WINAPI (*_AU3_ControlGetHandle)(HWND hWnd, LPCWSTR szControl);
typedef void WINAPI (*_AU3_ControlGetHandleAsText)(LPCWSTR szTitle, /*[in,defaultvalue("")]*/LPCWSTR szText, LPCWSTR szControl, LPWSTR szRetText, int nBufSize);
typedef int WINAPI (*_AU3_ControlGetPos)(LPCWSTR szTitle, LPCWSTR szText, LPCWSTR szControl, LPRECT lpRect);
typedef int WINAPI (*_AU3_ControlGetPosByHandle)(HWND hWnd, HWND hCtrl, LPRECT lpRect);
typedef void WINAPI (*_AU3_ControlGetText)(LPCWSTR szTitle, LPCWSTR szText, LPCWSTR szControl, LPWSTR szControlText, int nBufSize);
typedef void WINAPI (*_AU3_ControlGetTextByHandle)(HWND hWnd, HWND hCtrl, LPWSTR szControlText, int nBufSize);
typedef int WINAPI (*_AU3_ControlHide)(LPCWSTR szTitle, LPCWSTR szText, LPCWSTR szControl);
typedef int WINAPI (*_AU3_ControlHideByHandle)(HWND hWnd, HWND hCtrl);
/* DEFAULTS _AU3_ControlMove: int nWidth = -1, int nHeight = -1 */
typedef int WINAPI (*_AU3_ControlMove)(LPCWSTR szTitle, LPCWSTR szText, LPCWSTR szControl, int nX, int nY, int nWidth, int nHeight);
/* DEFAULTS _AU3_ControlMoveByHandle: int nWidth = -1, int nHeight = -1 */
typedef int WINAPI (*_AU3_ControlMoveByHandle)(HWND hWnd, HWND hCtrl, int nX, int nY, int nWidth, int nHeight);
/* DEFAULTS _AU3_ControlSend: int nMode = 0 */
typedef int WINAPI (*_AU3_ControlSend)(LPCWSTR szTitle, LPCWSTR szText, LPCWSTR szControl, LPCWSTR szSendText, int nMode);
/* DEFAULTS _AU3_ControlSendByHandle: int nMode = 0 */
typedef int WINAPI (*_AU3_ControlSendByHandle)(HWND hWnd, HWND hCtrl, LPCWSTR szSendText, int nMode);
typedef int WINAPI (*_AU3_ControlSetText)(LPCWSTR szTitle, LPCWSTR szText, LPCWSTR szControl, LPCWSTR szControlText);
typedef int WINAPI (*_AU3_ControlSetTextByHandle)(HWND hWnd, HWND hCtrl, LPCWSTR szControlText);
typedef int WINAPI (*_AU3_ControlShow)(LPCWSTR szTitle, LPCWSTR szText, LPCWSTR szControl);
typedef int WINAPI (*_AU3_ControlShowByHandle)(HWND hWnd, HWND hCtrl);
typedef void WINAPI (*_AU3_ControlTreeView)(LPCWSTR szTitle, LPCWSTR szText, LPCWSTR szControl, LPCWSTR szCommand, LPCWSTR szExtra1, LPCWSTR szExtra2, LPWSTR szResult, int nBufSize);
typedef void WINAPI (*_AU3_ControlTreeViewByHandle)(HWND hWnd, HWND hCtrl, LPCWSTR szCommand, LPCWSTR szExtra1, LPCWSTR szExtra2, LPWSTR szResult, int nBufSize);

typedef void WINAPI (*_AU3_DriveMapAdd)(LPCWSTR szDevice, LPCWSTR szShare, int nFlags, /*[in,defaultvalue("")]*/LPCWSTR szUser, /*[in,defaultvalue("")]*/LPCWSTR szPwd, LPWSTR szResult, int nBufSize);
typedef int WINAPI (*_AU3_DriveMapDel)(LPCWSTR szDevice);
typedef void WINAPI (*_AU3_DriveMapGet)(LPCWSTR szDevice, LPWSTR szMapping, int nBufSize);

typedef int WINAPI (*_AU3_IsAdmin)(void);

/* DEFAULTS _AU3_MouseClick: int nX = AU3_INTDEFAULT, int nY = AU3_INTDEFAULT, int nClicks = 1, int nSpeed = -1 */
typedef int WINAPI (*_AU3_MouseClick)(/*[in,defaultvalue("LEFT")]*/LPCWSTR szButton, int nX, int nY, int nClicks, int nSpeed);
/* DEFAULTS _AU3_MouseClickDrag: int nSpeed = -1 */
typedef int WINAPI (*_AU3_MouseClickDrag)(LPCWSTR szButton, int nX1, int nY1, int nX2, int nY2, int nSpeed);
typedef void WINAPI (*_AU3_MouseDown)(/*[in,defaultvalue("LEFT")]*/LPCWSTR szButton);
typedef int WINAPI (*_AU3_MouseGetCursor)(void);
typedef void WINAPI (*_AU3_MouseGetPos)(LPPOINT lpPoint);
/* DEFAULTS _AU3_MouseMove: int nSpeed = -1 */
typedef int WINAPI (*_AU3_MouseMove)(int nX, int nY, int nSpeed);
typedef void WINAPI (*_AU3_MouseUp)(/*[in,defaultvalue("LEFT")]*/LPCWSTR szButton);
typedef void WINAPI (*_AU3_MouseWheel)(LPCWSTR szDirection, int nClicks);

typedef int WINAPI (*_AU3_Opt)(LPCWSTR szOption, int nValue);

/* DEFAULTS _AU3_PixelChecksum: int nStep = 1 */
typedef unsigned int WINAPI (*_AU3_PixelChecksum)(LPRECT lpRect, int nStep);
typedef int WINAPI (*_AU3_PixelGetColor)(int nX, int nY);
typedef void WINAPI (*_AU3_PixelSearch)(LPRECT lpRect, int nCol, /*default 0*/int nVar, /*default 1*/int nStep, LPPOINT pPointResult);
typedef int WINAPI (*_AU3_ProcessClose)(LPCWSTR szProcess);
typedef int WINAPI (*_AU3_ProcessExists)(LPCWSTR szProcess);
typedef int WINAPI (*_AU3_ProcessSetPriority)(LPCWSTR szProcess, int nPriority);
/* DEFAULTS _AU3_ProcessWait: int nTimeout = 0 */
typedef int WINAPI (*_AU3_ProcessWait)(LPCWSTR szProcess, int nTimeout);
/* DEFAULTS _AU3_ProcessWaitClose: int nTimeout = 0 */
typedef int WINAPI (*_AU3_ProcessWaitClose)(LPCWSTR szProcess, int nTimeout);

/* DEFAULTS _AU3_Run: int nShowFlag = SW_SHOWNORMAL */
typedef int WINAPI (*_AU3_Run)(LPCWSTR szProgram, /*[in,defaultvalue("")]*/LPCWSTR szDir, int nShowFlag);
/* DEFAULTS _AU3_RunWait: int nShowFlag = SW_SHOWNORMAL */
typedef int WINAPI (*_AU3_RunWait)(LPCWSTR szProgram, /*[in,defaultvalue("")]*/LPCWSTR szDir, int nShowFlag);
/* DEFAULTS _AU3_RunAs: int nShowFlag = SW_SHOWNORMAL */
typedef int WINAPI (*_AU3_RunAs)(LPCWSTR szUser, LPCWSTR szDomain, LPCWSTR szPassword, int nLogonFlag, LPCWSTR szProgram, /*[in,defaultvalue("")]*/LPCWSTR szDir, int nShowFlag);
/* DEFAULTS _AU3_RunAsWait: int nShowFlag = SW_SHOWNORMAL */
typedef int WINAPI (*_AU3_RunAsWait)(LPCWSTR szUser, LPCWSTR szDomain, LPCWSTR szPassword, int nLogonFlag, LPCWSTR szProgram, /*[in,defaultvalue("")]*/LPCWSTR szDir, int nShowFlag);

/* DEFAULTS _AU3_Send: int nMode = 0 */
typedef void WINAPI (*_AU3_Send)(LPCWSTR szSendText, int nMode);
typedef int WINAPI (*_AU3_Shutdown)(int nFlags);
typedef void WINAPI (*_AU3_Sleep)(int nMilliseconds);
typedef int WINAPI (*_AU3_StatusbarGetText)(LPCWSTR szTitle, /*[in,defaultvalue("")]*/LPCWSTR szText, /*[in,defaultvalue(1)]*/int nPart, LPWSTR szStatusText, int nBufSize);
typedef int WINAPI (*_AU3_StatusbarGetTextByHandle)(HWND hWnd, /*[in,defaultvalue(1)]*/int nPart, LPWSTR szStatusText, int nBufSize);

/* DEFAULTS _AU3_ToolTip: int nX = AU3_INTDEFAULT, int nY = AU3_INTDEFAULT */
typedef void WINAPI (*_AU3_ToolTip)(LPCWSTR szTip, int nX, int nY);

typedef int WINAPI (*_AU3_WinActivate)(LPCWSTR szTitle, /*[in,defaultvalue("")]*/LPCWSTR szText);
typedef int WINAPI (*_AU3_WinActivateByHandle)(HWND hWnd);
typedef int WINAPI (*_AU3_WinActive)(LPCWSTR szTitle, /*[in,defaultvalue("")]*/LPCWSTR szText);
typedef int WINAPI (*_AU3_WinActiveByHandle)(HWND hWnd);
typedef int WINAPI (*_AU3_WinClose)(LPCWSTR szTitle, /*[in,defaultvalue("")]*/LPCWSTR szText);
typedef int WINAPI (*_AU3_WinCloseByHandle)(HWND hWnd);
typedef int WINAPI (*_AU3_WinExists)(LPCWSTR szTitle, /*[in,defaultvalue("")]*/LPCWSTR szText);
typedef int WINAPI (*_AU3_WinExistsByHandle)(HWND hWnd);
typedef int WINAPI (*_AU3_WinGetCaretPos)(LPPOINT lpPoint);
typedef void WINAPI (*_AU3_WinGetClassList)(LPCWSTR szTitle, /*[in,defaultvalue("")]*/LPCWSTR szText, LPWSTR szRetText, int nBufSize);
typedef void WINAPI (*_AU3_WinGetClassListByHandle)(HWND hWnd, LPWSTR szRetText, int nBufSize);
typedef int WINAPI (*_AU3_WinGetClientSize)(LPCWSTR szTitle, /*[in,defaultvalue("")]*/LPCWSTR szText, LPRECT lpRect);
typedef int WINAPI (*_AU3_WinGetClientSizeByHandle)(HWND hWnd, LPRECT lpRect);
typedef HWND WINAPI (*_AU3_WinGetHandle)(LPCWSTR szTitle, /*[in,defaultvalue("")]*/LPCWSTR szText);
typedef void WINAPI (*_AU3_WinGetHandleAsText)(LPCWSTR szTitle, /*[in,defaultvalue("")]*/LPCWSTR szText, LPWSTR szRetText, int nBufSize);
typedef int WINAPI (*_AU3_WinGetPos)(LPCWSTR szTitle, /*[in,defaultvalue("")]*/LPCWSTR szText, LPRECT lpRect);
typedef int WINAPI (*_AU3_WinGetPosByHandle)(HWND hWnd, LPRECT lpRect);
typedef DWORD WINAPI (*_AU3_WinGetProcess)(LPCWSTR szTitle, /*[in,defaultvalue("")]*/LPCWSTR szText);
typedef DWORD WINAPI (*_AU3_WinGetProcessByHandle)(HWND hWnd);
typedef int WINAPI (*_AU3_WinGetState)(LPCWSTR szTitle, /*[in,defaultvalue("")]*/LPCWSTR szText);
typedef int WINAPI (*_AU3_WinGetStateByHandle)(HWND hWnd);
typedef void WINAPI (*_AU3_WinGetText)(LPCWSTR szTitle, /*[in,defaultvalue("")]*/LPCWSTR szText, LPWSTR szRetText, int nBufSize);
typedef void WINAPI (*_AU3_WinGetTextByHandle)(HWND hWnd, LPWSTR szRetText, int nBufSize);
typedef void WINAPI (*_AU3_WinGetTitle)(LPCWSTR szTitle, /*[in,defaultvalue("")]*/LPCWSTR szText, LPWSTR szRetText, int nBufSize);
typedef void WINAPI (*_AU3_WinGetTitleByHandle)(HWND hWnd, LPWSTR szRetText, int nBufSize);
typedef int WINAPI (*_AU3_WinKill)(LPCWSTR szTitle, /*[in,defaultvalue("")]*/LPCWSTR szText);
typedef int WINAPI (*_AU3_WinKillByHandle)(HWND hWnd);
typedef int WINAPI (*_AU3_WinMenuSelectItem)(LPCWSTR szTitle, /*[in,defaultvalue("")]*/LPCWSTR szText, LPCWSTR szItem1, LPCWSTR szItem2, LPCWSTR szItem3, LPCWSTR szItem4, LPCWSTR szItem5, LPCWSTR szItem6, LPCWSTR szItem7, LPCWSTR szItem8);
typedef int WINAPI (*_AU3_WinMenuSelectItemByHandle)(HWND hWnd, LPCWSTR szItem1, LPCWSTR szItem2, LPCWSTR szItem3, LPCWSTR szItem4, LPCWSTR szItem5, LPCWSTR szItem6, LPCWSTR szItem7, LPCWSTR szItem8);
typedef void WINAPI (*_AU3_WinMinimizeAll)();
typedef void WINAPI (*_AU3_WinMinimizeAllUndo)();
/* DEFAULTS _AU3_WinMove: int nWidth = -1, int nHeight = -1 */
typedef int WINAPI (*_AU3_WinMove)(LPCWSTR szTitle, /*[in,defaultvalue("")]*/LPCWSTR szText, int nX, int nY, int nWidth, int nHeight);
/* DEFAULTS _AU3_WinMoveByHandle: int nWidth = -1, int nHeight = -1 */
typedef int WINAPI (*_AU3_WinMoveByHandle)(HWND hWnd, int nX, int nY, int nWidth, int nHeight);
typedef int WINAPI (*_AU3_WinSetOnTop)(LPCWSTR szTitle, /*[in,defaultvalue("")]*/LPCWSTR szText, int nFlag);
typedef int WINAPI (*_AU3_WinSetOnTopByHandle)(HWND hWnd, int nFlag);
typedef int WINAPI (*_AU3_WinSetState)(LPCWSTR szTitle, /*[in,defaultvalue("")]*/LPCWSTR szText, int nFlags);
typedef int WINAPI (*_AU3_WinSetStateByHandle)(HWND hWnd, int nFlags);
typedef int WINAPI (*_AU3_WinSetTitle)(LPCWSTR szTitle,/*[in,defaultvalue("")]*/ LPCWSTR szText, LPCWSTR szNewTitle);
typedef int WINAPI (*_AU3_WinSetTitleByHandle)(HWND hWnd, LPCWSTR szNewTitle);
typedef int WINAPI (*_AU3_WinSetTrans)(LPCWSTR szTitle, /*[in,defaultvalue("")]*/LPCWSTR szText, int nTrans);
typedef int WINAPI (*_AU3_WinSetTransByHandle)(HWND hWnd, int nTrans);
/* DEFAULTS _AU3_WinWait: int nTimeout = 0 */
typedef int WINAPI (*_AU3_WinWait)(LPCWSTR szTitle, /*[in,defaultvalue("")]*/LPCWSTR szText, int nTimeout);
typedef int WINAPI (*_AU3_WinWaitByHandle)(HWND hWnd, int nTimeout);
/* DEFAULTS _AU3_WinWaitActive: int nTimeout = 0 */
typedef int WINAPI (*_AU3_WinWaitActive)(LPCWSTR szTitle, /*[in,defaultvalue("")]*/LPCWSTR szText, int nTimeout);
typedef int WINAPI (*_AU3_WinWaitActiveByHandle)(HWND hWnd, int nTimeout);
/* DEFAULTS _AU3_WinWaitClose: int nTimeout = 0 */
typedef int WINAPI (*_AU3_WinWaitClose)(LPCWSTR szTitle, /*[in,defaultvalue("")]*/LPCWSTR szText, int nTimeout);
typedef int WINAPI (*_AU3_WinWaitCloseByHandle)(HWND hWnd, int nTimeout);
typedef int WINAPI (*_AU3_WinWaitNotActive)(LPCWSTR szTitle, /*[in,defaultvalue("")]*/LPCWSTR szText, int nTimeout);
/* DEFAULTS _AU3_WinWaitNotActiveByHandle: int nTimeout = 0 */
typedef int WINAPI (*_AU3_WinWaitNotActiveByHandle)(HWND hWnd, int nTimeout);

/* Function pointer extern definitions */
extern _AU3_error AU3_error;
extern _AU3_AutoItSetOption AU3_AutoItSetOption;
extern _AU3_ClipGet AU3_ClipGet;
extern _AU3_ClipPut AU3_ClipPut;
extern _AU3_ControlClick AU3_ControlClick;
extern _AU3_ControlClickByHandle AU3_ControlClickByHandle;
extern _AU3_ControlCommand AU3_ControlCommand;
extern _AU3_ControlCommandByHandle AU3_ControlCommandByHandle;
extern _AU3_ControlListView AU3_ControlListView;
extern _AU3_ControlListViewByHandle AU3_ControlListViewByHandle;
extern _AU3_ControlDisable AU3_ControlDisable;
extern _AU3_ControlDisableByHandle AU3_ControlDisableByHandle;
extern _AU3_ControlEnable AU3_ControlEnable;
extern _AU3_ControlEnableByHandle AU3_ControlEnableByHandle;
extern _AU3_ControlFocus AU3_ControlFocus;
extern _AU3_ControlFocusByHandle AU3_ControlFocusByHandle;
extern _AU3_ControlGetFocus AU3_ControlGetFocus;
extern _AU3_ControlGetFocusByHandle AU3_ControlGetFocusByHandle;
extern _AU3_ControlGetHandle AU3_ControlGetHandle;
extern _AU3_ControlGetHandleAsText AU3_ControlGetHandleAsText;
extern _AU3_ControlGetPos AU3_ControlGetPos;
extern _AU3_ControlGetPosByHandle AU3_ControlGetPosByHandle;
extern _AU3_ControlGetText AU3_ControlGetText;
extern _AU3_ControlGetTextByHandle AU3_ControlGetTextByHandle;
extern _AU3_ControlHide AU3_ControlHide;
extern _AU3_ControlHideByHandle AU3_ControlHideByHandle;
extern _AU3_ControlMove AU3_ControlMove;
extern _AU3_ControlMoveByHandle AU3_ControlMoveByHandle;
extern _AU3_ControlSend AU3_ControlSend;
extern _AU3_ControlSendByHandle AU3_ControlSendByHandle;
extern _AU3_ControlSetText AU3_ControlSetText;
extern _AU3_ControlSetTextByHandle AU3_ControlSetTextByHandle;
extern _AU3_ControlShow AU3_ControlShow;
extern _AU3_ControlShowByHandle AU3_ControlShowByHandle;
extern _AU3_ControlTreeView AU3_ControlTreeView;
extern _AU3_ControlTreeViewByHandle AU3_ControlTreeViewByHandle;
extern _AU3_DriveMapAdd AU3_DriveMapAdd;
extern _AU3_DriveMapDel AU3_DriveMapDel;
extern _AU3_DriveMapGet AU3_DriveMapGet;
extern _AU3_IsAdmin AU3_IsAdmin;
extern _AU3_MouseClick AU3_MouseClick;
extern _AU3_MouseClickDrag AU3_MouseClickDrag;
extern _AU3_MouseDown AU3_MouseDown;
extern _AU3_MouseGetCursor AU3_MouseGetCursor;
extern _AU3_MouseGetPos AU3_MouseGetPos;
extern _AU3_MouseMove AU3_MouseMove;
extern _AU3_MouseUp AU3_MouseUp;
extern _AU3_MouseWheel AU3_MouseWheel;
extern _AU3_Opt AU3_Opt;
extern _AU3_PixelChecksum AU3_PixelChecksum;
extern _AU3_PixelGetColor AU3_PixelGetColor;
extern _AU3_PixelSearch AU3_PixelSearch;
extern _AU3_ProcessClose AU3_ProcessClose;
extern _AU3_ProcessExists AU3_ProcessExists;
extern _AU3_ProcessSetPriority AU3_ProcessSetPriority;
extern _AU3_ProcessWait AU3_ProcessWait;
extern _AU3_ProcessWaitClose AU3_ProcessWaitClose;
extern _AU3_Run AU3_Run;
extern _AU3_RunWait AU3_RunWait;
extern _AU3_RunAs AU3_RunAs;
extern _AU3_RunAsWait AU3_RunAsWait;
extern _AU3_Send AU3_Send;
extern _AU3_Shutdown AU3_Shutdown;
extern _AU3_Sleep AU3_Sleep;
extern _AU3_StatusbarGetText AU3_StatusbarGetText;
extern _AU3_StatusbarGetTextByHandle AU3_StatusbarGetTextByHandle;
extern _AU3_ToolTip AU3_ToolTip;
extern _AU3_WinActivate AU3_WinActivate;
extern _AU3_WinActivateByHandle AU3_WinActivateByHandle;
extern _AU3_WinActive AU3_WinActive;
extern _AU3_WinActiveByHandle AU3_WinActiveByHandle;
extern _AU3_WinClose AU3_WinClose;
extern _AU3_WinCloseByHandle AU3_WinCloseByHandle;
extern _AU3_WinExists AU3_WinExists;
extern _AU3_WinExistsByHandle AU3_WinExistsByHandle;
extern _AU3_WinGetCaretPos AU3_WinGetCaretPos;
extern _AU3_WinGetClassList AU3_WinGetClassList;
extern _AU3_WinGetClassListByHandle AU3_WinGetClassListByHandle;
extern _AU3_WinGetClientSize AU3_WinGetClientSize;
extern _AU3_WinGetClientSizeByHandle AU3_WinGetClientSizeByHandle;
extern _AU3_WinGetHandle AU3_WinGetHandle;
extern _AU3_WinGetHandleAsText AU3_WinGetHandleAsText;
extern _AU3_WinGetPos AU3_WinGetPos;
extern _AU3_WinGetPosByHandle AU3_WinGetPosByHandle;
extern _AU3_WinGetProcess AU3_WinGetProcess;
extern _AU3_WinGetProcessByHandle AU3_WinGetProcessByHandle;
extern _AU3_WinGetState AU3_WinGetState;
extern _AU3_WinGetStateByHandle AU3_WinGetStateByHandle;
extern _AU3_WinGetText AU3_WinGetText;
extern _AU3_WinGetTextByHandle AU3_WinGetTextByHandle;
extern _AU3_WinGetTitle AU3_WinGetTitle;
extern _AU3_WinGetTitleByHandle AU3_WinGetTitleByHandle;
extern _AU3_WinKill AU3_WinKill;
extern _AU3_WinKillByHandle AU3_WinKillByHandle;
extern _AU3_WinMenuSelectItem AU3_WinMenuSelectItem;
extern _AU3_WinMenuSelectItemByHandle AU3_WinMenuSelectItemByHandle;
extern _AU3_WinMinimizeAll AU3_WinMinimizeAll;
extern _AU3_WinMinimizeAllUndo AU3_WinMinimizeAllUndo;
extern _AU3_WinMove AU3_WinMove;
extern _AU3_WinMoveByHandle AU3_WinMoveByHandle;
extern _AU3_WinSetOnTop AU3_WinSetOnTop;
extern _AU3_WinSetOnTopByHandle AU3_WinSetOnTopByHandle;
extern _AU3_WinSetState AU3_WinSetState;
extern _AU3_WinSetStateByHandle AU3_WinSetStateByHandle;
extern _AU3_WinSetTitle AU3_WinSetTitle;
extern _AU3_WinSetTitleByHandle AU3_WinSetTitleByHandle;
extern _AU3_WinSetTrans AU3_WinSetTrans;
extern _AU3_WinSetTransByHandle AU3_WinSetTransByHandle;
extern _AU3_WinWait AU3_WinWait;
extern _AU3_WinWaitByHandle AU3_WinWaitByHandle;
extern _AU3_WinWaitActive AU3_WinWaitActive;
extern _AU3_WinWaitActiveByHandle AU3_WinWaitActiveByHandle;
extern _AU3_WinWaitClose AU3_WinWaitClose;
extern _AU3_WinWaitCloseByHandle AU3_WinWaitCloseByHandle;
extern _AU3_WinWaitNotActive AU3_WinWaitNotActive;
extern _AU3_WinWaitNotActiveByHandle AU3_WinWaitNotActiveByHandle;

////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

#endif /* AUTOIT3_MINGW_H */
