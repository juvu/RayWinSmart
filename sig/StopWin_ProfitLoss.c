input:
    PathLocation("")
    , FileName("")
    , Strategy_ON_OFF(1)
    ;
var:
    Define_Broker(0)
    , Value_CurrentPosition(0)
    , Value_Initial_Value_CurrentPosition(0)
    , Value_AvgEntryPrice(0)
    , Value_StopWin_Active_Begin(0)
    , Value_Highest_OpenPositionProfit(0)
    , Define_StopWin_ProfitLoss_Active_Point(0)        // 獲利啟動點數
    , Define_StopWin_ProfitLoss_Percentage(0)      // 獲利回吐%
    ;
//-------------------------------------------------------------------------------------------------------------------
// Read From File
Define_Broker = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 1);
//"
RaySmart_ReturnCurrentPositionAvgEntryPrice(
    Define_Broker
    , Value_CurrentPosition
    , Value_AvgEntryPrice
);

if( Value_CurrentPosition <> 0 ) then begin
Define_StopWin_ProfitLoss_Active_Point = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 10);
Define_StopWin_ProfitLoss_Percentage = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 11);
//"
end ;

RaySmart_ReturnStopWinProfitLoss(
    Define_StopWin_ProfitLoss_Active_Point
    , Value_CurrentPosition
    , Value_AvgEntryPrice
    , Value_StopWin_Active_Begin
    , Value_Highest_OpenPositionProfit
);

//-------------------------------------------------------------------------------------------------------------------
if( Strategy_ON_OFF = 1 ) then begin
// Strategy Begin

if( Value_StopWin_Active_Begin = 1 ) then begin
    if( (OpenPositionProfit / bigpointvalue) < (Value_Highest_OpenPositionProfit * (100 - Define_StopWin_ProfitLoss_Percentage))/100 ) then begin
        sell next bar market ;
        buytocover next bar market ;
    end ;
end ;

// Strategy End
end ;
//-------------------------------------------------------------------------------------------------------------------
