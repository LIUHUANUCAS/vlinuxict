#!/bin/perl

use Encode;
use Encode qw(encode);
use utf8;
#binmode(STDIN,':encoding(gbk)');
#binmode(STDOUT,':encoding(gbk)');
#binmode(STDERR,':encoding(utf8)');
require "NLP.pl";
sub encodeGBK{
	return encode("gbk",$_[0]);
}
sub tips{
	my $hash = $_[0];
	my $M = $_[1];
	$selectresult = PrintAllLinkable(\%$hash,$M);
	$length = $#$selectresult;
	print "tips \n";
	$count = 0;
	foreach my $e(@$selectresult){
	print "$count:",encodeGBK($e);
	  #print "$count:",Encode::encode('utf8',$e);
	  $count ++;
	}
	print "\n";
}
sub mainloop{
	  #print "汉语我这吗我这里\n";
      my $filename = "list2";
      my %hash = ();
      &CreateHash($filename,\%hash);
      $ph = $hash{"wordindex"};
      $len = keys %hash;
      $Start = time();
      my $M = MachineFirst(\%hash);
      my $Score = 0;
      while(1){
		  #$M = encode("utf8",decode('utf8',$M)); 
		  #$M = encode("gbk",$M);
		  #$M = encodeGBK($M);
		  print "Machine: ",encodeGBK($M),"\n";
		  #&tips(\%hash,$M);
		  print "your turn:";
          print "\n";
          $U=<stdin>;
          chomp($U);
		  #$U = encode('utf8',$U);
		  
		  #print encode('gbk',$U);
          $U = decode('gbk',$U);
		  if( IsLinked(\%hash,$M,$U)){
          	print "OK!\n";
            $M = $U;
            $Score++;
          }else{
            $selectresult = PrintAllLinkable(\%hash,$M);
            $length = $#$selectresult;
            if($length <=0){
              print encodeGBK("机器在词典中没有找到可以接龙的成语....\n");
              print encodeGBK("得分:$Score\n");
              last;
            }
            print "Select One to Cout.\n";
            $count = 0;
            foreach my $e(@$selectresult){
			print "$count:",encodeGBK($e);
              #print "$count:",Encode::encode('utf8',$e);
              $count ++;
            }
            print "\n";
            print "please input the index :";
            $ID=<stdin>;
            chomp($ID);
            $End = time();
            print "You select:",encodeGBK($$selectresult[$ID]),"\n";
            $M = "$$selectresult[$ID]";
            $Score--;
            
        }
			$End = time();
        	if(($End - $Start )/60 > 2){
        		print encodeGBK("得分:$Score\n");
        		last;
        	}
        $M = MachineIdiom(\%hash,$M);
        if(!$M){
          print encodeGBK("机器在词典中没有找到可以接龙的成语...!!\n");
          print encodeGBK("得分:$Score\n");
          last;
        }
    }
}
&mainloop;
