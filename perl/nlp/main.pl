#!/bin/perl
# package main;
# use strict;
# use warnings;
use Encode;
use Foo;  # import default list of items.
# use NLP;
require "NLP.pl";

sub mainloop{

      my $filename = "list2";
      my %hash = ();
      &CreateHash($filename,\%hash);
      # &printhash(\%hash);
      $ph = $hash{"wordindex"};
      # foreach (keys %$ph){
      #     print "key :$_ ->";
      #     $pa = $ph->{$_};
      #     foreach my $e (@$pa){
      #       # print Encode::encode("gbk",$e);
      #       print "$e ";
      #     }
      #     print "\n";
      # }

      $len = keys %hash;
      my $M = MachineFirst(\%hash);
      # $M = decode('utf8',$M);
      # $M = decode('gbk',$M);
      # print "$len\n";
      # print "$M\n";
      while(1){
      print "Machine: $M\n";
      print "your turn:\n";
      $U=<stdin>;
      chomp($U);
      chomp($U);
      if( IsLinked(\%hash,$M,$U)){
      	print "OK!\n";
	$Score++;
      }else{
      $selectresult = PrintAllLinkable(\%hash,$M);
      print "Select One to Cout.\n";
      $count = 0;
      foreach (@$selectresult){
        print "$count :$_ ";
        $count ++;
      }
      print "\n";
      $ID=<stdin>;
      chomp($ID);
      $End = time();
      print "You select:$$selectresult[$ID]\n";
      $Score--;
      }
      # MachineIdiom(\%hash,$$selectresult[$ID]);
      $M = "$$selectresult[$ID]";
      MachineIdiom(\%hash,$M);
      print "\n";
    }

}
sub readlist{
    open(fd,'list2');
    @array = <fd>;
    foreach my $e (@array){
        @words = split(' ',$e);
        print "$words[0] === $words[1]\n";
        # print "$e \n";
        # print "\n";

    }

}
&mainloop;
# &readlist;


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
