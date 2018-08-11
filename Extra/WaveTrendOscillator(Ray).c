//{ // Reference : "https://tw.tradingview.com/script/2KE8wTuF-Indicator-WaveTrend-Oscillator-WT/"
////
//// @author LazyBear
////
//// If you use this code in its original/modified form, do drop me a note. 
////
//study(title="WaveTrend [LazyBear]", shorttitle="WT_LB")
//n1 = input(10, "Channel Length")
//n2 = input(21, "Average Length")
//obLevel1 = input(60, "Over Bought Level 1")
//obLevel2 = input(53, "Over Bought Level 2")
//osLevel1 = input(-60, "Over Sold Level 1")
//osLevel2 = input(-53, "Over Sold Level 2")
// 
//ap = hlc3 
//esa = ema(ap, n1)
//d = ema(abs(ap - esa), n1)
//ci = (ap - esa) / (0.015 * d)
//tci = ema(ci, n2)
// 
//wt1 = tci
//wt2 = sma(wt1,4)
//
//plot(0, color=gray)
//plot(obLevel1, color=red)
//plot(osLevel1, color=green)
//plot(obLevel2, color=red, style=3)
//plot(osLevel2, color=green, style=3)
//
//plot(wt1, color=green)
//plot(wt2, color=red, style=3)
//plot(wt1-wt2, color=blue, style=area, transp=80)
//}
input: 
	Define_Arw_Size(10)
	, EmaFastLength(10), EmaSlowLength(21)
       , StrongShow(1), WeakShow(1)
       , ObOsLength(43);

var:
	value_ap(0), value_esa(0), value_d(0), value_ci(0), value_tci(0), wt1(0), wt2(0)
	, obLevel1(60), obLevel2(53), osLevel1(-60), osLevel2(-53)
    , Arw_Direction_Down(True) , Arw_Direction_Up(False)
    ;


obLevel1 = (ObOsLength + 7) ;
obLevel2 = ObOsLength ;
osLevel1 = (-1) * (ObOsLength + 7) ;
osLevel2 = (-1) * ObOsLength ;

value_ap = (high + low + close)/3 ;
//value_ap = (high + low + 2*close)/4 ;
value_esa = XAverage(value_ap, EmaFastLength) ;
value_d = XAverage(absvalue(value_ap - value_esa), EmaFastLength) ;
if value_d = 0 then value_d = 0.001 ;
value_ci = (value_ap - value_esa) / (0.015 * value_d) ;
value_tci = XAverage(value_ci, EmaSlowLength) ;
 
wt1 = value_tci ;
wt2 = SmoothedAverage(wt1,4) ;
//{
//plot1(0, "", white);
//plot2(obLevel1, "", red);
//plot3(osLevel1, "", green);
//plot4(obLevel2, "", red); // cross
//plot5(osLevel2, "", green); // cross
//plot6(wt1, "", green);
//plot7(wt2, "", red); // cross
//plot8(wt1-wt2, "", blue); // histogram
//}
// end 2018/04/25-18:00

if (StrongShow = 1) and ( wt1 cross above wt2 ) and (Lowest(wt2,5) <= osLevel2) then begin
    Value1 = Arw_New_bn (currentbar + 1, Close, Arw_Direction_Up);
    Arw_SetColor(Value1, WEBColor("Tomato"));
    Arw_SetSize(Value1, Define_Arw_Size);
end ;
if (WeakShow = 1) and ( wt1 cross under wt2 ) and (Highest(wt2,5) >= obLevel2) then begin
    Value2 = Arw_New_bn (currentbar + 1, Close, Arw_Direction_Down);
    Arw_SetColor(Value2, WEBColor("Lime"));
    Arw_SetSize(Value2, Define_Arw_Size);
end ;
