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

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "autoit3.h"
#include "../common.h"

/* Function pointer declarations */
typedef void WINAPI (*_AU3_Init_fromlib)(void);

/* Function load fail */
static void FuncLoadFail(void);

/* DLL instance */
static HINSTANCE hDll = NULL;

/* Function pointer definitions */
_AU3_Init_fromlib AU3_Init_fromlib = NULL;
_AU3_error AU3_error = NULL;
_AU3_AutoItSetOption AU3_AutoItSetOption = NULL;
_AU3_ClipGet AU3_ClipGet = NULL;
_AU3_ClipPut AU3_ClipPut = NULL;
_AU3_ControlClick AU3_ControlClick = NULL;
_AU3_ControlClickByHandle AU3_ControlClickByHandle = NULL;
_AU3_ControlCommand AU3_ControlCommand = NULL;
_AU3_ControlCommandByHandle AU3_ControlCommandByHandle = NULL;
_AU3_ControlListView AU3_ControlListView = NULL;
_AU3_ControlListViewByHandle AU3_ControlListViewByHandle = NULL;
_AU3_ControlDisable AU3_ControlDisable = NULL;
_AU3_ControlDisableByHandle AU3_ControlDisableByHandle = NULL;
_AU3_ControlEnable AU3_ControlEnable = NULL;
_AU3_ControlEnableByHandle AU3_ControlEnableByHandle = NULL;
_AU3_ControlFocus AU3_ControlFocus = NULL;
_AU3_ControlFocusByHandle AU3_ControlFocusByHandle = NULL;
_AU3_ControlGetFocus AU3_ControlGetFocus = NULL;
_AU3_ControlGetFocusByHandle AU3_ControlGetFocusByHandle = NULL;
_AU3_ControlGetHandle AU3_ControlGetHandle = NULL;
_AU3_ControlGetHandleAsText AU3_ControlGetHandleAsText = NULL;
_AU3_ControlGetPos AU3_ControlGetPos = NULL;
_AU3_ControlGetPosByHandle AU3_ControlGetPosByHandle = NULL;
_AU3_ControlGetText AU3_ControlGetText = NULL;
_AU3_ControlGetTextByHandle AU3_ControlGetTextByHandle = NULL;
_AU3_ControlHide AU3_ControlHide = NULL;
_AU3_ControlHideByHandle AU3_ControlHideByHandle = NULL;
_AU3_ControlMove AU3_ControlMove = NULL;
_AU3_ControlMoveByHandle AU3_ControlMoveByHandle = NULL;
_AU3_ControlSend AU3_ControlSend = NULL;
_AU3_ControlSendByHandle AU3_ControlSendByHandle = NULL;
_AU3_ControlSetText AU3_ControlSetText = NULL;
_AU3_ControlSetTextByHandle AU3_ControlSetTextByHandle = NULL;
_AU3_ControlShow AU3_ControlShow = NULL;
_AU3_ControlShowByHandle AU3_ControlShowByHandle = NULL;
_AU3_ControlTreeView AU3_ControlTreeView = NULL;
_AU3_ControlTreeViewByHandle AU3_ControlTreeViewByHandle = NULL;
_AU3_DriveMapAdd AU3_DriveMapAdd = NULL;
_AU3_DriveMapDel AU3_DriveMapDel = NULL;
_AU3_DriveMapGet AU3_DriveMapGet = NULL;
_AU3_IsAdmin AU3_IsAdmin = NULL;
_AU3_MouseClick AU3_MouseClick = NULL;
_AU3_MouseClickDrag AU3_MouseClickDrag = NULL;
_AU3_MouseDown AU3_MouseDown = NULL;
_AU3_MouseGetCursor AU3_MouseGetCursor = NULL;
_AU3_MouseGetPos AU3_MouseGetPos = NULL;
_AU3_MouseMove AU3_MouseMove = NULL;
_AU3_MouseUp AU3_MouseUp = NULL;
_AU3_MouseWheel AU3_MouseWheel = NULL;
_AU3_Opt AU3_Opt = NULL;
_AU3_PixelChecksum AU3_PixelChecksum = NULL;
_AU3_PixelGetColor AU3_PixelGetColor = NULL;
_AU3_PixelSearch AU3_PixelSearch = NULL;
_AU3_ProcessClose AU3_ProcessClose = NULL;
_AU3_ProcessExists AU3_ProcessExists = NULL;
_AU3_ProcessSetPriority AU3_ProcessSetPriority = NULL;
_AU3_ProcessWait AU3_ProcessWait = NULL;
_AU3_ProcessWaitClose AU3_ProcessWaitClose = NULL;
_AU3_Run AU3_Run = NULL;
_AU3_RunWait AU3_RunWait = NULL;
_AU3_RunAs AU3_RunAs = NULL;
_AU3_RunAsWait AU3_RunAsWait = NULL;
_AU3_Send AU3_Send = NULL;
_AU3_Shutdown AU3_Shutdown = NULL;
_AU3_Sleep AU3_Sleep = NULL;
_AU3_StatusbarGetText AU3_StatusbarGetText = NULL;
_AU3_StatusbarGetTextByHandle AU3_StatusbarGetTextByHandle = NULL;
_AU3_ToolTip AU3_ToolTip = NULL;
_AU3_WinActivate AU3_WinActivate = NULL;
_AU3_WinActivateByHandle AU3_WinActivateByHandle = NULL;
_AU3_WinActive AU3_WinActive = NULL;
_AU3_WinActiveByHandle AU3_WinActiveByHandle = NULL;
_AU3_WinClose AU3_WinClose = NULL;
_AU3_WinCloseByHandle AU3_WinCloseByHandle = NULL;
_AU3_WinExists AU3_WinExists = NULL;
_AU3_WinExistsByHandle AU3_WinExistsByHandle = NULL;
_AU3_WinGetCaretPos AU3_WinGetCaretPos = NULL;
_AU3_WinGetClassList AU3_WinGetClassList = NULL;
_AU3_WinGetClassListByHandle AU3_WinGetClassListByHandle = NULL;
_AU3_WinGetClientSize AU3_WinGetClientSize = NULL;
_AU3_WinGetClientSizeByHandle AU3_WinGetClientSizeByHandle = NULL;
_AU3_WinGetHandle AU3_WinGetHandle = NULL;
_AU3_WinGetHandleAsText AU3_WinGetHandleAsText = NULL;
_AU3_WinGetPos AU3_WinGetPos = NULL;
_AU3_WinGetPosByHandle AU3_WinGetPosByHandle = NULL;
_AU3_WinGetProcess AU3_WinGetProcess = NULL;
_AU3_WinGetProcessByHandle AU3_WinGetProcessByHandle = NULL;
_AU3_WinGetState AU3_WinGetState = NULL;
_AU3_WinGetStateByHandle AU3_WinGetStateByHandle = NULL;
_AU3_WinGetText AU3_WinGetText = NULL;
_AU3_WinGetTextByHandle AU3_WinGetTextByHandle = NULL;
_AU3_WinGetTitle AU3_WinGetTitle = NULL;
_AU3_WinGetTitleByHandle AU3_WinGetTitleByHandle = NULL;
_AU3_WinKill AU3_WinKill = NULL;
_AU3_WinKillByHandle AU3_WinKillByHandle = NULL;
_AU3_WinMenuSelectItem AU3_WinMenuSelectItem = NULL;
_AU3_WinMenuSelectItemByHandle AU3_WinMenuSelectItemByHandle = NULL;
_AU3_WinMinimizeAll AU3_WinMinimizeAll = NULL;
_AU3_WinMinimizeAllUndo AU3_WinMinimizeAllUndo = NULL;
_AU3_WinMove AU3_WinMove = NULL;
_AU3_WinMoveByHandle AU3_WinMoveByHandle = NULL;
_AU3_WinSetOnTop AU3_WinSetOnTop = NULL;
_AU3_WinSetOnTopByHandle AU3_WinSetOnTopByHandle = NULL;
_AU3_WinSetState AU3_WinSetState = NULL;
_AU3_WinSetStateByHandle AU3_WinSetStateByHandle = NULL;
_AU3_WinSetTitle AU3_WinSetTitle = NULL;
_AU3_WinSetTitleByHandle AU3_WinSetTitleByHandle = NULL;
_AU3_WinSetTrans AU3_WinSetTrans = NULL;
_AU3_WinSetTransByHandle AU3_WinSetTransByHandle = NULL;
_AU3_WinWait AU3_WinWait = NULL;
_AU3_WinWaitByHandle AU3_WinWaitByHandle = NULL;
_AU3_WinWaitActive AU3_WinWaitActive = NULL;
_AU3_WinWaitActiveByHandle AU3_WinWaitActiveByHandle = NULL;
_AU3_WinWaitClose AU3_WinWaitClose = NULL;
_AU3_WinWaitCloseByHandle AU3_WinWaitCloseByHandle = NULL;
_AU3_WinWaitNotActive AU3_WinWaitNotActive = NULL;
_AU3_WinWaitNotActiveByHandle AU3_WinWaitNotActiveByHandle = NULL;

void WINAPI AU3_Init(void)
{
    if(hDll != NULL) return;

    /* Load dll */
    hDll = LoadLibrary("AutoItX3.dll");

    /* Check for error */
    if(hDll == NULL)
    {
        print_logs(1, "Program can not load AutoItX3.dll!");
        exit(EXIT_FAILURE);
    }

    /* Load functions */
    AU3_Init_fromlib = (_AU3_Init_fromlib) GetProcAddress(hDll, "AU3_Init");
    AU3_error = (_AU3_error) GetProcAddress(hDll, "AU3_error");
    AU3_AutoItSetOption = (_AU3_AutoItSetOption) GetProcAddress(hDll, "AU3_AutoItSetOption");
    AU3_ClipGet = (_AU3_ClipGet) GetProcAddress(hDll, "AU3_ClipGet");
    AU3_ClipPut = (_AU3_ClipPut) GetProcAddress(hDll, "AU3_ClipPut");
    AU3_ControlClick = (_AU3_ControlClick) GetProcAddress(hDll, "AU3_ControlClick");
    AU3_ControlClickByHandle = (_AU3_ControlClickByHandle) GetProcAddress(hDll, "AU3_ControlClickByHandle");
    AU3_ControlCommand = (_AU3_ControlCommand) GetProcAddress(hDll, "AU3_ControlCommand");
    AU3_ControlCommandByHandle = (_AU3_ControlCommandByHandle) GetProcAddress(hDll, "AU3_ControlCommandByHandle");
    AU3_ControlListView = (_AU3_ControlListView) GetProcAddress(hDll, "AU3_ControlListView");
    AU3_ControlListViewByHandle = (_AU3_ControlListViewByHandle) GetProcAddress(hDll, "AU3_ControlListViewByHandle");
    AU3_ControlDisable = (_AU3_ControlDisable) GetProcAddress(hDll, "AU3_ControlDisable");
    AU3_ControlDisableByHandle = (_AU3_ControlDisableByHandle) GetProcAddress(hDll, "AU3_ControlDisableByHandle");
    AU3_ControlEnable = (_AU3_ControlEnable) GetProcAddress(hDll, "AU3_ControlEnable");
    AU3_ControlEnableByHandle = (_AU3_ControlEnableByHandle) GetProcAddress(hDll, "AU3_ControlEnableByHandle");
    AU3_ControlFocus = (_AU3_ControlFocus) GetProcAddress(hDll, "AU3_ControlFocus");
    AU3_ControlFocusByHandle = (_AU3_ControlFocusByHandle) GetProcAddress(hDll, "AU3_ControlFocusByHandle");
    AU3_ControlGetFocus = (_AU3_ControlGetFocus) GetProcAddress(hDll, "AU3_ControlGetFocus");
    AU3_ControlGetFocusByHandle = (_AU3_ControlGetFocusByHandle) GetProcAddress(hDll, "AU3_ControlGetFocusByHandle");
    AU3_ControlGetHandle = (_AU3_ControlGetHandle) GetProcAddress(hDll, "AU3_ControlGetHandle");
    AU3_ControlGetHandleAsText = (_AU3_ControlGetHandleAsText) GetProcAddress(hDll, "AU3_ControlGetHandleAsText");
    AU3_ControlGetPos = (_AU3_ControlGetPos) GetProcAddress(hDll, "AU3_ControlGetPos");
    AU3_ControlGetPosByHandle = (_AU3_ControlGetPosByHandle) GetProcAddress(hDll, "AU3_ControlGetPosByHandle");
    AU3_ControlGetText = (_AU3_ControlGetText) GetProcAddress(hDll, "AU3_ControlGetText");
    AU3_ControlGetTextByHandle = (_AU3_ControlGetTextByHandle) GetProcAddress(hDll, "AU3_ControlGetTextByHandle");
    AU3_ControlHide = (_AU3_ControlHide) GetProcAddress(hDll, "AU3_ControlHide");
    AU3_ControlHideByHandle = (_AU3_ControlHideByHandle) GetProcAddress(hDll, "AU3_ControlHideByHandle");
    AU3_ControlMove = (_AU3_ControlMove) GetProcAddress(hDll, "AU3_ControlMove");
    AU3_ControlMoveByHandle = (_AU3_ControlMoveByHandle) GetProcAddress(hDll, "AU3_ControlMoveByHandle");
    AU3_ControlSend = (_AU3_ControlSend) GetProcAddress(hDll, "AU3_ControlSend");
    AU3_ControlSendByHandle = (_AU3_ControlSendByHandle) GetProcAddress(hDll, "AU3_ControlSendByHandle");
    AU3_ControlSetText = (_AU3_ControlSetText) GetProcAddress(hDll, "AU3_ControlSetText");
    AU3_ControlSetTextByHandle = (_AU3_ControlSetTextByHandle) GetProcAddress(hDll, "AU3_ControlSetTextByHandle");
    AU3_ControlShow = (_AU3_ControlShow) GetProcAddress(hDll, "AU3_ControlShow");
    AU3_ControlShowByHandle = (_AU3_ControlShowByHandle) GetProcAddress(hDll, "AU3_ControlShowByHandle");
    AU3_ControlTreeView = (_AU3_ControlTreeView) GetProcAddress(hDll, "AU3_ControlTreeView");
    AU3_ControlTreeViewByHandle = (_AU3_ControlTreeViewByHandle) GetProcAddress(hDll, "AU3_ControlTreeViewByHandle");
    AU3_DriveMapAdd = (_AU3_DriveMapAdd) GetProcAddress(hDll, "AU3_DriveMapAdd");
    AU3_DriveMapDel = (_AU3_DriveMapDel) GetProcAddress(hDll, "AU3_DriveMapDel");
    AU3_DriveMapGet = (_AU3_DriveMapGet) GetProcAddress(hDll, "AU3_DriveMapGet");
    AU3_IsAdmin = (_AU3_IsAdmin) GetProcAddress(hDll, "AU3_IsAdmin");
    AU3_MouseClick = (_AU3_MouseClick) GetProcAddress(hDll, "AU3_MouseClick");
    AU3_MouseClickDrag = (_AU3_MouseClickDrag) GetProcAddress(hDll, "AU3_MouseClickDrag");
    AU3_MouseDown = (_AU3_MouseDown) GetProcAddress(hDll, "AU3_MouseDown");
    AU3_MouseGetCursor = (_AU3_MouseGetCursor) GetProcAddress(hDll, "AU3_MouseGetCursor");
    AU3_MouseGetPos = (_AU3_MouseGetPos) GetProcAddress(hDll, "AU3_MouseGetPos");
    AU3_MouseMove = (_AU3_MouseMove) GetProcAddress(hDll, "AU3_MouseMove");
    AU3_MouseUp = (_AU3_MouseUp) GetProcAddress(hDll, "AU3_MouseUp");
    AU3_MouseWheel = (_AU3_MouseWheel) GetProcAddress(hDll, "AU3_MouseWheel");
    AU3_Opt = (_AU3_Opt) GetProcAddress(hDll, "AU3_Opt");
    AU3_PixelChecksum = (_AU3_PixelChecksum) GetProcAddress(hDll, "AU3_PixelChecksum");
    AU3_PixelGetColor = (_AU3_PixelGetColor) GetProcAddress(hDll, "AU3_PixelGetColor");
    AU3_PixelSearch = (_AU3_PixelSearch) GetProcAddress(hDll, "AU3_PixelSearch");
    AU3_ProcessClose = (_AU3_ProcessClose) GetProcAddress(hDll, "AU3_ProcessClose");
    AU3_ProcessExists = (_AU3_ProcessExists) GetProcAddress(hDll, "AU3_ProcessExists");
    AU3_ProcessSetPriority = (_AU3_ProcessSetPriority) GetProcAddress(hDll, "AU3_ProcessSetPriority");
    AU3_ProcessWait = (_AU3_ProcessWait) GetProcAddress(hDll, "AU3_ProcessWait");
    AU3_ProcessWaitClose = (_AU3_ProcessWaitClose) GetProcAddress(hDll, "AU3_ProcessWaitClose");
    AU3_Run = (_AU3_Run) GetProcAddress(hDll, "AU3_Run");
    AU3_RunWait = (_AU3_RunWait) GetProcAddress(hDll, "AU3_RunWait");
    AU3_RunAs = (_AU3_RunAs) GetProcAddress(hDll, "AU3_RunAs");
    AU3_RunAsWait = (_AU3_RunAsWait) GetProcAddress(hDll, "AU3_RunAsWait");
    AU3_Send = (_AU3_Send) GetProcAddress(hDll, "AU3_Send");
    AU3_Shutdown = (_AU3_Shutdown) GetProcAddress(hDll, "AU3_Shutdown");
    AU3_Sleep = (_AU3_Sleep) GetProcAddress(hDll, "AU3_Sleep");
    AU3_StatusbarGetText = (_AU3_StatusbarGetText) GetProcAddress(hDll, "AU3_StatusbarGetText");
    AU3_StatusbarGetTextByHandle = (_AU3_StatusbarGetTextByHandle) GetProcAddress(hDll, "AU3_StatusbarGetTextByHandle");
    AU3_ToolTip = (_AU3_ToolTip) GetProcAddress(hDll, "AU3_ToolTip");
    AU3_WinActivate = (_AU3_WinActivate) GetProcAddress(hDll, "AU3_WinActivate");
    AU3_WinActivateByHandle = (_AU3_WinActivateByHandle) GetProcAddress(hDll, "AU3_WinActivateByHandle");
    AU3_WinActive = (_AU3_WinActive) GetProcAddress(hDll, "AU3_WinActive");
    AU3_WinActiveByHandle = (_AU3_WinActiveByHandle) GetProcAddress(hDll, "AU3_WinActiveByHandle");
    AU3_WinClose = (_AU3_WinClose) GetProcAddress(hDll, "AU3_WinClose");
    AU3_WinCloseByHandle = (_AU3_WinCloseByHandle) GetProcAddress(hDll, "AU3_WinCloseByHandle");
    AU3_WinExists = (_AU3_WinExists) GetProcAddress(hDll, "AU3_WinExists");
    AU3_WinExistsByHandle = (_AU3_WinExistsByHandle) GetProcAddress(hDll, "AU3_WinExistsByHandle");
    AU3_WinGetCaretPos = (_AU3_WinGetCaretPos) GetProcAddress(hDll, "AU3_WinGetCaretPos");
    AU3_WinGetClassList = (_AU3_WinGetClassList) GetProcAddress(hDll, "AU3_WinGetClassList");
    AU3_WinGetClassListByHandle = (_AU3_WinGetClassListByHandle) GetProcAddress(hDll, "AU3_WinGetClassListByHandle");
    AU3_WinGetClientSize = (_AU3_WinGetClientSize) GetProcAddress(hDll, "AU3_WinGetClientSize");
    AU3_WinGetClientSizeByHandle = (_AU3_WinGetClientSizeByHandle) GetProcAddress(hDll, "AU3_WinGetClientSizeByHandle");
    AU3_WinGetHandle = (_AU3_WinGetHandle) GetProcAddress(hDll, "AU3_WinGetHandle");
    AU3_WinGetHandleAsText = (_AU3_WinGetHandleAsText) GetProcAddress(hDll, "AU3_WinGetHandleAsText");
    AU3_WinGetPos = (_AU3_WinGetPos) GetProcAddress(hDll, "AU3_WinGetPos");
    AU3_WinGetPosByHandle = (_AU3_WinGetPosByHandle) GetProcAddress(hDll, "AU3_WinGetPosByHandle");
    AU3_WinGetProcess = (_AU3_WinGetProcess) GetProcAddress(hDll, "AU3_WinGetProcess");
    AU3_WinGetProcessByHandle = (_AU3_WinGetProcessByHandle) GetProcAddress(hDll, "AU3_WinGetProcessByHandle");
    AU3_WinGetState = (_AU3_WinGetState) GetProcAddress(hDll, "AU3_WinGetState");
    AU3_WinGetStateByHandle = (_AU3_WinGetStateByHandle) GetProcAddress(hDll, "AU3_WinGetStateByHandle");
    AU3_WinGetText = (_AU3_WinGetText) GetProcAddress(hDll, "AU3_WinGetText");
    AU3_WinGetTextByHandle = (_AU3_WinGetTextByHandle) GetProcAddress(hDll, "AU3_WinGetTextByHandle");
    AU3_WinGetTitle = (_AU3_WinGetTitle) GetProcAddress(hDll, "AU3_WinGetTitle");
    AU3_WinGetTitleByHandle = (_AU3_WinGetTitleByHandle) GetProcAddress(hDll, "AU3_WinGetTitleByHandle");
    AU3_WinKill = (_AU3_WinKill) GetProcAddress(hDll, "AU3_WinKill");
    AU3_WinKillByHandle = (_AU3_WinKillByHandle) GetProcAddress(hDll, "AU3_WinKillByHandle");
    AU3_WinMenuSelectItem = (_AU3_WinMenuSelectItem) GetProcAddress(hDll, "AU3_WinMenuSelectItem");
    AU3_WinMenuSelectItemByHandle = (_AU3_WinMenuSelectItemByHandle) GetProcAddress(hDll, "AU3_WinMenuSelectItemByHandle");
    AU3_WinMinimizeAll = (_AU3_WinMinimizeAll) GetProcAddress(hDll, "AU3_WinMinimizeAll");
    AU3_WinMinimizeAllUndo = (_AU3_WinMinimizeAllUndo) GetProcAddress(hDll, "AU3_WinMinimizeAllUndo");
    AU3_WinMove = (_AU3_WinMove) GetProcAddress(hDll, "AU3_WinMove");
    AU3_WinMoveByHandle = (_AU3_WinMoveByHandle) GetProcAddress(hDll, "AU3_WinMoveByHandle");
    AU3_WinSetOnTop = (_AU3_WinSetOnTop) GetProcAddress(hDll, "AU3_WinSetOnTop");
    AU3_WinSetOnTopByHandle = (_AU3_WinSetOnTopByHandle) GetProcAddress(hDll, "AU3_WinSetOnTopByHandle");
    AU3_WinSetState = (_AU3_WinSetState) GetProcAddress(hDll, "AU3_WinSetState");
    AU3_WinSetStateByHandle = (_AU3_WinSetStateByHandle) GetProcAddress(hDll, "AU3_WinSetStateByHandle");
    AU3_WinSetTitle = (_AU3_WinSetTitle) GetProcAddress(hDll, "AU3_WinSetTitle");
    AU3_WinSetTitleByHandle = (_AU3_WinSetTitleByHandle) GetProcAddress(hDll, "AU3_WinSetTitleByHandle");
    AU3_WinSetTrans = (_AU3_WinSetTrans) GetProcAddress(hDll, "AU3_WinSetTrans");
    AU3_WinSetTransByHandle = (_AU3_WinSetTransByHandle) GetProcAddress(hDll, "AU3_WinSetTransByHandle");
    AU3_WinWait = (_AU3_WinWait) GetProcAddress(hDll, "AU3_WinWait");
    AU3_WinWaitByHandle = (_AU3_WinWaitByHandle) GetProcAddress(hDll, "AU3_WinWaitByHandle");
    AU3_WinWaitActive = (_AU3_WinWaitActive) GetProcAddress(hDll, "AU3_WinWaitActive");
    AU3_WinWaitActiveByHandle = (_AU3_WinWaitActiveByHandle) GetProcAddress(hDll, "AU3_WinWaitActiveByHandle");
    AU3_WinWaitClose = (_AU3_WinWaitClose) GetProcAddress(hDll, "AU3_WinWaitClose");
    AU3_WinWaitCloseByHandle = (_AU3_WinWaitCloseByHandle) GetProcAddress(hDll, "AU3_WinWaitCloseByHandle");
    AU3_WinWaitNotActive = (_AU3_WinWaitNotActive) GetProcAddress(hDll, "AU3_WinWaitNotActive");
    AU3_WinWaitNotActiveByHandle = (_AU3_WinWaitNotActiveByHandle) GetProcAddress(hDll, "AU3_WinWaitNotActiveByHandle");

    /* Check function pointers */
    if(!AU3_Init_fromlib) FuncLoadFail();
    if(!AU3_error) FuncLoadFail();
    if(!AU3_AutoItSetOption) FuncLoadFail();
    if(!AU3_ClipGet) FuncLoadFail();
    if(!AU3_ClipPut) FuncLoadFail();
    if(!AU3_ControlClick) FuncLoadFail();
    if(!AU3_ControlClickByHandle) FuncLoadFail();
    if(!AU3_ControlCommand) FuncLoadFail();
    if(!AU3_ControlCommandByHandle) FuncLoadFail();
    if(!AU3_ControlListView) FuncLoadFail();
    if(!AU3_ControlListViewByHandle) FuncLoadFail();
    if(!AU3_ControlDisable) FuncLoadFail();
    if(!AU3_ControlDisableByHandle) FuncLoadFail();
    if(!AU3_ControlEnable) FuncLoadFail();
    if(!AU3_ControlEnableByHandle) FuncLoadFail();
    if(!AU3_ControlFocus) FuncLoadFail();
    if(!AU3_ControlFocusByHandle) FuncLoadFail();
    if(!AU3_ControlGetFocus) FuncLoadFail();
    if(!AU3_ControlGetFocusByHandle) FuncLoadFail();
    if(!AU3_ControlGetHandle) FuncLoadFail();
    if(!AU3_ControlGetHandleAsText) FuncLoadFail();
    if(!AU3_ControlGetPos) FuncLoadFail();
    if(!AU3_ControlGetPosByHandle) FuncLoadFail();
    if(!AU3_ControlGetText) FuncLoadFail();
    if(!AU3_ControlGetTextByHandle) FuncLoadFail();
    if(!AU3_ControlHide) FuncLoadFail();
    if(!AU3_ControlHideByHandle) FuncLoadFail();
    if(!AU3_ControlMove) FuncLoadFail();
    if(!AU3_ControlMoveByHandle) FuncLoadFail();
    if(!AU3_ControlSend) FuncLoadFail();
    if(!AU3_ControlSendByHandle) FuncLoadFail();
    if(!AU3_ControlSetText) FuncLoadFail();
    if(!AU3_ControlSetTextByHandle) FuncLoadFail();
    if(!AU3_ControlShow) FuncLoadFail();
    if(!AU3_ControlShowByHandle) FuncLoadFail();
    if(!AU3_ControlTreeView) FuncLoadFail();
    if(!AU3_ControlTreeViewByHandle) FuncLoadFail();
    if(!AU3_DriveMapAdd) FuncLoadFail();
    if(!AU3_DriveMapDel) FuncLoadFail();
    if(!AU3_DriveMapGet) FuncLoadFail();
    if(!AU3_IsAdmin) FuncLoadFail();
    if(!AU3_MouseClick) FuncLoadFail();
    if(!AU3_MouseClickDrag) FuncLoadFail();
    if(!AU3_MouseDown) FuncLoadFail();
    if(!AU3_MouseGetCursor) FuncLoadFail();
    if(!AU3_MouseGetPos) FuncLoadFail();
    if(!AU3_MouseMove) FuncLoadFail();
    if(!AU3_MouseUp) FuncLoadFail();
    if(!AU3_MouseWheel) FuncLoadFail();
    if(!AU3_Opt) FuncLoadFail();
    if(!AU3_PixelChecksum) FuncLoadFail();
    if(!AU3_PixelGetColor) FuncLoadFail();
    if(!AU3_PixelSearch) FuncLoadFail();
    if(!AU3_ProcessClose) FuncLoadFail();
    if(!AU3_ProcessExists) FuncLoadFail();
    if(!AU3_ProcessSetPriority) FuncLoadFail();
    if(!AU3_ProcessWait) FuncLoadFail();
    if(!AU3_ProcessWaitClose) FuncLoadFail();
    if(!AU3_Run) FuncLoadFail();
    if(!AU3_RunWait) FuncLoadFail();
    if(!AU3_RunAs) FuncLoadFail();
    if(!AU3_RunAsWait) FuncLoadFail();
    if(!AU3_Send) FuncLoadFail();
    if(!AU3_Shutdown) FuncLoadFail();
    if(!AU3_Sleep) FuncLoadFail();
    if(!AU3_StatusbarGetText) FuncLoadFail();
    if(!AU3_StatusbarGetTextByHandle) FuncLoadFail();
    if(!AU3_ToolTip) FuncLoadFail();
    if(!AU3_WinActivate) FuncLoadFail();
    if(!AU3_WinActivateByHandle) FuncLoadFail();
    if(!AU3_WinActive) FuncLoadFail();
    if(!AU3_WinActiveByHandle) FuncLoadFail();
    if(!AU3_WinClose) FuncLoadFail();
    if(!AU3_WinCloseByHandle) FuncLoadFail();
    if(!AU3_WinExists) FuncLoadFail();
    if(!AU3_WinExistsByHandle) FuncLoadFail();
    if(!AU3_WinGetCaretPos) FuncLoadFail();
    if(!AU3_WinGetClassList) FuncLoadFail();
    if(!AU3_WinGetClassListByHandle) FuncLoadFail();
    if(!AU3_WinGetClientSize) FuncLoadFail();
    if(!AU3_WinGetClientSizeByHandle) FuncLoadFail();
    if(!AU3_WinGetHandle) FuncLoadFail();
    if(!AU3_WinGetHandleAsText) FuncLoadFail();
    if(!AU3_WinGetPos) FuncLoadFail();
    if(!AU3_WinGetPosByHandle) FuncLoadFail();
    if(!AU3_WinGetProcess) FuncLoadFail();
    if(!AU3_WinGetProcessByHandle) FuncLoadFail();
    if(!AU3_WinGetState) FuncLoadFail();
    if(!AU3_WinGetStateByHandle) FuncLoadFail();
    if(!AU3_WinGetText) FuncLoadFail();
    if(!AU3_WinGetTextByHandle) FuncLoadFail();
    if(!AU3_WinGetTitle) FuncLoadFail();
    if(!AU3_WinGetTitleByHandle) FuncLoadFail();
    if(!AU3_WinKill) FuncLoadFail();
    if(!AU3_WinKillByHandle) FuncLoadFail();
    if(!AU3_WinMenuSelectItem) FuncLoadFail();
    if(!AU3_WinMenuSelectItemByHandle) FuncLoadFail();
    if(!AU3_WinMinimizeAll) FuncLoadFail();
    if(!AU3_WinMinimizeAllUndo) FuncLoadFail();
    if(!AU3_WinMove) FuncLoadFail();
    if(!AU3_WinMoveByHandle) FuncLoadFail();
    if(!AU3_WinSetOnTop) FuncLoadFail();
    if(!AU3_WinSetOnTopByHandle) FuncLoadFail();
    if(!AU3_WinSetState) FuncLoadFail();
    if(!AU3_WinSetStateByHandle) FuncLoadFail();
    if(!AU3_WinSetTitle) FuncLoadFail();
    if(!AU3_WinSetTitleByHandle) FuncLoadFail();
    if(!AU3_WinSetTrans) FuncLoadFail();
    if(!AU3_WinSetTransByHandle) FuncLoadFail();
    if(!AU3_WinWait) FuncLoadFail();
    if(!AU3_WinWaitByHandle) FuncLoadFail();
    if(!AU3_WinWaitActive) FuncLoadFail();
    if(!AU3_WinWaitActiveByHandle) FuncLoadFail();
    if(!AU3_WinWaitClose) FuncLoadFail();
    if(!AU3_WinWaitCloseByHandle) FuncLoadFail();
    if(!AU3_WinWaitNotActive) FuncLoadFail();
    if(!AU3_WinWaitNotActiveByHandle) FuncLoadFail();

    /* When program exit, free memory */
    atexit(AU3_Exit);

    /* Initialize AutoIt 3 library */
    AU3_Init_fromlib();
} /* AU3_Init */

void AU3_Exit(void)
{
    /* Write NULL in function pointers */
    AU3_Init_fromlib = NULL;
    AU3_error = NULL;
    AU3_AutoItSetOption = NULL;
    AU3_ClipGet = NULL;
    AU3_ClipPut = NULL;
    AU3_ControlClick = NULL;
    AU3_ControlClickByHandle = NULL;
    AU3_ControlCommand = NULL;
    AU3_ControlCommandByHandle = NULL;
    AU3_ControlListView = NULL;
    AU3_ControlListViewByHandle = NULL;
    AU3_ControlDisable = NULL;
    AU3_ControlDisableByHandle = NULL;
    AU3_ControlEnable = NULL;
    AU3_ControlEnableByHandle = NULL;
    AU3_ControlFocus = NULL;
    AU3_ControlFocusByHandle = NULL;
    AU3_ControlGetFocus = NULL;
    AU3_ControlGetFocusByHandle = NULL;
    AU3_ControlGetHandle = NULL;
    AU3_ControlGetHandleAsText = NULL;
    AU3_ControlGetPos = NULL;
    AU3_ControlGetPosByHandle = NULL;
    AU3_ControlGetText = NULL;
    AU3_ControlGetTextByHandle = NULL;
    AU3_ControlHide = NULL;
    AU3_ControlHideByHandle = NULL;
    AU3_ControlMove = NULL;
    AU3_ControlMoveByHandle = NULL;
    AU3_ControlSend = NULL;
    AU3_ControlSendByHandle = NULL;
    AU3_ControlSetText = NULL;
    AU3_ControlSetTextByHandle = NULL;
    AU3_ControlShow = NULL;
    AU3_ControlShowByHandle = NULL;
    AU3_ControlTreeView = NULL;
    AU3_ControlTreeViewByHandle = NULL;
    AU3_DriveMapAdd = NULL;
    AU3_DriveMapDel = NULL;
    AU3_DriveMapGet = NULL;
    AU3_IsAdmin = NULL;
    AU3_MouseClick = NULL;
    AU3_MouseClickDrag = NULL;
    AU3_MouseDown = NULL;
    AU3_MouseGetCursor = NULL;
    AU3_MouseGetPos = NULL;
    AU3_MouseMove = NULL;
    AU3_MouseUp = NULL;
    AU3_MouseWheel = NULL;
    AU3_Opt = NULL;
    AU3_PixelChecksum = NULL;
    AU3_PixelGetColor = NULL;
    AU3_PixelSearch = NULL;
    AU3_ProcessClose = NULL;
    AU3_ProcessExists = NULL;
    AU3_ProcessSetPriority = NULL;
    AU3_ProcessWait = NULL;
    AU3_ProcessWaitClose = NULL;
    AU3_Run = NULL;
    AU3_RunWait = NULL;
    AU3_RunAs = NULL;
    AU3_RunAsWait = NULL;
    AU3_Send = NULL;
    AU3_Shutdown = NULL;
    AU3_Sleep = NULL;
    AU3_StatusbarGetText = NULL;
    AU3_StatusbarGetTextByHandle = NULL;
    AU3_ToolTip = NULL;
    AU3_WinActivate = NULL;
    AU3_WinActivateByHandle = NULL;
    AU3_WinActive = NULL;
    AU3_WinActiveByHandle = NULL;
    AU3_WinClose = NULL;
    AU3_WinCloseByHandle = NULL;
    AU3_WinExists = NULL;
    AU3_WinExistsByHandle = NULL;
    AU3_WinGetCaretPos = NULL;
    AU3_WinGetClassList = NULL;
    AU3_WinGetClassListByHandle = NULL;
    AU3_WinGetClientSize = NULL;
    AU3_WinGetClientSizeByHandle = NULL;
    AU3_WinGetHandle = NULL;
    AU3_WinGetHandleAsText = NULL;
    AU3_WinGetPos = NULL;
    AU3_WinGetPosByHandle = NULL;
    AU3_WinGetProcess = NULL;
    AU3_WinGetProcessByHandle = NULL;
    AU3_WinGetState = NULL;
    AU3_WinGetStateByHandle = NULL;
    AU3_WinGetText = NULL;
    AU3_WinGetTextByHandle = NULL;
    AU3_WinGetTitle = NULL;
    AU3_WinGetTitleByHandle = NULL;
    AU3_WinKill = NULL;
    AU3_WinKillByHandle = NULL;
    AU3_WinMenuSelectItem = NULL;
    AU3_WinMenuSelectItemByHandle = NULL;
    AU3_WinMinimizeAll = NULL;
    AU3_WinMinimizeAllUndo = NULL;
    AU3_WinMove = NULL;
    AU3_WinMoveByHandle = NULL;
    AU3_WinSetOnTop = NULL;
    AU3_WinSetOnTopByHandle = NULL;
    AU3_WinSetState = NULL;
    AU3_WinSetStateByHandle = NULL;
    AU3_WinSetTitle = NULL;
    AU3_WinSetTitleByHandle = NULL;
    AU3_WinSetTrans = NULL;
    AU3_WinSetTransByHandle = NULL;
    AU3_WinWait = NULL;
    AU3_WinWaitByHandle = NULL;
    AU3_WinWaitActive = NULL;
    AU3_WinWaitActiveByHandle = NULL;
    AU3_WinWaitClose = NULL;
    AU3_WinWaitCloseByHandle = NULL;
    AU3_WinWaitNotActive = NULL;
    AU3_WinWaitNotActiveByHandle = NULL;

    /* Free Library */
    if(hDll) FreeLibrary(hDll);
    hDll = NULL;
} /* AU3_Exit */

static void FuncLoadFail(void)
{
    print_logs(1, "Program can not load function from dll!");
    exit(EXIT_FAILURE);
} /* FuncLoadFail */
