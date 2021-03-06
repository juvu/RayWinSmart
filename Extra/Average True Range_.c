inputs:
	ATRLength( 10 ),
	AlertLength( 14 ),
	ATRScale( 1.2 ) ;

variables:
	var0( 0 ) ;

var0 = AvgTrueRange( ATRLength ) ;

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
//

plot1( Average((H[1] + L[1] + C[1])/3 , ATRLength) + var0[1] * ATRScale ,"" , WEBColor("CadetBlue") );
plot2( Average((H[1] + L[1] + C[1])/3 , ATRLength) - var0[1] * ATRScale , "" , WEBColor("CadetBlue") );
