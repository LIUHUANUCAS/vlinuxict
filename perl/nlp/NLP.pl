#!/bin/perl
use Encode;
#use utf8;
#binmode(STDIN,':encoding(utf8)');
#binmode(STDOUT,':encoding(utf8)');
#binmode(STDERR,':encoding(utf8)');
our @ISA = qw ( Exporter);
# these CAN be exported.
our @EXPORT_OK=qw(printhash CreateHash);
# these are exported by default.
our @EXPORT = qw(printhash CreateHash);
# print hash table into the screen
sub printhash{
	my $phash = $_[0];
	foreach my $e (keys %$phash){
		print "$e:$phash->{$e}\n";
	}
	print "\n";
}

#create hash table according to the list file
#the returned value is a hash table that
##1.table = hash{"wordindex"} is also a hash table that stored the Idiom with the pinyin ,the first one and last one.
##for example, table{"天长日久"}=(tian1,jiu3);

##2.first = hash{"first"} is also a hash table, which stored Idioms that have the same  pinyin of the first words,
##for example, first{"yi"} =(  依然故我 依然如故 依山傍水 依依不舍 衣钵相传 衣不蔽体 衣冠楚楚 衣冠禽兽 衣锦还乡 衣食住行 ), so we can retrieve quickly
## according to the Idiom,such as ,量体裁衣.

##3.last = hash{"last"} is a hash table as well,which stored Idioms that have the same  pinyin of the last words.but this is not used at all.
sub CreateHash{
#("list.txt",\%I2I);
  my($filename,$hash) = ($_[0],$_[1]);
  # print $filename;
  # my $filedes;
  if( !open(fd,"<$filename")){
    die "open file failed...\n";
  }
	my %word2firstlast = ();

	my %last = ();#end with one words in pinyin
	my %first = ();#start with one words in pinyin
  my @array = <fd>;
  chomp(@array);
  foreach my $e(@array){
    my @words = split(' ',$e);
		my @firstlast = split('_',$words[1]);
		my $CODING = 'gbk';
		my $fl0 = decode($CODING,$firstlast[0]);
		my $fl3 = decode($CODING,$firstlast[-1]);
		my $words0 = decode($CODING,$words[0]);
		my $ee = decode($CODING,$e);

		my @tarray = ($fl0,$fl3);
		$word2firstlast{$words0} = \@tarray;

		# print "$fl3";
		if(defined $last{$fl3}){
				my $pa = $last{$fl3};
				push @$pa,$words0;
		}else{
			my @tmpa = ($words0);
			$last{$fl3}=\@tmpa;
		}

		if(defined $first{"$fl0"}){
				my $pa2 = $first{"$fl0"};
				push @$pa2,$words0;
		}else{
			my @tmpa2 = ($words0);
			$first{"$fl0"}=\@tmpa2;
		}

  }
		$hash->{"wordindex"} = \%word2firstlast;
		$hash->{"first"} = \%first;
		$hash->{"second"} = \%last;
  close(fd);
}

##the programe will randomly select one word from the  directory--the list file.
sub MachineFirst{
	my $phash = $_[0];
	my $len = keys %$phash;
	# print "$len in MachineFirst\n";
	my $stop = int(rand($len));
	# print "$stop is \n";
	my $M = "k";
	$refhash = $phash->{"wordindex"};
	while ( my($k,$v) = each(%$refhash) ){
				if ($stop <=0){
						$M = "$k";
						last;
				}else{
					$stop--;
				}
	}
	$M;
}

#judge the relation about 2 Idioms ,the is if the  last pinyin of Idiom is the same as the other Idiom,then return 1
#return 0 otherwise.
sub IsLinked{# (\%I2I,$M,$U)
		my $phash = $_[0];
		my $M = $_[1];
		my $U = $_[2];
		my $wordindex = $phash->{"wordindex"};
		if(! defined $wordindex->{"$U"}){
			return 0;
		}
		my $mlast = ${$wordindex->{"$M"}}[1];
		my $ufirst = ${$wordindex->{"$U"}}[0];
		#print "$mlast-> $ufirst\n";
		if( "$mlast" != "$ufirst"){
				return 0;
		}else {
			return 1;
		}
}

##print all the Idiom that have the same pinyin with the Selected Idioms,which will be used the hash table that created by CreateHash function.
##for example, Selected Idioms is 藏头露尾,the function will print 0:委靡不振 1:委曲求全
sub PrintAllLinkable{# (\%hash,$M);
		my $phash = $_[0];
		my $M = $_[1];
		my $wordindex = $phash->{"wordindex"};
		my $first = $phash->{"first"};
		my $lastyin = $wordindex->{"$M"};#last pingyin in word $M
		my $plastarray = $first->{"$lastyin->[1]"};
		print "\n";
		$size = @$plastarray;
		return \@$plastarray;
}

##select one Idiom according to the one that has been returned by function PrintAllLinkable.
sub MachineIdiom {
	 my $phash = $_[0];
	 my $U = $_[1];

	 $likedIdiomArray = PrintAllLinkable(\%$phash,$U);
	 my $wordindex = $phash->{"wordindex"};
	 my $first = $phash->{"first"};
	 my $lastyin = $wordindex->{"$U"};
	 my $likedIdiomArray = $first ->{"$lastyin->[1]"};
	 $count = $#$likedIdiomArray;
	 if($count <=0){
		 return "";
	 }
	 $stop = int(rand($count));
	 $returnvalue = "";
	 foreach my $e(@$likedIdiomArray){
			$stop--;
		 	if($stop <=0){
				$returnvalue = $e;
			}
			$count++;
	 }
	 return $returnvalue;
}






1;
