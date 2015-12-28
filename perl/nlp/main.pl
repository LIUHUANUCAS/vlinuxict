#!/bin/perl
use Encode;
use utf8;
binmode(STDIN,':encoding(utf8)');
binmode(STDOUT,':encoding(utf8)');
binmode(STDERR,':encoding(utf8)');
require "NLP.pl";

sub mainloop{

      my $filename = "list2";
      my %hash = ();
      &CreateHash($filename,\%hash);
      $ph = $hash{"wordindex"};
      $len = keys %hash;
      $Start = time();
      my $M = MachineFirst(\%hash);
      my $Score = 0;
      while(1){
          print "Machine: $M\n";
          print "your turn:";
          print "\n";
          $U=<stdin>;
          chomp($U);
          if( IsLinked(\%hash,$M,$U)){
          	print "OK!\n";
            $M = $U;
            $Score++;
          }else{
            $selectresult = PrintAllLinkable(\%hash,$M);
            $length = $#$selectresult;
            if($length <=0){
              print "机器在词典中没有找到可以接龙的成语....\n";
              print "得分:$Score\n";
              last;
            }
            print "Select One to Cout.\n";
            $count = 0;
            foreach my $e(@$selectresult){
              print "$count:$e";
              $count ++;
            }
            print "\n";
            print "please input the index :";
            $ID=<stdin>;
            chomp($ID);
            $End = time();
            print "You select:$$selectresult[$ID]\n";
            $M = "$$selectresult[$ID]";
            $Score--;
            $End = time();
        }
        	if(($End - $Start )/60 > 2){
        		print "得分:$Score\n";
        		last;
        	}
        $M = MachineIdiom(\%hash,$M);
        if(!$M){
          print "机器在词典中没有找到可以接龙的成语...!!\n";
          print "得分:$Score\n";
          last;
        }
    }
}
&mainloop;
