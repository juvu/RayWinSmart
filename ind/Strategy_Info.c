input :
	// user input
    PathLocation("")
    , FileName("")
    // Draw On Off
	, Define_OnOff_Draw_StopWin_HighestPullBackPrice(1)
    , Define_OnOff_Draw_StopWin_PreviousHighLow(1)
    // Draw Position
    , Define_FixInfoPositionX(20)
	, Define_FixInfoPositionY(80)
	, Define_TextDrawSize(9)
	, Define_DynamicShift(4)
	, Define_PrintDebug(0)
	// for chinese
	, String_CurrentPosition("CurrentPosition")                                     // 未平倉口數
	, String_AvgEntryPrice("AvgEntryPrice")                                         // 未平倉成本
	, String_OpenPositionProfit("OpenPositionProfit")                               // 未平倉損益
	, String_IncreaseAvgEntryPrice("IncreaseAvgEntryPrice")                         // 加碼成本
    , String_StopLoss_FixPoint("StopLoss_FixPoint")                                 // 最大損失停損
    , String_StopWin_HighestPullBackPrice("String_StopWin_HighestPullBackPrice")    // 高低拉回停利
    , String_StopWin_PreviousHighLow("String_StopWin_PreviousHighLow")              // 近期N根K棒停利
    , String_StopWin_Profit("String_StopWin_Profit")                                // 停利線平倉損益
    , String_StopWin_PivotHighLowPrice("String_StopWin_PivotHighLowPrice")          // 轉折高低停利出場
    , String_Daily_HighLow_Interval("String_Daily_HighLow_Interval")                // 當日高低差
    , String_Increase_Then_StopLoss_FixPoint_Price("String_Increase_Then_StopLoss_FixPoint_Price")  // 加碼後最大損失停損
    , String_StopWin_ProfitLossPrice("String_StopWin_ProfitLossPrice")              // 獲利回吐停利出場
    , String_StopWin_Protect_Active_Point("String_StopWin_Protect_Active_Point")    // 保本啟動中
	;

var :
	Value_IncreasePosition(0)
	, Define_Broker(0)
    , Define_TradeMode(0)
    , Define_Total_Money(0)
    , Define_MaxLossPersent(0)
    , Define_StopWin_HighestPullBackPoint(0)
    , Define_StopWin_PreviousHighLow_K_Number(0)
    , Define_StopWin_PivotHighLow_LeftStrength(0)
    , Define_StopWin_PivotHighLow_RightStrength(0)
    , Define_StopWin_TickOffset(0)
    , Define_StopWin_ProfitLoss_Active_Point(0)
    , Define_StopWin_ProfitLoss_Percentage(0)
	, Define_StopWin_Protect_Active_Point(0)
    , Value_TextDrawHorizPl(0)
	, Value_TextDrawVertPl(2)
	, Value_CurrentPosition(0)
	, Value_AvgEntryPrice(0)
 	, Value_OpenPositionProfit(0)
	, Value_IncreaseAvgEntryPrice(0)
    , Value_StopLoss_FixPoint_Price(0)
    , Value_Increase_Then_StopLoss_FixPoint_Price(0)
    , Value_StopWin_HighestPullBackPrice(0)
    , Value_StopWin_PreviousHighPrice(0)
    , Value_StopWin_PreviousLowPrice(0)
    , Value_StopLoss_Max_Point(0)
    , Value_Max_StopWin_Point(0)
    , Value_StopWin_PivotHighPrice(0)
    , Value_StopWin_PivotLowPrice(0)
    , Value_StopWin_ProfitLoss_Active_Begin(0)
    , Value_StopWin_ProfitLoss_Highest_OpenPositionProfit(0)
    , Value_StopWin_ProfitLossPrice(0)

    , Value_Daily_BarNumber(0)
    , Value_Daily_HighLow_Interval(0)

	, Color_FixInfo("Pink")
	, Color_AvgEntryPrice("LightSeaGreen")
	, Color_IncreaseAvgEntryPrice("DarkSeaGreen")
	, Color_StopLoss_FixPoint("SkyBlue")
	, Color_StopWin_HighestPullBackPrice("SteelBlue")
	, Color_StopWin_PreviousHighLow("DodgerBlue")
	, Color_StopWin_PivotHighLowPrice("CadetBlue")
	, Color_Increase_Then_StopLoss_FixPoint_Price("DeepSkyBlue")
	, Color_StopWin_ProfitLossPrice("LightBlue")

    , Dynamic_TextDrawHorizPl_Right(0)
    , Dynamic_TextDrawHorizPl_Left(1)
    , Dynamic_TextDrawHorizPl_Center(2)
    , Dynamic_TextDrawVertPl_Below(0)
    , Dynamic_TextDrawVertPl_Above(1)
    , Dynamic_TextDrawVertPl_Center(2)
    , Value_BeginDate(0) , Value_BeginTime(0)
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
Define_StopWin_HighestPullBackPoint = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 5);
Define_StopWin_PreviousHighLow_K_Number = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 6);
Define_StopWin_PivotHighLow_LeftStrength = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 7);
Define_StopWin_PivotHighLow_RightStrength = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 8);
Define_StopWin_TickOffset = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 9);
Define_StopWin_ProfitLoss_Active_Point = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 10);
Define_StopWin_ProfitLoss_Percentage = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 11);
Define_StopWin_Protect_Active_Point = _readfile("G:\_External_Txt\RayWinSmart\" + PathLocation + "\" + FileName + ".txt" , 12);
//"
end ;

RaySmart_ReturnIncreaseAvgEntryPrice(
    Value_CurrentPosition
    , 1 // Define_Increase_Position
    , Value_AvgEntryPrice
    , Value_IncreaseAvgEntryPrice
);

RaySmart_ReturnMaxLossPersentToPoint(
    Define_TradeMode
    , Define_Total_Money
    , Define_MaxLossPersent
    , Value_StopLoss_Max_Point
);

RaySmart_Return_StopLoss_FixPoint_Price(
    Value_AvgEntryPrice
    , Value_StopLoss_Max_Point
    , Value_CurrentPosition
    , Value_StopLoss_FixPoint_Price
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

// 計算加碼後最大損失出場價
if(Value_CurrentPosition > 0) then
    Value_Increase_Then_StopLoss_FixPoint_Price = Value_IncreaseAvgEntryPrice - (Value_StopLoss_Max_Point / (Value_CurrentPosition + 1)) ; // 預設加碼口數 1
if(Value_CurrentPosition < 0) then
    Value_Increase_Then_StopLoss_FixPoint_Price = Value_IncreaseAvgEntryPrice + (Value_StopLoss_Max_Point / absvalue(Value_CurrentPosition - 1)) ; // 預設加碼口數 1

// 計算獲利回吐停利出場價
if( Value_CurrentPosition > 0 ) then begin
RaySmart_ReturnStopWinProfitLoss(
    Define_StopWin_ProfitLoss_Active_Point
    , Value_CurrentPosition
    , Value_AvgEntryPrice
    , Value_StopWin_ProfitLoss_Active_Begin
    , Value_StopWin_ProfitLoss_Highest_OpenPositionProfit
);
Value_StopWin_ProfitLossPrice = 
    Value_AvgEntryPrice + (((Value_StopWin_ProfitLoss_Highest_OpenPositionProfit * (100 - Define_StopWin_ProfitLoss_Percentage)) / 100) / Value_CurrentPosition) ;
end ; // if( Value_CurrentPosition <> 0 )
if( Value_CurrentPosition < 0 ) then begin
RaySmart_ReturnStopWinProfitLoss(
    Define_StopWin_ProfitLoss_Active_Point
    , Value_CurrentPosition
    , Value_AvgEntryPrice
    , Value_StopWin_ProfitLoss_Active_Begin
    , Value_StopWin_ProfitLoss_Highest_OpenPositionProfit
);
Value_StopWin_ProfitLossPrice = 
    Value_AvgEntryPrice - (((Value_StopWin_ProfitLoss_Highest_OpenPositionProfit * (100 - Define_StopWin_ProfitLoss_Percentage)) / 100) / absvalue(Value_CurrentPosition)) ;
end ; // if( Value_CurrentPosition < 0 )

//-------------------------------------------------------------------------------------------------------------------

// Text Caculate : Value_OpenPositionProfit
if(Value_CurrentPosition > 0) then begin
    Value_OpenPositionProfit = (close - Value_AvgEntryPrice) * Value_CurrentPosition ;
end else if(Value_CurrentPosition < 0) then begin
    Value_OpenPositionProfit = (close - Value_AvgEntryPrice) * Value_CurrentPosition ;
end else if(Value_CurrentPosition = 0) then begin
    Value_OpenPositionProfit = 0 ;
end ;
// Text Caculate : Value_BeginBarNumber
if( Value_CurrentPosition <> Value_CurrentPosition[1] ) then begin
    Value_BeginDate = Date ;
    Value_BeginTime = Time ;
end ;
// Text Caculate : Value_Daily_HighLow_Interval
if( Time = 846 ) then begin
    Value_Daily_BarNumber = currentbar ;
end ;
Value_Daily_HighLow_Interval = Highest( High , currentbar - Value_Daily_BarNumber ) - Lowest( Low , currentbar - Value_Daily_BarNumber ) ;
//-------------------------------------------------------------------------------------------------------------------

// Text Draw : Value_BeginBarNumber
once begin
    value1 = Text_New (D, T, C, "");
end ;
Text_SetString(value1, "Date = " + numtostr(Value_BeginDate,0) + " / Time = " + numtostr(Value_BeginTime,0));
Text_SetStyle (value1, Dynamic_TextDrawHorizPl_Left, Dynamic_TextDrawVertPl_Center);
Text_SetSize(value1, Define_TextDrawSize);
Text_SetColor(value1, WEBColor(Color_FixInfo));
Text_SetLocation_Bn (value1, currentbar + RaySmart_ReturnTextDrawPositionX(98), RaySmart_ReturnTextDrawPositionY(95)) ;
// Text Draw : Value_CurrentPosition
once begin
    value2 = Text_New (D, T, C, "");
end ;
Text_SetString(value2, "\n\n" + String_CurrentPosition + " = " + numtostr(Value_CurrentPosition,0));
Text_SetStyle (value2, Dynamic_TextDrawHorizPl_Left, Dynamic_TextDrawVertPl_Center);
Text_SetSize(value2, Define_TextDrawSize);
Text_SetColor(value2, WEBColor(Color_FixInfo));
Text_SetLocation_Bn (value2, currentbar + RaySmart_ReturnTextDrawPositionX(98), RaySmart_ReturnTextDrawPositionY(95)) ;
// Text Draw : Value_AvgEntryPrice
once begin
    value3 = Text_New (D, T, C, "");
end ;
Text_SetString(value3, "\n\n\n\n" + String_AvgEntryPrice + " = " + numtostr(Value_AvgEntryPrice,0));
Text_SetStyle (value3, Dynamic_TextDrawHorizPl_Left, Dynamic_TextDrawVertPl_Center);
Text_SetSize(value3, Define_TextDrawSize);
Text_SetColor(value3, WEBColor(Color_FixInfo));
Text_SetLocation_Bn (value3, currentbar + RaySmart_ReturnTextDrawPositionX(98), RaySmart_ReturnTextDrawPositionY(95)) ;
once begin
    value4 = Text_New (D, T, Value_AvgEntryPrice, "");
end ;
Text_SetString(value4, String_AvgEntryPrice + " = " + numtostr(Value_AvgEntryPrice,0));
Text_SetStyle (value4, Dynamic_TextDrawHorizPl_Left, Dynamic_TextDrawVertPl_Above);
Text_SetSize(value4, Define_TextDrawSize);
Text_SetColor(value4, WEBColor(Color_AvgEntryPrice));
Text_SetLocation_Bn (value4, currentbar + RaySmart_ReturnTextDrawPositionX(50), Value_AvgEntryPrice) ;
if( Value_CurrentPosition <> 0 and Value_AvgEntryPrice <> 0 ) then begin
        plot1(Value_AvgEntryPrice,"Value_AvgEntryPrice",WEBColor(Color_AvgEntryPrice));
        once begin
            value5 = TL_New_BN (currentbar, Value_AvgEntryPrice, currentbar, Value_AvgEntryPrice);
            TL_SetColor(value5, WEBColor(Color_AvgEntryPrice));
        end ;
        TL_SetBegin_bn(value5, currentbar, Value_AvgEntryPrice);
        TL_SetEnd_bn(value5, currentbar + RaySmart_ReturnTextDrawPositionX(50), Value_AvgEntryPrice);
end ;
// Text Draw : Value_OpenPositionProfit
once begin
    value6 = Text_New (D, T, C, "");
end ;
Text_SetString(value6, "\n\n\n\n\n\n" + String_OpenPositionProfit + " = " + numtostr(Value_OpenPositionProfit,0));
Text_SetStyle (value6,Dynamic_TextDrawHorizPl_Left, Dynamic_TextDrawVertPl_Center);
Text_SetSize(value6, Define_TextDrawSize);
Text_SetColor(value6, WEBColor(Color_FixInfo));
Text_SetLocation_Bn (value6, currentbar + RaySmart_ReturnTextDrawPositionX(98), RaySmart_ReturnTextDrawPositionY(95)) ;
// Text Draw : Value_IncreaseAvgEntryPrice
once begin
    value7 = Text_New (D, T, C, "");
end ;
Text_SetString(value7, "\n\n\n\n\n\n\n\n" + String_IncreaseAvgEntryPrice + " = " + numtostr(Value_IncreaseAvgEntryPrice,0));
Text_SetStyle (value7, Dynamic_TextDrawHorizPl_Left, Dynamic_TextDrawVertPl_Center);
Text_SetSize(value7, Define_TextDrawSize);
Text_SetColor(value7, WEBColor(Color_FixInfo));
Text_SetLocation_Bn (value7, currentbar + RaySmart_ReturnTextDrawPositionX(98), RaySmart_ReturnTextDrawPositionY(95)) ;
once begin
    value8 = Text_New (D, T, Value_IncreaseAvgEntryPrice, "");
end ;
Text_SetString(value8, String_IncreaseAvgEntryPrice + " = " + numtostr(Value_IncreaseAvgEntryPrice,0));
Text_SetStyle (value8, Dynamic_TextDrawHorizPl_Left, Dynamic_TextDrawVertPl_Above);
Text_SetSize(value8, Define_TextDrawSize);
Text_SetColor(value8, WEBColor(Color_IncreaseAvgEntryPrice));
Text_SetLocation_Bn (value8, currentbar + RaySmart_ReturnTextDrawPositionX(50), Value_IncreaseAvgEntryPrice) ;
if( Value_CurrentPosition <> 0 and Value_IncreaseAvgEntryPrice <> 0 ) then begin
    plot2(Value_IncreaseAvgEntryPrice,"Value_IncreaseAvgEntryPrice",WEBColor(Color_IncreaseAvgEntryPrice));
    once begin
        value9 = TL_New_BN (currentbar, Value_IncreaseAvgEntryPrice, currentbar, Value_IncreaseAvgEntryPrice);
        TL_SetColor(value9, WEBColor(Color_IncreaseAvgEntryPrice));
    end ;
    TL_SetBegin_bn(value9, currentbar, Value_IncreaseAvgEntryPrice);
    TL_SetEnd_bn(value9, currentbar + RaySmart_ReturnTextDrawPositionX(50), Value_IncreaseAvgEntryPrice);
end ;
// Text Draw : Value_StopLoss_FixPoint_Price
once begin
    value10 = Text_New (D, T, Value_StopLoss_FixPoint_Price, "");
end ;
Text_SetString(value10, String_StopLoss_FixPoint + "=" + numtostr(Value_StopLoss_FixPoint_Price,0));
Text_SetStyle (value10, Dynamic_TextDrawHorizPl_Left, Dynamic_TextDrawVertPl_Above);
Text_SetSize(value10, Define_TextDrawSize);
Text_SetColor(value10, WEBColor(Color_StopLoss_FixPoint));
Text_SetLocation_Bn (value10, currentbar + RaySmart_ReturnTextDrawPositionX(50), Value_StopLoss_FixPoint_Price) ;
if( Value_CurrentPosition <> 0 and Value_StopLoss_FixPoint_Price > 0 ) then begin
    plot3(Value_StopLoss_FixPoint_Price,"Value_StopLoss_FixPoint_Price",WEBColor(Color_StopLoss_FixPoint));
    once begin
        value11 = TL_New_BN (currentbar, Value_StopLoss_FixPoint_Price, currentbar, Value_StopLoss_FixPoint_Price);
        TL_SetColor(value11, WEBColor(Color_StopLoss_FixPoint));
    end ;
    TL_SetBegin_bn(value11, currentbar, Value_StopLoss_FixPoint_Price);
    TL_SetEnd_bn(value11, currentbar + RaySmart_ReturnTextDrawPositionX(50), Value_StopLoss_FixPoint_Price);
end ;
// Text Draw : Value_StopWin_HighestPullBackPrice
if( Define_OnOff_Draw_StopWin_HighestPullBackPrice = 1 ) then begin
    once begin
        value12 = Text_New (D, T, Value_StopWin_HighestPullBackPrice, "");
    end ;
    Text_SetString(value12, String_StopWin_HighestPullBackPrice + "=" + numtostr(Value_StopWin_HighestPullBackPrice,0));
    Text_SetStyle (value12, Dynamic_TextDrawHorizPl_Left, Dynamic_TextDrawVertPl_Above);
    Text_SetSize(value12, Define_TextDrawSize);
    Text_SetColor(value12, WEBColor(Color_StopWin_HighestPullBackPrice));
    Text_SetLocation_Bn (value12, currentbar + RaySmart_ReturnTextDrawPositionX(50), Value_StopWin_HighestPullBackPrice) ;
    plot4(Value_StopWin_HighestPullBackPrice,"Value_StopWin_HighestPullBackPrice",WEBColor(Color_StopWin_HighestPullBackPrice));
    once begin
        value13 = TL_New_BN (currentbar, Value_StopWin_HighestPullBackPrice, currentbar, Value_StopWin_HighestPullBackPrice);
        TL_SetColor(value13, WEBColor(Color_StopWin_HighestPullBackPrice));
    end ;
    TL_SetBegin_bn(value13, currentbar, Value_StopWin_HighestPullBackPrice);
    TL_SetEnd_bn(value13, currentbar + RaySmart_ReturnTextDrawPositionX(50), Value_StopWin_HighestPullBackPrice);
end ;
// Text Draw : Value_StopWin_PreviousHighPrice / Value_StopWin_PreviousLowPrice
if( Define_OnOff_Draw_StopWin_PreviousHighLow = 1 ) then begin
    if( Value_CurrentPosition > 0 ) then begin
        once begin
            value14 = Text_New (D, T, Value_StopWin_PreviousLowPrice, "");
        end ;
        Text_SetString(value14, String_StopWin_PreviousHighLow + "=" + numtostr(Value_StopWin_PreviousLowPrice,0));
        Text_SetStyle (value14, Dynamic_TextDrawHorizPl_Left, Dynamic_TextDrawVertPl_Above);
        Text_SetSize(value14, Define_TextDrawSize);
        Text_SetColor(value14, WEBColor(Color_StopWin_PreviousHighLow));
        Text_SetLocation_Bn (value14, currentbar + RaySmart_ReturnTextDrawPositionX(50), Value_StopWin_PreviousLowPrice) ;
        plot5(Value_StopWin_PreviousLowPrice,"Value_StopWin_PreviousLowPrice",WEBColor(Color_StopWin_PreviousHighLow));
        once begin
            value15 = TL_New_BN (currentbar, Value_StopWin_PreviousLowPrice, currentbar, Value_StopWin_PreviousLowPrice);
            TL_SetColor(value15, WEBColor(Color_StopWin_PreviousHighLow));
        end ;
        TL_SetBegin_bn(value15, currentbar, Value_StopWin_PreviousLowPrice);
        TL_SetEnd_bn(value15, currentbar + RaySmart_ReturnTextDrawPositionX(50), Value_StopWin_PreviousLowPrice);
    end ; // if( Value_CurrentPosition > 0 )
    if( Value_CurrentPosition < 0 ) then begin
        once begin
            value16 = Text_New (D, T, Value_StopWin_PreviousHighPrice, "");
        end ;
        Text_SetString(value16, String_StopWin_PreviousHighLow + "=" + numtostr(Value_StopWin_PreviousHighPrice,0));
        Text_SetStyle (value16, Dynamic_TextDrawHorizPl_Left, Dynamic_TextDrawVertPl_Above);
        Text_SetSize(value16, Define_TextDrawSize);
        Text_SetColor(value16, WEBColor(Color_StopWin_PreviousHighLow));
        Text_SetLocation_Bn (value16, currentbar + RaySmart_ReturnTextDrawPositionX(50), Value_StopWin_PreviousHighPrice) ;
        plot5(Value_StopWin_PreviousHighPrice,"Value_StopWin_PreviousHighPrice",WEBColor(Color_StopWin_PreviousHighLow));
        once begin
            value17 = TL_New_BN (currentbar, Value_StopWin_PreviousHighPrice, currentbar, Value_StopWin_PreviousHighPrice);
            TL_SetColor(value17, WEBColor(Color_StopWin_PreviousHighLow));
        end ;
        TL_SetBegin_bn(value17, currentbar, Value_StopWin_PreviousHighPrice);
        TL_SetEnd_bn(value17, currentbar + RaySmart_ReturnTextDrawPositionX(50), Value_StopWin_PreviousHighPrice);
    end ; // if( Value_CurrentPosition < 0 )
end ;
// Text Draw : Value_Max_StopWin_Point
once begin
    value18 = Text_New (D, T, C, "");
end ;
Text_SetString(value18, "\n\n\n\n\n\n\n\n\n\n" + String_StopWin_Profit + " = " + numtostr(Value_Max_StopWin_Point,0));
Text_SetStyle (value18, Dynamic_TextDrawHorizPl_Left, Dynamic_TextDrawVertPl_Center);
Text_SetSize(value18, Define_TextDrawSize);
Text_SetColor(value18, WEBColor(Color_FixInfo));
Text_SetLocation_Bn (value18, currentbar + RaySmart_ReturnTextDrawPositionX(98), RaySmart_ReturnTextDrawPositionY(95)) ;
// Text Draw : Value_StopWin_PivotHighPrice / Value_StopWin_PivotLowPrice
if( Value_CurrentPosition > 0 ) then begin
    once begin
        value19 = Text_New (D, T, Value_StopWin_PivotLowPrice, "");
    end ;
    Text_SetString(value19, String_StopWin_PivotHighLowPrice + "=" + numtostr(Value_StopWin_PivotLowPrice,0));
    Text_SetStyle (value19, Dynamic_TextDrawHorizPl_Left, Dynamic_TextDrawVertPl_Above);
    Text_SetSize(value19, Define_TextDrawSize);
    Text_SetColor(value19, WEBColor(Color_StopWin_PivotHighLowPrice));
    Text_SetLocation_Bn (value19, currentbar + RaySmart_ReturnTextDrawPositionX(50), Value_StopWin_PivotLowPrice) ;
    plot6(Value_StopWin_PivotLowPrice,"Value_StopWin_PivotLowPrice",WEBColor(Color_StopWin_PivotHighLowPrice));
    once begin
        value20 = TL_New_BN (currentbar, Value_StopWin_PivotLowPrice, currentbar, Value_StopWin_PivotLowPrice);
        TL_SetColor(value20, WEBColor(Color_StopWin_PivotHighLowPrice));
    end ;
    TL_SetBegin_bn(value20, currentbar, Value_StopWin_PivotLowPrice);
    TL_SetEnd_bn(value20, currentbar + RaySmart_ReturnTextDrawPositionX(50), Value_StopWin_PivotLowPrice);
end ; // if( Value_CurrentPosition > 0 )
if( Value_CurrentPosition < 0 ) then begin
    once begin
        value21 = Text_New (D, T, Value_StopWin_PivotHighPrice, "");
    end ;
    Text_SetString(value21, String_StopWin_PivotHighLowPrice + "=" + numtostr(Value_StopWin_PivotHighPrice,0));
    Text_SetStyle (value21, Dynamic_TextDrawHorizPl_Left, Dynamic_TextDrawVertPl_Above);
    Text_SetSize(value21, Define_TextDrawSize);
    Text_SetColor(value21, WEBColor(Color_StopWin_PivotHighLowPrice));
    Text_SetLocation_Bn (value21, currentbar + RaySmart_ReturnTextDrawPositionX(50), Value_StopWin_PivotHighPrice) ;
    plot6(Value_StopWin_PivotHighPrice,"Value_StopWin_PivotHighPrice",WEBColor(Color_StopWin_PivotHighLowPrice));
    once begin
        value22 = TL_New_BN (currentbar, Value_StopWin_PivotHighPrice, currentbar, Value_StopWin_PivotHighPrice);
        TL_SetColor(value22, WEBColor(Color_StopWin_PivotHighLowPrice));
    end ;
    TL_SetBegin_bn(value22, currentbar, Value_StopWin_PivotHighPrice);
    TL_SetEnd_bn(value22, currentbar + RaySmart_ReturnTextDrawPositionX(50), Value_StopWin_PivotHighPrice);
end ; // if( Value_CurrentPosition < 0 )

// Text Caculate : Value_Daily_HighLow_Interval
once begin
    value23 = Text_New (D, T, C, "");
end ;
Text_SetString(value23, "\n\n\n\n\n\n\n\n\n\n\n\n" + String_Daily_HighLow_Interval + " = " + numtostr(Value_Daily_HighLow_Interval,0));
Text_SetStyle (value23, Dynamic_TextDrawHorizPl_Left, Dynamic_TextDrawVertPl_Center);
Text_SetSize(value23, Define_TextDrawSize);
Text_SetColor(value23, WEBColor(Color_FixInfo));
Text_SetLocation_Bn (value23, currentbar + RaySmart_ReturnTextDrawPositionX(98), RaySmart_ReturnTextDrawPositionY(95)) ;

// Text Draw : Value_Increase_Then_StopLoss_FixPoint_Price
once begin
    value24 = Text_New (D, T, Value_Increase_Then_StopLoss_FixPoint_Price, "");
end ;
Text_SetString(value24, String_Increase_Then_StopLoss_FixPoint_Price + "=" + numtostr(Value_Increase_Then_StopLoss_FixPoint_Price,0));
Text_SetStyle (value24, Dynamic_TextDrawHorizPl_Left, Dynamic_TextDrawVertPl_Above);
Text_SetSize(value24, Define_TextDrawSize);
Text_SetColor(value24, WEBColor(Color_Increase_Then_StopLoss_FixPoint_Price));
Text_SetLocation_Bn (value24, currentbar + RaySmart_ReturnTextDrawPositionX(50), Value_Increase_Then_StopLoss_FixPoint_Price) ;
if( Value_CurrentPosition <> 0 and Value_Increase_Then_StopLoss_FixPoint_Price > 0 ) then begin
    plot7(Value_Increase_Then_StopLoss_FixPoint_Price,"Value_Increase_Then_StopLoss_FixPoint_Price",WEBColor(Color_Increase_Then_StopLoss_FixPoint_Price));
    once begin
        value25 = TL_New_BN (currentbar, Value_Increase_Then_StopLoss_FixPoint_Price, currentbar, Value_Increase_Then_StopLoss_FixPoint_Price);
        TL_SetColor(value25, WEBColor(Color_Increase_Then_StopLoss_FixPoint_Price));
    end ;
    TL_SetBegin_bn(value25, currentbar, Value_Increase_Then_StopLoss_FixPoint_Price);
    TL_SetEnd_bn(value25, currentbar + RaySmart_ReturnTextDrawPositionX(50), Value_Increase_Then_StopLoss_FixPoint_Price);
end ;

// Text Draw : Value_StopWin_ProfitLossPrice
if( Value_StopWin_ProfitLoss_Active_Begin = 1 ) then begin
    once begin
        value26 = Text_New (D, T, Value_StopWin_ProfitLossPrice, "");
    end ;
    Text_SetString(value26, String_StopWin_ProfitLossPrice + "=" + numtostr(Value_StopWin_ProfitLossPrice,0));
    Text_SetStyle (value26, Dynamic_TextDrawHorizPl_Left, Dynamic_TextDrawVertPl_Above);
    Text_SetSize(value26, Define_TextDrawSize);
    Text_SetColor(value26, WEBColor(Color_StopWin_ProfitLossPrice));
    Text_SetLocation_Bn (value26, currentbar + RaySmart_ReturnTextDrawPositionX(50), Value_StopWin_ProfitLossPrice) ;
    if( Value_CurrentPosition <> 0 and Value_StopWin_ProfitLossPrice > 0 ) then begin
        plot8(Value_StopWin_ProfitLossPrice,"Value_StopWin_ProfitLossPrice",WEBColor(Color_StopWin_ProfitLossPrice));
        once begin
            value27 = TL_New_BN (currentbar, Value_StopWin_ProfitLossPrice, currentbar, Value_StopWin_ProfitLossPrice);
            TL_SetColor(value27, WEBColor(Color_StopWin_ProfitLossPrice));
        end ;
        TL_SetBegin_bn(value27, currentbar, Value_StopWin_ProfitLossPrice);
        TL_SetEnd_bn(value27, currentbar + RaySmart_ReturnTextDrawPositionX(50), Value_StopWin_ProfitLossPrice);
    end ;
end ; // if( Value_StopWin_ProfitLoss_Active_Begin = 1 )

// Text Caculate : Value_StopWin_Active_Begin
if( Value_CurrentPosition <> 0 ) and ( absvalue(Close - Value_AvgEntryPrice) >= Define_StopWin_Protect_Active_Point ) then begin
once begin
    value28 = Text_New (D, T, C, "");
end ;
Text_SetString(value28, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n" + String_StopWin_Protect_Active_Point);
Text_SetStyle (value28, Dynamic_TextDrawHorizPl_Right, Dynamic_TextDrawVertPl_Center);
Text_SetSize(value28, Define_TextDrawSize);
Text_SetColor(value28, WEBColor(Color_FixInfo));
Text_SetLocation_Bn (value28, currentbar + RaySmart_ReturnTextDrawPositionX(98), RaySmart_ReturnTextDrawPositionY(95)) ;
end ; // if( Value_CurrentPosition <> 0 ) and ( absvalue(Close - Value_AvgEntryPrice) >= Define_StopWin_Protect_Active_Point )
//-------------------------------------------------------------------------------------------------------------------
