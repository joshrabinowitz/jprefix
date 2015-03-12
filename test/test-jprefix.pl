#!/usr/bin/perl -w
use strict;

# test system, as per https://www.gnu.org/software/automake/manual/html_node/Scripts_002dbased-Testsuites.html#Scripts_002dbased-Testsuites

# tests to compare output of jprefix with expected output
my @tests = (
       # "TEST COMMAND",                          CMP,     "EXPECTED OUTPUT"
    [ "echo x | ./jprefix --text y",              "eq",    "y x" ],
    [ "echo x | ./jprefix --text=y",              "eq",    "y x" ],
    [ "echo x | ./jprefix --text=y --suffix",     "eq",    "x y" ],
    [ "echo x | ./jprefix --text ''",             "eq",    "x" ],    # edge case
    [ "echo x | ./jprefix --text ' '",            "eq",    "  x" ],  # edge case
    [ "echo x | ./jprefix --text y --hostname",   "=~",    '^y \S+ x$' ],
    [ "echo x | ./jprefix --text y --timestamp",  "=~",    '^y \S+ \S+ x$' ],
    [ "echo x | ./jprefix --text y --utimestamp", "=~",    '^y \S+ \S+ x$' ],

    [ "echo A | ./jprefix -s -t B -u",            '=~',    '^A B \S+ \S+$' ],
    [ "echo A | ./jprefix --suffix --text B --utime",'=~', '^A B \S+ \S+$' ],

    [ "echo B | ./jprefix --quotes",              "eq",    '"B"' ],
    [ "echo B | ./jprefix --quotes --text A",     "eq",    'A "B"' ],
    [ "echo B | ./jprefix --quotes --text A --suffix", "eq",    '"B" A' ],

    [ "./jprefix README.md | head -1",            'eq',    '# jprefix' ],
    [ "./jprefix --text y README.md | head -1",   'eq',    'y # jprefix' ],

    [ "echo 'a' | ./jprefix -v | tail -1",        '=~',    ' 2 bytes' ],

    [ "./jprefix --nonopt 2> /dev/null",         'FAIL',  '-'],
);

print "1.." . scalar(@tests) . "\n";    # TAP header

my @results = ();
my $test_num = 0;
for my $test (@tests) {
    $test_num++;
    my $ok;
    my ($cmd, $cmp, $expected) = @$test;
    chomp( my $out = `$cmd` );
    my $desc = shorten_string( $cmd, 30 );
    if ($cmp eq "FAIL") {
        $ok = ($? || $!) ? 1 : 0;
        printf( "%s: test$test_num (exit code expected, got exit code '$?') # %s\n", $ok ? "PASS" : "FAIL", $desc );
    } else {
        eval "\$ok = \$out $cmp \$expected";
        printf( "%s: test$test_num ('$out' $cmp '$expected') # '%s' \n", $ok ? "PASS" : "FAIL", $desc );
    }
    push(@results, $ok);
}
my @fails = grep { !$_ } @results;

exit( scalar(@fails) ? 1 : 0 );

sub shorten_string {
    my ($str, $max) = @_;
    $max ||= 30;
    if (length($str) > $max) {
        $str = substr( $str, 0, $max-3 ) . "...";
    }
    return $str;
}
