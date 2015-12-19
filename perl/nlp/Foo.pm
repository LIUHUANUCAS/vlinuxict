#!/bin/perl
package Foo;
use strict;
use warnings;
use Exporter;

our @ISA= qw( Exporter );

# these CAN be exported.
our @EXPORT_OK = qw( export_me export_me_too );

# these are exported by default.
our @EXPORT = qw( export_me );

sub export_me {
    # stuff
    print "me 111\n"
}

sub export_me_too {
    # stuff
    print "hello me to \n";
}

1;
