#!/usr/bin/perl -w
use strict;

# test system, as per https://www.gnu.org/software/automake/manual/html_node/Scripts_002dbased-Testsuites.html#Scripts_002dbased-Testsuites

# tests to compare output of jprefix with expected output
my @tests = (
       # "TEST COMMAND",                          CMP,     "EXPECTED OUTPUT"
    [ "echo x | src/jprefix --text y",              "eq",    "y x" ],
    [ "echo x | src/jprefix --text=y",              "eq",    "y x" ],
    [ "echo x | src/jprefix --text=y --suffix",     "eq",    "x y" ],
    [ "echo x | src/jprefix --text ''",             "eq",    "x" ],    # edge case
    [ "echo x | src/jprefix --text ' '",            "eq",    "  x" ],  # edge case
    [ "echo x | src/jprefix --text y --hostname",   "=~",    '^y \S+ x$' ],
    [ "echo x | src/jprefix --text y --timestamp",  "=~",    '^y \S+ \S+ x$' ],
    [ "echo x | src/jprefix --text y --utimestamp", "=~",    '^y \S+ \S+ x$' ],

    [ "echo A | src/jprefix -s -t B -u",            '=~',    '^A B \S+ \S+$' ],
    [ "echo A | src/jprefix --suffix --text B --utime",'=~', '^A B \S+ \S+$' ],

    [ "echo B | src/jprefix --quotes",              "eq",    '"B"' ],
    [ "echo B | src/jprefix --quotes --text A",     "eq",    'A "B"' ],
    [ "echo B | src/jprefix --quotes --text A --suffix", "eq",    '"B" A' ],

    [ "src/jprefix README.md | head -1",            'eq',    '# jprefix' ],
    [ "src/jprefix --text y README.md | head -1",   'eq',    'y # jprefix' ],

    [ "src/jprefix --nonopt",                       'FAIL', '-'],
);

print "1.." . scalar(@tests) . "\n";    # TAP header

my @results = ();
my $test_num = 0;
for my $test (@tests) {
    $test_num++;
    my $ok;
    my ($cmd, $cmp, $expected) = @$test;
    chomp( my $out = `$cmd` );
    if ($cmp eq "FAIL") {
        $ok = ($? || $!) ? 1 : 0;
        printf( "%s: test$test_num (exit code expected, got '$?' ($!))\n", $ok ? "PASS" : "FAIL" );
    } else {
        eval "\$ok = \$out $cmp \$expected";
        printf( "%s: test$test_num ('$out' $cmp '$expected')\n", $ok ? "PASS" : "FAIL" );
    }
    push(@results, $ok);
}
my @fails = grep { !$_ } @results;

exit( scalar(@fails) ? 1 : 0 );
