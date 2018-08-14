input:
    PathLocation("")
    , FileName("")
    , Strategy_ON_OFF(1)
    , String_StopWin_Active_Point("")
    , Define_StopWin_Active_Point(0)        // 獲利啟動點數
    , String_StopWin_Protect_Percentage("")
    , Define_StopWin_Protect_Percentage(0)      // 獲利回吐%
    ;
var:
    Define_Broker(0)
    , Value_CurrentPosition(0)
    , Value_Initial_Value_CurrentPosition(0)
    , Value_AvgEntryPrice(0)
    , Value_StopWin_Active_Begin(0)
    , Value_Highest_OpenPositionProfit(0)
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
//"
end ;

//-------------------------------------------------------------------------------------------------------------------
if( Strategy_ON_OFF = 1 ) then begin
// Strategy Begin

if( Value_CurrentPosition = 0 ) then begin
    Value_StopWin_Active_Begin = 0 ;
    Value_Highest_OpenPositionProfit = 0 ;
end ;

if( Value_CurrentPosition <> 0 ) and ( (OpenPositionProfit / bigpointvalue) > Define_StopWin_Active_Point ) then begin
    Value_StopWin_Active_Begin = 1 ;
end ;

if( (OpenPositionProfit / bigpointvalue) > Value_Highest_OpenPositionProfit ) then begin
    Value_Highest_OpenPositionProfit = OpenPositionProfit / bigpointvalue ;
end ;

if( Value_StopWin_Active_Begin = 1 ) then begin
    if( (OpenPositionProfit / bigpointvalue) < (Value_Highest_OpenPositionProfit * (100 - Define_StopWin_Protect_Percentage))/100 ) then begin
        sell next bar market ;
        buytocover next bar market ;
    end ;
end ;

// Strategy End
end ;
//-------------------------------------------------------------------------------------------------------------------
