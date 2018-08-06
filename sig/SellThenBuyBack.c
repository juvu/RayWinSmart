input:
    PathLocation("")
    , FileName("")
    , Strategy_ON_OFF(1)
    , String_After_K_Number("")
    , Define_After_K_Number(0)              // 經過K棒數
    , String_BuyBack_Position("")
    , Define_BuyBack_Position(0)            // 進場口數
    ;
var:
    Define_Broker(0)
    , Value_CurrentPosition(0)
    , Value_Initial_Value_CurrentPosition(0)
    , Value_AvgEntryPrice(0)
    , Value_SellThenBuyBack_Begin(0)
    ;

//-------------------------------------------------------------------------------------------------------------------
// Read From File
Define_Broker = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 1);
//"

//-------------------------------------------------------------------------------------------------------------------
RaySmart_ReturnCurrentPositionAvgEntryPrice(
    Define_Broker
    , Value_CurrentPosition
    , Value_AvgEntryPrice
);

if( Value_CurrentPosition[1] <> 0 and Value_CurrentPosition = 0 ) then begin
    Value_SellThenBuyBack_Begin = 1 ;
    Value_Initial_Value_CurrentPosition = Value_CurrentPosition[1] ;
end ;

if( Value_CurrentPosition <> 0 ) then begin
    Value_SellThenBuyBack_Begin = 0 ;
end ;

//-------------------------------------------------------------------------------------------------------------------
if( Strategy_ON_OFF = 1 ) then begin
// Strategy Begin
if(  Value_SellThenBuyBack_Begin = 1 ) then begin
    if( currentbar > (PosTradeExitBar(0, CurrentEntries - 1) + Define_After_K_Number) ) then begin
        if( Value_Initial_Value_CurrentPosition > 0 ) then begin
            if (close > minlist(PosTradeEntryPrice(0, CurrentEntries - 1), PosTradeExitPrice(0, CurrentEntries - 1))) then
                buy (Define_BuyBack_Position) contract next bar market ;
        end ;
        if( Value_Initial_Value_CurrentPosition < 0 ) then begin
            if (close < maxlist(PosTradeEntryPrice(0, CurrentEntries - 1), PosTradeExitPrice(0, CurrentEntries - 1))) then
                sellshort (Define_BuyBack_Position) contract next bar market ;
        end ;
    end ;
end ;
// Strategy End
end ;
//-------------------------------------------------------------------------------------------------------------------
