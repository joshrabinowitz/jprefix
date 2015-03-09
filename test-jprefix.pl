#!/usr/bin/perl -w
use strict;

# test system, as per https://www.gnu.org/software/automake/manual/html_node/Scripts_002dbased-Testsuites.html#Scripts_002dbased-Testsuites
#
print "PASS: test1\n";

my @tests = (
    [ "echo x | ./jprefix --text y", "y x" ],
    [ "echo x | ./jprefix --text y --hostname", "y ln3.joshr.com x" ],
);

print "1.." . scalar(@tests) . "\n";    # TAP header

my @results = ();
for my $test (@tests) {
    my ($cmd, $expected) = @$test;
    my $out = `$cmd`;
    chomp($out);
    my $ok = $out eq $expected;
    printf( "%s: got '$out', expected '$expected'\n", $ok ? "OK" : "NOT OK" );
    push(@results, $ok);
}
my @fails = grep { $_ != 0 } @results;

exit( @fails ? 1 : 0 );
