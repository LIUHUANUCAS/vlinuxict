#!/bin/perl
# package main;
# use strict;
# use warnings;
use Encode;
use Foo;  # import default list of items.
# use NLP;
require "NLP.pl";
my $filename = "list2";
my %hash = ();
&CreateHash($filename,\%hash);
# &printhash(\%hash);
$ph = $hash{"first"};
foreach (keys %$ph){
    print "key :$_ ->";
    $pa = $ph->{$_};
    foreach my $e (@$pa){
      # print Encode::encode("gbk",$e);
      print "$e ";
    }
    print "\n";
}

$len = keys %hash;
my $M = MachineFirst(\%hash);
print "$len\n";
print "$M\n";

print "Machine:$M\n";
print "your turn:\n";
# $U=<stdin>;
# $U = decode('gbk',$U);
print "$U---->\n";
# chomp($U);
# print IsLinked(\%hash,$M,$U);
@array = (1,2,3,4,5);
$selectresult = PrintAllLinkable(\%hash,$M);
$count = 0;
foreach (@$selectresult){
  print "$count :$_ ";
  $count ++;
}
print "\n";
$ID=<stdin>;
chomp($ID);
$End = time();
print "select -> ",$$selectresults[$ID];
print "You select:$$selectresult[$ID]\n";
#PrintAllLinkable(\%hash,$M);
print "\n";
# $End = time();
# print "u->$U\n";
# IsLinked(\%hash,$M,$U);
# while(1){

# 	if(IsLinked(\%I2I,$M,$U)){
# 		print "OK\n";
# 		$Score++;
# 	}else{

# 		print "Select One to Cont.";
# 		$ID=<stdin>;
# 		chomp($ID);
# 		$End = time();
# 		$U=PrintSelectedIdiom(\%I2I,$M,$ID);
# 		print "You select:$U\n";
# 		$Score--;
# 	}
# 	if(($End - $Start )/60 > 5){
# 		print "Your Score:$Score";
# 		# last;
# 	}
# 	$M = MachineIdiom(\%I2I,$U);
# # }
