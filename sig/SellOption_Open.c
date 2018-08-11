// Signal :
// ------------------------------------------------------------------------------------------------
[IntrabarOrderGeneration = True];

input:
    Class("")
    , Define_Option_Catagory(0)   // 1 : CALL , -1 : PUT
    , Define_Order_Limit_OffsetPoint(5)
    ;
var:
    InfoMap(MapSN.New)
    , ADE_UseFile(ADE.UseFile)
// Read From File
    , TXF1_Value_CurrentPosition(0)
//Local Value
    , Option_Value_CurrentPosition(0)
// DEBUG
    , Define_PrintDebug(0)
    ;

// ------------------------------------------------------------------------------------------------
if( currentbar = 1 ) and ( ADE_UseFile ) then begin
    Value1 = ADE.OpenMap(Class, "TXF1", 1);
end ;
// ------------------------------------------------------------------------------------------------
Option_Value_CurrentPosition = marketposition * currentshares ;

// Read From File
Value1 = ADE.GetBarInfo(Class, "TXF1", 1, ADE.BarID, InfoMap);
TXF1_Value_CurrentPosition = MapSN.Get(InfoMap, "TXF1_Value_CurrentPosition");
// ------------------------------------------------------------------------------------------------
// SELL OPTION
if( TXF1_Value_CurrentPosition * Define_Option_Catagory < 0 ) and ( absvalue(TXF1_Value_CurrentPosition) <> absvalue(Option_Value_CurrentPosition) ) then begin
    if( absvalue(TXF1_Value_CurrentPosition) > absvalue(Option_Value_CurrentPosition) ) then begin
        sellshort (absvalue(TXF1_Value_CurrentPosition) - absvalue(Option_Value_CurrentPosition)) contract next bar IntPortion(close - Define_Order_Limit_OffsetPoint) limit ;
    end ;
    if( absvalue(TXF1_Value_CurrentPosition) < absvalue(Option_Value_CurrentPosition )) then begin
        buytocover (absvalue(Option_Value_CurrentPosition) - absvalue(TXF1_Value_CurrentPosition)) contract next bar IntPortion(close - Define_Order_Limit_OffsetPoint) stop ;
    end ;
end ;

// Exit
if( TXF1_Value_CurrentPosition = 0 ) then begin
    buytocover next bar IntPortion(close - Define_Order_Limit_OffsetPoint) stop ;
end ;
//-------------------------------------------------------------------------------------------------------------------
// Real Time Infomation Collection
if( LastBarOnChart and (Option_Value_CurrentPosition <> 0) ) then begin
    _outputfile( "G:\_External_Txt\RayWinSmart\LongTrade_OP\Option_RealTime_Info.txt" ,
        "Option CurrentPosition" + " = " + numtostr(Option_Value_CurrentPosition, 0) + NewLine +
        "Option AvgEntryPrice" + " = " + numtostr(AvgEntryPrice, 0) + NewLine +
        "Option OpenPositionProfit" + " = " + numtostr(OpenPositionProfit / bigpointvalue, 0) + NewLine
    );
end ;

// Define_PrintDebug
if( LastBarOnChart and Define_PrintDebug = 1) then begin
    _writelog("G:\_External_Txt\RayWinSmart\LongTrade_OP\DEBUG\DEBUG_Option_RealTime_Info",
        numtostr(Date,0) + "_" + numtostr(Time,0) + "_" + numtostr(TXF1_Value_CurrentPosition,0)
    );
end ;
