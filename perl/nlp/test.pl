#!/bin/perl
use Encode;
binmode(STDIN,':encoding(utf8)');
print "傻逼 perl 语言\n";
print "hell ow world\n";
print "begin game...\n";
sub pro{
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
}
$u = "傻逼";
#$u = decode('utf8',$u);
print  encode("gbk",decode('utf8',$u)); 
# print "@$hash{"1"}";
#$pa = $hash{"1"};
#print $$pa[0];
