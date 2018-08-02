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
    , Value_StopWin_PivotHighPrice(0)
    , Value_StopWin_PivotLowPrice(0)
    , Value_Initial_Value_StopWin_PivotHighPrice(0)
    , Value_Initial_Value_StopWin_PivotLowPrice(0)
    , Define_StopWin_PivotHighLow_LeftStrength(0)           // 轉折左邊 K 棒數
    , Define_StopWin_PivotHighLow_RightStrength(0)          // 轉折右邊 K 棒數
    , Define_StopWin_TickOffset(0)
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
Define_StopWin_PivotHighLow_LeftStrength = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 7);
Define_StopWin_PivotHighLow_RightStrength = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 8);
Define_StopWin_TickOffset = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 9);
//"
end ;

RaySmart_ReturnPivotHighLowPrice(
    High , Low
    , Define_StopWin_PivotHighLow_LeftStrength
    , Define_StopWin_PivotHighLow_RightStrength
    , Value_CurrentPosition
    , Value_StopWin_PivotHighPrice
    , Value_StopWin_PivotLowPrice
);

Value_StopWin_PivotHighPrice = Value_StopWin_PivotHighPrice + Define_StopWin_TickOffset ;
Value_StopWin_PivotLowPrice = Value_StopWin_PivotLowPrice - Define_StopWin_TickOffset ;

//-------------------------------------------------------------------------------------------------------------------
if( Strategy_ON_OFF = 1 ) then begin
// Strategy Begin
if( Value_CurrentPosition[1] = 0 and Value_CurrentPosition <> 0 ) then begin
    Value_Initial_Value_StopWin_PivotLowPrice = Value_StopWin_PivotLowPrice ;
    Value_Initial_Value_StopWin_PivotHighPrice = Value_StopWin_PivotHighPrice ;
    Value_Initial_Value_CurrentPosition = absvalue(Value_CurrentPosition) ;
end ;

if( Value_Initial_Value_StopWin_PivotLowPrice <> Value_StopWin_PivotLowPrice ) then begin
    if( Value_CurrentPosition > 0 ) and ( (OpenPositionProfit > 0) or (absvalue(Value_CurrentPosition) > Value_Initial_Value_CurrentPosition) ) then begin
        sell next bar IntPortion(Value_StopWin_PivotLowPrice) stop ;
    end ; // if( Value_CurrentPosition > 0 )
end ;
if( Value_Initial_Value_StopWin_PivotHighPrice <> Value_StopWin_PivotHighPrice ) then begin
    if( Value_CurrentPosition < 0 ) and ( (OpenPositionProfit > 0) or (absvalue(Value_CurrentPosition) > Value_Initial_Value_CurrentPosition) ) then begin
        buytocover next bar IntPortion(Value_StopWin_PivotHighPrice) stop ;
    end ; // if( Value_CurrentPosition < 0 )
end ;
// Strategy End
end ;
//-------------------------------------------------------------------------------------------------------------------
