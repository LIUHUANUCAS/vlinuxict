#!/bin/perl
sub hello {
	print "hello \n";
}
&hello;

sub max{
	my($a,$b) = @_;
	
	if($a > $b){
		$a;
	}else{
		$b;
	}
}
sub max2{
	if($_[0] >$_[1]){
		$_[0];
	}else{
		$_[1];
	}
}
print &max2(1,2);
sub readfile {
	while(<>){
		chomp;
		print "$_\n";
	}
}
sub printhash{
#	foreach $e(keys $%_){
#		print "$e:%$_{$e}\n";
#	}
}
sub creathash{
	$_{"liu"} = "huan";
}
%hash = ("ict","mcg");
&printhash( %hash);
&creathash (%hash);
&printhash (%hash);

&readfile;
