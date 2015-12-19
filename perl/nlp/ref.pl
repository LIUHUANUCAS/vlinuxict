#!/bin/perl
$str = "data";
$pstr=\$str;
$$pstr .= " world";
print "$str\n";
print "$$pstr\n";
@array = (1,2,3,4);
$pa = \@array;
foreach $e(@$pa){
	print "$e ";
}
print "\n";
@array2 = @$pa;
foreach (@array2){
	print "$_ "
}
print "\n";
print "$pa->[1]\n";
print "$$pa[1]\n";

%hash = ("a",1,"b"=>2,"c"=>3);
$ph = \%hash;
foreach (keys %$ph){
	print "$_:$ph->{$_}\n";
}

