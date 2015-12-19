#!/bin/perl
package hash;
use strict;
use warnings;

our @ISA = qw ( Exporter);
our @EXPORT_OK=qw(printhash);
our @EXPORT = qw(printhash);
sub printhash{

	my $phash = $_[0];
	foreach my $e (keys %$phash){
		print "$e:$phash->{$e}\n";
	}
	print "\n";
}
#sub printhash2{
#	while(my($key,$value)= each(%$_)){
#		print "$key:$value\n";
#	}
#}
sub changehash{
	my($phash)  =$_[0];
	$phash->{"chang"} = "hash";
	#print "change hash\n"
}
#%hash = ("first","1","second","2","3","third");
#foreach my $e (keys %hash){
#	print "$e->$hash{$e}\n";
#}

#@harray = %hash;
#foreach  (@harray){
#	print "$_,"
#}
#print "\n";
#%rhash = reverse %hash;
#&printhash(\%rhash);
#&printhash2(\%rhash);
#$phash = \%rhash;
#&changehash(\%rhash);

#foreach $key (keys %rhash){
#	print "$key->$rhash{$key}\n";
#}
1;
