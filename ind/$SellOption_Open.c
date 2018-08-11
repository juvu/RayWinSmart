// Indicator :
// ------------------------------------------------------------------------------------------------
input:
    Class("")
    ;
var :
    InfoMap(MapSN.New)

    , Value_CurrentPosition(0)
    , WriteOK(True)
    , ADE_UseFile(ADE.UseFile)
    ;

// ------------------------------------------------------------------------------------------------
if( currentbar = 1 ) and ( ADE_UseFile ) then begin
    Value1 = ADE.OpenMap(Class, GetSymbolName, ADE.BarInterval);
end ;
// ------------------------------------------------------------------------------------------------
Value_CurrentPosition = i_CurrentContracts * i_MarketPosition ;

Value1 = MapSN.Put(InfoMap, "TXF1_Value_CurrentPosition", Value_CurrentPosition);
Value1 = ADE.PutBarInfo(Class, GetSymbolName, ADE.BarInterval, ADE.BarID, InfoMap);
// ------------------------------------------------------------------------------------------------
if( LastBarOnChart ) and ( ADE_UseFile ) then begin
    Value1 = ADE.SaveMap(Class, GetSymbolName, ADE.BarInterval) ;
    WriteOK = False ;
end;
