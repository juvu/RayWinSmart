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
    , Value_StopWin_PreviousHighPrice(0)
    , Value_StopWin_PreviousLowPrice(0)
    , Value_Initial_Value_StopWin_PreviousHighPrice(0)
    , Value_Initial_Value_StopWin_PreviousLowPrice(0)
    , Define_StopWin_PreviousHighLow_K_Number(0)            // 近期 N 根 K 棒
    , Define_StopWin_TickOffset(0)
    ;
//-------------------------------------------------------------------------------------------------------------------
// Read From File
Define_Broker = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 1);
Define_StopWin_PreviousHighLow_K_Number = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 6);
Define_StopWin_TickOffset = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 9);
//"

RaySmart_ReturnCurrentPositionAvgEntryPrice(
    Define_Broker
    , Value_CurrentPosition
    , Value_AvgEntryPrice
);

RaySmart_ReturnPreviousHighLow(
    Define_StopWin_PreviousHighLow_K_Number
    , Value_CurrentPosition
    , Value_StopWin_PreviousHighPrice
    , Value_StopWin_PreviousLowPrice
);

Value_StopWin_PreviousHighPrice = Value_StopWin_PreviousHighPrice + Define_StopWin_TickOffset ;
Value_StopWin_PreviousLowPrice = Value_StopWin_PreviousLowPrice - Define_StopWin_TickOffset ;

//-------------------------------------------------------------------------------------------------------------------
if( Strategy_ON_OFF = 1 ) then begin
// Strategy Begin
if( Value_CurrentPosition[1] = 0 and Value_CurrentPosition <> 0 ) then begin
    Value_Initial_Value_StopWin_PreviousHighPrice = Value_StopWin_PreviousHighPrice ;
    Value_Initial_Value_StopWin_PreviousLowPrice = Value_StopWin_PreviousLowPrice ;
    Value_Initial_Value_CurrentPosition = absvalue(Value_CurrentPosition) ;
end ;

if( Value_Initial_Value_StopWin_PreviousLowPrice <> Value_StopWin_PreviousLowPrice ) then begin
    if( Value_CurrentPosition > 0 ) and ( (OpenPositionProfit > 0) or (absvalue(Value_CurrentPosition) > Value_Initial_Value_CurrentPosition) ) then begin
        sell next bar IntPortion(Value_StopWin_PreviousLowPrice) stop ;
    end ; // if( Value_CurrentPosition > 0 )
end ;

if( Value_Initial_Value_StopWin_PreviousHighPrice <> Value_StopWin_PreviousHighPrice ) then begin
    if( Value_CurrentPosition < 0 ) and ( (OpenPositionProfit > 0) or (absvalue(Value_CurrentPosition) > Value_Initial_Value_CurrentPosition) ) then begin
        buytocover next bar IntPortion(Value_StopWin_PreviousHighPrice) stop ;
    end ; // if( Value_CurrentPosition < 0 )
end ;
// Strategy End
end ;
//-------------------------------------------------------------------------------------------------------------------
