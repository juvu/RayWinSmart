//inputs:
//	ATRLength( 14 ),
//	AlertLength( 14 ) ;
//
//variables:
//	var0( 0 ) ;
//
//var0 = AvgTrueRange( ATRLength ) ;
//
//Plot1( var0, "ATR" ) ; 
//
//                  
//condition1 = HighestBar( var0, AlertLength ) = 0 ;
//if condition1 then
//	Alert( "Indicator at high" ) 
//else 
//begin 
//condition1 = LowestBar( var0, AlertLength ) = 0 ;
//if condition1 then
//	Alert( "Indicator at low" ) ;
//end;
input:
    ATRLength( 14 )
    ;
var:
    Value_DayOpenBarNumber(0)
    , Value_Yesterday_Close(0)
    , Value_TrueRange(0)
    ;
array:
    TrueRange[3](0)
    ;

//ATR 平均真實波幅
//算法
//真實波幅 True Range 是取以下三著最大的一項
//1.當天 最高價 與 最低價的幅度
//2.當天 最高價 與 昨天收盤價的幅度
//3.當天 最低價 與 昨天收盤價的幅度


//1.當天 最高價 與 最低價的幅度
TrueRange[1] = absvalue(High - Low) ;
//2.當天 最高價 與 昨天收盤價的幅度
TrueRange[2] = absvalue(High - Close[1]) ;
//3.當天 最低價 與 昨天收盤價的幅度
TrueRange[3] = absvalue(Low - Close[1]) ;

Value_TrueRange = HighestArray(TrueRange , 3) ;

plot1( Value_TrueRange , "Value_TrueRange" ,
    iff( Value_TrueRange > Value_TrueRange[1], WEBColor("OrangeRed"),
    iff(Value_TrueRange < Value_TrueRange[1], WEBColor("LimeGreen"), white) )
);

plot2( Average(Value_TrueRange, ATRLength), "AvgTrueRange" , WEBColor("Yellow"));
