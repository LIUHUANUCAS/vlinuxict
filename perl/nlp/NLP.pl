#!/bin/perl
# package NLP;
# use strict;
# use warnings;
use Encode;
use utf8;
our @ISA = qw ( Exporter);
# these CAN be exported.
our @EXPORT_OK=qw(printhash CreateHash);
# these are exported by default.
our @EXPORT = qw(printhash CreateHash);
sub printhash{
	my $phash = $_[0];
	foreach my $e (keys %$phash){
		print "$e:$phash->{$e}\n";
	}
	print "\n";
}

sub CreateHash{
#("list.txt",\%I2I);
  my($filename,$hash) = ($_[0],$_[1]);
  print $filename;
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
		# $firstlast[0] .="_";
		# $firstlast[0] .="$firstlast[3]";
    # $hash->{"$words[0]"} = $firstlast[0];
		#create index about word to pinyin
		my $fl0 = decode('gbk',$firstlast[0]);
		my $fl3 = decode('gbk',$firstlast[3]);
		my $words0 = decode('gbk',$words[0]);
		my $ee = decode('gbk',$e);

		my @tarray = ($fl0,$fl3);
		$word2firstlast{$ee} = \@tarray;

		print "$fl3";
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

sub MachineFirst{
	my $phash = $_[0];
	my $len = keys %$phash;
	print "$len in MachineFirst\n";
	my $stop = int(rand($len));
	print "$stop is \n";
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

sub IsLinked{# (\%I2I,$M,$U)
		my $phash = $_[0];
		my $M = $_[1];
		my $U = $_[2];
		my $wordindex = $phash->{"wordindex"};
		my $out = Encode::encode("gbk",$U);
		print "out= $out\n";
		print "u= $U\n";
		print "u->",$wordindex->{"$U"},"\n";
		print "out->",$wordindex->{"$out"},"\n";
		if(! defined $wordindex->{"$U"}){
			return 0;
		}
		my $mlast = ${$wordindex->{"$M"}  }->[1];
		my $ufirst = ${$wordindex->{"$U"}  }->[1];
		if( "$mlast" == "$ufirst"){
				return 1;
		}else {
			return 0;
		}
}

sub PrintAllLinkable{# (\%hash,$M);
		my $phash = $_[0];
		my $M = $_[1];
		my $wordindex = $phash->{"wordindex"};
		my $first = $phash->{"first"};
		my $lastyin = $wordindex->{"$M"};#last pingyin in word $M
		print "$lastyin->[0] : $lastyin->[1] \n";
		print "$first \n";
		my $plastarray = $first->{"$lastyin->[1]"};
		print "$plastarray \n";
		foreach (@$plastarray){
				print "$_ "
		}
		print "\n";
		return \@$plastarray;
}







1;
