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
    , Define_StopWin_HighestPullBackPoint(0)    // 最高最低拉回點數
    , Define_StopWin_TickOffset(0)              // 停利線讓價點數
    , Value_StopWin_HighestPullBackPrice(0)
    , Value_Initial_Value_StopWin_HighestPullBackPrice(0)
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
Define_StopWin_HighestPullBackPoint = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 5);
Define_StopWin_TickOffset = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 9);
//"
end ;

if( Value_CurrentPosition <> 0 ) then begin
    RaySmart_ReturnStopWinHighestPullBackPrice(
        Define_StopWin_HighestPullBackPoint
        , Value_CurrentPosition
        , iff( Value_CurrentPosition > 0 , High , Low)
        , Value_StopWin_HighestPullBackPrice
    );
end ;

if( Value_CurrentPosition > 0 ) then
    Value_StopWin_HighestPullBackPrice = Value_StopWin_HighestPullBackPrice - Define_StopWin_TickOffset ;
if( Value_CurrentPosition < 0 ) then
    Value_StopWin_HighestPullBackPrice = Value_StopWin_HighestPullBackPrice + Define_StopWin_TickOffset ;

//-------------------------------------------------------------------------------------------------------------------
if( Strategy_ON_OFF = 1 ) then begin
// Strategy Begin
if( Value_CurrentPosition[1] = 0 and Value_CurrentPosition <> 0 ) then begin
    Value_Initial_Value_StopWin_HighestPullBackPrice = Value_StopWin_HighestPullBackPrice ;
    Value_Initial_Value_CurrentPosition = absvalue(Value_CurrentPosition) ;
end ;

//if( Value_Initial_Value_StopWin_HighestPullBackPrice <> Value_StopWin_HighestPullBackPrice ) then begin
//    if( Value_CurrentPosition > 0 ) and ( (OpenPositionProfit > 0) or (absvalue(Value_CurrentPosition) > Value_Initial_Value_CurrentPosition) ) then begin
    if( Value_CurrentPosition > 0 ) then begin
        sell next bar IntPortion(Value_StopWin_HighestPullBackPrice) stop ;
    end ; // if( Value_CurrentPosition > 0 )

//    if( Value_CurrentPosition < 0 ) and ( (OpenPositionProfit > 0) or (absvalue(Value_CurrentPosition) > Value_Initial_Value_CurrentPosition) ) then begin
    if( Value_CurrentPosition < 0 ) then begin
        buytocover next bar IntPortion(Value_StopWin_HighestPullBackPrice) stop ;
    end ; // if( Value_CurrentPosition < 0 )
//end ;
// Strategy End
end ;
//-------------------------------------------------------------------------------------------------------------------
