#!/usr/bin/perl -w
use strict;

# test system, as per https://www.gnu.org/software/automake/manual/html_node/Scripts_002dbased-Testsuites.html#Scripts_002dbased-Testsuites
#
print "PASS: test1\n";

# tests to compare output of jprefix with expected output
my @tests = (
        # "TEST COMMAND",                     , CMP , "EXPECTED OUTPUT"
    [ "echo x | ./jprefix --text y",            "eq", "y x" ],
    [ "echo x | ./jprefix --text ''",           "eq", "x" ],    # edge case
    [ "echo x | ./jprefix --text ' '",          "eq", "  x" ],  # edge case
    [ "echo x | ./jprefix --text y --hostname", "=~", 'y \S+ x' ],
    [ "echo x | ./jprefix --text y --timestamp", "=~", 'y \S+ \S+ x' ],
    [ "echo x | ./jprefix --text y --utimestamp", "=~", 'y \S+ \S+ x' ],
);

print "1.." . scalar(@tests) . "\n";    # TAP header

my @results = ();
for my $test (@tests) {
    my ($cmd, $cmp, $expected) = @$test;
    my $out = `$cmd`;
    chomp($out);
    my $ok;
    eval "\$ok = \$out $cmp \$expected";
    printf( "%s: ('$out' $cmp '$expected')\n", $ok ? "OK" : "NOT OK" );
    push(@results, $ok);
}
my @fails = grep { !$_ } @results;

exit( scalar(@fails) ? 1 : 0 );
