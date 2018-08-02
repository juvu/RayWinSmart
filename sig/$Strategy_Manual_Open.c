input:
    Define_BeginBarNumber(0)
    , Define_Strategy_KNumber(0)
    , Define_BeginPosition(1)
	;

//-------------------------------------------------------------------------------------------------------------------
// Strategy Begin
if ( Define_BeginBarNumber <> 0 and currentbar = (Define_BeginBarNumber - Define_Strategy_KNumber) ) then begin
	if ( Define_BeginPosition > 0 ) then buy absvalue(Define_BeginPosition) contract next bar market ;
    if ( Define_BeginPosition < 0 ) then sellshort absvalue(Define_BeginPosition) contract next bar market ;
end ;
// Strategy End
//-------------------------------------------------------------------------------------------------------------------
