input:
    PathLocation("")
    , FileName("")
    , Define_Broker(0)
    , Define_TradeMode(0)
    , String_Total_Money("")                            // 總資金
    , Define_Total_Money(0)
    , String_MaxLossPersent("")                         // 單筆最大損失幅度
    , Define_MaxLossPersent(0)
    , String_StopWin_HighestPullBackPoint("")
    , Define_StopWin_HighestPullBackPoint(0)            // 最高最低拉回點數
    , String_StopWin_PreviousHighLow_K_Number("")
    , Define_StopWin_PreviousHighLow_K_Number(0)        // 近期 N 根 K 棒
    , String_StopWin_PivotHighLow_LeftStrength("")
    , Define_StopWin_PivotHighLow_LeftRightStrength(0)  // 轉折左右邊 K 棒數
    , String_StopWin_TickOffset("")
    , Define_StopWin_TickOffset(0)                      // 停利線讓價點數
    ;
var:
    InfoMap(MapSN.New)
    ;
//-------------------------------------------------------------------------------------------------------------------
// Write to File
_outputfile( "G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" ,
    numtostr(Define_Broker, 0) + NewLine +                                      // 1
    numtostr(Define_TradeMode, 0) + NewLine +                                   // 2
    numtostr(Define_Total_Money, 0) + NewLine +                                 // 3
    numtostr(Define_MaxLossPersent, 0) + NewLine +                              // 4
    numtostr(Define_StopWin_HighestPullBackPoint, 0) + NewLine +                // 5
    numtostr(Define_StopWin_PreviousHighLow_K_Number, 0) + NewLine +            // 6
    numtostr(Define_StopWin_PivotHighLow_LeftRightStrength, 0) + NewLine +      // 7
    numtostr(Define_StopWin_PivotHighLow_LeftRightStrength, 0) + NewLine +      // 8
    numtostr(Define_StopWin_TickOffset, 0) + NewLine                            // 9
);