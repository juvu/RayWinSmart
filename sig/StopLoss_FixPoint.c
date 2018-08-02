input:
    PathLocation("")
    , FileName("")
    , String_Override_StopLoss_FixPoint("")
    , Define_Override_StopLoss_FixPoint(0)  // 自定最大損失點數
    ;
var:
    Define_Broker(0)
    , Define_TradeMode(0)                   // 交易商品模式 1 : 1 大點除以 4 , 0 : 1 大點不除以 4
    , Define_Total_Money(0)                   // 總資金
    , Define_MaxLossPersent(0)              // 最大容忍損失 %
    , Value_CurrentPosition(0)
    , Value_Initial_Value_CurrentPosition(0)
    , Value_AvgEntryPrice(0)
    , Value_StopLoss_FixPoint_Price(0)
    , Value_StopLoss_Max_Point(0)
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
Define_TradeMode = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 2);
Define_Total_Money = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 3);
Define_MaxLossPersent = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 4);
//"
end ;

RaySmart_ReturnMaxLossPersentToPoint(
    Define_TradeMode
    , Define_Total_Money
    , Define_MaxLossPersent
    , Value_StopLoss_Max_Point
);

if( Value_CurrentPosition > 0 ) then
    Value_StopLoss_FixPoint_Price = Value_AvgEntryPrice - (Value_StopLoss_Max_Point / Value_CurrentPosition) ;
if( Value_CurrentPosition < 0 ) then
    Value_StopLoss_FixPoint_Price = Value_AvgEntryPrice + (Value_StopLoss_Max_Point / absvalue(Value_CurrentPosition)) ;

//-------------------------------------------------------------------------------------------------------------------
// Strategy Begin
if( Define_Override_StopLoss_FixPoint = 0 ) then begin
    if( Value_CurrentPosition > 0 ) then begin
        sell next bar IntPortion(Value_StopLoss_FixPoint_Price) stop ;
    end ; // if( Value_CurrentPosition > 0 )

    if( Value_CurrentPosition < 0 ) then begin
        buytocover next bar IntPortion(Value_StopLoss_FixPoint_Price) stop ;
    end ; // if( Value_CurrentPosition < 0 )
end ;

if( Define_Override_StopLoss_FixPoint <> 0 ) then begin
    if( Value_CurrentPosition > 0 ) then begin
        sell next bar IntPortion((Value_AvgEntryPrice - (Define_Override_StopLoss_FixPoint / absvalue(Value_CurrentPosition)))) stop ;
    end ; // if( Value_CurrentPosition > 0 )

    if( Value_CurrentPosition < 0 ) then begin
        buytocover next bar IntPortion((Value_AvgEntryPrice + (Define_Override_StopLoss_FixPoint / absvalue(Value_CurrentPosition)))) stop ;
    end ; // if( Value_CurrentPosition < 0 )
end ;
// Strategy End
//-------------------------------------------------------------------------------------------------------------------
