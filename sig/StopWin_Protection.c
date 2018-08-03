input:
    PathLocation("")
    , FileName("")
    , Strategy_ON_OFF(1)
    , String_StopWin_Active_Point("")
    , Define_StopWin_Active_Point(0)        // 保本啟動點數
    , String_StopWin_Protect_Point("")
    , Define_StopWin_Protect_Point(0)      // 保本停利點數
    ;
var:
    Define_Broker(0)
    , Value_CurrentPosition(0)
    , Value_Initial_Value_CurrentPosition(0)
    , Value_AvgEntryPrice(0)
    , Value_OpenPositionProfit(0)
    , Value_StopWin_Active_Begin(0)
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

if(Value_CurrentPosition > 0) then begin
    Value_OpenPositionProfit = (close - Value_AvgEntryPrice) * Value_CurrentPosition ;
end else if(Value_CurrentPosition < 0) then begin
    Value_OpenPositionProfit = (close - Value_AvgEntryPrice) * Value_CurrentPosition ;
end else if(Value_CurrentPosition = 0) then begin
    Value_OpenPositionProfit = 0 ;
end ;
//-------------------------------------------------------------------------------------------------------------------
if( Strategy_ON_OFF = 1 ) then begin
// Strategy Begin

if( Value_CurrentPosition = 0 ) then begin
    Value_StopWin_Active_Begin = 0 ;
end ;

if( Value_CurrentPosition <> 0 ) and ( Value_OpenPositionProfit > (Define_StopWin_Active_Point * absvalue(Value_CurrentPosition)) ) then begin
    Value_StopWin_Active_Begin = 1 ;
end ;

if( Value_StopWin_Active_Begin = 1 ) then begin
    if( Value_CurrentPosition > 0 ) then begin
        sell next bar IntPortion(Value_AvgEntryPrice + (Define_StopWin_Protect_Point * absvalue(Value_CurrentPosition))) stop ;
    end ;
    if( Value_CurrentPosition < 0 ) then begin
        buytocover next bar IntPortion(Value_AvgEntryPrice - (Define_StopWin_Protect_Point * absvalue(Value_CurrentPosition))) stop ;
    end ;
end ;

// Strategy End
end ;
//-------------------------------------------------------------------------------------------------------------------
