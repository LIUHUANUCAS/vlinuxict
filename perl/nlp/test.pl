#!/bin/perl
use Encode;

print "begin game...\n";

@array = (1,2,3,5);

# $hash{"1"} = \@array;
%hash = ("1"=>\@array);
$pa = $hash{"1"};
@a2 = @$pa;
push @$pa ,200;
foreach (@{$hash{"1"} }){
	print "$_ ";
}
$word = "刘欢好人";
open(fd,"list");
while($line = <fd>){
	# chomp($line);
	my $out = decode("gbk",$line);
	print "$out";

}
print $word,"\n";
# print "@$hash{"1"}";
#$pa = $hash{"1"};
#print $$pa[0];
