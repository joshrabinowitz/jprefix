#!/usr/bin/perl -w
use strict;

# test system, as per https://www.gnu.org/software/automake/manual/html_node/Scripts_002dbased-Testsuites.html#Scripts_002dbased-Testsuites
#
print "PASS: test1\n";

# tests to compare output of jprefix with expected output
my @tests = (
        # "test name",  "TEST COMMAND",                     , CMP , "EXPECTED OUTPUT"
    [ "echo x | ./jprefix --text y",            "eq", "y x" ],
    [ "echo x | ./jprefix --text=y",            "eq", "y x" ],
    [ "echo x | ./jprefix --text ''",           "eq", "x" ],    # edge case
    [ "echo x | ./jprefix --text ' '",          "eq", "  x" ],  # edge case
    [ "echo x | ./jprefix --text y --hostname", "=~", '^y \S+ x$' ],
    [ "echo x | ./jprefix --text y --timestamp", "=~", '^y \S+ \S+ x$' ],
    [ "echo x | ./jprefix --text y --utimestamp", "=~", '^y \S+ \S+ x$' ],

    [ "./jprefix README.md | head -1",            '=~', '^# jprefix$' ],
    [ "./jprefix --text y README.md | head -1",   '=~', '^y # jprefix$' ],
);

print "1.." . scalar(@tests) . "\n";    # TAP header

my @results = ();
my $test_num = 0;
for my $test (@tests) {
    $test_num++;
    my ($cmd, $cmp, $expected) = @$test;
    chomp( my $out = `$cmd` );
    my $ok;
    eval "\$ok = \$out $cmp \$expected";
    printf( "%s: test$test_num ('$out' $cmp '$expected')\n", $ok ? "OK" : "NOT OK" );
    push(@results, $ok);
}
my @fails = grep { !$_ } @results;

exit( scalar(@fails) ? 1 : 0 );
