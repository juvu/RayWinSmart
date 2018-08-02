input:
    PathLocation("")
    , FileName("")
    , Strategy_ON_OFF(1)
    , String_MaxPosition("")
    , Define_MaxPosition(0)                             // 最大口數
    , String_Increase_Position("")
    , Define_Increase_Position(1)                       // 加碼口數
    , String_Increase_ONOFF_StopWinBestPrice_Over_LatestOrder("")
    , Define_Increase_ONOFF_StopWinBestPrice_Over_LatestOrder(0) // 停利線越過最後一碼
    , String_Increase_LatestPosition_Win_Point("")       // 最後一碼賺多少點才可以加碼
    , Define_Increase_LatestPosition_Win_Point(0)       // 最後一碼賺多少點才可以加碼
    , String_Override_StopLoss_FixPoint("")
    , Define_Override_StopLoss_FixPoint(0)              // 自定最大損失點數
    , Define_Order_Limit_OffsetPoint(5)                 // 限價單讓價點數
    ;
var:
    Define_Broker(0)
    , Define_TradeMode(0)
    , Define_Total_Money(0)
    , Define_MaxLossPersent(0)
    , Value_CurrentPosition(0)
    , Value_Initial_Value_CurrentPosition(0)
    , Value_AvgEntryPrice(0)
    , Value_IncreaseAvgEntryPrice(0)
    , Value_StopLoss_Max_Point(0)
    , Value_Max_StopWin_Point(0)
    , Value_Initial_StopWin_Best_Price(0)
    , Value_StopWin_Best_Price(0)
    // [1]
    , Define_StopWin_HighestPullBackPoint(0)            // 最高最低拉回點數
    // [2]
    , Define_StopWin_PreviousHighLow_K_Number(0)        // 近期 N 根 K 棒
    // [3]
    , Define_StopWin_PivotHighLow_LeftStrength(0)       // 轉折左邊 K 棒數
    , Define_StopWin_PivotHighLow_RightStrength(0)      // 轉折右邊 K 棒數
    // [1]
    , Value_StopWin_HighestPullBackPrice(0)
    // [2]
    , Value_StopWin_PreviousHighPrice(0)
    , Value_StopWin_PreviousLowPrice(0)
    // [3]
    , Value_StopWin_PivotHighPrice(0)
    , Value_StopWin_PivotLowPrice(0)
    , Define_StopWin_TickOffset(0)                      // 停利線讓價點數
    ;
//-------------------------------------------------------------------------------------------------------------------
// Read From File
Define_Broker = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 1);
Define_TradeMode = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 2);
Define_Total_Money = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 3);
Define_MaxLossPersent = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 4);
Define_StopWin_HighestPullBackPoint = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 5);
Define_StopWin_PreviousHighLow_K_Number = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 6);
Define_StopWin_PivotHighLow_LeftStrength = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 7);
Define_StopWin_PivotHighLow_RightStrength = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 8);
Define_StopWin_TickOffset = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 9);
//"

RaySmart_ReturnCurrentPositionAvgEntryPrice(
    Define_Broker
    , Value_CurrentPosition
    , Value_AvgEntryPrice
);

RaySmart_ReturnIncreaseAvgEntryPrice(
    Value_CurrentPosition
    , Define_Increase_Position
    , Value_AvgEntryPrice
    , Value_IncreaseAvgEntryPrice
);

RaySmart_ReturnMaxLossPersentToPoint(
    Define_TradeMode
    , Define_Total_Money
    , Define_MaxLossPersent
    , Value_StopLoss_Max_Point
);

// [1]
// Calculate
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

// [2]
// Calculate
    RaySmart_ReturnPreviousHighLow(
        Define_StopWin_PreviousHighLow_K_Number
        , Value_CurrentPosition
        , Value_StopWin_PreviousHighPrice
        , Value_StopWin_PreviousLowPrice
    ); 
    Value_StopWin_PreviousHighPrice = Value_StopWin_PreviousHighPrice + Define_StopWin_TickOffset ;
    Value_StopWin_PreviousLowPrice = Value_StopWin_PreviousLowPrice - Define_StopWin_TickOffset ;

// [3]
// Calculate
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

// 計算最佳的停利價
RaySmart_ReturnStopWinProfit(
    1, 1, 1                                     // ON / OFF
    , 0                                         // Value_StopLoss_FixPoint_Price : Not Use Here
    , Value_StopWin_HighestPullBackPrice
    , Value_StopWin_PreviousLowPrice
    , Value_StopWin_PreviousHighPrice
    , Value_StopWin_PivotHighPrice
    , Value_StopWin_PivotLowPrice
    , Value_AvgEntryPrice
    , Value_CurrentPosition
    , Value_Max_StopWin_Point
);

if( Value_CurrentPosition > 0 ) then begin
    Value_StopWin_Best_Price = ((Value_Max_StopWin_Point / absvalue(Value_CurrentPosition)) + Value_AvgEntryPrice) ;
end ;
if( Value_CurrentPosition < 0 ) then begin
    Value_StopWin_Best_Price = (Value_AvgEntryPrice - (Value_Max_StopWin_Point / absvalue(Value_CurrentPosition))) ;
end ;

if( Value_CurrentPosition[1] = 0 and Value_CurrentPosition <> 0 ) then begin
    Value_Initial_StopWin_Best_Price = Value_StopWin_Best_Price ;
end ;

//-------------------------------------------------------------------------------------------------------------------
if( Strategy_ON_OFF = 1 ) then begin
// Strategy Begin

condition1 = false ;
condition2 = false ;
condition3 = false ;
condition4 = false ;
condition5 = false ;

// 加碼不可超過最大口數
condition1 = absvalue(Value_CurrentPosition) < Define_MaxPosition ;

// 未平倉損益為正 , 才加碼
condition2 = OpenPositionProfit > 0 ;

// 加碼後 , 可接受的最大損失 / 最小獲利
if( Define_Override_StopLoss_FixPoint = 0 ) then begin
    if( Value_CurrentPosition > 0 ) then begin
    condition3 = ((Value_StopWin_Best_Price - Value_IncreaseAvgEntryPrice) * (absvalue(Value_CurrentPosition) + absvalue(Define_Increase_Position)))
                > ((-1) * Value_StopLoss_Max_Point) ;
    end ;
    if( Value_CurrentPosition < 0 ) then begin
    condition3 = ((Value_IncreaseAvgEntryPrice - Value_StopWin_Best_Price) * (absvalue(Value_CurrentPosition) + absvalue(Define_Increase_Position)))
                > ((-1) * Value_StopLoss_Max_Point) ;
    end ;
end else if( Define_Override_StopLoss_FixPoint <> 0 ) then begin
    if( Value_CurrentPosition > 0 ) then begin
    condition3 = ((Value_StopWin_Best_Price - Value_IncreaseAvgEntryPrice) * (absvalue(Value_CurrentPosition) + absvalue(Define_Increase_Position)))
                > (Define_Override_StopLoss_FixPoint) ;
    end ;
    if( Value_CurrentPosition < 0 ) then begin
    condition3 = ((Value_IncreaseAvgEntryPrice - Value_StopWin_Best_Price) * (absvalue(Value_CurrentPosition) + absvalue(Define_Increase_Position)))
                > (Define_Override_StopLoss_FixPoint) ;
    end ;
end ;

// 停利線越過最後一碼
if( Define_Increase_ONOFF_StopWinBestPrice_Over_LatestOrder <> 0 ) then begin
    if( Value_CurrentPosition > 0 ) then begin
        condition4 = (Value_StopWin_Best_Price > PosTradeEntryPrice(0, CurrentEntries - 1)) ;
    end ;
    if( Value_CurrentPosition < 0 ) then begin
        condition4 = (Value_StopWin_Best_Price < PosTradeEntryPrice(0, CurrentEntries - 1)) ;
    end ;
end else if( Define_Increase_ONOFF_StopWinBestPrice_Over_LatestOrder = 0 ) then begin
    condition4 = True ;
end ;

// 最後一碼賺多少點才可以加碼
if( Value_CurrentPosition > 0 ) then begin
    condition5 = (close - PosTradeEntryPrice(0, CurrentEntries - 1)) > Define_Increase_LatestPosition_Win_Point ;
end ;
if( Value_CurrentPosition < 0 ) then begin
    condition5 = (PosTradeEntryPrice(0, CurrentEntries - 1) - close) > Define_Increase_LatestPosition_Win_Point ;
end ;

// 目前停利線與初始停利線不同後 , 才可以加碼
if( Value_Initial_StopWin_Best_Price <> Value_StopWin_Best_Price ) then begin

if condition1 and condition2 and condition3 and condition4 and condition5 then begin
    if( Value_CurrentPosition > 0 ) then begin
        if( Define_Order_Limit_OffsetPoint = 0 ) then begin
            buy absvalue(Define_Increase_Position) contract next bar market ;
        end else begin
            buy absvalue(Define_Increase_Position) contract next bar IntPortion(close + Define_Order_Limit_OffsetPoint) limit ;
        end ;
    end ; // if( Value_CurrentPosition > 0 )
    if( Value_CurrentPosition < 0 ) then begin
        if( Define_Order_Limit_OffsetPoint = 0 ) then begin
            sellshort absvalue(Define_Increase_Position) contract next bar market ;
        end else begin
            sellshort absvalue(Define_Increase_Position) contract next bar IntPortion(close - Define_Order_Limit_OffsetPoint) limit ;
        end ;
    end ; // if( Value_CurrentPosition < 0 )
end ;

end ; //if( Value_Initial_StopWin_Best_Price <> Value_StopWin_Best_Price )

// Strategy End
end ;
//-------------------------------------------------------------------------------------------------------------------
