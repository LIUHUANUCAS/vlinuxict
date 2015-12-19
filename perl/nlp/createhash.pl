#!/bin/perl
use Encode;
sub printhash{
	my $phash = $_[0];
	foreach $e(keys %$phash){
		#print "$e:$phash->{$e} ";
		print "$e:";
		@words = split('_',$phash->{$e});
		foreach (@words){
			print "$_ "
		}
		print "\n";
	}
}
sub readFileHash{
	my $filename = $_[0];
	my $hash = $_[1];
	if(! open(fd,"<$filename")){
		die "can not open $filename";
	}
	@all = <fd>;
	chomp(@all);
	foreach $e(@all){
		@words = split / /, $e;
		#print "$words[0]:$words[1]\n";
		$hash->{"$words[0]"} = "$words[1]"; 
#		print "$e";
	}
	close(fd);
	#&printhash(\%$hash);
}

$filename = "list";
%hash = ("liu"=>"huan");
&readFileHash ($filename,\%hash);
#foreach $e(keys %hash){
#	print "$e->$hash{$e}\n";
#}
&printhash(\%hash);
#print "$hash->{"liu"} \n";
#while($line = <fd>){
#	chomp($line);
#	print "$line\n";
#}
#close(fd);
#print "$line";
printf "%s---->>>>>\n",$line;
$str = "hello world is good perfermance yes it is";
@words = split / /,$str;
foreach (@words){
	print "$_\n";
}
